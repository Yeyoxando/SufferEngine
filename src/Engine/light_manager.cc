#include "light_manager.h"
#include "suffermanager.h"


// ----------------------------------------------------------------------- //

Suffer::LightManager::LightManager(){


}

// ----------------------------------------------------------------------- //

Suffer::LightManager::~LightManager(){



}

// ----------------------------------------------------------------------- //

void Suffer::LightManager::StartUp(){

  current_lights_ = 0;

}

// ----------------------------------------------------------------------- //

void Suffer::LightManager::ShutDown(){



}

// ----------------------------------------------------------------------- //

void Suffer::LightManager::Light::SetActive(bool active){
  active_ = active;
}

// ----------------------------------------------------------------------- //

void Suffer::LightManager::Light::SetIntensity(float new_intensity){
  intensity_ = new_intensity;
}

// ----------------------------------------------------------------------- //

void Suffer::LightManager::Light::SetColor(float* new_color){
  color_ = new_color;
}

// ----------------------------------------------------------------------- //

void Suffer::LightManager::Light::SetPosition(float* new_position){

  position_.x_ = new_position[0];
  position_.y_ = new_position[1];
  position_.z_ = new_position[2];

}

// ----------------------------------------------------------------------- //

void Suffer::LightManager::Light::SetDirection(float* new_direction){

  direction_.x_ = new_direction[0];
  direction_.y_ = new_direction[1];
  direction_.z_ = new_direction[2];

}

// ----------------------------------------------------------------------- //

float* Suffer::LightManager::Light::Color(){
  return &color_.x_;
}

// ----------------------------------------------------------------------- //

bool Suffer::LightManager::Light::Active(){
  return active_;
}

// ----------------------------------------------------------------------- //

float* Suffer::LightManager::Light::Position(){
  return &position_.x_;
}

// ----------------------------------------------------------------------- //

float* Suffer::LightManager::Light::Direction(){
  return &direction_.x_;
}

// ----------------------------------------------------------------------- //

float Suffer::LightManager::Light::Intensity(){
  return intensity_;
}

// ----------------------------------------------------------------------- //

void Suffer::LightManager::Light::SetDirection(mathmorra::Vector3 new_direction){

  direction_.x_ = new_direction.x_;
  direction_.y_ = new_direction.y_;
  direction_.z_ = new_direction.z_;

}

// ----------------------------------------------------------------------- //

void Suffer::LightManager::Light::SetDirection(float x, float y, float z){

  direction_.x_ = x;
  direction_.y_ = y;
  direction_.z_ = z;

}

// ----------------------------------------------------------------------- //

void Suffer::LightManager::Light::SetPosition(mathmorra::Vector3 new_position){

  position_.x_ = new_position.x_;
  position_.y_ = new_position.y_;
  position_.z_ = new_position.z_;

}

// ----------------------------------------------------------------------- //

void Suffer::LightManager::Light::SetPosition(float x, float y, float z){

  position_.x_ = x;
  position_.y_ = y;
  position_.z_ = z;

}

// ----------------------------------------------------------------------- //

void Suffer::LightManager::Light::SetColor(mathmorra::Vector3 new_color){

  color_.x_ = new_color.x_;
  color_.y_ = new_color.y_;
  color_.z_ = new_color.z_;

}

// ----------------------------------------------------------------------- //

void Suffer::LightManager::Light::SetColor(float r, float g, float b){

  color_.x_ = r;
  color_.y_ = g;
  color_.z_ = b;

}

// ----------------------------------------------------------------------- //

Suffer::LightManager::Light::Light(){

  assert(suffer.light_manager_.current_lights_ < MAX_LIGHTS);
  if (suffer.light_manager_.current_lights_ >= MAX_LIGHTS) return;

  // Attributes
  active_ = true;
  intensity_ = 0.0f;

  suffer.light_manager_.current_lights_++;
  suffer.light_manager_.lights_.push_back(this);

}

// ----------------------------------------------------------------------- //

Suffer::LightManager::Light::~Light(){



}

// ----------------------------------------------------------------------- //

Suffer::LightManager::DirectionalLight::DirectionalLight(){



}

// ----------------------------------------------------------------------- //

Suffer::LightManager::DirectionalLight::~DirectionalLight(){



}

// ----------------------------------------------------------------------- //

Suffer::LightManager::PointLight::PointLight(){



}

// ----------------------------------------------------------------------- //

Suffer::LightManager::PointLight::~PointLight(){



}

// ----------------------------------------------------------------------- //

Suffer::LightManager::SpotLight::SpotLight(){



}

// ----------------------------------------------------------------------- //

Suffer::LightManager::SpotLight::~SpotLight(){



}

// ----------------------------------------------------------------------- //
