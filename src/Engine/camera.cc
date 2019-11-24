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

    field_of_view_ = 50.0f;
    speed_ = 1.0f;
    sensibility_ = 0.5f;

    camera_target_ = mathmorra::Vector3(0.0f, 0.0f, 0.0f);
    camera_position_ = mathmorra::Vector3(0.0f, 0.0f, 15.0f);
    camera_direction_ = camera_position_ - camera_target_;
    camera_direction_.Normalize();

    camera_right_ = mathmorra::Vector3::CrossProduct(mathmorra::Vector3(0.0f, 1.0f, 0.0f), camera_direction_);
    camera_right_.Normalize();

    camera_up_ = mathmorra::Vector3::CrossProduct(camera_direction_, camera_right_);
    camera_up_.Normalize();

    fps_movement_ = false;

}

// --------------------------------------------------- //

Suffer::Camera& Suffer::Camera::operator=(const Camera& cam){

    Camera camera_;

    camera_.camera_position_ = cam.camera_position_;
    camera_.camera_target_ = cam.camera_target_;
    camera_.camera_direction_ = cam.camera_direction_;

    camera_.camera_up_ = cam.camera_up_;
   // camera_.camera_right_ = cam.camera_right_;

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
    camera_direction_ = view_direction;
}

// --------------------------------------------------- //

void Suffer::Camera::SetViewDirection(const float view_direction[3]) {
    camera_direction_ = mathmorra::Vector3(view_direction[0], view_direction[1], view_direction[2]);
}

// --------------------------------------------------- //

void Suffer::Camera::SetPosition(const float position[3]) {
    camera_position_ = mathmorra::Vector3(position[0], position[1], position[2]);
}

// --------------------------------------------------- //

void Suffer::Camera::SetFOV(const float new_fov){
    field_of_view_ = new_fov;
}

// --------------------------------------------------- //

void Suffer::Camera::SetProjectionMatrix(mathmorra::Matrix4 projection_matrix){
    projection_matrix_ = projection_matrix;
}

// --------------------------------------------------- //

void Suffer::Camera::SetProjectionMatrix(const float m[16]){
    projection_matrix_ = mathmorra::Matrix4(m[16]);
}

// --------------------------------------------------- //

void Suffer::Camera::SetViewMatrix(mathmorra::Matrix4 view_matrix){
    view_matrix_ = view_matrix;
}

// --------------------------------------------------- //

void Suffer::Camera::SetViewMatrix(const float m[16]){
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

const float Suffer::Camera::Fov() const{
    return field_of_view_;
}

// --------------------------------------------------- //

mathmorra::Matrix4 Suffer::Camera::ProjectionMatrix(){
    return projection_matrix_;
}

// --------------------------------------------------- //

mathmorra::Matrix4 Suffer::Camera::ViewMatrix(){
    return view_matrix_;
}

// --------------------------------------------------- //

void Suffer::Camera::CameraMovement(ref_ptr<Camera> camera){

    float time = SufferManager::instance().DeltaTime() * 0.01f;
    float camera_speed = speed_;

    // MOUSE UTILS
    mathmorra::Vector2 current_position;
    mathmorra::Vector2 last_position;

    // CAMERA UTILS
    camera_direction_ = camera_position_ - camera_target_;
    camera_direction_.Normalize();

    camera_right_ = mathmorra::Vector3::CrossProduct(mathmorra::Vector3(0.0f, 1.0f, 0.0f), camera_direction_);
    camera_right_.Normalize();

    camera_up_ = mathmorra::Vector3::CrossProduct(camera_direction_, camera_right_);
    camera_up_.Normalize();

    // FORWARD
    if (suffer.input_manager_.IsKeyPressed(InputManager::k_W)) {

        mathmorra::Matrix4 translations = translations.Translate(
            -camera_direction_.x_ * camera_speed * time,
            -camera_direction_.y_ * camera_speed * time,
            -camera_direction_.z_ * camera_speed * time);

        //Transform Matrix4 / Vector3
        camera_position_ = translations * camera_position_;
    }

    // LEFT
    if (suffer.input_manager_.IsKeyPressed(InputManager::k_A)) {

        mathmorra::Vector3 left = camera_right_;
        mathmorra::Matrix4 translations = translations.Translate(
            left.x_ * camera_speed * time,
            0.0f,
            left.z_ * camera_speed * time);

        //Transform Matrix4 / Vector3
        camera_position_ = translations * camera_position_ ;
    }

    // RIGHT
    if (suffer.input_manager_.IsKeyPressed(InputManager::k_D)) {
        mathmorra::Vector3 left = camera_right_ * -1.0f;
        mathmorra::Matrix4 translations = translations.Translate(
            left.x_ * camera_speed * time,
            0.0f,
            left.z_ * camera_speed * time);

        //Transform Matrix4 / Vector3
        camera_position_ = translations * camera_position_ ;

    }

    // BACK
    if (suffer.input_manager_.IsKeyPressed(InputManager::k_S)) {

        mathmorra::Matrix4 translations = translations.Translate(
            camera_direction_.x_ * camera_speed * time,
            camera_direction_.y_ * camera_speed * time,
            camera_direction_.z_ * camera_speed * time);

        //Transform Matrix4 / Vector3
        camera_position_ = translations * camera_position_ ;

    }

    //UP
    if (suffer.input_manager_.IsKeyPressed(InputManager::k_Q)) {

        mathmorra::Matrix4 translations = translations.Translate(
            0.0f,
            -camera_up_.y_ * camera_speed * time,
            0.0f);

        //Transform Matrix4 / Vector3
        camera_position_ = translations * camera_position_ ;

    }

    //DOWN
    if (suffer.input_manager_.IsKeyPressed(InputManager::k_E)) {

        mathmorra::Vector3 down = camera_up_;

        mathmorra::Matrix4 translations = translations.Translate(
            0.0f,
            down.y_ * speed_ * time,
            0.0f);

        //Transform Matrix4 / Vector3
        camera_position_ = translations * camera_position_;

    }

    //ROTATE Y
    if (suffer.input_manager_.IsKeyPressed(InputManager::k_Left)) {
        camera_direction_ = mathmorra::Matrix4::RotateY(0.004f) * camera_direction_;
    }
    if (suffer.input_manager_.IsKeyPressed(InputManager::k_Right)) {
        camera_direction_ = mathmorra::Matrix4::RotateY(-0.004f) * camera_direction_;
    }

    if (suffer.input_manager_.IsKeyPressed(InputManager::k_Up)) {
        camera_direction_ = mathmorra::Matrix4::RotateX(0.004f) * camera_direction_;
    }
    if (suffer.input_manager_.IsKeyPressed(InputManager::k_Down)) {
        camera_direction_ = mathmorra::Matrix4::RotateX(-0.004f) * camera_direction_;
    }

    camera->SetPosition(camera_position_);

    mathmorra::Vector2 mouse = suffer.GetMousePosition();

    float angleX = (mouse.x_ / (WINDOW_WIDTH)) * 6.28f;
    float angleY = (mouse.y_ / (WINDOW_HEIGHT)) * 6.28f;
    
    
    //MOUSE CONTROL - QUATERNIONS
    mathmorra::Vector3 x = mathmorra::Vector3(1.0f, 0.0f, 0.0f);
    mathmorra::Vector3 y = mathmorra::Vector3(0.0f, 1.0f, 0.0f);

    mathmorra::Quaternion q = q.EulerAngles(x, -angleY);
    mathmorra::Quaternion p = p.EulerAngles(y, angleX);
    mathmorra::Quaternion quaternion = quaternion.Multiply(p, q);

    quaternion.Normalize();

    mathmorra::Vector3 back;
    back = { 0.0f, 0.0f, -1.0f };
    back = quaternion.RotateVectorByQuaternion(back, quaternion);
    back.Normalize();

    camera_target_ = -(back);

}

// --------------------------------------------------- //

void Suffer::Camera::SetSensibility(float new_sensibility){
    sensibility_ = new_sensibility;
}

// --------------------------------------------------- //

void Suffer::Camera::SetSpeed(float new_speed){
    speed_ = new_speed;
}

// --------------------------------------------------- //

bool Suffer::Camera::FPS(){
    return fps_movement_;
}

// --------------------------------------------------- //

Suffer::Camera::~Camera() {

}

// --------------------------------------------------- //

void Suffer::Camera::Update(){

    if (suffer.input_manager_.IsKeyDown(InputManager::k_F1)) {
        fps_movement_ = !fps_movement_;
    }

    SetupPerspective(field_of_view_, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.01f, 150.0f);

    view_matrix_ = mathmorra::Matrix4(
        mathmorra::Vector4(camera_right_, 0.0f),
        mathmorra::Vector4(camera_up_, 0.0f),
        mathmorra::Vector4(camera_target_, 0.0f),
        mathmorra::Vector4(camera_position_, 1.0f)
    );

    view_matrix_.GetInverse(&view_matrix_);

}

// --------------------------------------------------- //