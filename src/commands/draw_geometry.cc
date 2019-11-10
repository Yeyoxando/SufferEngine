#include <draw_geometry.h>
#include <glm.hpp>
#include <gl/glew.h>
#include <data_types.h>
#include "suffermanager.h"

struct Suffer::DrawGeometry::Data {
	// Geometry
	ref_ptr<SufferManager::VertexBuffer> vertex_buffer_;
	ref_ptr<SufferManager::IndexBuffer> index_buffer_;

	// Material
  ref_ptr<Material> material_;

  // Transform 
  glm::mat4 model_matrix_;
	glm::mat4 view_matrix_;
	glm::mat4 projection_matrix_;
  
  
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

void Suffer::DrawGeometry::SetModelMatrix(glm::mat4 model){
  data_->model_matrix_ = model;
}

// --------------------------------------------------- //

void Suffer::DrawGeometry::SetViewMatrix(glm::mat4 view){
  data_->view_matrix_ = view;
}

// --------------------------------------------------- //

void Suffer::DrawGeometry::SetProjectionMatrix(glm::mat4 projection){
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
    //data_->mat_params_->default_params_->color_ = mat->material_settings_
    break;
  case Material::kBasicMaterials_Phong:

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
	
  //const Vector4 color = //materialsettings
  //float colorAux[3] = { color.x, color.y, color.z };
  //
  //int u_pos =  glGetUniformLocation(program_id_, name)
  //if (u_pos < 0) {
  //  printf("\nERROR: uniform not exists.");
  //  return false;
  //}
  //
  //glUniform4f(uniform_pos, value[0], value[1], value[2], value[3]);



  glBindBuffer(GL_ARRAY_BUFFER, id_vertex);
  error = glGetError();
  glEnableVertexAttribArray(0);
  error = glGetError();
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
  error = glGetError();
	
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_index);
  error = glGetError();
  glDrawElements(GL_TRIANGLES, number_elements, GL_UNSIGNED_SHORT, (GLvoid*)0);
  error = glGetError();

}

// --------------------------------------------------- //