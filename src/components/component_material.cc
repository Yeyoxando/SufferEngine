/*
* Author: Diego Ochando Torres <ochandoto@esat-alumni.com>
* Date: 12-12-2019
* MaterialInstance Source
*/

#include "component_material.h"

// ------------------------------------------------------------------------- //

void Suffer::Material::SetParams(ref_ptr<BaseParams> params){

  assert(params.get() != nullptr && "Error: params is null");
  assert(params->params_type_ != kParams_NONE && "Error: params has no type");

  // Store current params
  current_params_ = params.get();

}

// ------------------------------------------------------------------------- //

Suffer::Material::~Material(){


}

// ------------------------------------------------------------------------- //



// ------------------------------------------------------------------------- //

Suffer::Material::BaseParams::BaseParams() {

  params_type_ = kParams_NONE;

}

// ------------------------------------------------------------------------- //

Suffer::Material::DefaultParams::DefaultParams() {

  params_type_ = kParams_Default;
  color_ = mathmorra::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
  albedo_texture_id_ = -1;

}

// ------------------------------------------------------------------------- //

Suffer::Material::UnlitParams::UnlitParams() {

  params_type_ = kParams_Unlit;
  color_ = mathmorra::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
  u_time_ = 0.0f;

}

// ------------------------------------------------------------------------- //
