// Author: Diego Ochando Torres <ochandoto@esat-alumni.com>

#include "light_manager.h"
#include "suffermanager.h"


// ----------------------------------------------------------------------- //

Suffer::LightManager::LightManager(){

  // Do in StartUp instead here

}

// ----------------------------------------------------------------------- //

Suffer::LightManager::~LightManager() {

  // Do in ShutDown instead here

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

void Suffer::LightManager::Light::SetColor(float* new_color) {

  color_.x_ = new_color[0];
  color_.y_ = new_color[1];
  color_.z_ = new_color[2];

}

// ----------------------------------------------------------------------- //

void Suffer::LightManager::Light::SetColor(mathmorra::Vector3 new_color) {

  color_.x_ = new_color.x_;
  color_.y_ = new_color.y_;
  color_.z_ = new_color.z_;

}

// ----------------------------------------------------------------------- //

void Suffer::LightManager::Light::SetColor(float r, float g, float b) {

  color_.x_ = r;
  color_.y_ = g;
  color_.z_ = b;

}

// ----------------------------------------------------------------------- //

void Suffer::LightManager::Light::SetPosition(float* new_position) {

  position_.x_ = new_position[0];
  position_.y_ = new_position[1];
  position_.z_ = new_position[2];

}

// ----------------------------------------------------------------------- //

void Suffer::LightManager::Light::SetPosition(mathmorra::Vector3 new_position) {

  position_.x_ = new_position.x_;
  position_.y_ = new_position.y_;
  position_.z_ = new_position.z_;

}

// ----------------------------------------------------------------------- //

void Suffer::LightManager::Light::SetPosition(float x, float y, float z) {

  position_.x_ = x;
  position_.y_ = y;
  position_.z_ = z;

}

// ----------------------------------------------------------------------- //

void Suffer::LightManager::Light::SetDirection(float* new_direction){

  direction_.x_ = new_direction[0];
  direction_.y_ = new_direction[1];
  direction_.z_ = new_direction[2];

}

// ----------------------------------------------------------------------- //

void Suffer::LightManager::Light::SetDirection(mathmorra::Vector3 new_direction) {

  direction_.x_ = new_direction.x_;
  direction_.y_ = new_direction.y_;
  direction_.z_ = new_direction.z_;

}

// ----------------------------------------------------------------------- //

void Suffer::LightManager::Light::SetDirection(float x, float y, float z) {

  direction_.x_ = x;
  direction_.y_ = y;
  direction_.z_ = z;

}

// ----------------------------------------------------------------------- //

void Suffer::LightManager::Light::SetAmbient(float* new_ambient) {

  ambient_.x_ = new_ambient[0];
  ambient_.y_ = new_ambient[1];
  ambient_.z_ = new_ambient[2];

}

// ----------------------------------------------------------------------- //

void Suffer::LightManager::Light::SetAmbient(mathmorra::Vector3 new_ambient) {

  ambient_.x_ = new_ambient.x_;
  ambient_.y_ = new_ambient.y_;
  ambient_.z_ = new_ambient.z_;

}

// ----------------------------------------------------------------------- //

void Suffer::LightManager::Light::SetAmbient(float x, float y, float z) {

  ambient_.x_ = x;
  ambient_.y_ = y;
  ambient_.z_ = z;

}

// ----------------------------------------------------------------------- //

void Suffer::LightManager::Light::SetDiffuse(float* new_diffuse){

  diffuse_.x_ = new_diffuse[0];
  diffuse_.y_ = new_diffuse[1];
  diffuse_.z_ = new_diffuse[2];

}

// ----------------------------------------------------------------------- //

void Suffer::LightManager::Light::SetDiffuse(mathmorra::Vector3 new_diffuse) {

  diffuse_.x_ = new_diffuse.x_;
  diffuse_.y_ = new_diffuse.y_;
  diffuse_.z_ = new_diffuse.z_;

}

// ----------------------------------------------------------------------- //

void Suffer::LightManager::Light::SetDiffuse(float x, float y, float z) {

  diffuse_.x_ = x;
  diffuse_.y_ = y;
  diffuse_.z_ = z;

}

// ----------------------------------------------------------------------- //

void Suffer::LightManager::Light::SetSpecular(float* new_specular){

  specular_.x_ = new_specular[0];
  specular_.y_ = new_specular[1];
  specular_.z_ = new_specular[2];

}

// ----------------------------------------------------------------------- //

void Suffer::LightManager::Light::SetSpecular(mathmorra::Vector3 new_specular) {

  specular_.x_ = new_specular.x_;
  specular_.y_ = new_specular.y_;
  specular_.z_ = new_specular.z_;

}

// ----------------------------------------------------------------------- //

void Suffer::LightManager::Light::SetSpecular(float x, float y, float z) {

  specular_.x_ = x;
  specular_.y_ = y;
  specular_.z_ = z;

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

float* Suffer::LightManager::Light::Ambient(){

  return &ambient_.x_;

}

// ----------------------------------------------------------------------- //

float* Suffer::LightManager::Light::Diffuse(){

  return &diffuse_.x_;

}

// ----------------------------------------------------------------------- //

float* Suffer::LightManager::Light::Specular(){

  return &specular_.x_;

}

// ----------------------------------------------------------------------- //

float Suffer::LightManager::Light::Intensity(){

  return intensity_;

}

// ----------------------------------------------------------------------- //

u16 Suffer::LightManager::Light::GetLightKind(){

  return (u16)light_kind_;

}

// ----------------------------------------------------------------------- //

Suffer::LightManager::Light::Light(){

  assert(suffer.light_manager_.current_lights_ < MAX_LIGHTS);
  if (suffer.light_manager_.current_lights_ >= MAX_LIGHTS) return;

  // Attributes
  active_ = true;
  intensity_ = 1.0f;

  light_kind_ = kLightKind_Directional;

  suffer.light_manager_.current_lights_++;
  suffer.light_manager_.lights_.push_back(this);

}

// ----------------------------------------------------------------------- //

Suffer::LightManager::Light::~Light(){



}

// ----------------------------------------------------------------------- //

Suffer::LightManager::DirectionalLight::DirectionalLight(){

  assert(suffer.light_manager_.current_lights_ < MAX_LIGHTS);
  if (suffer.light_manager_.current_lights_ >= MAX_LIGHTS) return;

  // Attributes
  active_ = true;
  intensity_ = 1.0f;

  light_kind_ = kLightKind_Directional;

  suffer.light_manager_.current_lights_++;
  suffer.light_manager_.lights_.push_back(this);

}

// ----------------------------------------------------------------------- //

Suffer::LightManager::DirectionalLight::~DirectionalLight(){



}

// ----------------------------------------------------------------------- //

Suffer::LightManager::PointLight::PointLight(){

  assert(suffer.light_manager_.current_lights_ < MAX_LIGHTS);
  if (suffer.light_manager_.current_lights_ >= MAX_LIGHTS) return;

  // Attributes
  active_ = true;
  intensity_ = 1.0f;

  light_kind_ = kLightKind_Point;

  suffer.light_manager_.current_lights_++;
  suffer.light_manager_.lights_.push_back(this);

}

// ----------------------------------------------------------------------- //

Suffer::LightManager::PointLight::~PointLight(){



}

// ----------------------------------------------------------------------- //

void Suffer::LightManager::PointLight::SetConstant(float new_constant){

  constant_ = new_constant;

}

// ----------------------------------------------------------------------- //

void Suffer::LightManager::PointLight::SetLinear(float new_linear){

  linear_ = new_linear;

}

// ----------------------------------------------------------------------- //

void Suffer::LightManager::PointLight::SetQuadratic(float new_quadratic){

  quadratic_ = new_quadratic;

}

// ----------------------------------------------------------------------- //

float Suffer::LightManager::PointLight::Constant(){

  return constant_;

}

// ----------------------------------------------------------------------- //

float Suffer::LightManager::PointLight::Linear(){

  return linear_;

}

// ----------------------------------------------------------------------- //

float Suffer::LightManager::PointLight::Quadratic() {

  return quadratic_;

}

// ----------------------------------------------------------------------- //

Suffer::LightManager::SpotLight::SpotLight(){

  assert(suffer.light_manager_.current_lights_ < MAX_LIGHTS);
  if (suffer.light_manager_.current_lights_ >= MAX_LIGHTS) return;

  // Attributes
  active_ = true;
  intensity_ = 1.0f;

  light_kind_ = kLightKind_Spot;

  suffer.light_manager_.current_lights_++;
  suffer.light_manager_.lights_.push_back(this);

}

// ----------------------------------------------------------------------- //

Suffer::LightManager::SpotLight::~SpotLight(){



}

// ----------------------------------------------------------------------- //

void Suffer::LightManager::SpotLight::SetCutOff(float new_cut_off){

  cut_off_ = new_cut_off;

}

// ----------------------------------------------------------------------- //

void Suffer::LightManager::SpotLight::SetOuterCutOff(float new_outer_cut_off){

  outer_cut_off_ = new_outer_cut_off;

}

// ----------------------------------------------------------------------- //

float Suffer::LightManager::SpotLight::CutOff(){

  return cut_off_;

}

// ----------------------------------------------------------------------- //

float Suffer::LightManager::SpotLight::OuterCutOff(){

  return outer_cut_off_;

}

// ----------------------------------------------------------------------- //
