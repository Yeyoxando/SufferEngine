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

Suffer::MaterialComponent::BaseParams* Suffer::MaterialComponent::CurrentParams(){

  return current_params_.get();

}

// ------------------------------------------------------------------------- //

Suffer::MaterialComponent::~MaterialComponent(){


}

// ------------------------------------------------------------------------- //

Suffer::MaterialComponent::BaseParams::BaseParams() {

  params_type_ = kParamsType_Invalid;

}

// ------------------------------------------------------------------------- //

Suffer::MaterialComponent::BlinnPhongParams::BlinnPhongParams() {

  params_type_ = kParamsType_BlinnPhong;
  color_ = mathmorra::Vector4(1.0f, 1.0f, 1.0f, 1.0f);

  specular_strength_ = 1.0f;
  specular_pow_ = 32.0f;
  reflection_strength_ = 0.0f;

  u_time_ = 0.0f;
  tiling_ = mathmorra::Vector2(1.0f, 1.0f);

  // Set default engine textures
  albedo_texture_id_ = 0;
  specular_texture_id_ = 0;

}

// ------------------------------------------------------------------------- //

Suffer::MaterialComponent::RenderToTextureParams::RenderToTextureParams(){

  params_type_ = kParamsType_RenderToTexture;
  color_ = mathmorra::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
  albedo_texture_id_ = -1;

}

// ------------------------------------------------------------------------- //
