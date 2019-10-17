#include <draw_geometry.h>
#include <glm.hpp>
#include <gl/glew.h>
#include <data_types.h>

struct DrawGeometry::Data {
	u16 number_elements_;
	u16 indices_;
	glm::vec4 color_;
	glm::vec3 position_;
	glm::vec3 rotation_;
	glm::vec3 scale_;
};

// --------------------------------------------------- //

DrawGeometry::DrawGeometry(){
	data_ = new Data();
}

// --------------------------------------------------- //

DrawGeometry::~DrawGeometry(){
	if (!data_) return;

	delete data_;
	data_ = nullptr;
}

// --------------------------------------------------- //

void DrawGeometry::SetData(EDK3::ref_ptr<GameObject> go){
	//SetTransform(go.get()->GetTransform());
	//SetGeometry(go.get()->GetGeometry());
	//SetMaterial(go.get()->GetMaterial());
}

// --------------------------------------------------- //

void DrawGeometry::SetTransform(Transform t){
	data_->position_ = t.position;
	data_->rotation_ = t.rotation;
	data_->scale_ = t.scale;
}

// --------------------------------------------------- //

void DrawGeometry::SetGeometry(EDK3::ref_ptr<Geometry> geo){
	//data_->number_elements_ = geo.get()->GetElements();
	//data_->indices_ = geo.get()->GetIndices();
}

// --------------------------------------------------- //

void DrawGeometry::SetMaterial(EDK3::ref_ptr<Material> mat){
	//data_->color_ = mat.get()->GetColor();
}

// --------------------------------------------------- //

void DrawGeometry::Execute(){
	
}

// --------------------------------------------------- //