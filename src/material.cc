#include <material.h>
#include <GL/glew.h>

// --------------------------------------------------- //

struct Suffer::MaterialInstance::Data {
	GLuint program_ID;

  //Material values
  mathmorra::Vector4 color_;
};

// --------------------------------------------------- //

float* Suffer::MaterialInstance::GetColor() const{
 // This switch will be needed in other atrributtes that can only be set in specific material, 
  // For example specular in phong will be needed, but not it default
  
  //mathmorra::Vector4 color;
 //switch (params_type_) {
 //case Suffer::MaterialInstance::kParams_Default:
 //  color = data_->color_;
 //  break;
 //case Suffer::MaterialInstance::kParams_Phong:
 //  color = data_->color_;
 //  break;
 //case Suffer::MaterialInstance::kParams_NONE:
 //  break;
 //default:
 //  break;
 //}


  return data_->color_.GetValues();
}

// --------------------------------------------------- //

void Suffer::MaterialInstance::SetColor(mathmorra::Vector4 new_color) {
  // This switch will be needed in other atrributtes that can only be set in specific material, 
  // For example specular in phong will be needed, but not it default
  
  //switch (params_type_) {
  //case Suffer::MaterialInstance::kParams_Default:
  //  data_->color_ = new_color;
  //  break;
  //case Suffer::MaterialInstance::kParams_Phong:
  //  data_->color_ = new_color;
  //  break;
  //case Suffer::MaterialInstance::kParams_NONE:
  //  break;
  //default:
  //  break;
  //}

  data_->color_ = new_color;
}

// --------------------------------------------------- //

Suffer::MaterialInstance::MaterialInstance() {

	data_ = new Data();

  params_type_ = kParams_NONE;
  
  data_->color_ = mathmorra::Vector4(0.0f, 0.0f, 0.0f, 1.0f);
}

// --------------------------------------------------- //

void Suffer::MaterialInstance::SetMaterialParamsType(ParamsType type){
  params_type_ = type;
  switch (params_type_){
  case Suffer::MaterialInstance::kParams_Default:
    SetColor((1.0f, 0.0f, 0.0f, 1.0f));
    break;
  case Suffer::MaterialInstance::kParams_Phong:
    SetColor((1.0f, 0.0f, 0.0f, 1.0f));
    break;
  case Suffer::MaterialInstance::kParams_NONE:
    break;
  default:
    break;
  }
}

// --------------------------------------------------- //

u32 Suffer::MaterialInstance::GetMaterialParamsType() const{
  return params_type_;
}

// --------------------------------------------------- //

Suffer::MaterialInstance::~MaterialInstance() {
	if (!data_) return;
	delete data_;
	data_ = nullptr;
}

// --------------------------------------------------- //
