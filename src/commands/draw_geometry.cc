#include <draw_geometry.h>
#include <gl/glew.h>
#include <data_types.h>
#include <glm.hpp>
#include "suffermanager.h"

struct Suffer::DrawGeometry::Data {
	// Geometry
  const SufferManager::VertexBuffer* vertex_buffer_;
  const SufferManager::IndexBuffer* index_buffer_;

  // Transform 
  mathmorra::Matrix4 model_matrix_;
  mathmorra::Matrix4 view_matrix_;
  mathmorra::Matrix4 projection_matrix_;
 
  // Material 
  struct DefaultParams {
    DefaultParams() {}
    ~DefaultParams() {}
    
    mathmorra::Vector4 color_;
  };

  struct PhongParams{
    PhongParams() {}
    ~PhongParams() {}

    mathmorra::Vector4 color_;
  
  };

  union Params {
    Params() {}
    ~Params() {}

    DefaultParams default_params_;
    PhongParams phong_params_;
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

Suffer::DrawGeometry::~DrawGeometry(){
	if (!data_) return;

	delete data_;
	data_ = nullptr;
}

// --------------------------------------------------- //

void Suffer::DrawGeometry::SetData(GameObject* go){
	SetGeometry(go->GetGeometry());
	SetMaterial(go->GetMaterial());
}

// --------------------------------------------------- //

void Suffer::DrawGeometry::SetModelMatrix(mathmorra::Matrix4 model){
  data_->model_matrix_ = model;
}

// --------------------------------------------------- //

void Suffer::DrawGeometry::SetViewMatrix(mathmorra::Matrix4 view){
  data_->view_matrix_ = view;
}

// --------------------------------------------------- //

void Suffer::DrawGeometry::SetProjectionMatrix(mathmorra::Matrix4 projection){
  data_->projection_matrix_ = projection;
}

// --------------------------------------------------- //

void Suffer::DrawGeometry::SetGeometry(const ref_ptr<Geometry> geo){
	data_->vertex_buffer_ = geo.get()->vertex_buffer_.get();
	data_->index_buffer_ = geo.get()->index_buffer_.get();
}

// --------------------------------------------------- //

void Suffer::DrawGeometry::SetMaterial(const ref_ptr<MaterialInstance> mat){
  data_->internal_material_id_ = (u32)mat->params_type_;

  switch (mat->params_type_){
  case MaterialInstance::ParamsType::kParams_Default:
    data_->material_params_.default_params_.color_ = mat->GetColor();
    break;
  case MaterialInstance::ParamsType::kParams_Phong:
    data_->material_params_.default_params_.color_ = mat->GetColor();
    //Other parameters for phong
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
	u32 id_vertex = SufferManager::instance().IsBufferCreated(data_->vertex_buffer_);
	u32 id_index = SufferManager::instance().IsBufferCreated(data_->index_buffer_);
	u32 number_elements = SufferManager::instance().NumberElements(data_->index_buffer_);

  u32 program_id = SufferManager::instance().IsMaterialCreated(data_->internal_material_id_);

  glUseProgram(program_id);
  error = glGetError();
	
  s32 u_pos = -1;

  // MaterialInstance setting uniforms
  switch (data_->internal_material_id_) {
  case MaterialInstance::kParams_Default: {

    mathmorra::Vector4 color = data_->material_params_.default_params_.color_;
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



  glBindBuffer(GL_ARRAY_BUFFER, id_vertex);

  switch (data_->vertex_buffer_->format_) {
  case SufferManager::VertexBuffer::kVertexFormat_3P:
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    break;
  case SufferManager::VertexBuffer::kVertexFormat_3P_3N:
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (6 * sizeof(float)), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (6 * sizeof(float)), (GLvoid*)(3 * sizeof(float)));
    break;
  default:

    break;
  }
  
  




  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_index);
  error = glGetError();
  glDrawElements(GL_TRIANGLES, number_elements, GL_UNSIGNED_SHORT, (GLvoid*)0);
  error = glGetError();

}

// --------------------------------------------------- //