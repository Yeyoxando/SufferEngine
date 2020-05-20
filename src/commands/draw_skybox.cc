/*
 * Author: Diego Ochando Torres <ochandoto@esat-alumni.com>
 * Date: 03-05-2020
 * Draw Skybox command source
 */

#include "draw_skybox.h"
#include <gl/glew.h>
#include "suffermanager.h"
#include "internal_resource_manager.h"
#include "common_definitions.h"
#include "scene.h"
#include "matrix4.h"

static const u32 kMaxUsedVec4Data_DrawSkybox = 8;

struct Suffer::DrawSkybox::Data {

  // Geometry
  s32 vertex_buffer_id_;
  s32 index_buffer_id_;

  // Contains the model, view and projections matrixes
  float u_data_[kMaxUsedVec4Data_DrawSkybox * 4];

  u32 cubemap_id_;

};

 // ------------------------------------------------------------------------- //

Suffer::DrawSkybox::DrawSkybox(){

  cmd_type_ = Command::kCommandType_Render;
  data_ = new Data();

}

// ------------------------------------------------------------------------- //

Suffer::DrawSkybox::~DrawSkybox() {

  if (!data_) return;

  delete data_;
  data_ = nullptr;

}

// ------------------------------------------------------------------------- //

void Suffer::DrawSkybox::SetData(Skybox* skybox){

  data_->cubemap_id_ = skybox->cubemap_id_;
  data_->vertex_buffer_id_ = 2;
  data_->index_buffer_id_ = 2;

  //Matrices
  mathmorra::Matrix4 view = suffer.GetCurrentScene()->GetMainCamera()->ViewMatrix();
  mathmorra::Matrix4 projection = suffer.GetCurrentScene()->GetMainCamera()->ProjectionMatrix();
  for (u32 i = 0; i < 16; ++i) {
    // View will be in u_data[0] to u_data[3]
    data_->u_data_[i] = view.m[i];
    // Projection will be in u_data[4] to u_data[7]
    data_->u_data_[i + 16] = projection.m[i];
  }

}

// ------------------------------------------------------------------------- //

void Suffer::DrawSkybox::Execute() const{
  
  glEnable(GL_CULL_FACE);
  glDepthFunc(GL_LEQUAL);
  glCullFace(GL_BACK);
  glFrontFace(GL_CW);

  // ---------------------- IsBufferCreated (Vertex) ----------------------- //

  {

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

  {

    s32 id_texture = 1;// data_->cubemap_id_;
    if (id_texture < 0) return;


    if (suffer.resource_manager_.data_->internal_cubemaps_[id_texture].gpu_version_ == 0) {
      glGenTextures(1, &suffer.resource_manager_.data_->internal_cubemaps_[id_texture].current_texture_id_);
    }

    if (suffer.resource_manager_.data_->internal_cubemaps_[id_texture].gpu_version_ < suffer.resource_manager_.data_->internal_cubemaps_[id_texture].version_) {
      glBindTexture(GL_TEXTURE_CUBE_MAP, suffer.resource_manager_.data_->internal_cubemaps_[id_texture].current_texture_id_);

      // WRAP S
      switch (suffer.resource_manager_.data_->internal_cubemaps_[id_texture].wrap_s_) {
      case ResourceManager::Texture::kTextureWrap_Repeat:
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
        break;
      case ResourceManager::Texture::kTextureWrap_MirroredRepeat:
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        break;
      case ResourceManager::Texture::kTextureWrap_ClampToEdge:
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        break;
      default:
        break;
      }

      // WRAP T
      switch (suffer.resource_manager_.data_->internal_cubemaps_[id_texture].wrap_t_) {
      case ResourceManager::Texture::kTextureWrap_Repeat:
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
        break;
      case ResourceManager::Texture::kTextureWrap_MirroredRepeat:
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        break;
      case ResourceManager::Texture::kTextureWrap_ClampToEdge:
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        break;
      default:
        break;
      }

      // MIN FILTER
      switch (suffer.resource_manager_.data_->internal_cubemaps_[id_texture].min_filter_) {
      case ResourceManager::Texture::kTextureFilter_Linear:
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        break;
      case ResourceManager::Texture::kTextureFilter_Nearest:
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        break;
      default:
        break;
      }

      // MAG FILTER
      switch (suffer.resource_manager_.data_->internal_cubemaps_[id_texture].mag_filter_) {
      case ResourceManager::Texture::kTextureFilter_Linear:
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        break;
      case ResourceManager::Texture::kTextureFilter_Nearest:
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        break;
      default:
        break;
      }

      // UPLOAD DATA DEPENDING ON NUMBER CHANNELS
      switch (suffer.resource_manager_.data_->internal_cubemaps_[id_texture].number_channels_) {
      case 3: {
        for (u32 i = 0; i < 6; i++) {
          glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
            0, GL_RGB,
            suffer.resource_manager_.data_->internal_cubemaps_[id_texture].width_,
            suffer.resource_manager_.data_->internal_cubemaps_[id_texture].height_,
            0, GL_RGB, GL_UNSIGNED_BYTE,
            suffer.resource_manager_.data_->internal_cubemaps_[id_texture].data_[i].get());
        }
        break;
      }
      case 4: {
        for (u32 i = 0; i < 6; i++) {
          glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
            0, GL_RGBA,
            suffer.resource_manager_.data_->internal_cubemaps_[id_texture].width_,
            suffer.resource_manager_.data_->internal_cubemaps_[id_texture].height_,
            0, GL_RGBA, GL_UNSIGNED_BYTE,
            suffer.resource_manager_.data_->internal_cubemaps_[id_texture].data_[i].get());
        }
        break;
      }
      default: {
        assert(1 && "\n Not contemplated number of channels.");
        break;
      }
      }

      suffer.resource_manager_.data_->internal_cubemaps_[id_texture].gpu_version_ = suffer.resource_manager_.data_->internal_cubemaps_[id_texture].version_;
    }

  }

  // --------------------------- IsTextureCreated -------------------------- //

  // ----------------------------------------------------------------------- //

  // -------------------------- IsMaterialCreated -------------------------- //

  {

    // 1 equals to resource manager internal skybox material
    u32 mat_type = 1;

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


    // -------------------------- IsMaterialCreated -------------------------- //

    // ----------------------------------------------------------------------- //

    // ------------------------------- Uniforms ------------------------------ //

    u32 program_id = suffer.resource_manager_.data_->internal_materials_[mat_type].current_program_;

    glUseProgram(program_id);

    s32 u_pos = -1;

    // -- Uniform Block --
    u_pos = glGetUniformLocation(program_id, "u_data");
    if (u_pos < 0) {
      printf("\nERROR: u_data uniform not exists.\n");
      //return;
    }

    glUniform4fv(u_pos, kMaxUsedVec4Data_DrawSkybox, data_->u_data_);
    u_pos = -1;


    // -- Textures --
    const char* str = "u_skybox";
    u_pos = glGetUniformLocation(program_id, str);
    if (u_pos < 0) {
      printf("\nERROR: texture skybox uniform not exists.");
      //return;
    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 1);// suffer.resource_manager_.data_->internal_cubemaps_[data_->cubemap_id_].current_texture_id_);

    glUniform1i(u_pos, 0);
    u_pos = -1;

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
      //glEnableVertexAttribArray(1);
      //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (6 * sizeof(float)), (GLvoid*)(3 * sizeof(float)));
      break;
    case Suffer::ResourceManager::VertexBuffer::kVertexFormat_3P_3N_2UV:
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (8 * sizeof(float)), (GLvoid*)0);
      //glEnableVertexAttribArray(1);
      //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (8 * sizeof(float)), (GLvoid*)(3 * sizeof(float)));
      //glEnableVertexAttribArray(2);
      //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, (8 * sizeof(float)), (GLvoid*)(6 * sizeof(float)));

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

    glDrawElements(GL_TRIANGLES, number_elements, GL_UNSIGNED_SHORT, (GLvoid*)0);

  }

  // --------------------------------- Draw -------------------------------- //


}

// ------------------------------------------------------------------------- //

