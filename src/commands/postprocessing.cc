/*
 * Author: Diego Ochando Torres <ochandoto@esat-alumni.com>
 * Date: 24-02-2019
 * Post-processing command Header
 */

#include <postprocessing.h>
#include <gl/glew.h>
#include "time.h"
#include <data_types.h>
#include "vector4.h"
#include "suffermanager.h"
#include "internal_resource_manager.h"
#include "internal_shaders.h"
#include "component_material.h"
#include "common_definitions.h"
#include <string>

// ------------------------------------------------------------------------- //

struct Suffer::Postprocessing::Data {

  // Geometry
  s32 vertex_buffer_id_;
  s32 index_buffer_id_;

  // Textures has to be separated
  s32 texture_ids_[MAX_USED_TEXTURES];
  u32 current_used_textures_;

  u32 postpro_type_;

};

// ------------------------------------------------------------------------- //

Suffer::Postprocessing::Postprocessing() {

  cmd_type_ = Command::kCommandType_Render;
  data_ = new Data();
  data_->current_used_textures_ = 0;

  for (u32 i = 0; i < MAX_USED_TEXTURES; ++i) {
    data_->texture_ids_[i] = -1;
  }

}

// ------------------------------------------------------------------------- //

Suffer::Postprocessing::~Postprocessing() {

  if (!data_) return;

  delete data_;
  data_ = nullptr;

}

// ------------------------------------------------------------------------- //

void Suffer::Postprocessing::SetData(PostproccessKind postpro) {

  // ---------------------------- SetGeometry ------------------------------ //

  {
    // Set quad ids
    data_->vertex_buffer_id_ = 1;
    data_->index_buffer_id_ = 1;

  }

  // ---------------------------- SetGeometry ------------------------------ //


  // ---------------------------- SetMaterial ------------------------------ //

  {

      data_->current_used_textures_ = 1;
      data_->postpro_type_ = postpro;
  }

  // ---------------------------- SetMaterial ------------------------------ //

}

// ------------------------------------------------------------------------- //

void Suffer::Postprocessing::Execute() const {

  glDisable(GL_DEPTH_TEST);

  glCullFace(GL_FRONT);

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

  // -------------------------- IsMaterialCreated -------------------------- //

  {

    u32 mat_type;
    switch (data_->postpro_type_) {
    case PostproccessKind::kPostproccessKind_RenderToTexture: {
      mat_type = 0;
    }
      break;
    case PostproccessKind::kPostproccessKind_BlackAndWhite: {
      mat_type = 1;
    }
      break;
    default:
      break;
    }
    
    // If internal material is not created, creates it
    if (!suffer.resource_manager_.data_->internal_postproccess_materials_[mat_type].is_created_) {
      // Create vertex shader
      suffer.resource_manager_.data_->internal_postproccess_materials_[mat_type].vertex_shader_id_ =
        glCreateShader(GL_VERTEX_SHADER);

      // Create fragment shader
      suffer.resource_manager_.data_->internal_postproccess_materials_[mat_type].fragment_shader_id_ =
        glCreateShader(GL_FRAGMENT_SHADER);

      // Get shaders length
      const GLint vertex_size = strlen(suffer.resource_manager_.data_->internal_postproccess_materials_[mat_type].vertex_shader_);
      const GLint fragment_size = strlen(suffer.resource_manager_.data_->internal_postproccess_materials_[mat_type].fragment_shader_);

      // Upload vertex shader data
      glShaderSource(suffer.resource_manager_.data_->internal_postproccess_materials_[mat_type].vertex_shader_id_,
        1, &suffer.resource_manager_.data_->internal_postproccess_materials_[mat_type].vertex_shader_,
        &vertex_size);

      // Upload fragment shader data
      glShaderSource(suffer.resource_manager_.data_->internal_postproccess_materials_[mat_type].fragment_shader_id_,
        1, &suffer.resource_manager_.data_->internal_postproccess_materials_[mat_type].fragment_shader_, &fragment_size);

      // Compile vertex shader
      glCompileShader(suffer.resource_manager_.data_->internal_postproccess_materials_[mat_type].vertex_shader_id_);

      GLint status = 0;
      glGetShaderiv(suffer.resource_manager_.data_->internal_postproccess_materials_[mat_type].vertex_shader_id_, GL_COMPILE_STATUS, &status);
      GLint log_length = 0;
      glGetShaderiv(suffer.resource_manager_.data_->internal_postproccess_materials_[mat_type].vertex_shader_id_, GL_INFO_LOG_LENGTH, &log_length);
      Array<char> info_log;
      info_log.alloc(log_length + 1);
      info_log[log_length] = '\0';
      glGetShaderInfoLog(suffer.resource_manager_.data_->internal_postproccess_materials_[mat_type].vertex_shader_id_, log_length, &log_length, &info_log[0]);

      printf("\n\n%s", info_log.get());
      if (status == GL_FALSE)
        printf("\nERROR: vertex shader not compiled");

      // Compile fragment shader
      glCompileShader(suffer.resource_manager_.data_->internal_postproccess_materials_[mat_type].fragment_shader_id_);
      status = 0;
      glGetShaderiv(suffer.resource_manager_.data_->internal_postproccess_materials_[mat_type].fragment_shader_id_, GL_COMPILE_STATUS, &status);
      log_length = 0;
      info_log.release();
      glGetShaderiv(suffer.resource_manager_.data_->internal_postproccess_materials_[mat_type].fragment_shader_id_, GL_INFO_LOG_LENGTH, &log_length);
      info_log.alloc(log_length + 1);
      info_log[log_length] = '\0';
      glGetShaderInfoLog(suffer.resource_manager_.data_->internal_postproccess_materials_[mat_type].fragment_shader_id_, log_length, &log_length, &info_log[0]);
      printf("\n\n%s", info_log.get());
      if (status == GL_FALSE)
        printf("\nERROR: fragment shader not compiled");
      info_log.release();


      // Create program
      suffer.resource_manager_.data_->internal_postproccess_materials_[mat_type].current_program_ = glCreateProgram();

      // Attach shaders
      glAttachShader(suffer.resource_manager_.data_->internal_postproccess_materials_[mat_type].current_program_,
        suffer.resource_manager_.data_->internal_postproccess_materials_[mat_type].vertex_shader_id_);

      glAttachShader(suffer.resource_manager_.data_->internal_postproccess_materials_[mat_type].current_program_,
        suffer.resource_manager_.data_->internal_postproccess_materials_[mat_type].fragment_shader_id_);

      // Link program
      glLinkProgram(suffer.resource_manager_.data_->internal_postproccess_materials_[mat_type].current_program_);

      // Mark internal material as created
      suffer.resource_manager_.data_->internal_postproccess_materials_[mat_type].is_created_ = true;
    }


  // -------------------------- IsMaterialCreated -------------------------- //

  // ----------------------------------------------------------------------- //

  // ------------------------------- Uniforms ------------------------------ //
  
    u32 program_id = suffer.resource_manager_.data_->internal_postproccess_materials_[mat_type].current_program_;

    glUseProgram(program_id);

    s32 u_pos = -1;

    // -- Textures --
    std::string base_tex_name = "u_tex";

    for (u32 i = 0; i < data_->current_used_textures_; ++i) {

      std::string tex_name = base_tex_name + std::to_string(i);
      const char* str = tex_name.c_str();
      u_pos = glGetUniformLocation(program_id, str);
      if (u_pos < 0) {
        printf("\nERROR: texture %d uniform not exists.", i);
      }

      glActiveTexture(GL_TEXTURE0 + i);
      suffer.render_manager_.current_drawn_texture_id_;
      glBindTexture(GL_TEXTURE_2D, suffer.render_manager_.current_drawn_texture_id_);

      glUniform1i(u_pos, i);
      u_pos = -1;

    }

  }

  // ------------------------------- Uniforms ------------------------------ //

  // ----------------------------------------------------------------------- //

  // --------------------------- Vertex Attributes ------------------------- //

  {

    glBindBuffer(GL_ARRAY_BUFFER, suffer.resource_manager_.data_->internal_vertex_buffers_[data_->vertex_buffer_id_].current_gl_buffer_);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (8 * sizeof(float)), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (8 * sizeof(float)), (GLvoid*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, (8 * sizeof(float)), (GLvoid*)(6 * sizeof(float)));

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

// --------------------------------------------------- //
