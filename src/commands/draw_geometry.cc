/*
 * Author: Diego Ochando Torres <ochandoto@esat-alumni.com>
 * Date: 15-10-2019
 * Draw Geometry command Header
 */


#include <draw_geometry.h>
#include <gl/glew.h>
#include <data_types.h>
#include <glm.hpp>
#include "suffermanager.h"
#include "internal_resource_manager.h"
#include "common_definitions.h"

struct Suffer::DrawGeometry::Data {
  // Geometry
  const Suffer::ResourceManager::VertexBuffer* vertex_buffer_;
  const Suffer::ResourceManager::IndexBuffer* index_buffer_;


  // Transform 
  mathmorra::Matrix4 model_matrix_;
  mathmorra::Matrix4 view_matrix_;
  mathmorra::Matrix4 projection_matrix_;

  // Material 
  struct DefaultParams {

  };

  struct PhongParams {

  };

  union Params {

    DefaultParams default_params_;
    PhongParams phong_params_;

    //Common parameters
    float color_[4];
  };

  u32 internal_material_id_;
  Params material_params_;
};

// --------------------------------------------------- //

Suffer::DrawGeometry::DrawGeometry() {
  cmd_type_ = Command::kRender;
  data_ = new Data();
}

// --------------------------------------------------- //

Suffer::DrawGeometry::~DrawGeometry() {
  if (!data_) return;

  delete data_;
  data_ = nullptr;
}

// --------------------------------------------------- //

void Suffer::DrawGeometry::SetData(GameObject* go) {
  SetGeometry(go->GetGeometry());
  SetMaterial(go->GetMaterial());
}

// --------------------------------------------------- //

void Suffer::DrawGeometry::SetModelMatrix(mathmorra::Matrix4 model) {
  data_->model_matrix_ = model;
}

// --------------------------------------------------- //

void Suffer::DrawGeometry::SetViewMatrix(mathmorra::Matrix4 view) {
  data_->view_matrix_ = view;
}

// --------------------------------------------------- //

void Suffer::DrawGeometry::SetProjectionMatrix(mathmorra::Matrix4 projection) {
  data_->projection_matrix_ = projection;
}

// --------------------------------------------------- //

void Suffer::DrawGeometry::SetGeometry(const ref_ptr<Geometry> geo) {
  data_->vertex_buffer_ = geo.get()->vertex_buffer_.get();
  data_->index_buffer_ = geo.get()->index_buffer_.get();
}

// --------------------------------------------------- //

void Suffer::DrawGeometry::SetMaterial(const ref_ptr<MaterialInstance> mat) {
  data_->internal_material_id_ = (u32)mat->params_type_;


  memcpy(data_->material_params_.color_, mat->GetColor(), sizeof(float) * 4);

  switch (mat->params_type_) {
  case MaterialInstance::ParamsType::kParams_Default:
    //data_->material_params_.default_params_.
    break;
  case MaterialInstance::ParamsType::kParams_Phong:
    //Other parameters for phong
    //data_->material_params_.phong_params_.
    break;
  case MaterialInstance::ParamsType::kParams_NONE:
#ifdef ASSERT
    assert(mat->params_type_ != MaterialInstance::kParams_NONE && "MaterialInstance type not set");
#endif
    break;
  default:
    break;
  }

  //data_->material_ = mat.get();

}

// --------------------------------------------------- //

void Suffer::DrawGeometry::Execute() const {

  GLenum error;
  
  // ---------------------- IsBufferCreated (Vertex) ----------------------- //

  {

#ifdef ASSERT
    assert(data_->vertex_buffer_ != nullptr);
#endif
    if (data_->vertex_buffer_->id_ < 0) return;

    s32 id_vertex = data_->vertex_buffer_->id_;

    if (suffer.resource_manager_.data_->internal_vertex_buffers_[id_vertex].gpu_version_ == 0) {
      glGenBuffers(1, &suffer.resource_manager_.data_->internal_vertex_buffers_[id_vertex].current_gl_buffer_);
      error = glGetError();
      glBindBuffer(GL_ARRAY_BUFFER, suffer.resource_manager_.data_->internal_vertex_buffers_[id_vertex].current_gl_buffer_);
      error = glGetError();

      glBufferData(GL_ARRAY_BUFFER,
        suffer.resource_manager_.data_->internal_vertex_buffers_[id_vertex].data_.sizeInBytes(),
        suffer.resource_manager_.data_->internal_vertex_buffers_[id_vertex].data_.get(),
        GL_STATIC_DRAW);
      error = glGetError();

      suffer.resource_manager_.data_->internal_vertex_buffers_[id_vertex].gpu_version_ = suffer.resource_manager_.data_->internal_vertex_buffers_[id_vertex].version_;
    }

    if (suffer.resource_manager_.data_->internal_vertex_buffers_[id_vertex].gpu_version_ < suffer.resource_manager_.data_->internal_vertex_buffers_[id_vertex].version_) {
      glBindBuffer(GL_ARRAY_BUFFER, suffer.resource_manager_.data_->internal_vertex_buffers_[id_vertex].current_gl_buffer_);
      error = glGetError();

      glBufferData(GL_ARRAY_BUFFER,
        suffer.resource_manager_.data_->internal_vertex_buffers_[id_vertex].data_.sizeInBytes(),
        suffer.resource_manager_.data_->internal_vertex_buffers_[id_vertex].data_.get(),
        GL_STATIC_DRAW);
      error = glGetError();

      suffer.resource_manager_.data_->internal_vertex_buffers_[id_vertex].gpu_version_ = suffer.resource_manager_.data_->internal_vertex_buffers_[id_vertex].version_;
    }

  }

  // ---------------------- IsBufferCreated (Vertex) ----------------------- //

  // ----------------------------------------------------------------------- //

  // ----------------------- IsBufferCreated (Index) ----------------------- //

  {
  
#ifdef ASSERT
    assert(data_->index_buffer_ != nullptr);
#endif
    if (data_->index_buffer_->id_ < 0) return;
    s32 id_index = data_->index_buffer_->id_;
    if (suffer.resource_manager_.data_->internal_index_buffers_[id_index].gpu_version_ == 0) {
      glGenBuffers(1, &suffer.resource_manager_.data_->internal_index_buffers_[id_index].current_gl_buffer_);
      error = glGetError();
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, suffer.resource_manager_.data_->internal_index_buffers_[id_index].current_gl_buffer_);
      error = glGetError();

      glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        suffer.resource_manager_.data_->internal_index_buffers_[id_index].data_.sizeInBytes(),
        suffer.resource_manager_.data_->internal_index_buffers_[id_index].data_.get(),
        GL_STATIC_DRAW);
      error = glGetError();
    }

    if (suffer.resource_manager_.data_->internal_index_buffers_[id_index].gpu_version_ < suffer.resource_manager_.data_->internal_index_buffers_[id_index].version_) {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, suffer.resource_manager_.data_->internal_index_buffers_[id_index].current_gl_buffer_);
      error = glGetError();

      glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        suffer.resource_manager_.data_->internal_index_buffers_[id_index].data_.sizeInBytes(),
        suffer.resource_manager_.data_->internal_index_buffers_[id_index].data_.get(),
        GL_STATIC_DRAW);
      error = glGetError();
    }

    suffer.resource_manager_.data_->internal_index_buffers_[id_index].gpu_version_ = suffer.resource_manager_.data_->internal_index_buffers_[id_index].version_;

  }

  // ----------------------- IsBufferCreated (Index) ----------------------- //

  // ----------------------------------------------------------------------- //

  // -------------------------- IsMaterialCreated -------------------------- //

  {
  
    u32 mat_id = data_->internal_material_id_;

    // If internal material is not created, creates it
    if (!suffer.resource_manager_.data_->internal_materials_[mat_id].is_created_) {
      // Create vertex shader
      suffer.resource_manager_.data_->internal_materials_[mat_id].vertex_shader_id_ =
        glCreateShader(GL_VERTEX_SHADER);
      error = glGetError();

      // Create fragment shader
      suffer.resource_manager_.data_->internal_materials_[mat_id].fragment_shader_id_ =
        glCreateShader(GL_FRAGMENT_SHADER);
      error = glGetError();

      // Get shaders length
      const GLint vertex_size = strlen(suffer.resource_manager_.data_->internal_materials_[mat_id].vertex_shader_);
      const GLint fragment_size = strlen(suffer.resource_manager_.data_->internal_materials_[mat_id].fragment_shader_);

      // Upload vertex shader data
      glShaderSource(suffer.resource_manager_.data_->internal_materials_[mat_id].vertex_shader_id_,
        1, &suffer.resource_manager_.data_->internal_materials_[mat_id].vertex_shader_,
        &vertex_size);
      error = glGetError();

      // Upload fragment shader data
      glShaderSource(suffer.resource_manager_.data_->internal_materials_[mat_id].fragment_shader_id_,
        1, &suffer.resource_manager_.data_->internal_materials_[mat_id].fragment_shader_, &fragment_size);
      error = glGetError();

      // Compile vertex shader
      glCompileShader(suffer.resource_manager_.data_->internal_materials_[mat_id].vertex_shader_id_);
      error = glGetError();

      GLint status = 0;
      glGetShaderiv(suffer.resource_manager_.data_->internal_materials_[mat_id].vertex_shader_id_, GL_COMPILE_STATUS, &status);
      GLint log_length = 0;
      glGetShaderiv(suffer.resource_manager_.data_->internal_materials_[mat_id].vertex_shader_id_, GL_INFO_LOG_LENGTH, &log_length);
      Array<char> info_log;
      info_log.alloc(log_length + 1);
      info_log[log_length] = '\0';
      glGetShaderInfoLog(suffer.resource_manager_.data_->internal_materials_[mat_id].vertex_shader_id_, log_length, &log_length, &info_log[0]);

      printf("\n\n%s", info_log.get());
      if (status == GL_FALSE)
        printf("\nERROR: vertex shader not compiled");

      // Compile fragment shader
      glCompileShader(suffer.resource_manager_.data_->internal_materials_[mat_id].fragment_shader_id_);
      error = glGetError();
      status = 0;
      glGetShaderiv(suffer.resource_manager_.data_->internal_materials_[mat_id].fragment_shader_id_, GL_COMPILE_STATUS, &status);
      log_length = 0;
      info_log.release();
      glGetShaderiv(suffer.resource_manager_.data_->internal_materials_[mat_id].fragment_shader_id_, GL_INFO_LOG_LENGTH, &log_length);
      info_log.alloc(log_length + 1);
      info_log[log_length] = '\0';
      glGetShaderInfoLog(suffer.resource_manager_.data_->internal_materials_[mat_id].fragment_shader_id_, log_length, &log_length, &info_log[0]);
      printf("\n\n%s", info_log.get());
      if (status == GL_FALSE)
        printf("\nERROR: fragment shader not compiled");
      info_log.release();


      // Create program
      suffer.resource_manager_.data_->internal_materials_[mat_id].current_program_ = glCreateProgram();
      error = glGetError();

      // Attach shaders
      glAttachShader(suffer.resource_manager_.data_->internal_materials_[mat_id].current_program_,
        suffer.resource_manager_.data_->internal_materials_[mat_id].vertex_shader_id_);
      error = glGetError();

      glAttachShader(suffer.resource_manager_.data_->internal_materials_[mat_id].current_program_,
        suffer.resource_manager_.data_->internal_materials_[mat_id].fragment_shader_id_);
      error = glGetError();

      // Link program
      glLinkProgram(suffer.resource_manager_.data_->internal_materials_[mat_id].current_program_);
      error = glGetError();

      // Mark internal material as created
      suffer.resource_manager_.data_->internal_materials_[mat_id].is_created_ = true;
    }

  }

  // -------------------------- IsMaterialCreated -------------------------- //

  // ----------------------------------------------------------------------- //

  // ------------------------------- Uniforms ------------------------------ //

  u32 program_id = suffer.resource_manager_.data_->internal_materials_[data_->internal_material_id_].current_program_;

  {

    glUseProgram(program_id);
    error = glGetError();

    s32 u_pos = -1;

    // MaterialInstance setting uniforms
    switch (data_->internal_material_id_) {
    case MaterialInstance::kParams_Default: {
      mathmorra::Vector4 color(data_->material_params_.color_);
      u_pos = glGetUniformLocation(program_id, "u_color");
      if (u_pos < 0) {
        printf("\nERROR: u_color uniform not exists.");
        //return;
      }

      glUniform4f(u_pos, color.x_, color.y_, color.z_, color.w_);
      u_pos = -1;
    }
    break;
    case MaterialInstance::kParams_Phong:

      break;
    case MaterialInstance::kParams_NONE:
      break;
    default:
      break;
    }

    //Matrix uniforms
    u_pos = glGetUniformLocation(program_id, "u_m_matrix");
    if (u_pos < 0) {
      printf("\nERROR: model matrix uniform not exists.");
      return;
    }

    glUniformMatrix4fv(u_pos, 1, GL_FALSE, data_->model_matrix_.m);
    u_pos = -1;

    u_pos = glGetUniformLocation(program_id, "u_v_matrix");
    if (u_pos < 0) {
      printf("\nERROR: view matrix uniform not exists.");
      return;
    }

    glUniformMatrix4fv(u_pos, 1, GL_FALSE, data_->view_matrix_.m);
    u_pos = -1;

    u_pos = glGetUniformLocation(program_id, "u_p_matrix");
    if (u_pos < 0) {
      printf("\nERROR: projection matrix uniform not exists.");
      return;
    }

    glUniformMatrix4fv(u_pos, 1, GL_FALSE, data_->projection_matrix_.m);
    u_pos = -1;

  }

  // ------------------------------- Uniforms ------------------------------ //

  // ----------------------------------------------------------------------- //

  // --------------------------- Vertex Attributes ------------------------- //

  {

    glBindBuffer(GL_ARRAY_BUFFER, suffer.resource_manager_.data_->internal_vertex_buffers_[data_->vertex_buffer_->id_].current_gl_buffer_);

    switch (data_->vertex_buffer_->format_) {
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

    u32 number_elements = suffer.resource_manager_.data_->internal_index_buffers_[data_->index_buffer_->id_].data_.size();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, suffer.resource_manager_.data_->internal_index_buffers_[data_->index_buffer_->id_].current_gl_buffer_);
    error = glGetError();
    glDrawElements(GL_TRIANGLES, number_elements, GL_UNSIGNED_SHORT, (GLvoid*)0);
    error = glGetError();

  }

  // --------------------------------- Draw -------------------------------- //

}

// --------------------------------------------------- //