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
}

// ----------------------------------------------------------------------- //

void Suffer::LightComponent::SetDirection(float* new_direction){
    assert(reference_ != nullptr && "ERROR: NULL light");
    if (reference_ == nullptr) return;
}

// ----------------------------------------------------------------------- //

void Suffer::LightComponent::SetAmbient(float* new_ambient){
    assert(reference_ != nullptr && "ERROR: NULL light");
    if (reference_ == nullptr) return;
}

// ----------------------------------------------------------------------- //

void Suffer::LightComponent::SetDiffuse(float* new_diffuse){
    assert(reference_ != nullptr && "ERROR: NULL light");
    if (reference_ == nullptr) return;
}

// ----------------------------------------------------------------------- //

void Suffer::LightComponent::SetSpecular(float* new_specular){
    assert(reference_ != nullptr && "ERROR: NULL light");
    if (reference_ == nullptr) return;
}

// ----------------------------------------------------------------------- //
//
//float* Suffer::LightComponent::Color(){
//    assert(reference_ != nullptr && "ERROR: NULL light");
//    if (reference_ == nullptr) return;
//}
//
//// ----------------------------------------------------------------------- //
//
//bool Suffer::LightComponent::Active(){
//    assert(reference_ != nullptr && "ERROR: NULL light");
//    if (reference_ == nullptr) return;
//}
//
//// ----------------------------------------------------------------------- //
//
//float* Suffer::LightComponent::Position(){
//    assert(reference_ != nullptr && "ERROR: NULL light");
//    if (reference_ == nullptr) return;
//}
//
//// ----------------------------------------------------------------------- //
//
//float* Suffer::LightComponent::Direction()
//{
//    assert(reference_ != nullptr && "ERROR: NULL light");
//    if (reference_ == nullptr) return;
//}
//
//// ----------------------------------------------------------------------- //
//
//float* Suffer::LightComponent::Ambient()
//{
//    assert(reference_ != nullptr && "ERROR: NULL light");
//    if (reference_ == nullptr) return;
//}
//
//// ----------------------------------------------------------------------- //
//
//float* Suffer::LightComponent::Diffuse()
//{
//    assert(reference_ != nullptr && "ERROR: NULL light");
//    if (reference_ == nullptr) return;
//}
//
//// ----------------------------------------------------------------------- //
//
//float* Suffer::LightComponent::Specular()
//{
//    assert(reference_ != nullptr && "ERROR: NULL light");
//    if (reference_ == nullptr) return;
//}
//
//// ----------------------------------------------------------------------- //
//
//float Suffer::LightComponent::Intensity()
//{
//    assert(reference_ != nullptr && "ERROR: NULL light");
//    if (reference_ == nullptr) return;
//}
//
//// ----------------------------------------------------------------------- //
//
//u16 Suffer::LightComponent::GetLightKind()
//{
//    assert(reference_ != nullptr && "ERROR: NULL light");
//    if (reference_ == nullptr) return;
//}
//
//// ----------------------------------------------------------------------- //

void Suffer::LightComponent::SetLightKind(LightKind new_kind)
{
    assert(reference_ != nullptr && "ERROR: NULL light");
    if (reference_ == nullptr) return;
}

// ----------------------------------------------------------------------- //

void Suffer::LightComponent::SetSpecular(mathmorra::Vector3 new_specular)
{
    assert(reference_ != nullptr && "ERROR: NULL light");
    if (reference_ == nullptr) return;
}

// ----------------------------------------------------------------------- //

void Suffer::LightComponent::SetSpecular(float x, float y, float z)
{
    assert(reference_ != nullptr && "ERROR: NULL light");
    if (reference_ == nullptr) return;
}

// ----------------------------------------------------------------------- //

void Suffer::LightComponent::SetDiffuse(mathmorra::Vector3 new_diffuse)
{
    assert(reference_ != nullptr && "ERROR: NULL light");
    if (reference_ == nullptr) return;
}

// ----------------------------------------------------------------------- //

void Suffer::LightComponent::SetDiffuse(float x, float y, float z)
{
    assert(reference_ != nullptr && "ERROR: NULL light");
    if (reference_ == nullptr) return;
}

// ----------------------------------------------------------------------- //

void Suffer::LightComponent::SetAmbient(mathmorra::Vector3 new_ambient)
{
    assert(reference_ != nullptr && "ERROR: NULL light");
    if (reference_ == nullptr) return;
}

// ----------------------------------------------------------------------- //

void Suffer::LightComponent::SetAmbient(float x, float y, float z)
{
    assert(reference_ != nullptr && "ERROR: NULL light");
    if (reference_ == nullptr) return;
}

// ----------------------------------------------------------------------- //

void Suffer::LightComponent::SetDirection(mathmorra::Vector3 new_direction)
{
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

void Suffer::LightComponent::SetPosition(mathmorra::Vector3 new_position)
{
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


