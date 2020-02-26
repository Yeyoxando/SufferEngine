/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 11-10-2019
* Camera Source
*/

#include "camera.h"
#include "input.h"
#include "suffermanager.h"
#include "common_definitions.h"
#include "math_utils.h"
#include "GL/glew.h"
#include "glm.hpp"

// --------------------------------------------------- //

Suffer::Camera::Camera() {

  speed_ = 0.5f;
  sensitivity_ = 0.05f;
  field_of_view_ = 50.0f;
  yaw_ = -90.0f;
  pitch_ = 0.0f;

  // Camera view space
  camera_up_ = { 0.0f, 1.0f, 0.0f };
  camera_back_ = { 0.0f, 0.0f, -1.0f };
  camera_right_ = { 1.0f, 0.0f, 0.0f };
  camera_target_ = { 0.0f, 0.0f, 1.0f };
  camera_position_ = { -1.5f, 0.0f, -30.0f };

  last_cursor_position_.x_ = 800.0f * 0.5f;
  last_cursor_position_.y_ = 600.0f * 0.5f;

  fps_movement_ = false;

}

// --------------------------------------------------- //

Suffer::Camera& Suffer::Camera::operator=(const Camera& cam) {

  Camera camera_;

  camera_.camera_position_ = cam.camera_position_;
  camera_.camera_target_ = cam.camera_target_;

  camera_.camera_up_ = cam.camera_up_;

  camera_.field_of_view_ = cam.field_of_view_;

  return camera_;

}

// --------------------------------------------------- //

void Suffer::Camera::SetupPerspective(float fov, float aspect, float znear, float zfar) {

  float cotangent = 1.0f / tanf(fov * 0.5f);
  float rcpdz = 1.0f / (znear - zfar);

  mathmorra::Vector4 a(cotangent / aspect, 0.0f, 0.0f, 0.0f);
  mathmorra::Vector4 b(0.0f, cotangent, 0.0f, 0.0f);
  mathmorra::Vector4 c(0.0f, 0.0f, (zfar + znear) * rcpdz, -1.0f);
  mathmorra::Vector4 d(0.0f, 0.0f, 2.0f * znear * zfar * rcpdz, 0.0f);

  projection_matrix_ = mathmorra::Matrix4(a, b, c, d);

}

// --------------------------------------------------- //

void Suffer::Camera::SetPosition(const mathmorra::Vector3 position) {
  camera_position_ = position;
}

// --------------------------------------------------- //

void Suffer::Camera::SetViewDirection(const mathmorra::Vector3 view_direction) {
  camera_target_ = view_direction;
}

// --------------------------------------------------- //

void Suffer::Camera::SetViewDirection(const float view_direction[3]) {
  camera_target_ = mathmorra::Vector3(view_direction[0], view_direction[1], view_direction[2]);
}

// --------------------------------------------------- //

void Suffer::Camera::SetPosition(const float position[3]) {
  camera_position_ = mathmorra::Vector3(position[0], position[1], position[2]);
}

// --------------------------------------------------- //

void Suffer::Camera::SetFOV(const float new_fov) {
  float aux_fov = new_fov;
  aux_fov = ThiefUtils::Math::Clamp(aux_fov, 48.5f, 50.0f);
  field_of_view_ = aux_fov;
}

// --------------------------------------------------- //

void Suffer::Camera::SetProjectionMatrix(mathmorra::Matrix4 projection_matrix) {
  projection_matrix_ = projection_matrix;
}

// --------------------------------------------------- //

void Suffer::Camera::SetProjectionMatrix(const float m[16]) {
  projection_matrix_ = mathmorra::Matrix4(m[16]);
}

// --------------------------------------------------- //

void Suffer::Camera::SetViewMatrix(mathmorra::Matrix4 view_matrix) {
  view_matrix_ = view_matrix;
}

const float* Suffer::Camera::Target() {
  return &camera_target_.x_;
}

// --------------------------------------------------- //

void Suffer::Camera::SetViewMatrix(const float m[16]) {
  view_matrix_ = mathmorra::Matrix4(m[16]);
}

// --------------------------------------------------- //

const float* Suffer::Camera::Position() const {
  return &camera_position_.x_;
}

// --------------------------------------------------- //

const float* Suffer::Camera::Up() const {
  return &camera_up_.x_;
}

// --------------------------------------------------- //

const float Suffer::Camera::Fov() const {
  return field_of_view_;
}

// --------------------------------------------------- //

mathmorra::Matrix4 Suffer::Camera::ProjectionMatrix() {
  return projection_matrix_;
}

// --------------------------------------------------- //

mathmorra::Matrix4 Suffer::Camera::ViewMatrix() {
  return view_matrix_;
}

// --------------------------------------------------- //

void Suffer::Camera::CameraMovement(ref_ptr<Camera> camera) {

  float time = SufferManager::instance().DeltaTime() * 0.01f;

  // FORWARD
  if (suffer.input_manager_.IsKeyPressed(InputManager::k_W)) {

    mathmorra::Matrix4 translations = translations.Translate(
      camera_target_.x_ * speed_ * time,
      camera_target_.y_ * speed_ * time,
      camera_target_.z_ * speed_ * time);

    //Transform Matrix4 / Vector3
    camera_position_ = translations.Transpose() * camera_position_;
  }

  // LEFT
  if (suffer.input_manager_.IsKeyPressed(InputManager::k_A)) {

    mathmorra::Matrix4 translations = translations.Translate(
      -camera_right_.x_ * speed_ * time,
      0.0f,
      -camera_right_.z_ * speed_ * time);

    //Transform Matrix4 / Vector3
    camera_position_ = translations.Transpose() * camera_position_;
  }

  // RIGHT
  if (suffer.input_manager_.IsKeyPressed(InputManager::k_D)) {

    mathmorra::Matrix4 translations = translations.Translate(
      camera_right_.x_ * speed_ * time,
      0.0f,
      camera_right_.z_ * speed_ * time);

    //Transform Matrix4 / Vector3
    camera_position_ = translations.Transpose() * camera_position_;

  }

  // BACK
  if (suffer.input_manager_.IsKeyPressed(InputManager::k_S)) {

    mathmorra::Matrix4 translations = translations.Translate(
      -camera_target_.x_ * speed_ * time,
      -camera_target_.y_ * speed_ * time,
      -camera_target_.z_ * speed_ * time);

    //Transform Matrix4 / Vector3
    camera_position_ = translations.Transpose() * camera_position_;

  }

  //UP
  if (suffer.input_manager_.IsKeyPressed(InputManager::k_Q)) {

    mathmorra::Matrix4 translations = translations.Translate(
      0.0f,
      camera_up_.y_ * speed_ * time,
      0.0f);

    //Transform Matrix4 / Vector3
    camera_position_ = translations.Transpose() * camera_position_;

  }

  //DOWN
  if (suffer.input_manager_.IsKeyPressed(InputManager::k_E)) {

    mathmorra::Vector3 down = -camera_up_;

    mathmorra::Matrix4 translations = translations.Translate(
      0.0f,
      down.y_ * speed_ * time,
      0.0f);

    //Transform Matrix4 / Vector3
    camera_position_ = translations.Transpose() * camera_position_;

  }

  //ROTATE Y
  if (suffer.input_manager_.IsKeyPressed(InputManager::k_Left)) {
    camera_target_ = mathmorra::Matrix4::RotateY(0.008f) * camera_target_;
  }
  if (suffer.input_manager_.IsKeyPressed(InputManager::k_Right)) {
    camera_target_ = mathmorra::Matrix4::RotateY(-0.008f) * camera_target_;
  }

  if (suffer.input_manager_.IsKeyPressed(InputManager::k_Up)) {
    camera_target_ = mathmorra::Matrix4::RotateX(-0.008f) * camera_target_;
  }
  if (suffer.input_manager_.IsKeyPressed(InputManager::k_Down)) {
    camera_target_ = mathmorra::Matrix4::RotateX(0.008f) * camera_target_;
  }

  // Mouse Stuff
  if (pitch_ > 89.0f)
    pitch_ = 89.0f;
  if (pitch_ < -89.0f)
    pitch_ = -89.0f;

  camera_right_ = -mathmorra::Vector3::CrossProduct(camera_target_, mathmorra::Vector3(0.0f, 1.0f, 0.0f)).Normalized();
  camera_up_ = -mathmorra::Vector3::CrossProduct(camera_right_, camera_target_).Normalized();

}

// --------------------------------------------------- //

void Suffer::Camera::SetSensibility(float new_sensitivity_) {
  sensitivity_ = sensitivity_;
}

// --------------------------------------------------- //

void Suffer::Camera::SetSpeed(float new_speed) {
  speed_ = new_speed;
}

// --------------------------------------------------- //

void Suffer::Camera::SetTarget(mathmorra::Vector3 new_target){
  camera_target_ = new_target;
}

// --------------------------------------------------- //

bool Suffer::Camera::FPS() {
  return fps_movement_;
}

// --------------------------------------------------- //

float Suffer::Camera::Sensitivity(){
  return sensitivity_;
}

// --------------------------------------------------- //

Suffer::Camera::~Camera() {

}

// --------------------------------------------------- //

void Suffer::Camera::Update() {

  if (suffer.input_manager_.IsKeyDown(InputManager::k_F1)) {
    fps_movement_ = !fps_movement_;
  }

  if (suffer.input_manager_.IsKeyPressed(InputManager::k_Shift)) {
    speed_ = 1.5f;
  }
  else {
    speed_ = 0.5f;
  }

  SetupPerspective(field_of_view_, (float)suffer.GetWindowSize().x_ / (float)suffer.GetWindowSize().y_, 0.001f, 450.0f);
  view_matrix_ = mathmorra::Matrix4::LookAt(camera_position_, camera_position_ + camera_target_, camera_up_);

}

// --------------------------------------------------- //