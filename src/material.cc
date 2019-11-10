#include <material.h>
#include <GL/glew.h>

// --------------------------------------------------- //

struct Suffer::Material::Data {
	GLuint program_ID;
};


// --------------------------------------------------- //

Suffer::Material::MaterialSettings::Params::DefaultParams::DefaultParams(){

  color_ = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

}

// --------------------------------------------------- //

glm::vec4 Suffer::Material::MaterialSettings::Params::DefaultParams::GetColor() {
  return color_;
}

// --------------------------------------------------- //

void Suffer::Material::MaterialSettings::Params::DefaultParams::SetColor(glm::vec4 new_color) {
  color_ = new_color;
}

// --------------------------------------------------- //

Suffer::Material::MaterialSettings::Params::PhongParams::PhongParams() {
  
  color_ = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

}

// --------------------------------------------------- //

glm::vec4 Suffer::Material::MaterialSettings::Params::PhongParams::GetColor() {
  return color_;
}

// --------------------------------------------------- //

void Suffer::Material::MaterialSettings::Params::PhongParams::SetColor(glm::vec4 new_color) {
  color_ = new_color;
}

// --------------------------------------------------- //

Suffer::Material::Material() {

	data_ = new Data();

}

// --------------------------------------------------- //

void Suffer::Material::SetMaterialType(MaterialType type){
  material_type_ = type;
}

u32 Suffer::Material::GetMaterialType(){
  return (u32)material_type_;
}

// --------------------------------------------------- //

Suffer::Material::~Material() {
	if (!data_) return;
	delete data_;
	data_ = nullptr;
}

// --------------------------------------------------- //
