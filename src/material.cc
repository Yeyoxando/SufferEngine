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

glm::vec4 Suffer::Material::MaterialSettings::GetColor() const{
  glm::vec4 color;
  switch (params_type_) {
  case Suffer::Material::MaterialSettings::kParams_Default:
    color = material_params_.default_params_.color_;
    break;
  case Suffer::Material::MaterialSettings::kParams_Phong:
    color = material_params_.phong_params_.color_;
    break;
  case Suffer::Material::MaterialSettings::kParams_NONE:
    break;
  default:
    break;
  }
  return color;
}

// --------------------------------------------------- //

void Suffer::Material::MaterialSettings::SetColor(glm::vec4 new_color) {
  switch (params_type_) {
  case Suffer::Material::MaterialSettings::kParams_Default:
    material_params_.default_params_.color_ = new_color;
    break;
  case Suffer::Material::MaterialSettings::kParams_Phong:
    material_params_.phong_params_.color_ = new_color;
    break;
  case Suffer::Material::MaterialSettings::kParams_NONE:
    break;
  default:
    break;
  }
}

// --------------------------------------------------- //

Suffer::Material::MaterialSettings::PhongParams::PhongParams() {
  
  color_ = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

}

// --------------------------------------------------- //

Suffer::Material::Material() {

	data_ = new Data();

  material_settings_.alloc();
  material_settings_.get()->params_type_ = MaterialSettings::kParams_NONE;
}

// --------------------------------------------------- //

void Suffer::Material::SetMaterialParamsType(MaterialSettings::ParamsType type){
  material_settings_.get()->params_type_ = type;
  switch (type){
  case Suffer::Material::MaterialSettings::kParams_Default:
    material_settings_->SetColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    break;
  case Suffer::Material::MaterialSettings::kParams_Phong:
    material_settings_->SetColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    break;
  case Suffer::Material::MaterialSettings::kParams_NONE:
    break;
  default:
    break;
  }
}

u32 Suffer::Material::GetMaterialParamsType() const{
  return (u32)material_settings_.get()->params_type_;
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
  printf("shit");
}

Suffer::Material::MaterialSettings::Params::Params(){

}

Suffer::Material::MaterialSettings::Params::~Params(){

}
