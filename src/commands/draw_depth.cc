/*
 * Author: Diego Ochando Torres <ochandoto@esat-alumni.com>
 * Date: 03-03-2020
 * Draw Depth command source
 */

#include <draw_depth.h>
#include <gl/glew.h>
#include "time.h"
#include <data_types.h>
#include "scene.h"
#include "vector4.h"
#include "suffermanager.h"
#include "internal_resource_manager.h"
#include "component_geometry.h"
#include "component_material.h"
#include "common_definitions.h"

#define MAX_USED_TEXTURES 5
 //12 for matrixes
#define MAX_USED_VEC4DATA 12 

// ------------------------------------------------------------------------- //

struct Suffer::DrawDepth::Data {

  // Geometry
  s32 vertex_buffer_id_;
  s32 index_buffer_id_;

  // Contains the model, view and projections matrixes
  float u_data_[MAX_USED_VEC4DATA * 4];

};

// ------------------------------------------------------------------------- //

Suffer::DrawDepth::DrawDepth() {

  cmd_type_ = Command::kCommandType_Render;
  data_ = new Data();

}

// ------------------------------------------------------------------------- //

Suffer::DrawDepth::~DrawDepth() {

  if (!data_) return;

  delete data_;
  data_ = nullptr;

}

// ------------------------------------------------------------------------- //

void Suffer::DrawDepth::SetData(GameObject* go) {

  // ---------------------------- SetGeometry ------------------------------ //

  {

    if (!go->HasComponent(Component::ComponentKind::kComponentKind_Geometry) ||
      go->HasComponent(Component::ComponentKind::kComponentKind_Light)) {
      data_->vertex_buffer_id_ = -1;
      data_->index_buffer_id_ = -1;
    }
    else {

      auto geometry_component = go->GetComponent(Suffer::Component::kComponentKind_Geometry);
      GeometryComponent* geometry_ = reinterpret_cast<GeometryComponent*>(geometry_component);

      data_->vertex_buffer_id_ = geometry_->vertex_buffer_id_;
      data_->index_buffer_id_ = geometry_->index_buffer_id_;

    }
  }

  // ---------------------------- SetGeometry ------------------------------ //

}

// ------------------------------------------------------------------------- //

void Suffer::DrawDepth::SetMatrix(mathmorra::Matrix4 model, mathmorra::Matrix4 view, mathmorra::Matrix4 projection) {

  for (u32 i = 0; i < 16; ++i) {
    // Model will be in u_data[0] to u_data[3]
    data_->u_data_[i] = model.m[i];
    // View will be in u_data[4] to u_data[7]
    data_->u_data_[i + 16] = view.m[i];
    // Projection will be in u_data[8] to u_data[11]
    data_->u_data_[i + 32] = projection.m[i];
  }

}

// ------------------------------------------------------------------------- //

void Suffer::DrawDepth::Execute() const {

  GLenum error;


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

  // -------------------------- IsMaterialCreated -------------------------- //

  {

    // 4 equals to resource manager internal depth material
    u32 mat_type = 4;

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

    glUniform4fv(u_pos, MAX_USED_VEC4DATA, data_->u_data_);
    u_pos = -1;

  }

  // ------------------------------- Uniforms ------------------------------ //

  // ----------------------------------------------------------------------- //

  // --------------------------- Vertex Attributes ------------------------- //

  {

    // We only need position

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

// --------------------------------------------------- //
