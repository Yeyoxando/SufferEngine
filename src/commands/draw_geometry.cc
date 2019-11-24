/*
 * Author: Diego Ochando Torres <ochandoto@esat-alumni.com>
 * Date: 15-10-2019
 * Draw Geometry command Header
 */

#include <draw_geometry.h>
#include <gl/glew.h>
#include <data_types.h>
#include "vector4.h"
#include "suffermanager.h"
#include "internal_resource_manager.h"
#include "common_definitions.h"

// ------------------------------------------------------------------------- //

struct Suffer::DrawGeometry::Data {

  // Geometry
  s32 vertex_buffer_id_;
  s32 index_buffer_id_;
  GLenum draw_mode_;

  // Contains the model, view and projections matrixes + 1 color Vector4 (13 Vector4 in total)
  float u_data_[13 * 4];
  u32 material_type_;

};

// ------------------------------------------------------------------------- //

Suffer::DrawGeometry::DrawGeometry() {

  cmd_type_ = Command::kRender;
  data_ = new Data();

}

// ------------------------------------------------------------------------- //

Suffer::DrawGeometry::~DrawGeometry() {

  if (!data_) return;

  delete data_;
  data_ = nullptr;

}

// ------------------------------------------------------------------------- //

void Suffer::DrawGeometry::SetData(GameObject* go) {

  // ---------------------------- SetGeometry ------------------------------ //

  {
  
    data_->vertex_buffer_id_ = go->GetGeometry()->vertex_buffer_id_;
    data_->index_buffer_id_ = go->GetGeometry()->index_buffer_id_;
    Suffer::Geometry::DrawMode mode_ = go->GetGeometry()->mode_;

    switch (mode_){

        case Suffer::Geometry::kDrawMode_Invalid:
            data_->draw_mode_ = GL_NONE;
            break;
        case Suffer::Geometry::kDrawMode_Triangles:
            data_->draw_mode_ = GL_TRIANGLES;
            break;
        case Suffer::Geometry::kDrawMode_Lines:
            data_->draw_mode_ = GL_LINES;
            break;
        case Suffer::Geometry::kDrawMode_LineLoop:
            data_->draw_mode_ = GL_LINE_LOOP;
            break;
        case Suffer::Geometry::kDrawMode_LineStrip:
            data_->draw_mode_ = GL_LINE_STRIP;
            break;
        case Suffer::Geometry::kDrawMode_Points:
            data_->draw_mode_ = GL_POINTS;
            break;
        case Suffer::Geometry::kDrawMode_Patches:
            data_->draw_mode_ = GL_PATCHES;
        default:
            break;
    }
  
  }

  // ---------------------------- SetGeometry ------------------------------ //


  // --------------------------- StoreUniforms ----------------------------- //

  {

    data_->material_type_ = (u32)go->GetMaterial()->GetMaterialParamsType();

    // -- Common Attributes --
    MaterialInstance::BaseParams* params = go->GetMaterial()->GetMaterialParams();
    mathmorra::Vector4 aux_color = params->color_;
    float values[4] = { aux_color.x_, aux_color.y_, aux_color.z_, aux_color.w_ };
    // Copy color to next free uniform space, after Vector n12 because of 3 matrixes, > u_data[48]
    data_->u_data_[48] = values[0];
    data_->u_data_[49] = values[1];
    data_->u_data_[50] = values[2];
    data_->u_data_[51] = values[3];

    // -- Set specific material parameters --
    switch (data_->material_type_) {
    case MaterialInstance::ParamsType::kParams_Default: {
      MaterialInstance::DefaultParams* default_params_;
      default_params_ = reinterpret_cast<MaterialInstance::DefaultParams*>(params);

      //data_->material_params_.default_params_.albedo_texture_id_ = params_->albedo_texture_id_;
    }
      break;
    case MaterialInstance::ParamsType::kParams_Phong: {
      MaterialInstance::PhongParams* phong_params_;
      phong_params_ = reinterpret_cast<MaterialInstance::PhongParams*>(params);

      //data_->material_params_.default_params_.albedo_texture_id_ = params_->albedo_texture_id_;
    }
      // Specific parameters for phong
      break;
    case MaterialInstance::ParamsType::kParams_NONE:
      assert(data_->material_type_ != MaterialInstance::kParams_NONE && "MaterialInstance type not set");
      break;
    default:
      break;
    }
  
    // Set textures

  }

  // --------------------------- StoreUniforms ----------------------------- //

}

// ------------------------------------------------------------------------- //

void Suffer::DrawGeometry::SetModelMatrix(mathmorra::Matrix4 model) {

  // Model will be in u_data[0] to u_data[3]
  for (u32 i = 0; i < 16; ++i) {
    data_->u_data_[i] = model.m[i];
  }

}

// ------------------------------------------------------------------------- //

void Suffer::DrawGeometry::SetViewMatrix(mathmorra::Matrix4 view) {

  // View will be in u_data[4] to u_data[7]
  for (u32 i = 0; i < 16; ++i) {
    data_->u_data_[i + 16] = view.m[i];
  }

}

// ------------------------------------------------------------------------- //

void Suffer::DrawGeometry::SetProjectionMatrix(mathmorra::Matrix4 projection) {

  // Projection will be in u_data[8] to u_data[11]
  for (u32 i = 0; i < 16; ++i) {
    data_->u_data_[i + 32] = projection.m[i];
  }

}

// ------------------------------------------------------------------------- //

void Suffer::DrawGeometry::Execute() const {

  GLenum error;
  
  // ---------------------- IsBufferCreated (Vertex) ----------------------- //

  {

    assert(data_->vertex_buffer_id_ >= 0);

    if (data_->vertex_buffer_id_ < 0) return;

    s32 id_vertex = data_->vertex_buffer_id_;

    if (suffer.resource_manager_.data_->internal_vertex_buffers_[id_vertex].gpu_version_ == 0) {
      glGenBuffers(1, &suffer.resource_manager_.data_->internal_vertex_buffers_[id_vertex].current_gl_buffer_);
    }

    if (suffer.resource_manager_.data_->internal_vertex_buffers_[id_vertex].gpu_version_ < suffer.resource_manager_.data_->internal_vertex_buffers_[id_vertex].version_) {
      glBindBuffer(GL_ARRAY_BUFFER, suffer.resource_manager_.data_->internal_vertex_buffers_[id_vertex].current_gl_buffer_);

      glBufferData(GL_ARRAY_BUFFER,
        suffer.resource_manager_.data_->internal_vertex_buffers_[id_vertex].data_.sizeInBytes(),
        suffer.resource_manager_.data_->internal_vertex_buffers_[id_vertex].data_.get(),
        GL_STATIC_DRAW);

      suffer.resource_manager_.data_->internal_vertex_buffers_[id_vertex].gpu_version_ = suffer.resource_manager_.data_->internal_vertex_buffers_[id_vertex].version_;
    }

  }

  // ---------------------- IsBufferCreated (Vertex) ----------------------- //

  // ----------------------------------------------------------------------- //

  // ----------------------- IsBufferCreated (Index) ----------------------- //

  {
  
    assert(data_->index_buffer_id_ >= 0);

    if (data_->index_buffer_id_ < 0) return;
    s32 id_index = data_->index_buffer_id_;
    if (suffer.resource_manager_.data_->internal_index_buffers_[id_index].gpu_version_ == 0) {
      glGenBuffers(1, &suffer.resource_manager_.data_->internal_index_buffers_[id_index].current_gl_buffer_);
    }

    if (suffer.resource_manager_.data_->internal_index_buffers_[id_index].gpu_version_ < suffer.resource_manager_.data_->internal_index_buffers_[id_index].version_) {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, suffer.resource_manager_.data_->internal_index_buffers_[id_index].current_gl_buffer_);

      glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        suffer.resource_manager_.data_->internal_index_buffers_[id_index].data_.sizeInBytes(),
        suffer.resource_manager_.data_->internal_index_buffers_[id_index].data_.get(),
        GL_STATIC_DRAW);

      suffer.resource_manager_.data_->internal_index_buffers_[id_index].gpu_version_ = suffer.resource_manager_.data_->internal_index_buffers_[id_index].version_;
    }

  }

  // ----------------------- IsBufferCreated (Index) ----------------------- //

  // ----------------------------------------------------------------------- //

  // --------------------------- IsTextureCreated -------------------------- //

  //{
  //
  //  // TODO: need a switch and a loop initializing all required textures in material
  //  if (data_->material_params_.default_params_.albedo_texture_id_ < 0) return;
  //  s32 id_texture = data_->material_params_.default_params_.albedo_texture_id_;
  //
  //  if (suffer.resource_manager_.data_->internal_textures_[id_texture].gpu_version_ == 0) {
  //    glGenTextures(1, &suffer.resource_manager_.data_->internal_textures_[id_texture].current_texture_id_);
  //  }
  //
  //  if (suffer.resource_manager_.data_->internal_textures_[id_texture].gpu_version_ < suffer.resource_manager_.data_->internal_textures_[id_texture].version_) {
  //    glBindTexture(GL_TEXTURE_2D, suffer.resource_manager_.data_->internal_textures_[id_texture].current_texture_id_);
  //
  //    // WRAP S
  //    switch (suffer.resource_manager_.data_->internal_textures_[id_texture].wrap_s_) {
  //    case ResourceManager::Texture::kTextureWrap_Repeat:
  //      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  //      break;
  //    case ResourceManager::Texture::kTextureWrap_MirroredRepeat:
  //      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  //      break;
  //    case ResourceManager::Texture::kTextureWrap_ClampToEdge:
  //      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  //      break;
  //    default:
  //      break;
  //    }
  //
  //    // WRAP T
  //    switch (suffer.resource_manager_.data_->internal_textures_[id_texture].wrap_t_) {
  //    case ResourceManager::Texture::kTextureWrap_Repeat:
  //      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  //      break;
  //    case ResourceManager::Texture::kTextureWrap_MirroredRepeat:
  //      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
  //      break;
  //    case ResourceManager::Texture::kTextureWrap_ClampToEdge:
  //      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  //      break;
  //    default:
  //      break;
  //    }
  //
  //    // MIN FILTER
  //    switch (suffer.resource_manager_.data_->internal_textures_[id_texture].min_filter_) {
  //    case ResourceManager::Texture::kTextureFilter_Linear:
  //      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  //      break;
  //    case ResourceManager::Texture::kTextureFilter_Nearest:
  //      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  //      break;
  //    default:
  //      break;
  //    }
  //
  //    // MAG FILTER
  //    switch (suffer.resource_manager_.data_->internal_textures_[id_texture].mag_filter_) {
  //    case ResourceManager::Texture::kTextureFilter_Linear:
  //      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  //      break;
  //    case ResourceManager::Texture::kTextureFilter_Nearest:
  //      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  //      break;
  //    default:
  //      break;
  //    }
  //
  //    // UPLOAD DATA DEPENDING ON NUMBER CHANNELS
  //    switch (suffer.resource_manager_.data_->internal_textures_[id_texture].number_channels_) {
  //    case 3:
  //      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
  //        suffer.resource_manager_.data_->internal_textures_[id_texture].width_,
  //        suffer.resource_manager_.data_->internal_textures_[id_texture].height_,
  //        0, GL_RGB, GL_UNSIGNED_BYTE,
  //        suffer.resource_manager_.data_->internal_textures_[id_texture].data_.get());
  //      break;
  //    case 4:
  //      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
  //        suffer.resource_manager_.data_->internal_textures_[id_texture].width_,
  //        suffer.resource_manager_.data_->internal_textures_[id_texture].height_,
  //        0, GL_RGBA, GL_UNSIGNED_BYTE,
  //        suffer.resource_manager_.data_->internal_textures_[id_texture].data_.get());
  //      break;
  //    default:
  //      assert(1 && "\n Not contemplated number of channels.");
  //      break;
  //    }
  //
  //    glGenerateMipmap(GL_TEXTURE_2D);
  //
  //    suffer.resource_manager_.data_->internal_textures_[id_texture].gpu_version_ = suffer.resource_manager_.data_->internal_textures_[id_texture].version_;
  //  }
  //
  //}

  // --------------------------- IsTextureCreated -------------------------- //

  // ----------------------------------------------------------------------- //

  // -------------------------- IsMaterialCreated -------------------------- //

  {
  
    u32 mat_type = data_->material_type_;

    // If internal material is not created, creates it
    if (!suffer.resource_manager_.data_->internal_materials_[mat_type].is_created_) {
      // Create vertex shader
      suffer.resource_manager_.data_->internal_materials_[mat_type].vertex_shader_id_ =
        glCreateShader(GL_VERTEX_SHADER);

      // Create fragment shader
      suffer.resource_manager_.data_->internal_materials_[mat_type].fragment_shader_id_ =
        glCreateShader(GL_FRAGMENT_SHADER);

      // Get shaders length
      const GLint vertex_size = strlen(suffer.resource_manager_.data_->internal_materials_[mat_type].vertex_shader_);
      const GLint fragment_size = strlen(suffer.resource_manager_.data_->internal_materials_[mat_type].fragment_shader_);

      // Upload vertex shader data
      glShaderSource(suffer.resource_manager_.data_->internal_materials_[mat_type].vertex_shader_id_,
        1, &suffer.resource_manager_.data_->internal_materials_[mat_type].vertex_shader_,
        &vertex_size);

      // Upload fragment shader data
      glShaderSource(suffer.resource_manager_.data_->internal_materials_[mat_type].fragment_shader_id_,
        1, &suffer.resource_manager_.data_->internal_materials_[mat_type].fragment_shader_, &fragment_size);
      
      // Compile vertex shader
      glCompileShader(suffer.resource_manager_.data_->internal_materials_[mat_type].vertex_shader_id_);
      
      GLint status = 0;
      glGetShaderiv(suffer.resource_manager_.data_->internal_materials_[mat_type].vertex_shader_id_, GL_COMPILE_STATUS, &status);
      GLint log_length = 0;
      glGetShaderiv(suffer.resource_manager_.data_->internal_materials_[mat_type].vertex_shader_id_, GL_INFO_LOG_LENGTH, &log_length);
      Array<char> info_log;
      info_log.alloc(log_length + 1);
      info_log[log_length] = '\0';
      glGetShaderInfoLog(suffer.resource_manager_.data_->internal_materials_[mat_type].vertex_shader_id_, log_length, &log_length, &info_log[0]);

      printf("\n\n%s", info_log.get());
      if (status == GL_FALSE)
        printf("\nERROR: vertex shader not compiled");

      // Compile fragment shader
      glCompileShader(suffer.resource_manager_.data_->internal_materials_[mat_type].fragment_shader_id_);
      status = 0;
      glGetShaderiv(suffer.resource_manager_.data_->internal_materials_[mat_type].fragment_shader_id_, GL_COMPILE_STATUS, &status);
      log_length = 0;
      info_log.release();
      glGetShaderiv(suffer.resource_manager_.data_->internal_materials_[mat_type].fragment_shader_id_, GL_INFO_LOG_LENGTH, &log_length);
      info_log.alloc(log_length + 1);
      info_log[log_length] = '\0';
      glGetShaderInfoLog(suffer.resource_manager_.data_->internal_materials_[mat_type].fragment_shader_id_, log_length, &log_length, &info_log[0]);
      printf("\n\n%s", info_log.get());
      if (status == GL_FALSE)
        printf("\nERROR: fragment shader not compiled");
      info_log.release();


      // Create program
      suffer.resource_manager_.data_->internal_materials_[mat_type].current_program_ = glCreateProgram();
      
      // Attach shaders
      glAttachShader(suffer.resource_manager_.data_->internal_materials_[mat_type].current_program_,
        suffer.resource_manager_.data_->internal_materials_[mat_type].vertex_shader_id_);
      
      glAttachShader(suffer.resource_manager_.data_->internal_materials_[mat_type].current_program_,
        suffer.resource_manager_.data_->internal_materials_[mat_type].fragment_shader_id_);
      
      // Link program
      glLinkProgram(suffer.resource_manager_.data_->internal_materials_[mat_type].current_program_);
      
      // Mark internal material as created
      suffer.resource_manager_.data_->internal_materials_[mat_type].is_created_ = true;
    }

  }

  // -------------------------- IsMaterialCreated -------------------------- //

  // ----------------------------------------------------------------------- //

  // ------------------------------- Uniforms ------------------------------ //

  u32 program_id = suffer.resource_manager_.data_->internal_materials_[data_->material_type_].current_program_;

  {

    glUseProgram(program_id);
    
    s32 u_pos = -1;

    // Uniform Block
    u_pos = glGetUniformLocation(program_id, "u_data");
    if (u_pos < 0) {
      printf("\nERROR: u_data uniform not exists.");
      return;
    }

    glUniform4fv(u_pos, 13, data_->u_data_);
    u_pos = -1;
    // TODO: pass the textures
  
//// Albedo Texture
//  u_pos = glGetUniformLocation(program_id, "u_albedo");
//  if (u_pos < 0) {
//    printf("\nERROR: u_albedo uniform not exists.");
//    //return;
//  }
//  
//  glActiveTexture(GL_TEXTURE0);
//  glBindTexture(GL_TEXTURE_2D, suffer.resource_manager_.data_->internal_textures_[data_->material_params_.default_params_.albedo_texture_id_].current_texture_id_);
//
//  glUniform1i(u_pos, 0);
//  u_pos = -1;

  }

  // ------------------------------- Uniforms ------------------------------ //

  // ----------------------------------------------------------------------- //

  // --------------------------- Vertex Attributes ------------------------- //

  {

    glBindBuffer(GL_ARRAY_BUFFER, suffer.resource_manager_.data_->internal_vertex_buffers_[data_->vertex_buffer_id_].current_gl_buffer_);
    auto type = suffer.resource_manager_.data_->internal_vertex_buffers_[data_->vertex_buffer_id_].vertex_format_;
    switch (type) {
    case Suffer::ResourceManager::VertexBuffer::kVertexFormat_3P:
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
      break;
    case Suffer::ResourceManager::VertexBuffer::kVertexFormat_3P_3N:
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (6 * sizeof(float)), (GLvoid*)0);
      glEnableVertexAttribArray(1);
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (6 * sizeof(float)), (GLvoid*)(3 * sizeof(float)));
      break;
    case Suffer::ResourceManager::VertexBuffer::kVertexFormat_3P_3N_2UV:
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (8 * sizeof(float)), (GLvoid*)0);
      glEnableVertexAttribArray(1);
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (8 * sizeof(float)), (GLvoid*)(3 * sizeof(float)));
      glEnableVertexAttribArray(2);
      glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, (8 * sizeof(float)), (GLvoid*)(6 * sizeof(float)));

      break;
    default:

      break;
    }
  
  }

  // --------------------------- Vertex Attributes ------------------------- //

  // ----------------------------------------------------------------------- //

  // --------------------------------- Draw -------------------------------- //

  {

    u32 number_elements = suffer.resource_manager_.data_->internal_index_buffers_[data_->index_buffer_id_].data_.size();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, suffer.resource_manager_.data_->internal_index_buffers_[data_->index_buffer_id_].current_gl_buffer_);
    
    glDrawElements(data_->draw_mode_, number_elements, GL_UNSIGNED_SHORT, (GLvoid*)0);
    
  }

  // --------------------------------- Draw -------------------------------- //

}

// --------------------------------------------------- //
