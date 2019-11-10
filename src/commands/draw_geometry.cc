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
	glm::vec3 position_;
	glm::vec3 rotation_;
	glm::vec3 scale_;
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
	SetTransform(go->GetTransform());
	SetGeometry(go->GetGeometry());
	SetMaterial(go->GetMaterial());
}

// --------------------------------------------------- //

void Suffer::DrawGeometry::SetTransform(Transform t){
	data_->position_ = t.position;
	data_->rotation_ = t.rotation;
	data_->scale_ = t.scale;
}

// --------------------------------------------------- //

void Suffer::DrawGeometry::SetGeometry(ref_ptr<Geometry> geo){
	data_->vertex_buffer_ = geo.get()->vertex_buffer_;
	data_->index_buffer_ = geo.get()->index_buffer_;
}

// --------------------------------------------------- //

void Suffer::DrawGeometry::SetMaterial(ref_ptr<Material> mat){
  data_->material_ = mat;
}

// --------------------------------------------------- //

void Suffer::DrawGeometry::Execute() const {

	u32 id_vertex = SufferManager::instance().IsBufferCreated(data_->vertex_buffer_);
	u32 id_index = SufferManager::instance().IsBufferCreated(data_->index_buffer_);
	u32 number_elements = SufferManager::instance().NumberElements(data_->index_buffer_);

  u32 program_id = SufferManager::instance().IsMaterialCreated(data_->material_);

  glUseProgram(program_id);
	
 	glBindBuffer(GL_ARRAY_BUFFER, id_vertex);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_index);
	glDrawElements(GL_TRIANGLES, number_elements, GL_UNSIGNED_BYTE, (GLvoid*)0);

}

// --------------------------------------------------- //