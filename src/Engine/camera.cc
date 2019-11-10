/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 11-10-2019
* Camera Source
*/

#include "camera.h"
#include "input.h"
#include "gtx/transform.hpp"
#include "suffermanager.h"
#include "matrix4.h"

Suffer::Camera::Camera() {

    field_of_view_ = 45.0f;
    position_ = glm::vec3(0.0f, 0.0f, -5.0f);
    camera_target_ = glm::vec3(0.0f, 0.0f, 0.0f);
    camera_direction_ = glm::vec3(0.0f, 0.0f, 0.0f);

    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    camera_right_ = glm::normalize(glm::cross(up, camera_direction_));
    camera_up_ = glm::cross(camera_direction_, camera_right_);

    glm::mat4 view;
    view =   glm::mat3(glm::vec3(0.0f, 0.0f, 3.0f),
                       glm::vec3(0.0f, 0.0f, 0.0f),
                       glm::vec3(0.0f, 1.0f, 0.0f));

}


Suffer::Camera& Suffer::Camera::operator=(const Camera& cam){

    Camera camera_;

    camera_.position_ = cam.position_;
    camera_.camera_target_ = cam.camera_target_;
    camera_.camera_direction_ = cam.camera_direction_;

    camera_.camera_up_ = cam.camera_up_;
    camera_.camera_right_ = cam.camera_right_;
    camera_.camera_forward_ = cam.camera_forward_;

    camera_.field_of_view_ = cam.field_of_view_;

    return camera_;

}

void Suffer::Camera::SetupPerspective(float fovy, float aspect, float znear, float zfar) {

}

void Suffer::Camera::SetupFrustum(float left, float right, float bottom, float top, float znear, float zfar){

}

void Suffer::Camera::SetPosition(const glm::vec3 position) {
    position_ = position;
}

void Suffer::Camera::SetViewDirection(const glm::vec3 view_direction) {
    camera_direction_ = view_direction;
}

void Suffer::Camera::SetViewDirection(const float view_direction[3]) {
    camera_direction_ = glm::vec3(view_direction[0], view_direction[1], view_direction[2]);
}

void Suffer::Camera::SetPosition(const float position[3]) {
    position_ = glm::vec3(position[0], position[1], position[2]);
}

void Suffer::Camera::SetViewTarget(const glm::vec3 target) {
    camera_target_ = target;
}

void Suffer::Camera::SetFOV(const float new_fov){
    field_of_view_ = new_fov;
}

void Suffer::Camera::SetViewTarget(const float target[3]) {
    camera_target_ = glm::vec3(target[0], target[1], target[2]);
}

void Suffer::Camera::SetForward(const float forward[3]){
    camera_forward_ = glm::vec3(forward[0], forward[1], forward[2]);
}

void Suffer::Camera::SetProjectionMatrix(glm::mat4 projection_matrix){
    projection_matrix_ = projection_matrix;
}

void Suffer::Camera::SetProjectionMatrix(const float m[16]){
    projection_matrix_ = glm::mat4(
        m[0],  m[1],  m[2],  m[3],
        m[4],  m[5],  m[6],  m[7],
        m[8],  m[9],  m[10], m[11],
        m[12], m[12], m[14], m[15]
    );
}

void Suffer::Camera::SetForward(const glm::vec3 forward){
    camera_forward_ = forward;
}

void Suffer::Camera::SetViewMatrix(glm::mat4 view_matrix){
    view_matrix_ = view_matrix;
}

void Suffer::Camera::SetViewMatrix(const float m[16]){
    view_matrix_ = glm::mat4(
        m[0],  m[1],  m[2],  m[3],
        m[4],  m[5],  m[6],  m[7],
        m[8],  m[9],  m[10], m[11],
        m[12], m[12], m[14], m[15]
    );
}

const float* Suffer::Camera::Position() const {
    return &position_.x;
}

const float* Suffer::Camera::Target() const {
    return &camera_target_.x;
}

const float* Suffer::Camera::Up() const {
    return &camera_up_.x;
}

const float Suffer::Camera::Fov() const{
    return field_of_view_;
}

// FPS Movement
void Suffer::Camera::CameraMovement(ref_ptr<Camera> camera){

    camera_right_ = glm::cross(camera_forward_, camera_up_);
    float time_ = SufferManager::instance().DeltaTime();

    // Input Stuff
    if (Suffer::IsKeyDown(k_W)) { // FORWARD
        //glm::mat4 translate_ = glm::translate(
        //    camera_forward_.x * speed_ * time_,
        //    camera_forward_.y * speed_ * time_,
        //    camera_forward_.z * speed_ * time_,
        //    );
    }

}

void Suffer::Camera::SetSensibility(float new_sensibility){
    sensibility_ = new_sensibility;
}

void Suffer::Camera::SetSpeed(float new_speed){
    speed_ = new_speed;
}

Suffer::Camera::~Camera() {

}
