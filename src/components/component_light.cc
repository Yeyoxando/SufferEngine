/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 02-27-2019
* ComponentLight Source
*/

#include "component_light.h"
#include "common_definitions.h"
#include "shadow_map.h"
#include "internal_resource_manager.h"
#include "internal_suffermanager.h"
#include "suffermanager.h"

void Suffer::LightComponent::Init(LightKind kind){

    switch (kind){
      case Suffer::LightComponent::kLightKind_Invalid:
          break;
      case Suffer::LightComponent::kLightKind_Directional: {
          ref_ptr<LightManager::DirectionalLight> dir_light;
          dir_light.alloc();
          dir_light->SetActive(false);
          reference_ = dir_light.get();
          break;
      }
      case Suffer::LightComponent::kLightKind_Point: {
          ref_ptr<LightManager::PointLight> point;
          point.alloc();
          point->SetActive(false);
          reference_ = point.get();
          break;
      }
      case Suffer::LightComponent::kLightKind_Spot: {
          ref_ptr<LightManager::SpotLight> spot;
          spot.alloc();
          spot->SetActive(false);
          reference_ = spot.get();
          break;
      }
      default: {
          abort();
          break;
      }
    }

    s32 id = suffer.resource_manager_.data_->number_of_light_frame_buffers_;
    suffer.resource_manager_.data_->internal_light_frame_buffers_[id].height_ = SHADOW_SIZE;
    suffer.resource_manager_.data_->internal_light_frame_buffers_[id].width_ = SHADOW_SIZE;

    // Depth
    Suffer::ref_ptr<Suffer::ResourceManager::Texture> frame_buffer_depth_texture;
    frame_buffer_depth_texture.alloc();

    suffer.resource_manager_.data_->internal_light_frame_buffers_[id].depth_texture_id_ = frame_buffer_depth_texture->id_;
    suffer.resource_manager_.data_->internal_textures_[suffer.resource_manager_.data_->internal_light_frame_buffers_[id].depth_texture_id_].width_ = SHADOW_SIZE;
    suffer.resource_manager_.data_->internal_textures_[suffer.resource_manager_.data_->internal_light_frame_buffers_[id].depth_texture_id_].height_ = SHADOW_SIZE;
    suffer.resource_manager_.data_->internal_textures_[suffer.resource_manager_.data_->internal_light_frame_buffers_[id].depth_texture_id_].number_channels_ = 1;
    suffer.resource_manager_.data_->internal_textures_[suffer.resource_manager_.data_->internal_light_frame_buffers_[id].depth_texture_id_].version_++;

    suffer.resource_manager_.data_->internal_light_frame_buffers_[id].version_++;

    framebuffer_id_ = id;

    initialized_ = true;

}

// ----------------------------------------------------------------------- //

void Suffer::LightComponent::SetActive(bool active){

    assert(reference_ != nullptr && "ERROR: NULL light");
    if (reference_ == nullptr) return;

    reference_->active_ = active;

}

// ----------------------------------------------------------------------- //

void Suffer::LightComponent::SetIntensity(float new_intensity){
    assert(reference_ != nullptr && "ERROR: NULL light");
    if (reference_ == nullptr) return;
    reference_->intensity_ = new_intensity;
}

// ----------------------------------------------------------------------- //

void Suffer::LightComponent::SetColor(float* new_color){
    assert(reference_ != nullptr && "ERROR: NULL light");
    if (reference_ == nullptr) return;
    
    reference_->color_.x_ = new_color[0];
    reference_->color_.y_ = new_color[1];
    reference_->color_.z_ = new_color[2];

}

// ----------------------------------------------------------------------- //

void Suffer::LightComponent::SetPosition(float* new_position){
    assert(reference_ != nullptr && "ERROR: NULL light");
    if (reference_ == nullptr) return;
    reference_->position_.x_ = new_position[0];
    reference_->position_.y_ = new_position[1];
    reference_->position_.z_ = new_position[2];
}

// ----------------------------------------------------------------------- //

void Suffer::LightComponent::SetDirection(float* new_direction){
    assert(reference_ != nullptr && "ERROR: NULL light");
    if (reference_ == nullptr) return;
    reference_->direction_.x_ = new_direction[0];
    reference_->direction_.y_ = new_direction[1];
    reference_->direction_.z_ = new_direction[2];
}

// ----------------------------------------------------------------------- //

void Suffer::LightComponent::SetAmbient(float* new_ambient){
    assert(reference_ != nullptr && "ERROR: NULL light");
    if (reference_ == nullptr) return;
    reference_->ambient_.x_ = new_ambient[0];
    reference_->ambient_.y_ = new_ambient[1];
    reference_->ambient_.z_ = new_ambient[2];
}

// ----------------------------------------------------------------------- //

void Suffer::LightComponent::SetDiffuse(float* new_diffuse){
    assert(reference_ != nullptr && "ERROR: NULL light");
    if (reference_ == nullptr) return;
    reference_->diffuse_.x_ = new_diffuse[0];
    reference_->diffuse_.y_ = new_diffuse[1];
    reference_->diffuse_.z_ = new_diffuse[2];
}

// ----------------------------------------------------------------------- //

void Suffer::LightComponent::SetSpecular(float* new_specular){
    assert(reference_ != nullptr && "ERROR: NULL light");
    if (reference_ == nullptr) return;
    reference_->specular_.x_ = new_specular[0];
    reference_->specular_.y_ = new_specular[1];
    reference_->specular_.z_ = new_specular[2];
}

// ----------------------------------------------------------------------- //

void Suffer::LightComponent::SetLinear(float new_linear /*= 1.0f*/){
    assert(reference_ != nullptr && "ERROR: NULL light");
    if (reference_ == nullptr) return;
    if (reference_->GetLightKind() == LightManager::kLightKind_Directional) return;

    Suffer::LightManager::PointLight* light = static_cast<Suffer::LightManager::PointLight*>(reference_);
    if (light == nullptr) return;
    light->SetLinear(new_linear);
}

// ----------------------------------------------------------------------- //

void Suffer::LightComponent::SetConstant(float new_constant /*= 0.09f*/){
    assert(reference_ != nullptr && "ERROR: NULL light");
    if (reference_ == nullptr) return;
    if (reference_->GetLightKind() == LightManager::kLightKind_Directional) return;

    Suffer::LightManager::PointLight* light = static_cast<Suffer::LightManager::PointLight*>(reference_);
    if (light == nullptr) return;
    light->SetConstant(new_constant);
}

// ----------------------------------------------------------------------- //

void Suffer::LightComponent::SetQuadratic(float new_quadratic /*= 0.032f*/){
    assert(reference_ != nullptr && "ERROR: NULL light");
    if (reference_ == nullptr) return;
    if (reference_->GetLightKind() == LightManager::kLightKind_Directional) return;

    Suffer::LightManager::PointLight* light = static_cast<Suffer::LightManager::PointLight*>(reference_);
    if (light == nullptr) return;
    light->SetQuadratic(new_quadratic);
}

// ----------------------------------------------------------------------- //

void Suffer::LightComponent::SetCutOff(float new_cut_off /*= 0.9978f*/){
    assert(reference_ != nullptr && "ERROR: NULL light");
    if (reference_ == nullptr) return;
    if (reference_->GetLightKind() != kLightKind_Spot) return;

    Suffer::LightManager::SpotLight* light = static_cast<Suffer::LightManager::SpotLight*>(reference_);
    if (light == nullptr) return;
    light->SetCutOff(new_cut_off);

}

// ----------------------------------------------------------------------- //

void Suffer::LightComponent::SetOuterCutOff(float new_outer_cut_off /*= 0.99f*/){
    assert(reference_ != nullptr && "ERROR: NULL light");
    if (reference_ == nullptr) return;
    if (reference_->GetLightKind() != kLightKind_Spot) return;

    Suffer::LightManager::SpotLight* light = static_cast<Suffer::LightManager::SpotLight*>(reference_);
    if (light == nullptr) return;
    light->SetOuterCutOff(new_outer_cut_off);

}

// ----------------------------------------------------------------------- //

float* Suffer::LightComponent::Color(){
    assert(reference_ != nullptr && "ERROR: NULL light");
    if (reference_ == nullptr) return nullptr;
    return &reference_->color_.x_;
}

// ----------------------------------------------------------------------- //

bool Suffer::LightComponent::Active(){
    assert(reference_ != nullptr && "ERROR: NULL light");
    if (reference_ == nullptr) return nullptr;
    return reference_->active_;
}

// ----------------------------------------------------------------------- //

float* Suffer::LightComponent::Position(){
    assert(reference_ != nullptr && "ERROR: NULL light");
    if (reference_ == nullptr) return nullptr;
    return &reference_->position_.x_;
}

// ----------------------------------------------------------------------- //

float* Suffer::LightComponent::Direction(){
    assert(reference_ != nullptr && "ERROR: NULL light");
    if (reference_ == nullptr) return nullptr;
    return &reference_->direction_.x_;
}

// ----------------------------------------------------------------------- //

float* Suffer::LightComponent::Ambient(){
    assert(reference_ != nullptr && "ERROR: NULL light");
    if (reference_ == nullptr) return nullptr;
    return &reference_->ambient_.x_;
}

// ----------------------------------------------------------------------- //

float* Suffer::LightComponent::Diffuse(){
    assert(reference_ != nullptr && "ERROR: NULL light");
    if (reference_ == nullptr) return nullptr;
    return &reference_->diffuse_.x_;
}

// ----------------------------------------------------------------------- //

float* Suffer::LightComponent::Specular(){
    assert(reference_ != nullptr && "ERROR: NULL light");
    if (reference_ == nullptr) return nullptr;
    return &reference_->specular_.x_;
}

// ----------------------------------------------------------------------- //

float Suffer::LightComponent::Intensity(){
    assert(reference_ != nullptr && "ERROR: NULL light");
    if (reference_ == nullptr) abort();
    return reference_->intensity_;
}

// ----------------------------------------------------------------------- //

u16 Suffer::LightComponent::GetLightKind(){
    assert(reference_ != nullptr && "ERROR: NULL light");
    if (reference_ == nullptr) abort();
    return reference_->light_kind_;
}

// ----------------------------------------------------------------------- //

void Suffer::LightComponent::SetLightKind(LightKind new_kind){
    assert(reference_ != nullptr && "ERROR: NULL light");
    if (reference_ == nullptr) abort();
    reference_->light_kind_ = new_kind;
    kind_ = new_kind;
}

// ----------------------------------------------------------------------- //

void Suffer::LightComponent::Reset(){
    reference_->SetPosition(0.0f, 0.0f, 0.0f);
    reference_->SetAmbient(0.0f, 0.0f, 0.0f);
    reference_->SetSpecular(0.0f, 0.0f, 0.0f);
    reference_->SetDiffuse(0.0f, 0.0f, 0.0f);
    reference_->SetDirection(0.0f, 0.0f, 0.0f);
    reference_->SetIntensity(1.0f);
    reference_->SetColor(1.0f, 1.0f, 1.0f);
}

// ----------------------------------------------------------------------- //

void Suffer::LightComponent::SetSpecular(mathmorra::Vector3 new_specular){
    assert(reference_ != nullptr && "ERROR: NULL light");
    if (reference_ == nullptr) return;
    reference_->specular_ = new_specular;
}

// ----------------------------------------------------------------------- //

void Suffer::LightComponent::SetSpecular(float x, float y, float z){
    assert(reference_ != nullptr && "ERROR: NULL light");
    if (reference_ == nullptr) return;
    reference_->specular_ = mathmorra::Vector3(x, y, z);
}

// ----------------------------------------------------------------------- //

void Suffer::LightComponent::SetDiffuse(mathmorra::Vector3 new_diffuse){
    assert(reference_ != nullptr && "ERROR: NULL light");
    if (reference_ == nullptr) return;
    reference_->diffuse_ = new_diffuse;
}

// ----------------------------------------------------------------------- //

void Suffer::LightComponent::SetDiffuse(float x, float y, float z){
    assert(reference_ != nullptr && "ERROR: NULL light");
    if (reference_ == nullptr) return;
    reference_->diffuse_ = mathmorra::Vector3(x, y, z);
}

// ----------------------------------------------------------------------- //

void Suffer::LightComponent::SetAmbient(mathmorra::Vector3 new_ambient){
    assert(reference_ != nullptr && "ERROR: NULL light");
    if (reference_ == nullptr) return;
    reference_->ambient_ = new_ambient;
}

// ----------------------------------------------------------------------- //

void Suffer::LightComponent::SetAmbient(float x, float y, float z){
    assert(reference_ != nullptr && "ERROR: NULL light");
    if (reference_ == nullptr) return;
    reference_->ambient_ = mathmorra::Vector3(x, y, z);
}

// ----------------------------------------------------------------------- //

void Suffer::LightComponent::SetDirection(mathmorra::Vector3 new_direction){
    assert(reference_ != nullptr && "ERROR: NULL light");
    if (reference_ == nullptr) return;
    reference_->direction_.x_ = new_direction.x_;
    reference_->direction_.y_ = new_direction.y_;
    reference_->direction_.z_ = new_direction.z_;
}

// ----------------------------------------------------------------------- //

void Suffer::LightComponent::SetDirection(float x, float y, float z){
    assert(reference_ != nullptr && "ERROR: NULL light");
    if (reference_ == nullptr) return;

    reference_->direction_.x_ = x;
    reference_->direction_.y_ = y;
    reference_->direction_.z_ = z;
}

// ----------------------------------------------------------------------- //

void Suffer::LightComponent::SetPosition(mathmorra::Vector3 new_position){
    assert(reference_ != nullptr && "ERROR: NULL light");
    if (reference_ == nullptr) return;

    reference_->position_.x_ = new_position.x_;
    reference_->position_.y_ = new_position.y_;
    reference_->position_.z_ = new_position.z_;
}

// ----------------------------------------------------------------------- //

void Suffer::LightComponent::SetPosition(float x, float y, float z){
    assert(reference_ != nullptr && "ERROR: NULL light");
    if (reference_ == nullptr) return;

    reference_->position_.x_ = x;
    reference_->position_.y_ = y;
    reference_->position_.z_ = z;
}

// ----------------------------------------------------------------------- //

void Suffer::LightComponent::SetColor(mathmorra::Vector3 new_color){
    assert(reference_ != nullptr && "ERROR: NULL light");
    if (reference_ == nullptr) return;

    reference_->color_.x_ = new_color.x_;
    reference_->color_.y_ = new_color.y_;
    reference_->color_.z_ = new_color.z_;
}

// ----------------------------------------------------------------------- //

void Suffer::LightComponent::SetColor(float r, float g, float b){
    assert(reference_ != nullptr && "ERROR: NULL light");
    if (reference_ == nullptr) return;

    reference_->color_.x_ = r;
    reference_->color_.y_ = g;
    reference_->color_.z_ = b;
}

// ----------------------------------------------------------------------- //


