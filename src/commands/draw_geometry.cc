#include <draw_geometry.h>
#include <gl/glew.h>
#include <data_types.h>
#include <glm.hpp>
#include "suffermanager.h"

struct Suffer::DrawGeometry::Data {
	// Geometry
	ref_ptr<SufferManager::VertexBuffer> vertex_buffer_;
	ref_ptr<SufferManager::IndexBuffer> index_buffer_;

	// Material
  ref_ptr<Material> material_;

  // Transform 
  mathmorra::Matrix4 model_matrix_;
  mathmorra::Matrix4 view_matrix_;
  mathmorra::Matrix4 projection_matrix_;
  
  
  struct DefaultParams {
    glm::vec4 color_;
  };

  struct PhongParams {
    glm::vec4 color_;
  };

  union MaterialParams {
    DefaultParams default_params_;
    PhongParams phong_params_;
  };


  MaterialParams mat_params_;
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

void Suffer::DrawGeometry::SetGeometry(ref_ptr<Geometry> geo){
	data_->vertex_buffer_ = geo.get()->vertex_buffer_;
	data_->index_buffer_ = geo.get()->index_buffer_;
}

// --------------------------------------------------- //

void Suffer::DrawGeometry::SetMaterial(ref_ptr<Material> mat){
  data_->material_ = mat;

  switch (mat.get()->material_type_){
  case Material::kBasicMaterials_Default:
    data_->mat_params_.default_params_.color_ = mat->material_settings_.get()->material_params_.default_params_.GetColor();
    break;
  case Material::kBasicMaterials_Phong:
    data_->mat_params_.phong_params_.color_ = mat->material_settings_.get()->material_params_.phong_params_.GetColor();
    break;
  case Material::kBasicMaterials_NONE:

    break;
  default:
    break;
  }
}

// --------------------------------------------------- //

void Suffer::DrawGeometry::Execute() const {
#ifdef ASSERT
  assert(data_->material_->material_type_ != Material::kBasicMaterials_NONE && "Material type not set");
#endif


  GLenum error;
	u32 id_vertex = SufferManager::instance().IsBufferCreated(data_->vertex_buffer_);
	u32 id_index = SufferManager::instance().IsBufferCreated(data_->index_buffer_);
	u32 number_elements = SufferManager::instance().NumberElements(data_->index_buffer_);

  u32 program_id = SufferManager::instance().IsMaterialCreated(data_->material_);

  glUseProgram(program_id);
  error = glGetError();
	
  s32 u_pos = -1;

  // Material setting uniforms
  switch (data_->material_->material_type_) {
  case Material::kBasicMaterials_Default:
    glm::vec4 color = data_->mat_params_.default_params_.color_;

    u_pos = glGetUniformLocation(program_id, "u_color");
    if (u_pos < 0) {
      printf("\nERROR: u_color uniform not exists.");
      return;
    }

    glUniform4f(u_pos, color.r, color.g, color.b, color.a);
    u_pos = -1;
    break;
  case Material::kBasicMaterials_Phong:
    
    break;
  case Material::kBasicMaterials_NONE:
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
  error = glGetError();
  glEnableVertexAttribArray(0);
  error = glGetError();
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
  error = glGetError();


  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);


  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_index);
  error = glGetError();
  glDrawElements(GL_TRIANGLES, number_elements, GL_UNSIGNED_SHORT, (GLvoid*)0);
  error = glGetError();

}

// --------------------------------------------------- //