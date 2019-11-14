#include <material.h>
#include <GL/glew.h>

// --------------------------------------------------- //

struct Suffer::MaterialInstance::Data {

	GLuint program_ID;

  //Material values
  mathmorra::Vector4 color_;
  u32 albedo_texture_id_;

};

// --------------------------------------------------- //

float* Suffer::MaterialInstance::GetColor() const{

  return data_->color_.GetValues();

}

// --------------------------------------------------- //

u32 Suffer::MaterialInstance::GetAlbedoTexture() const{

  return data_->albedo_texture_id_;

}

// --------------------------------------------------- //

void Suffer::MaterialInstance::SetColor(mathmorra::Vector4 new_color) {

  data_->color_ = new_color;

}

// --------------------------------------------------- //

void Suffer::MaterialInstance::SetAlbedoTexture(ref_ptr<ResourceManager::Texture> texture){

  data_->albedo_texture_id_ = texture->id_;

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

  SetColor((1.0f, 0.0f, 0.0f, 1.0f));
  data_->albedo_texture_id_ = -1;

  switch (params_type_){
  case Suffer::MaterialInstance::kParams_Default:
    
    break;
  case Suffer::MaterialInstance::kParams_Phong:
    
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
