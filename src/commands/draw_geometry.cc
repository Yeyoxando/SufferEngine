#include <draw_geometry.h>
#include <glm.hpp>
#include <gl/glew.h>
#include <data_types.h>
#include "suffermanager.h"

struct DrawGeometry::Data {
	//Geometry
	u32 number_elements_;
	GLuint indices_ID;
	GLuint vertices_ID;

	//Material
	GLuint program_ID;
	glm::vec4 color_;
	glm::vec3 position_;
	glm::vec3 rotation_;
	glm::vec3 scale_;
};

// --------------------------------------------------- //

DrawGeometry::DrawGeometry() {
	cmd_type_ = Command::kRender;
	data_ = new Data();
}

// --------------------------------------------------- //

DrawGeometry::~DrawGeometry(){
	if (!data_) return;

	delete data_;
	data_ = nullptr;
}

// --------------------------------------------------- //

void DrawGeometry::SetData(GameObject* go){
	SetTransform(go->GetTransform());
	SetGeometry(go->GetGeometry());
	SetMaterial(go->GetMaterial());
}

// --------------------------------------------------- //

void DrawGeometry::SetTransform(Transform t){
	data_->position_ = t.position;
	data_->rotation_ = t.rotation;
	data_->scale_ = t.scale;
}

// --------------------------------------------------- //

void DrawGeometry::SetGeometry(ref_ptr<Geometry> geo){
	data_->number_elements_ = geo.get()->GetNumberElements();
	data_->indices_ID = (GLint)geo.get()->GetIndicesID();
	data_->vertices_ID = (GLint)geo.get()->GetVerticesID();
}

// --------------------------------------------------- //

void DrawGeometry::SetMaterial(ref_ptr<Material> mat){
	data_->color_ = mat.get()->GetColor();
	data_->program_ID = mat.get()->GetProgramID();
}

// --------------------------------------------------- //

void DrawGeometry::Execute() const {

	glUseProgram(data_->program_ID);

	glBindBuffer(GL_ARRAY_BUFFER, data_->vertices_ID);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data_->indices_ID);
	glDrawElements(GL_TRIANGLES, data_->number_elements_, GL_UNSIGNED_BYTE, (GLvoid*)0);
}


// --------------------------------------------------- //