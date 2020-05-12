#include "component_geometry.h"
#include <GL/glew.h>
#include "internal_suffermanager.h"
#include "internal_resource_manager.h"
#include "common_definitions.h"
#include "tiny_obj_loader.h"


// --------------------------------------------------- //

Suffer::GeometryComponent::GeometryComponent() : Component(Component::kComponentKind_Geometry){

  mode_ = kDrawMode_Triangles;
  shape_ = kBasicShapes_Invalid;

}

// --------------------------------------------------- //

void Suffer::GeometryComponent::SetIndexBuffer(ref_ptr<Suffer::ResourceManager::IndexBuffer> buffer) {

  index_buffer_id_ = buffer.get()->id_;

}

// --------------------------------------------------- //

void Suffer::GeometryComponent::CreateGeometryWithOBJ(const char* obj_file){

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
    printf("\n %s", warn);
  }

  if (!err.empty()) {
    printf("\n %s", err);
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
      for (s32 v = 0; v < fv ; ++v) {
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
        tinyobj::real_t ty = attrib.texcoords[2 * idx.texcoord_index + 1];
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
  }

  ref_ptr<ResourceManager::VertexBuffer> new_vertex_buffer;
  new_vertex_buffer.alloc();
  new_vertex_buffer->SetVertexFormat(ResourceManager::VertexBuffer::kVertexFormat_3P_3N_2UV);
  Array<ResourceManager::VertexBuffer::Vertex> vertexes;
  vertexes.alloc(v_positions.size());
  for (u32 i = 0; i < vertexes.size(); ++i) {
    vertexes[i] = ResourceManager::VertexBuffer::Vertex(v_positions[i], v_normals[i], v_tcoordinates[i]);
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


  SetBuffers(new_vertex_buffer, new_index_buffer);

  printf("\nDonete");

}

// --------------------------------------------------- //

void Suffer::GeometryComponent::CreateGeometryWithShape(BasicShapes shape) {

  shape_ = shape;
  vertex_buffer_id_ = suffer.resource_manager_.data_->internal_vertex_buffers_[(s32)shape].id_handle_;
  index_buffer_id_ = suffer.resource_manager_.data_->internal_index_buffers_[(s32)shape].id_handle_;

}

// --------------------------------------------------- //

Suffer::GeometryComponent::BasicShapes Suffer::GeometryComponent::GetGeometry(){
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

void Suffer::GeometryComponent::SetVertexBuffer(ref_ptr<Suffer::ResourceManager::VertexBuffer> buffer) {
  vertex_buffer_id_ = buffer.get()->id_;
}

// --------------------------------------------------- //

void Suffer::GeometryComponent::SetBuffers(ref_ptr<Suffer::ResourceManager::VertexBuffer> vertex_buffer, ref_ptr<Suffer::ResourceManager::IndexBuffer> index_buffer) {
  vertex_buffer_id_ = vertex_buffer.get()->id_;
  index_buffer_id_ = index_buffer.get()->id_;
}

// --------------------------------------------------- //

Suffer::GeometryComponent::~GeometryComponent() {

}

// --------------------------------------------------- //