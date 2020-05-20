#include "component_geometry.h"
#include <GL/glew.h>
#include "internal_suffermanager.h"
#include "internal_resource_manager.h"
#include "common_definitions.h"
#include "tiny_obj_loader.h"
#include "component_material.h"
#include "math_utils.h"

// --------------------------------------------------- //

float Interpolate(float x, float y, float a) {

    float negA = 1.0 - a;
    float negASqr = negA * negA;
    float fac1 = 3.0 * (negASqr)-2.0 * (negASqr * negA);
    float aSqr = a * a;
    float fac2 = 3.0 * aSqr - 2.0 * (aSqr * a);

    return x * fac1 + y * fac2; //add the weighted factors

}

// --------------------------------------------------- //

float Noise(int x, int z) {

    int n = x + z * 57;
    n = (n << 13) ^ n;
    int t = (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff;
    return 1.0 - float(t) * 0.931322574615478515625e-9;

}

// --------------------------------------------------- //

float GetPerlinElevation(float x, float z) {

    int Xint = (int)x;
    int Yint = (int)z;

    mathmorra::Vector2 frac;
    frac.x_ = x - Xint;
    frac.y_ = z - Yint;

    //noise values
    float n01 = Noise(Xint - 1, Yint - 1);
    float n02 = Noise(Xint + 1, Yint - 1);
    float n03 = Noise(Xint - 1, Yint + 1);
    float n04 = Noise(Xint + 1, Yint + 1);
    float n05 = Noise(Xint - 1, Yint);
    float n06 = Noise(Xint + 1, Yint);
    float n07 = Noise(Xint, Yint - 1);
    float n08 = Noise(Xint, Yint + 1);
    float n09 = Noise(Xint, Yint);

    float n12 = Noise(Xint + 2, Yint - 1);
    float n14 = Noise(Xint + 2, Yint + 1);
    float n16 = Noise(Xint + 2, Yint);

    float n23 = Noise(Xint - 1, Yint + 2);
    float n24 = Noise(Xint + 1, Yint + 2);
    float n28 = Noise(Xint, Yint + 2);

    float n34 = Noise(Xint + 2, Yint + 2);

    //find the noise values of the four corners
    float x0y0 = 0.0625 * (n01 + n02 + n03 + n04) + 0.125 * (n05 + n06 + n07 + n08) + 0.25 * (n09);
    float x1y0 = 0.0625 * (n07 + n12 + n08 + n14) + 0.125 * (n09 + n16 + n02 + n04) + 0.25 * (n06);
    float x0y1 = 0.0625 * (n05 + n06 + n23 + n24) + 0.125 * (n03 + n04 + n09 + n28) + 0.25 * (n08);
    float x1y1 = 0.0625 * (n09 + n16 + n28 + n34) + 0.125 * (n08 + n14 + n06 + n24) + 0.25 * (n04);

    //interpolate between those values according to the x and y fractions
    float v1 = Interpolate(x0y0, x1y0, frac.x_); //interpolate in x direction (y)
    float v2 = Interpolate(x0y1, x1y1, frac.x_); //interpolate in x direction (y+1)
    float fin = Interpolate(v1, v2, frac.y_);  //interpolate in y direction

    return fin;

}

// --------------------------------------------------- //

Suffer::GeometryComponent::GeometryComponent() : Component(Component::kComponentKind_Geometry) {

    mode_ = kDrawMode_Triangles;
    shape_ = kBasicShapes_Invalid;
    number_shapes_ = 0;

}

// --------------------------------------------------- //

void Suffer::GeometryComponent::CreateGeometryWithOBJ(const char* obj_file) {

  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;
  std::vector<mathmorra::Vector3> v_positions;
  std::vector<mathmorra::Vector3> v_normals;
  std::vector<mathmorra::Vector2> v_tcoordinates;

  std::string warn;
  std::string err;

  bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, obj_file);

  if (!warn.empty()) {
    printf("\n %s", warn.c_str());
  }

  if (!err.empty()) {
    printf("\n %s", err.c_str());
  }

  if (!ret) {
    exit(1);
  }


  // Loop over shapes
  for (size_t s = 0; s < shapes.size(); ++s) {
    // Loop over faces(polygon)
    s32 index_offset = 0;
    for (s32 f = 0; f < shapes[s].mesh.num_face_vertices.size(); ++f) {
      int fv = shapes[s].mesh.num_face_vertices[f];

      // Loop over vertices in the face.
      for (s32 v = 0; v < fv; ++v) {
        // access to vertex
        tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
        tinyobj::real_t vx = attrib.vertices[3 * idx.vertex_index + 0];
        tinyobj::real_t vy = attrib.vertices[3 * idx.vertex_index + 1];
        tinyobj::real_t vz = attrib.vertices[3 * idx.vertex_index + 2];
        v_positions.push_back(mathmorra::Vector3(vx, vy, vz));
        tinyobj::real_t nx = attrib.normals[3 * idx.normal_index + 0];
        tinyobj::real_t ny = attrib.normals[3 * idx.normal_index + 1];
        tinyobj::real_t nz = attrib.normals[3 * idx.normal_index + 2];
        v_normals.push_back(mathmorra::Vector3(nx, ny, nz));
        tinyobj::real_t tx = attrib.texcoords[2 * idx.texcoord_index + 0];
        tinyobj::real_t ty = (1.0f - attrib.texcoords[2 * idx.texcoord_index + 1]);
        v_tcoordinates.push_back(mathmorra::Vector2(tx, ty));
        // Optional: vertex colors
        // tinyobj::real_t red = attrib.colors[3*idx.vertex_index+0];
        // tinyobj::real_t green = attrib.colors[3*idx.vertex_index+1];
        // tinyobj::real_t blue = attrib.colors[3*idx.vertex_index+2];
      }
      index_offset += fv;

      // per-face material
      shapes[s].mesh.material_ids[f];
    }



    ref_ptr<ResourceManager::VertexBuffer> new_vertex_buffer;
    new_vertex_buffer.alloc();
    new_vertex_buffer->SetVertexFormat(ResourceManager::VertexBuffer::kVertexFormat_3P);
    Array<ResourceManager::VertexBuffer::Vertex> vertexes;
    vertexes.alloc(v_positions.size());
    for (u32 i = 0; i < vertexes.size(); ++i) {
      vertexes[i] = ResourceManager::VertexBuffer::Vertex(v_positions[i] * 0.1f, v_normals[i], v_tcoordinates[i]);
    }
    new_vertex_buffer->UploadVertexData(vertexes.get(), vertexes.size());

    ref_ptr<ResourceManager::IndexBuffer> new_index_buffer;
    new_index_buffer.alloc();
    Array<ResourceManager::IndexBuffer::Triangle> triangles;
    triangles.alloc(vertexes.size() / 3);
    for (u32 i = 0; i < triangles.size(); ++i) {
      triangles[i] = ResourceManager::IndexBuffer::Triangle(0 + (i * 3), 1 + (i * 3), 2 + (i * 3));
    }
    new_index_buffer->UploadIndexData(triangles.get(), triangles.size());


    AddBuffers(new_vertex_buffer, new_index_buffer);
  }

}

void Suffer::GeometryComponent::CreateGeometryWithOBJAndMTL(const char* obj_file, Suffer::MaterialComponent& mat, const char* mtl_base_route, const char* textures_base_route) {

  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;
  std::vector<mathmorra::Vector3> v_positions;
  std::vector<mathmorra::Vector3> v_normals;
  std::vector<mathmorra::Vector2> v_tcoordinates;

  std::string warn;
  std::string err;

  bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, obj_file, mtl_base_route);

  if (!warn.empty()) {
    printf("\n %s", warn.c_str());
  }

  if (!err.empty()) {
    printf("\n %s", err.c_str());
  }

  if (!ret) {
    exit(1);
  }

  // Loop over shapes
  for (size_t s = 0; s < shapes.size(); ++s) {
    // Loop over faces(polygon)
    s32 index_offset = 0;
    for (s32 f = 0; f < shapes[s].mesh.num_face_vertices.size(); ++f) {
      int fv = shapes[s].mesh.num_face_vertices[f];

      // Loop over vertices in the face.
      for (s32 v = 0; v < fv; ++v) {
        // access to vertex
        tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
        tinyobj::real_t vx = attrib.vertices[3 * idx.vertex_index + 0];
        tinyobj::real_t vy = attrib.vertices[3 * idx.vertex_index + 1];
        tinyobj::real_t vz = attrib.vertices[3 * idx.vertex_index + 2];
        v_positions.push_back(mathmorra::Vector3(vx, vy, vz));
        tinyobj::real_t nx = attrib.normals[3 * idx.normal_index + 0];
        tinyobj::real_t ny = attrib.normals[3 * idx.normal_index + 1];
        tinyobj::real_t nz = attrib.normals[3 * idx.normal_index + 2];
        v_normals.push_back(mathmorra::Vector3(nx, ny, nz));
        tinyobj::real_t tx = attrib.texcoords[2 * idx.texcoord_index + 0];
        tinyobj::real_t ty = (1.0f - attrib.texcoords[2 * idx.texcoord_index + 1]);
        v_tcoordinates.push_back(mathmorra::Vector2(tx, ty));
        // Optional: vertex colors
        // tinyobj::real_t red = attrib.colors[3*idx.vertex_index+0];
        // tinyobj::real_t green = attrib.colors[3*idx.vertex_index+1];
        // tinyobj::real_t blue = attrib.colors[3*idx.vertex_index+2];
      }
      index_offset += fv;

      // per-face material
      shapes[s].mesh.material_ids[f];
    }



    // Geometries buffers
    ref_ptr<ResourceManager::VertexBuffer> new_vertex_buffer;
    new_vertex_buffer.alloc();
    new_vertex_buffer->SetVertexFormat(ResourceManager::VertexBuffer::kVertexFormat_3P_3N_2UV_3T_3B);
    Array<ResourceManager::VertexBuffer::Vertex> vertexes;
    vertexes.alloc(v_positions.size());
    for (u32 i = 0; i < vertexes.size(); ++i) {
      vertexes[i] = ResourceManager::VertexBuffer::Vertex(v_positions[i] * 0.1f, v_normals[i], v_tcoordinates[i]);
    }
    new_vertex_buffer->UploadVertexData(vertexes.get(), vertexes.size());

    ref_ptr<ResourceManager::IndexBuffer> new_index_buffer;
    new_index_buffer.alloc();
    Array<ResourceManager::IndexBuffer::Triangle> triangles;
    triangles.alloc(vertexes.size() / 3);
    for (u32 i = 0; i < triangles.size(); ++i) {
      triangles[i] = ResourceManager::IndexBuffer::Triangle(0 + (i * 3), 1 + (i * 3), 2 + (i * 3));
    }
    new_index_buffer->UploadIndexData(triangles.get(), triangles.size());


    AddBuffers(new_vertex_buffer, new_index_buffer);



    // Materials params
    ref_ptr<MaterialComponent::BlinnPhongParams> material_params;
    material_params.alloc();
    u32 mat_id = shapes[s].mesh.material_ids[0];
    material_params->color_ = mathmorra::Vector4(materials[mat_id].diffuse[0], materials[mat_id].diffuse[1], materials[mat_id].diffuse[2], 1.0f);
    material_params->specular_strength_ = materials[mat_id].specular[0];
    if (!materials[mat_id].diffuse_texname.empty()) {

      Suffer::ref_ptr<Suffer::ResourceManager::Texture> diffuse_texture;
      diffuse_texture.alloc();
      diffuse_texture->SetTextureFilter(Suffer::ResourceManager::Texture::kTextureFilter_Linear, Suffer::ResourceManager::Texture::kTextureFilter_Linear);
      diffuse_texture->SetTextureWrap(Suffer::ResourceManager::Texture::kTextureWrap_ClampToEdge, Suffer::ResourceManager::Texture::kTextureWrap_ClampToEdge);
      std::string tex_route = std::string(textures_base_route);
      tex_route.append(materials[mat_id].diffuse_texname);
      diffuse_texture->LoadTextureData(tex_route.c_str());

      material_params->SetAlbedoTexture(diffuse_texture.get());

    }
    if (!materials[mat_id].specular_texname.empty()) {

      Suffer::ref_ptr<Suffer::ResourceManager::Texture> specular_texture;
      specular_texture.alloc();
      specular_texture->SetTextureFilter(Suffer::ResourceManager::Texture::kTextureFilter_Linear, Suffer::ResourceManager::Texture::kTextureFilter_Linear);
      specular_texture->SetTextureWrap(Suffer::ResourceManager::Texture::kTextureWrap_ClampToEdge, Suffer::ResourceManager::Texture::kTextureWrap_ClampToEdge);
      std::string tex_route = std::string(textures_base_route);
      tex_route.append(materials[mat_id].specular_texname);
      specular_texture->LoadTextureData(tex_route.c_str());

      material_params->SetSpecularTexture(specular_texture.get());

    }
    if (!materials[mat_id].reflection_texname.empty()) {

      Suffer::ref_ptr<Suffer::ResourceManager::Texture> reflection_texture;
      reflection_texture.alloc();
      reflection_texture->SetTextureFilter(Suffer::ResourceManager::Texture::kTextureFilter_Linear, Suffer::ResourceManager::Texture::kTextureFilter_Linear);
      reflection_texture->SetTextureWrap(Suffer::ResourceManager::Texture::kTextureWrap_ClampToEdge, Suffer::ResourceManager::Texture::kTextureWrap_ClampToEdge);
      std::string tex_route = std::string(textures_base_route);
      tex_route.append(materials[mat_id].reflection_texname);
      reflection_texture->LoadTextureData(tex_route.c_str());

      material_params->SetReflectionTexture(reflection_texture.get(), 1.0f);

    }


    mat.AddParams(material_params.get());

  }

}

// --------------------------------------------------- //

void Suffer::GeometryComponent::CreateTerrainGeometry(float frequency, float elevation, float terrace_value, int rows /*= 200*/, int columns /*= 200*/) {

  Array<mathmorra::Vector3> normals_;
  Array<mathmorra::Vector3> tangents_;
  Array<mathmorra::Vector3> positions_;
  Array<mathmorra::Vector2> uv_;

  positions_.alloc(rows * columns);
  normals_.alloc(rows * columns);
  tangents_.alloc(rows * columns);
  uv_.alloc(rows * columns);

  // POSITIONS and UV
  for (u32 x = 0; x < rows; ++x) {
    for (u32 z = 0; z < columns; ++z) {
      float perlin_value = GetPerlinElevation(x * frequency, z * frequency) * elevation;
      perlin_value = round(perlin_value * terrace_value) / terrace_value;

      // POSITIONS
      positions_[x * columns + z] = { (float)x, perlin_value, (float)z };

      // UV
      uv_[x * columns + z].x_ = positions_[x * columns + z].x_ / (float)rows;
      uv_[x * columns + z].y_ = positions_[x * columns + z].z_ / (float)columns;
    }
  }

  // NORMALS
  for (int x = 1; x < rows - 1; ++x) {
    for (int z = 1; z < columns - 1; ++z) {

      // Normals
      mathmorra::Vector3 up;
      mathmorra::Vector3 right;
      mathmorra::Vector3 down;
      mathmorra::Vector3 left;

      right = positions_[x * columns + z + 1] - positions_[x * columns + z];
      up = positions_[x * columns + z + columns] - positions_[x * columns + z];
      left = positions_[x * columns + z - 1] - positions_[x * columns + z];
      down = positions_[x * columns + z - columns] - positions_[x * columns + z];

      mathmorra::Vector3 right_up = mathmorra::Vector3::CrossProduct(right, up);
      mathmorra::Vector3 up_left = mathmorra::Vector3::CrossProduct(up, left);
      mathmorra::Vector3 left_down = mathmorra::Vector3::CrossProduct(left, down);
      mathmorra::Vector3 down_right = mathmorra::Vector3::CrossProduct(down, right);

      normals_[x * columns + z] = (right_up + up_left + left_down + down_right).Normalized();
      
      mathmorra::Vector3 tangent_ = normals_[x * columns + z];
      tangent_.x_ = tangent_.y_;
      tangent_.y_ = 0.0f;
      tangent_.Normalize();

      tangents_[x * columns + z] = tangent_;

    }
  }

  // VERTEX BUFFER
  ref_ptr<ResourceManager::VertexBuffer> new_vertex_buffer;
  Array<ResourceManager::VertexBuffer::Vertex> vertexes;
  new_vertex_buffer.alloc();
  new_vertex_buffer->SetVertexFormat(ResourceManager::VertexBuffer::kVertexFormat_3P_3N_2UV_3T_3B);
  vertexes.alloc(columns * rows);

  for (u32 i = 0; i < vertexes.size(); ++i) {
    vertexes[i] = ResourceManager::VertexBuffer::Vertex(positions_[i], normals_[i], uv_[i], tangents_[i], mathmorra::Vector3());
  }
  new_vertex_buffer->UploadVertexData(vertexes.get(), vertexes.size());

  ref_ptr<ResourceManager::IndexBuffer> new_index_buffer;
  new_index_buffer.alloc();

  // INDICES
  Array<u16> indices;
  indices.alloc((rows - 1) * (columns - 1) * 6);
  int index = 0;
  for (int x = 0; x < rows - 1; ++x) {
    for (int z = 0; z < columns - 1; ++z) {

      indices[index++] = (x * columns + z);
      indices[index++] = (x * columns + (z + 1));
      indices[index++] = ((x + 1) * columns + z);

      indices[index++] = x * columns + (z + 1);
      indices[index++] = (x + 1) * columns + (z + 1);
      indices[index++] = (x + 1) * columns + z;

    }
  }

  new_index_buffer->UploadIndexData(indices.get(), indices.size());

  AddBuffers(new_vertex_buffer, new_index_buffer);

}

// --------------------------------------------------- //

void Suffer::GeometryComponent::CreateGeometryWithShape(BasicShapes shape) {

  shape_ = shape;
  number_shapes_ = 1;
  vertex_buffer_id_.clear();
  vertex_buffer_id_.push_back(suffer.resource_manager_.data_->internal_vertex_buffers_[(s32)shape].id_handle_);
  index_buffer_id_.clear();
  index_buffer_id_.push_back(suffer.resource_manager_.data_->internal_index_buffers_[(s32)shape].id_handle_);

}

// --------------------------------------------------- //

Suffer::GeometryComponent::BasicShapes Suffer::GeometryComponent::GetGeometry() {

  return shape_;

}

// --------------------------------------------------- //

void Suffer::GeometryComponent::SetDrawMode(DrawMode newMode) {

  mode_ = newMode;

}

// --------------------------------------------------- //

Suffer::GeometryComponent::DrawMode Suffer::GeometryComponent::GetDrawMode() {

    return mode_;

}

// --------------------------------------------------- //

void Suffer::GeometryComponent::AddBuffers(ref_ptr<Suffer::ResourceManager::VertexBuffer> vertex_buffer, ref_ptr<Suffer::ResourceManager::IndexBuffer> index_buffer) {

  number_shapes_++;
  vertex_buffer_id_.push_back(vertex_buffer.get()->id_);
  index_buffer_id_.push_back(index_buffer.get()->id_);

}

// --------------------------------------------------- //

Suffer::GeometryComponent::~GeometryComponent() {

}

// --------------------------------------------------- //