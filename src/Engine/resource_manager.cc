// Author: Diego Ochando Torres <ochandoto@esat-alumni.com>

#include "resource_manager.h"
#include "internal_resource_manager.h"
#include "internal_shaders.h"
#include "common_definitions.h"
#include "suffermanager.h"
#include "math_utils.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// ------------------------------------------------------------------------- //

Suffer::ResourceManager::ResourceManager(){

  // Empty

}

// ------------------------------------------------------------------------- //

Suffer::ResourceManager::~ResourceManager(){

  // Empty

}

// ------------------------------------------------------------------------- //

void Suffer::ResourceManager::StartUp() {

  data_ = new ResourceData();

  data_->InitInternalBuffers();
  data_->InitInternalTextures();
  data_->InitInternalMaterials();
  data_->InitInternalFrameBuffers();

}

// ------------------------------------------------------------------------- //

void Suffer::ResourceManager::ShutDown() {

  //Delete textures and buffers and program and all resources
  for (u32 i = 0; i < data_->number_of_textures_; ++i) {
    glDeleteTextures(1, &data_->internal_textures_[i].current_texture_id_);
  }
  for (u32 i = 0; i < data_->number_of_vertex_buffers_; ++i) {
    glDeleteBuffers(1, &data_->internal_vertex_buffers_[i].current_gl_buffer_);
  }
  for (u32 i = 0; i < data_->number_of_index_buffers_; ++i) {
    glDeleteBuffers(1, &data_->internal_index_buffers_[i].current_gl_buffer_);
  }
  for (u32 i = 0; i < data_->number_of_materials_; ++i) {
    glDeleteProgram(data_->internal_materials_[i].current_program_);
  }
  for (u32 i = 0; i < data_->number_of_frame_buffers_; ++i) {
    glDeleteFramebuffers(1, &data_->internal_frame_buffers_[i].current_gl_framebuffer_);
  }

  if (data_ == nullptr) return;
  delete data_;
  data_ = nullptr;

}

// ------------------------------------------------------------------------- //

void Suffer::ResourceManager::VertexBuffer::UploadVertexData(VertexBuffer::Vertex* data, u32 size) {

  assert(suffer.resource_manager_.data_->internal_vertex_buffers_[id_].vertex_format_ != VertexBuffer::kVertexFormat_Invalid && "Vertex format is INVALID!");

  switch (suffer.resource_manager_.data_->internal_vertex_buffers_[id_].vertex_format_){
  case VertexBuffer::kVertexFormat_3P:
    suffer.resource_manager_.data_->internal_vertex_buffers_[id_].data_.alloc(size * 3);
    //Set contiguous memory
    for (u32 i = 0; i < size; ++i) {
      suffer.resource_manager_.data_->internal_vertex_buffers_[id_].data_[(i * 3) + 0] = data[i].vertices_.x_;
      suffer.resource_manager_.data_->internal_vertex_buffers_[id_].data_[(i * 3) + 1] = data[i].vertices_.y_;
      suffer.resource_manager_.data_->internal_vertex_buffers_[id_].data_[(i * 3) + 2] = data[i].vertices_.z_;
    }
    break;
  case VertexBuffer::kVertexFormat_3P_3N:
    suffer.resource_manager_.data_->internal_vertex_buffers_[id_].data_.alloc(size * 6);
    //Set contiguous memory
    for (u32 i = 0; i < size; ++i) {
      suffer.resource_manager_.data_->internal_vertex_buffers_[id_].data_[(i * 6) + 0] = data[i].vertices_.x_;
      suffer.resource_manager_.data_->internal_vertex_buffers_[id_].data_[(i * 6) + 1] = data[i].vertices_.y_;
      suffer.resource_manager_.data_->internal_vertex_buffers_[id_].data_[(i * 6) + 2] = data[i].vertices_.z_;
      
      suffer.resource_manager_.data_->internal_vertex_buffers_[id_].data_[(i * 6) + 3] = data[i].normals_.x_;
      suffer.resource_manager_.data_->internal_vertex_buffers_[id_].data_[(i * 6) + 4] = data[i].normals_.y_;
      suffer.resource_manager_.data_->internal_vertex_buffers_[id_].data_[(i * 6) + 5] = data[i].normals_.z_;
    }
    break;
  case VertexBuffer::kVertexFormat_3P_3N_2UV:
    suffer.resource_manager_.data_->internal_vertex_buffers_[id_].data_.alloc(size * 8);
    //Set contiguous memory
    for (u32 i = 0; i < size; ++i) {
      suffer.resource_manager_.data_->internal_vertex_buffers_[id_].data_[(i * 8) + 0] = data[i].vertices_.x_;
      suffer.resource_manager_.data_->internal_vertex_buffers_[id_].data_[(i * 8) + 1] = data[i].vertices_.y_;
      suffer.resource_manager_.data_->internal_vertex_buffers_[id_].data_[(i * 8) + 2] = data[i].vertices_.z_;

      suffer.resource_manager_.data_->internal_vertex_buffers_[id_].data_[(i * 8) + 3] = data[i].normals_.x_;
      suffer.resource_manager_.data_->internal_vertex_buffers_[id_].data_[(i * 8) + 4] = data[i].normals_.y_;
      suffer.resource_manager_.data_->internal_vertex_buffers_[id_].data_[(i * 8) + 5] = data[i].normals_.z_;

      suffer.resource_manager_.data_->internal_vertex_buffers_[id_].data_[(i * 8) + 6] = data[i].uvs_.x_;
      suffer.resource_manager_.data_->internal_vertex_buffers_[id_].data_[(i * 8) + 7] = data[i].uvs_.y_;
    }
    break;
  default:
    break;
  }

  suffer.resource_manager_.data_->internal_vertex_buffers_[id_].version_++;
  suffer.resource_manager_.data_->internal_vertex_buffers_[id_].id_handle_ = id_;

}

// ------------------------------------------------------------------------- //

void Suffer::ResourceManager::VertexBuffer::UploadVertexData(float* data, u32 size) {

  assert(data != nullptr && "Data is NULL!");
  assert(suffer.resource_manager_.data_->internal_vertex_buffers_[id_].vertex_format_ != VertexBuffer::kVertexFormat_Invalid && "Vertex format is INVALID!");

  Array<float> vertices_;
  vertices_.alloc(size);
  for (u32 i = 0; i < size; ++i) {
    vertices_[i] = data[i];
  }

  suffer.resource_manager_.data_->internal_vertex_buffers_[id_].data_.copy(vertices_);
  suffer.resource_manager_.data_->internal_vertex_buffers_[id_].version_++;
  suffer.resource_manager_.data_->internal_vertex_buffers_[id_].id_handle_ = id_;

}

// ------------------------------------------------------------------------- //

void Suffer::ResourceManager::IndexBuffer::UploadIndexData(IndexBuffer::Triangle* data, u32 size) {

  assert(data != nullptr && "Data is NULL!");

  suffer.resource_manager_.data_->internal_index_buffers_[id_].data_.alloc(size * 3);
  //Set contiguous memory
  for (u32 i = 0; i < size; ++i) {
    suffer.resource_manager_.data_->internal_index_buffers_[id_].data_[(i * 3) + 0] = data[i].indices_[0];
    suffer.resource_manager_.data_->internal_index_buffers_[id_].data_[(i * 3) + 1] = data[i].indices_[1];
    suffer.resource_manager_.data_->internal_index_buffers_[id_].data_[(i * 3) + 2] = data[i].indices_[2];
  }

  suffer.resource_manager_.data_->internal_index_buffers_[id_].version_++;
  suffer.resource_manager_.data_->internal_index_buffers_[id_].id_handle_ = id_;

}

// ------------------------------------------------------------------------- //

void Suffer::ResourceManager::IndexBuffer::UploadIndexData(u16* data, u32 size) {

  assert(data != nullptr && "Data is NULL!");

  Array<u16> indices_;
  indices_.alloc(size);
  for (u32 i = 0; i < size; ++i) {
    indices_[i] = data[i];
  }

  suffer.resource_manager_.data_->internal_index_buffers_[id_].data_.copy(indices_);
  suffer.resource_manager_.data_->internal_index_buffers_[id_].version_++;
  suffer.resource_manager_.data_->internal_index_buffers_[id_].id_handle_ = id_;

}

// ------------------------------------------------------------------------- //

void Suffer::ResourceManager::Texture::LoadTextureData(const char * file){

  assert(file != nullptr && "File is NULL!");

  unsigned char* data = stbi_load(file,
    (int*)&suffer.resource_manager_.data_->internal_textures_[id_].width_,
    (int*)&suffer.resource_manager_.data_->internal_textures_[id_].height_,
    (int*)&suffer.resource_manager_.data_->internal_textures_[id_].number_channels_, 0);

  if (!data) {
    printf("\n Can't load texture: %s", file);
    return;
  }

  u32 data_size = suffer.resource_manager_.data_->internal_textures_[id_].width_ * 
    suffer.resource_manager_.data_->internal_textures_[id_].height_ *
    suffer.resource_manager_.data_->internal_textures_[id_].number_channels_;

  suffer.resource_manager_.data_->internal_textures_[id_].data_.copy(data, data + data_size);

  suffer.resource_manager_.data_->internal_textures_[id_].version_++;
  suffer.resource_manager_.data_->internal_textures_[id_].id_handle_ = id_;

  stbi_image_free(data);

}

// ------------------------------------------------------------------------- //

Suffer::ResourceManager::GPUResource::GPUResource() {

  id_ = -1;
  type_ = kResourceType_Invalid;

}

// ------------------------------------------------------------------------- //

Suffer::ResourceManager::GPUResource::~GPUResource() {

}

// ------------------------------------------------------------------------- //

Suffer::ResourceManager::VertexBuffer::VertexBuffer() {

  type_ = GPUResource::kResourceType_VertexBuffer;
  id_ = suffer.resource_manager_.data_->number_of_vertex_buffers_;
  suffer.resource_manager_.data_->number_of_vertex_buffers_++;
  SetVertexFormat(kVertexFormat_Invalid);

}

// ------------------------------------------------------------------------- //

void Suffer::ResourceManager::VertexBuffer::SetVertexFormat(VertexFormat new_format){

  suffer.resource_manager_.data_->internal_vertex_buffers_[id_].vertex_format_ = (s32)new_format;

}

// ------------------------------------------------------------------------- //

Suffer::ResourceManager::IndexBuffer::IndexBuffer() {

  type_ = GPUResource::kResourceType_IndexBuffer;
  id_ = suffer.resource_manager_.data_->number_of_index_buffers_;
  suffer.resource_manager_.data_->number_of_index_buffers_++;

}

// ------------------------------------------------------------------------- //

Suffer::ResourceManager::Texture::Texture(){

  type_ = GPUResource::kResourceType_Texture;
  id_ = suffer.resource_manager_.data_->number_of_textures_;
  suffer.resource_manager_.data_->number_of_textures_++;
  suffer.resource_manager_.data_->internal_textures_[id_].wrap_s_ = kTextureWrap_Repeat;
  suffer.resource_manager_.data_->internal_textures_[id_].wrap_t_ = kTextureWrap_Repeat;
  suffer.resource_manager_.data_->internal_textures_[id_].min_filter_ = kTextureFilter_Linear;
  suffer.resource_manager_.data_->internal_textures_[id_].mag_filter_ = kTextureFilter_Linear;

}

// ------------------------------------------------------------------------- //

void Suffer::ResourceManager::Texture::SetTextureWrap(TextureWrap wrap_s, TextureWrap wrap_t) {

  suffer.resource_manager_.data_->internal_textures_[id_].wrap_s_ = wrap_s;
  suffer.resource_manager_.data_->internal_textures_[id_].wrap_t_ = wrap_t;

}

// ------------------------------------------------------------------------- //

void Suffer::ResourceManager::Texture::SetTextureFilter(TextureFilter min_filter, TextureFilter mag_filter) {

  suffer.resource_manager_.data_->internal_textures_[id_].min_filter_ = min_filter;
  suffer.resource_manager_.data_->internal_textures_[id_].mag_filter_ = mag_filter;

}

// ------------------------------------------------------------------------- //

Suffer::ResourceManager::ResourceData::ResourceData(){

}

// ------------------------------------------------------------------------- //

Suffer::ResourceManager::ResourceData::~ResourceData(){

}

// ------------------------------------------------------------------------- //

void Suffer::ResourceManager::ResourceData::InitInternalBuffers() {

  internal_index_buffers_.alloc(MAX_BUFFERS);
  internal_vertex_buffers_.alloc(MAX_BUFFERS);

  number_of_index_buffers_ = 0;
  number_of_vertex_buffers_ = 0;

  // TRIANGLE
  {

    float triangle[] = {
      // Positions             Normals            UV's
      0.0f,  0.5f, -1.0f,  0.0f, 0.0f, 1.0f,   0.5f, 1.0f,
      0.5f, -0.5f, -1.0f,  0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
      -0.5f, -0.5f, -1.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
    };

    Array<u16> triangle_indices;
    triangle_indices.alloc(3);
    triangle_indices[0] = { 0 };
    triangle_indices[1] = { 2 };
    triangle_indices[2] = { 1 };

    Array<float> vertices_;
    vertices_.alloc(sizeof(triangle) / sizeof(float));
    for (u32 i = 0; i < 24; ++i) {
        vertices_[i] = triangle[i];
    }

    internal_index_buffers_[number_of_index_buffers_].data_.copy(triangle_indices);
    internal_vertex_buffers_[number_of_vertex_buffers_].data_.copy(vertices_);

    internal_index_buffers_[number_of_index_buffers_].version_++;
    internal_vertex_buffers_[number_of_vertex_buffers_].version_++;

    internal_vertex_buffers_[number_of_vertex_buffers_].vertex_format_ = VertexBuffer::kVertexFormat_3P_3N_2UV;

    internal_index_buffers_[number_of_index_buffers_].id_handle_ = 0;
    internal_vertex_buffers_[number_of_vertex_buffers_].id_handle_ = 0;

    ++number_of_index_buffers_;
    ++number_of_vertex_buffers_;

  }

  // QUAD
  {
    float quad[] = {
        // Positions             Normals            UV's
        -1.0f,  -1.0f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
        -1.0f,   1.0f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f,
        1.0f,  1.0f,   0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
        1.0f, -1.0f,   0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
    };

    Array<u16> quad_indices;
    quad_indices.alloc(6);
    quad_indices[0] = { 0 };
    quad_indices[1] = { 1 };
    quad_indices[2] = { 2 };
    quad_indices[3] = { 0 };
    quad_indices[4] = { 2 };
    quad_indices[5] = { 3 };

    Array<float> vertices_;
    vertices_.alloc(sizeof(quad) / sizeof(float));
    for (u32 i = 0; i < 32; ++i) {
        vertices_[i] = quad[i];
    }

    internal_index_buffers_[number_of_index_buffers_].data_.copy(quad_indices);
    internal_vertex_buffers_[number_of_vertex_buffers_].data_.copy(vertices_);

    internal_index_buffers_[number_of_index_buffers_].version_++;
    internal_vertex_buffers_[number_of_vertex_buffers_].version_++;

    internal_vertex_buffers_[number_of_vertex_buffers_].vertex_format_ = VertexBuffer::kVertexFormat_3P_3N_2UV;

    internal_index_buffers_[number_of_index_buffers_].id_handle_ = 1;
    internal_vertex_buffers_[number_of_vertex_buffers_].id_handle_ = 1;

    ++number_of_index_buffers_;
    ++number_of_vertex_buffers_;

  }

  // CUBE
  {

    float cube[] = {
      1.0f,  1.0f,  1.0f,    1.0f,  0.0f,  0.0f,     0.0f, 1.0f,
      1.0f, -1.0f,  1.0f,    1.0f,  0.0f,  0.0f,     0.0f, 0.0f,
      1.0f, -1.0f, -1.0f,    1.0f,  0.0f,  0.0f,     1.0f, 0.0f,
      1.0f,  1.0f, -1.0f,    1.0f,  0.0f,  0.0f,     1.0f, 1.0f,

      -1.0f,  1.0f, -1.0f,   0.0f,  0.0f, -1.0f,     0.0f, 1.0f,
      -1.0f, -1.0f, -1.0f,   0.0f,  0.0f, -1.0f,     0.0f, 0.0f,
      1.0f, -1.0f, -1.0f,    0.0f,  0.0f, -1.0f,     1.0f, 0.0f,
      1.0f,  1.0f, -1.0f,    0.0f,  0.0f, -1.0f,     1.0f, 1.0f,

      -1.0f,  1.0f,  1.0f,  -1.0f,  0.0f,  0.0f,     0.0f, 1.0f,
      -1.0f, -1.0f,  1.0f,  -1.0f,  0.0f,  0.0f,     0.0f, 0.0f,
      -1.0f, -1.0f, -1.0f,  -1.0f,  0.0f,  0.0f,     1.0f, 0.0f,
      -1.0f,  1.0f, -1.0f,  -1.0f,  0.0f,  0.0f,     1.0f, 1.0f,

      -1.0f,  1.0f,  1.0f,   0.0f,  0.0f,  1.0f,     0.0f, 1.0f,
      -1.0f, -1.0f,  1.0f,   0.0f,  0.0f,  1.0f,     0.0f, 0.0f,
      1.0f, -1.0f,  1.0f,    0.0f,  0.0f,  1.0f,     1.0f, 0.0f,
      1.0f,  1.0f,  1.0f,    0.0f,  0.0f,  1.0f,     1.0f, 1.0f,

      -1.0f,  1.0f, -1.0f,   0.0f,  1.0f,  0.0f,     0.0f, 1.0f,
      -1.0f,  1.0f,  1.0f,   0.0f,  1.0f,  0.0f,     0.0f, 0.0f,
      1.0f,  1.0f,  1.0f,    0.0f,  1.0f,  0.0f,     1.0f, 0.0f,
      1.0f,  1.0f, -1.0f,    0.0f,  1.0f,  0.0f,     1.0f, 1.0f,

      -1.0f, -1.0f, -1.0f,   0.0f, -1.0f,  0.0f,     0.0f, 1.0f,
      -1.0f, -1.0f,  1.0f,   0.0f, -1.0f,  0.0f,     0.0f, 0.0f,
      1.0f, -1.0f,  1.0f,    0.0f, -1.0f,  0.0f,     1.0f, 0.0f,
      1.0f, -1.0f, -1.0f,    0.0f, -1.0f,  0.0f,     1.0f, 1.0f

    };

    u16 cube_indices2[]{
          0,  1,  2,  2,  3,  0,
          6,  5,  4,  4,  7,  6,
        10,  9,  8,  8, 11, 10,
        12, 13, 14, 14, 15, 12,
        16, 17, 18, 18, 19, 16,
        22, 21, 20, 20, 23, 22
    };

    Array<u16> cube_indices;
    cube_indices.alloc(36);

    for (int i = 0; i < 36; ++i) {
      cube_indices[i] = cube_indices2[i];
    }

    Array<float> vertices_;
    vertices_.alloc(192);
    for (u32 i = 0; i < 192; ++i) {
      vertices_[i] = cube[i];
    }

    internal_index_buffers_[number_of_index_buffers_].data_.copy(cube_indices);
    internal_vertex_buffers_[number_of_vertex_buffers_].data_.copy(vertices_);

    internal_index_buffers_[number_of_index_buffers_].version_++;
    internal_vertex_buffers_[number_of_vertex_buffers_].version_++;

    internal_index_buffers_[number_of_index_buffers_].id_handle_ = 2;
    internal_vertex_buffers_[number_of_vertex_buffers_].id_handle_ = 2;

    internal_vertex_buffers_[number_of_vertex_buffers_].vertex_format_ = ResourceManager::VertexBuffer::kVertexFormat_3P_3N_2UV;

    ++number_of_index_buffers_;
    ++number_of_vertex_buffers_;

  }

  // SPHERE
  {

    // SPHERE STUFF
    const int number_points = 25, number_revolutions = 25;

    Array<u16> sphere_indices;
    Array<mathmorra::Vector3> normals;
    Array<mathmorra::Vector3> sphere_points;

    normals.alloc(number_points * number_revolutions);
    sphere_points.alloc(number_points * number_revolutions);
    sphere_indices.alloc((number_points - 1) * (number_revolutions - 1) * 6);

    int index = 0;
    int radius = 1.0f;

    VertexBuffer::Vertex sphere_vertices[(number_revolutions * number_points)];

    for (int i = 0; i < number_points; ++i) {

      float latitude = ThiefUtils::Math::Map(i, 0, number_revolutions - 1, -ThiefUtils::Math::fPI / 2, ThiefUtils::Math::fPI / 2);

      for (int j = 0; j < number_revolutions; ++j) {

        float longitude = ThiefUtils::Math::Map(j, 0, number_revolutions - 1, -ThiefUtils::Math::fPI, ThiefUtils::Math::fPI);

        sphere_points[i * number_revolutions + j].x_ = radius * cos(longitude) * cos(latitude);
        sphere_points[i * number_revolutions + j].y_ = radius * sin(longitude) * cos(latitude);
        sphere_points[i * number_revolutions + j].z_ = radius * sin(latitude);

        normals[i * number_revolutions + j] = sphere_points[i * number_revolutions + j];
        normals[i * number_revolutions + j].Normalize();

        mathmorra::Vector2 uv;

        uv.x_ = (float)j / number_revolutions;
        uv.y_ = (float)i / number_points;

        sphere_vertices[(i * number_revolutions + j)] = VertexBuffer::Vertex(
          sphere_points[i * number_revolutions + j].x_,
          sphere_points[i * number_revolutions + j].y_,
          sphere_points[i * number_revolutions + j].z_,
          normals[i * number_revolutions + j].x_,
          normals[i * number_revolutions + j].y_,
          normals[i * number_revolutions + j].z_,
          uv.x_,
          uv.y_);

      }

    }


    for (int i = 0; i < number_points - 1; ++i) {

      for (int j = 0; j < number_revolutions - 1; ++j) {

        sphere_indices[index++] = i * number_revolutions + j;
        sphere_indices[index++] = (i + 1) * number_revolutions + j;
        sphere_indices[index++] = i * number_revolutions + j + 1;

        sphere_indices[index++] = i * number_revolutions + j + 1;
        sphere_indices[index++] = (i + 1) * number_revolutions + j;
        sphere_indices[index++] = (i + 1) * number_revolutions + j + 1;

      }

    }



    internal_index_buffers_[number_of_index_buffers_].data_.copy(sphere_indices);
    internal_vertex_buffers_[number_of_vertex_buffers_].data_.copy(&sphere_vertices[0].vertices_.x_, &sphere_vertices[(number_points * number_revolutions) - 1].vertices_.z_);

    internal_index_buffers_[number_of_index_buffers_].version_++;
    internal_vertex_buffers_[number_of_vertex_buffers_].version_++;

    internal_index_buffers_[number_of_index_buffers_].id_handle_ = 3;
    internal_vertex_buffers_[number_of_vertex_buffers_].id_handle_ = 3;

    internal_vertex_buffers_[number_of_vertex_buffers_].vertex_format_ = VertexBuffer::kVertexFormat_3P_3N_2UV;

    ++number_of_index_buffers_;
    ++number_of_vertex_buffers_;

  }

}

// ------------------------------------------------------------------------- //

void Suffer::ResourceManager::ResourceData::InitInternalTextures() {

  internal_textures_.alloc(MAX_TEXTURES);

  number_of_textures_ = 0;

}

// ------------------------------------------------------------------------- //

void Suffer::ResourceManager::ResourceData::InitInternalMaterials() {
  
  // Increase the number if you create a new one
  internal_materials_.alloc(4);
  number_of_materials_ = 0;

  // To create a new material define the shaders in internal_shaders.h

  // -------------------------- DefaultMaterial ---------------------------- //

  {

    internal_materials_[number_of_materials_].id_handle_ = number_of_materials_;

    internal_materials_[number_of_materials_].vertex_shader_ = Suffer::default_vertex_shader_;
    internal_materials_[number_of_materials_].fragment_shader_ = Suffer::default_fragment_shader_;
  
    number_of_materials_++;
  
  }

  // -------------------------- DefaultMaterial ---------------------------- //

  // --------------------------- PhongMaterial ----------------------------- //
  
  {
  
    internal_materials_[number_of_materials_].id_handle_ = number_of_materials_;
  
    internal_materials_[number_of_materials_].vertex_shader_ = Suffer::phong_vertex_shader;
    internal_materials_[number_of_materials_].fragment_shader_ = Suffer::phong_fragment_shader;
  
    number_of_materials_++;
  
  }

  // --------------------------- PhongMaterial ----------------------------- //

  // ---------------------- RenderToTextureMaterial ------------------------ //

  {

    internal_materials_[number_of_materials_].id_handle_ = number_of_materials_;

    internal_materials_[number_of_materials_].vertex_shader_ = Suffer::render_to_texture_vertex_;
    internal_materials_[number_of_materials_].fragment_shader_ = Suffer::render_to_texture_fragment_;

    number_of_materials_++;

  }

  // ---------------------- RenderToTextureMaterial ------------------------ //

  // ----------------------- BlackAndWhiteMaterial ------------------------- //

  {

    internal_materials_[number_of_materials_].id_handle_ = number_of_materials_;

    internal_materials_[number_of_materials_].vertex_shader_ = Suffer::black_and_white_vertex_;
    internal_materials_[number_of_materials_].fragment_shader_ = Suffer::black_and_white_fragment_;

    number_of_materials_++;

  }

  // ----------------------- BlackAndWhiteMaterial ------------------------- //

}

// ------------------------------------------------------------------------- //

void Suffer::ResourceManager::ResourceData::InitInternalFrameBuffers(){

  internal_frame_buffers_.alloc(MAX_FRAMEBUFFERS);

  number_of_frame_buffers_ = 0;

}

// ------------------------------------------------------------------------- //

void Suffer::ResourceManager::ResourceData::RefreshFrameBuffers() {
  
  for (u32 i = 0; i < number_of_frame_buffers_; ++i) {
    internal_frame_buffers_[i].width_ = suffer.GetWindowSize().x_;
    internal_frame_buffers_[i].height_ = suffer.GetWindowSize().y_;

    // Color
    //Suffer::ref_ptr<Suffer::ResourceManager::Texture> frame_buffer_color_texture;
    //frame_buffer_color_texture.alloc();

    internal_textures_[internal_frame_buffers_[i].color_texture_id_].width_ = suffer.GetWindowSize().x_;
    internal_textures_[internal_frame_buffers_[i].color_texture_id_].height_ = suffer.GetWindowSize().y_;
    internal_textures_[internal_frame_buffers_[i].color_texture_id_].number_channels_ = 3;
    internal_textures_[internal_frame_buffers_[i].color_texture_id_].version_++;

    // Depth
   //Suffer::ref_ptr<Suffer::ResourceManager::Texture> frame_buffer_depth_texture;
   //frame_buffer_depth_texture.alloc();

    internal_textures_[internal_frame_buffers_[i].depth_texture_id_].width_ = suffer.GetWindowSize().x_;
    internal_textures_[internal_frame_buffers_[i].depth_texture_id_].height_ = suffer.GetWindowSize().y_;
    internal_textures_[internal_frame_buffers_[i].depth_texture_id_].number_channels_ = 1;
    internal_textures_[internal_frame_buffers_[i].depth_texture_id_].version_++;

    suffer.resource_manager_.data_->internal_frame_buffers_[i].version_++;
  }

}

// ------------------------------------------------------------------------- //

Suffer::ResourceManager::VertexBuffer::Vertex::Vertex(float vertex_x, float vertex_y, float vertex_z){

  vertices_ = mathmorra::Vector3(vertex_x, vertex_y, vertex_z);

}

// ------------------------------------------------------------------------- //

Suffer::ResourceManager::VertexBuffer::Vertex::Vertex(float vertex_x, float vertex_y, float vertex_z, float normal_x, float normal_y, float normal_z){

  vertices_ = mathmorra::Vector3(vertex_x, vertex_y, vertex_z);
  normals_ = mathmorra::Vector3(normal_x, normal_y, normal_z);

}

// ------------------------------------------------------------------------- //

Suffer::ResourceManager::VertexBuffer::Vertex::Vertex(float vertex_x, float vertex_y, float vertex_z, float normal_x, float normal_y, float normal_z, float uv_x, float uv_y){

  vertices_ = mathmorra::Vector3(vertex_x, vertex_y, vertex_z);
  normals_ = mathmorra::Vector3(normal_x, normal_y, normal_z);
  uvs_ = mathmorra::Vector2(uv_x, uv_y);

}

// ------------------------------------------------------------------------- //

Suffer::ResourceManager::IndexBuffer::Triangle::Triangle(u16 index1, u16 index2, u16 index3){

  indices_[0] = index1;
  indices_[1] = index2;
  indices_[2] = index3;

}

// ------------------------------------------------------------------------- //

Suffer::ResourceManager::FrameBuffer::FrameBuffer(){

  type_ = GPUResource::kResourceType_FrameBuffer;
  id_ = suffer.resource_manager_.data_->number_of_frame_buffers_;
  suffer.resource_manager_.data_->number_of_frame_buffers_++;

}

// ------------------------------------------------------------------------- //

Suffer::ResourceManager::FrameBuffer::~FrameBuffer()
{

}

// ------------------------------------------------------------------------- //

void Suffer::ResourceManager::FrameBuffer::InitFrameBuffer(u16 width, u16 height){

  suffer.resource_manager_.data_->internal_frame_buffers_[id_].height_ = height;
  suffer.resource_manager_.data_->internal_frame_buffers_[id_].width_ = width;

  // Color
  Suffer::ref_ptr<Suffer::ResourceManager::Texture> frame_buffer_color_texture;
  frame_buffer_color_texture.alloc();

  suffer.resource_manager_.data_->internal_frame_buffers_[id_].color_texture_id_ = frame_buffer_color_texture->id_;
  suffer.resource_manager_.data_->internal_textures_[suffer.resource_manager_.data_->internal_frame_buffers_[id_].color_texture_id_].width_ = width;
  suffer.resource_manager_.data_->internal_textures_[suffer.resource_manager_.data_->internal_frame_buffers_[id_].color_texture_id_].height_ = height;
  suffer.resource_manager_.data_->internal_textures_[suffer.resource_manager_.data_->internal_frame_buffers_[id_].color_texture_id_].number_channels_ = 3;
  suffer.resource_manager_.data_->internal_textures_[suffer.resource_manager_.data_->internal_frame_buffers_[id_].color_texture_id_].version_++;
  
  // Depth
  Suffer::ref_ptr<Suffer::ResourceManager::Texture> frame_buffer_depth_texture;
  frame_buffer_depth_texture.alloc();

  suffer.resource_manager_.data_->internal_frame_buffers_[id_].depth_texture_id_ = frame_buffer_depth_texture->id_;
  suffer.resource_manager_.data_->internal_textures_[suffer.resource_manager_.data_->internal_frame_buffers_[id_].depth_texture_id_].width_ = width;
  suffer.resource_manager_.data_->internal_textures_[suffer.resource_manager_.data_->internal_frame_buffers_[id_].depth_texture_id_].height_ = height;
  suffer.resource_manager_.data_->internal_textures_[suffer.resource_manager_.data_->internal_frame_buffers_[id_].depth_texture_id_].number_channels_ = 1;
  suffer.resource_manager_.data_->internal_textures_[suffer.resource_manager_.data_->internal_frame_buffers_[id_].depth_texture_id_].version_++;

  suffer.resource_manager_.data_->internal_frame_buffers_[id_].version_++;

}

// ------------------------------------------------------------------------- //

