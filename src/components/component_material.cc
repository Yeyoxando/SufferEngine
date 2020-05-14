/*
* Author: Diego Ochando Torres <ochandoto@esat-alumni.com>
* Date: 12-12-2019
* MaterialInstance Source
*/

#include "component_material.h"
#include "math_utils.h"


// --------------------------------------------------- //

Suffer::MaterialComponent::MaterialComponent() : Component(Component::kComponentKind_Material) {

  current_params_number_ = 0;

}

// ------------------------------------------------------------------------- //

void Suffer::MaterialComponent::AddParams(ref_ptr<BaseParams> params){

  assert(params.get() != nullptr && "Error: params is null");
  assert(params->params_type_ != kParamsType_Invalid && "Error: params has no type");

  // Store current params
  current_params_.push_back(params);
  current_params_number_++;

}

// ------------------------------------------------------------------------- //

Suffer::MaterialComponent::BaseParams* Suffer::MaterialComponent::CurrentParams(u32 params_id){

  return current_params_[params_id].get();

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
  reflection_texture_id_ = 1;

  use_albedo_texture_ = false;
  use_specular_texture_ = false;
  use_reflection_texture_ = false;

}

// ------------------------------------------------------------------------- //

void Suffer::MaterialComponent::BlinnPhongParams::SetAlbedoTexture(ResourceManager::Texture * texture){

  albedo_texture_id_ = texture->id_;
  use_albedo_texture_ = true;

}

// ------------------------------------------------------------------------- //

void Suffer::MaterialComponent::BlinnPhongParams::SetSpecularTexture(ResourceManager::Texture * texture){

  specular_texture_id_ = texture->id_;
  use_specular_texture_ = true;

}

// ------------------------------------------------------------------------- //

void Suffer::MaterialComponent::BlinnPhongParams::SetReflectionTexture(ResourceManager::Texture* texture, float reflection_strength){

  reflection_texture_id_ = texture->id_;
  use_reflection_texture_ = true;
  reflection_strength_ = ThiefUtils::Math::Clamp(reflection_strength, 0.0f, 1.0f);

}

// ------------------------------------------------------------------------- //

Suffer::MaterialComponent::RenderToTextureParams::RenderToTextureParams(){

  params_type_ = kParamsType_RenderToTexture;
  color_ = mathmorra::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
  albedo_texture_id_ = -1;

}

// ------------------------------------------------------------------------- //
