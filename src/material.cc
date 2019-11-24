/*
* Author: Diego Ochando Torres <ochandoto@esat-alumni.com>
* Date: 10-12-2019
* MaterialInstance Source
*/

#include "material.h"
#include "internal_material.h"

// --------------------------------------------------- //

//mathmorra::Vector4 Suffer::MaterialInstance::GetColor() const{
//
//  return data_->color_;
//
//}
//
//// --------------------------------------------------- //
//
//u32 Suffer::MaterialInstance::GetAlbedoTexture() const{
//
//  return data_->albedo_texture_id_;
//
//}

// --------------------------------------------------- //

//void Suffer::MaterialInstance::SetColor(mathmorra::Vector4 new_color) {
//
//  data_->color_ = new_color;
//
//}
//
//// --------------------------------------------------- //
//
//void Suffer::MaterialInstance::SetAlbedoTexture(ref_ptr<ResourceManager::Texture> texture){
//
//  data_->albedo_texture_id_ = texture->id_;
//
//}
//
// --------------------------------------------------- //

Suffer::MaterialInstance::MaterialInstance() {

	data_ = new Data();
  
  data_->current_params_ = nullptr;

}

// --------------------------------------------------- //

u32 Suffer::MaterialInstance::GetMaterialParamsType() const{

  if(data_->current_params_)
    return data_->current_params_->params_type_;

  return kParams_NONE;

}

// --------------------------------------------------- //

Suffer::MaterialInstance::BaseParams* Suffer::MaterialInstance::GetMaterialParams(){
  
  if(data_->current_params_ != nullptr)
    return data_->current_params_;

  return nullptr;

}

// --------------------------------------------------- //

void Suffer::MaterialInstance::SetDefaultParams(ref_ptr<DefaultParams> params){

  assert(params.get() != nullptr && "Error: params is null");

  params->params_type_ = kParams_Default;
  data_->current_params_ = params.get();

}

// --------------------------------------------------- //

void Suffer::MaterialInstance::SetPhongParams(ref_ptr<PhongParams> params){

  assert(params.get() != nullptr && "Error: params is null");

  params->params_type_ = kParams_Phong;
  data_->current_params_ = params.get();

}

// --------------------------------------------------- //

Suffer::MaterialInstance::~MaterialInstance() {

	if (!data_) return;
	delete data_;
	data_ = nullptr;

}

// --------------------------------------------------- //

Suffer::MaterialInstance::BaseParams::BaseParams(){

  params_type_ = kParams_NONE;

}

// --------------------------------------------------- //

Suffer::MaterialInstance::DefaultParams::DefaultParams(){

  color_ = mathmorra::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
  albedo_texture_id_ = -1;

}

// --------------------------------------------------- //
