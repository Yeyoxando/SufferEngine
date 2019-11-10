#include <material.h>
#include <GL/glew.h>

// --------------------------------------------------- //

struct Suffer::Material::Data {
	GLuint program_ID;
};


// --------------------------------------------------- //

Suffer::Material::MaterialSettings::DefaultParams::DefaultParams(){

  color_ = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

}

// --------------------------------------------------- //

glm::vec4 Suffer::Material::MaterialSettings::DefaultParams::GetColor() {
  return color_;
}

// --------------------------------------------------- //

void Suffer::Material::MaterialSettings::DefaultParams::SetColor(glm::vec4 new_color) {
  color_ = new_color;
}

// --------------------------------------------------- //

Suffer::Material::MaterialSettings::PhongParams::PhongParams() {
  
  color_ = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

}

// --------------------------------------------------- //

glm::vec4 Suffer::Material::MaterialSettings::PhongParams::GetColor() {
  return color_;
}

// --------------------------------------------------- //

void Suffer::Material::MaterialSettings::PhongParams::SetColor(glm::vec4 new_color) {
  color_ = new_color;
}

// --------------------------------------------------- //

Suffer::Material::Material() {

	data_ = new Data();

  material_type_ = kBasicMaterials_NONE;
  material_settings_.alloc();
}

// --------------------------------------------------- //

void Suffer::Material::SetMaterialType(MaterialType type){
  material_type_ = type;
  switch (type){
  case Suffer::Material::kBasicMaterials_Default:
    material_settings_->material_params_.default_params_.SetColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    break;
  case Suffer::Material::kBasicMaterials_Phong:
    material_settings_->material_params_.phong_params_.SetColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    break;
  case Suffer::Material::kBasicMaterials_NONE:
    break;
  default:
    break;
  }
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

Suffer::Material::MaterialSettings::MaterialSettings(){

}

Suffer::Material::MaterialSettings::~MaterialSettings(){

}

Suffer::Material::MaterialSettings::Params::Params(){

}

Suffer::Material::MaterialSettings::Params::~Params(){

}
