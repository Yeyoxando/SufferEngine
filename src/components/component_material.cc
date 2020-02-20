/*
* Author: Diego Ochando Torres <ochandoto@esat-alumni.com>
* Date: 12-12-2019
* MaterialInstance Source
*/

#include "component_material.h"

// ------------------------------------------------------------------------- //

void Suffer::MaterialComponent::SetParams(ref_ptr<BaseParams> params){

  assert(params.get() != nullptr && "Error: params is null");
  assert(params->params_type_ != kParamsType_Invalid && "Error: params has no type");

  // Store current params
  current_params_ = params.get();

}

// ------------------------------------------------------------------------- //

Suffer::MaterialComponent::~MaterialComponent(){


}

// ------------------------------------------------------------------------- //

Suffer::MaterialComponent::BaseParams::BaseParams() {

  params_type_ = kParamsType_Invalid;

}

// ------------------------------------------------------------------------- //

Suffer::MaterialComponent::DefaultParams::DefaultParams() {

  params_type_ = kParamsType_Default;
  color_ = mathmorra::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
  albedo_texture_id_ = -1;

}

// ------------------------------------------------------------------------- //

Suffer::MaterialComponent::PhongParams::PhongParams() {

  params_type_ = kParamsType_Phong;
  color_ = mathmorra::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
  u_time_ = 0.0f;

}

// ------------------------------------------------------------------------- //

Suffer::MaterialComponent::RenderToTextureParams::RenderToTextureParams(){

  params_type_ = kParamsType_RenderToTexture;
  color_ = mathmorra::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
  albedo_texture_id_ = -1;

}

// ------------------------------------------------------------------------- //
