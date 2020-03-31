/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 03-11-2020
* DrawPointDepth Source
*/

#include <draw_point_depth.h>
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

#define MAX_USED_VEC4DATA 29 

// ------------------------------------------------------------------------- //

struct Suffer::DrawPointDepth::Data {

  // Geometry
  s32 vertex_buffer_id_;
  s32 index_buffer_id_;

  /*
  * (mat4) Model matrix
  * (mat4) 6 view matrices
  * (vec3) light_position
  * (float) far_plane
  */
  float u_data_[MAX_USED_VEC4DATA * 4];

};

// ------------------------------------------------------------------------- //

Suffer::DrawPointDepth::DrawPointDepth() {

  cmd_type_ = Command::kCommandType_Render;
  data_ = new Data();

}

// ------------------------------------------------------------------------- //

Suffer::DrawPointDepth::~DrawPointDepth() {

  if (!data_) return;

  delete data_;
  data_ = nullptr;

}

// ------------------------------------------------------------------------- //

void Suffer::DrawPointDepth::SetData(GameObject* go, mathmorra::Vector3 light_position, float far_plane) {

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

    data_->u_data_[112] = light_position.x_;
    data_->u_data_[113] = light_position.y_;
    data_->u_data_[114] = light_position.z_;

    data_->u_data_[115] = far_plane;

  }

  // ---------------------------- SetGeometry ------------------------------ //

}

// ------------------------------------------------------------------------- //

void Suffer::DrawPointDepth::SetMatrices(mathmorra::Matrix4 model, mathmorra::Matrix4 view_mat[6]) {

  u16 index = 0;

  for (u32 i = 0; i < 16; ++i) {
      data_->u_data_[i] = model.m[i];
  }

  for (u32 i = 0; i < 6; ++i) {
      for (u32 j = 0; j < 16; ++j) {
          data_->u_data_[index + 16] = view_mat[i].m[j];
          index++;
      }
  }

}

// ------------------------------------------------------------------------- //

void Suffer::DrawPointDepth::Execute() const {

  GLenum error;
  glEnable(GL_CULL_FACE);


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
    u32 mat_type = 5;
    auto ptr = suffer.resource_manager_.data_->internal_materials_[mat_type];
    // If internal material is not created, creates it
    if (!suffer.resource_manager_.data_->internal_materials_[mat_type].is_created_) {

      // Create vertex shader
      suffer.resource_manager_.data_->internal_materials_[mat_type].vertex_shader_id_ =
        glCreateShader(GL_VERTEX_SHADER);

      // Create geometry shader
      suffer.resource_manager_.data_->internal_materials_[mat_type].geometry_shader_id_ =
          glCreateShader(GL_GEOMETRY_SHADER);

      // Create fragment shader
      suffer.resource_manager_.data_->internal_materials_[mat_type].fragment_shader_id_ =
        glCreateShader(GL_FRAGMENT_SHADER);

      // Get shaders length
      const GLint vertex_size = strlen(suffer.resource_manager_.data_->internal_materials_[mat_type].vertex_shader_);
      const GLint fragment_size = strlen(suffer.resource_manager_.data_->internal_materials_[mat_type].fragment_shader_);
      const GLint geometry_size = strlen(suffer.resource_manager_.data_->internal_materials_[mat_type].geometry_shader_);

      // Upload vertex shader data
      glShaderSource(suffer.resource_manager_.data_->internal_materials_[mat_type].vertex_shader_id_,
        1, &suffer.resource_manager_.data_->internal_materials_[mat_type].vertex_shader_,
        &vertex_size);

      // Upload geometry shader data
      glShaderSource(suffer.resource_manager_.data_->internal_materials_[mat_type].geometry_shader_id_,
          1, &suffer.resource_manager_.data_->internal_materials_[mat_type].geometry_shader_,
          &geometry_size);

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


      // Compile geometry shader
      s16 vrtsh = suffer.resource_manager_.data_->internal_materials_[mat_type].geometry_shader_id_;
      glCompileShader(suffer.resource_manager_.data_->internal_materials_[mat_type].geometry_shader_id_);
      status = 0;
      glGetShaderiv(suffer.resource_manager_.data_->internal_materials_[mat_type].geometry_shader_id_, GL_COMPILE_STATUS, &status);
      log_length = 0;
      info_log.release();
      glGetShaderiv(suffer.resource_manager_.data_->internal_materials_[mat_type].geometry_shader_id_, GL_INFO_LOG_LENGTH, &log_length);
      info_log.alloc(log_length + 1);
      info_log[log_length] = '\0';
      glGetShaderInfoLog(suffer.resource_manager_.data_->internal_materials_[mat_type].geometry_shader_id_, log_length, &log_length, &info_log[0]);
      printf("\n\n%s", info_log.get());
      if (status == GL_FALSE)
          printf("\nERROR: geometry shader not compiled");
      info_log.release();


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
          suffer.resource_manager_.data_->internal_materials_[mat_type].geometry_shader_id_);

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

    //glCullFace(GL_FRONT);

    u32 number_elements = suffer.resource_manager_.data_->internal_index_buffers_[data_->index_buffer_id_].data_.size();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, suffer.resource_manager_.data_->internal_index_buffers_[data_->index_buffer_id_].current_gl_buffer_);

    glDrawElements(GL_TRIANGLES, number_elements, GL_UNSIGNED_SHORT, (GLvoid*)0);

  }

  // --------------------------------- Draw -------------------------------- //

}

// --------------------------------------------------- //
