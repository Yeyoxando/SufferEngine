/*
* Author: Diego Ochando Torres <ochandoto@esat-alumni.com>
* Date: 10-12-2019
* MaterialInstance Source
*/

#include "material.h"

// --------------------------------------------------- //

Suffer::MaterialInstance::MaterialInstance() {
  
  current_params_ = nullptr;

}

// --------------------------------------------------- //

void Suffer::MaterialInstance::SetParams(ref_ptr<BaseParams> params){

  assert(params.get() != nullptr && "Error: params is null");
  assert(params->params_type_ != kParams_NONE && "Error: params has no type");

  // Store current params
  current_params_ = params.get();

}

// --------------------------------------------------- //

Suffer::MaterialInstance::~MaterialInstance() {

}

// --------------------------------------------------- //

Suffer::MaterialInstance::BaseParams::BaseParams(){

  params_type_ = kParams_NONE;

}

// --------------------------------------------------- //

Suffer::MaterialInstance::DefaultParams::DefaultParams(){

  params_type_ = kParams_Default;
  color_ = mathmorra::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
  albedo_texture_id_ = -1;

}

// --------------------------------------------------- //

Suffer::MaterialInstance::PhongParams::PhongParams(){

  params_type_ = kParams_Phong;
  color_ = mathmorra::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
  albedo_texture_id_ = -1;

}

// --------------------------------------------------- //
