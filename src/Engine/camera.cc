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


Suffer::Camera::Camera() {

    field_of_view_ = 50.0f;
    speed_ = 1.0f;

    camera_position_ = mathmorra::Vector3(0.0f, 0.0f, -15.0f);
    camera_target_ = mathmorra::Vector3(0.0f, 0.0f, 1.0f);

    camera_up_ = mathmorra::Vector3(0.0f, 1.0f, 0.0f);
    camera_right_ = mathmorra::Vector3(1.0f, 0.0f, 0.0f);
    camera_forward_ = mathmorra::Vector3(0.0f, 0.0f, -1.0f);
    camera_direction_ = mathmorra::Vector3(0.0f, 0.0f, 1.0f);

    fps_movement_ = false;

}


Suffer::Camera& Suffer::Camera::operator=(const Camera& cam){

    Camera camera_;

    camera_.camera_position_ = cam.camera_position_;
    camera_.camera_target_ = cam.camera_target_;
    camera_.camera_direction_ = cam.camera_direction_;

    camera_.camera_up_ = cam.camera_up_;
   // camera_.camera_right_ = cam.camera_right_;
    camera_.camera_forward_ = cam.camera_forward_;

    camera_.field_of_view_ = cam.field_of_view_;

    return camera_;

}

void Suffer::Camera::SetupPerspective(float fovy, float aspect, float znear, float zfar) {

}

void Suffer::Camera::SetupFrustum(float left, float right, float bottom, float top, float znear, float zfar){

}

void Suffer::Camera::SetPosition(const mathmorra::Vector3 position) {
    camera_position_ = position;
}

void Suffer::Camera::SetViewDirection(const mathmorra::Vector3 view_direction) {
    camera_direction_ = view_direction;
}

void Suffer::Camera::SetViewDirection(const float view_direction[3]) {
    camera_direction_ = mathmorra::Vector3(view_direction[0], view_direction[1], view_direction[2]);
}

void Suffer::Camera::SetPosition(const float position[3]) {
    camera_position_ = mathmorra::Vector3(position[0], position[1], position[2]);
}

void Suffer::Camera::SetViewTarget(const mathmorra::Vector3 target) {
    camera_target_ = target;
}

void Suffer::Camera::SetFOV(const float new_fov){
    field_of_view_ = new_fov;
}

void Suffer::Camera::SetViewTarget(const float target[3]) {
    camera_target_ = mathmorra::Vector3(target[0], target[1], target[2]);
}

void Suffer::Camera::SetForward(const float forward[3]){
    camera_forward_ = mathmorra::Vector3(forward[0], forward[1], forward[2]);
}

void Suffer::Camera::SetProjectionMatrix(mathmorra::Matrix4 projection_matrix){
    projection_matrix_ = projection_matrix;
}

void Suffer::Camera::SetProjectionMatrix(const float m[16]){
    projection_matrix_ = mathmorra::Matrix4(m[16]);
}

void Suffer::Camera::SetForward(const mathmorra::Vector3 forward){
    camera_forward_ = forward;
}

void Suffer::Camera::SetViewMatrix(mathmorra::Matrix4 view_matrix){
    view_matrix_ = view_matrix;
}

void Suffer::Camera::SetViewMatrix(const float m[16]){
    view_matrix_ = mathmorra::Matrix4(m[16]);
}

const float* Suffer::Camera::Position() const {
    return &camera_position_.x_;
}

const float* Suffer::Camera::Target() const {
    return &camera_target_.x_;
}

const float* Suffer::Camera::Up() const {
    return &camera_up_.x_;
}

const float Suffer::Camera::Fov() const{
    return field_of_view_;
}

mathmorra::Matrix4 Suffer::Camera::ProjectionMatrix(){
    return projection_matrix_;
}

mathmorra::Matrix4 Suffer::Camera::ViewMatrix(){
    return view_matrix_;
}

// FPS Movement
void Suffer::Camera::CameraMovement(ref_ptr<Camera> camera){

    float time = SufferManager::instance().DeltaTime() * 0.01f;
    float camera_speed = speed_;

    // MOUSE UTILS
    mathmorra::Vector2 current_position;
    mathmorra::Vector2 last_position;

    // CAMERA UTILS
    mathmorra::Vector3 right;
    mathmorra::Vector3 up;
    const float* updirection = camera->Up();

    up.x_ = *updirection;
    up.y_ = *(updirection + 1);
    up.z_ = *(updirection + 2);

    right = right.CrossProduct(camera_forward_.Normalized(), up.Normalized());


    // FORWARD
    if (Suffer::IsKeyPressed(k_S)) {

        mathmorra::Matrix4 translations = translations.Translate(
            camera_forward_.x_ * camera_speed * time,
            camera_forward_.y_ * camera_speed * time,
            camera_forward_.z_ * camera_speed * time);

        //Transform Matrix4 / Vector3
        camera_position_ = translations.Transpose() * camera_position_;
    }

    // LEFT
    if (Suffer::IsKeyPressed(k_A)) {

        mathmorra::Vector3 left = right * -1.0f;
        mathmorra::Matrix4 translations = translations.Translate(
            left.x_ * camera_speed * time,
            0.0f,
            left.z_ * camera_speed * time);

        //Transform Matrix4 / Vector3
        camera_position_ = translations.Transpose() * camera_position_ ;
    }

    // RIGHT
    if (Suffer::IsKeyPressed(k_D)) {

        mathmorra::Matrix4 translations = translations.Translate(
            right.x_ * camera_speed * time,
            0.0f,
            right.z_ * camera_speed * time);

        //Transform Matrix4 / Vector3
        camera_position_ = translations.Transpose() * camera_position_ ;

    }

    // BACK
    if (Suffer::IsKeyPressed(k_W)) {

        mathmorra::Vector3 back = camera_forward_ * -1.0f;
        mathmorra::Matrix4 translations = translations.Translate(back.x_ * camera_speed * time,
            back.y_ * camera_speed * time,
            back.z_ * camera_speed * time);

        //Transform Matrix4 / Vector3
        camera_position_ = translations.Transpose() * camera_position_ ;

    }

    //UP
    if (Suffer::IsKeyPressed(k_E)) {

        mathmorra::Matrix4 translations = translations.Translate(
            0.0f,
            up.y_ * camera_speed * time,
            0.0f);

        //Transform Matrix4 / Vector3
        camera_position_ = translations.Transpose() * camera_position_ ;

    }

    //DOWN
    if (Suffer::IsKeyPressed(k_Q)) {

        mathmorra::Vector3 down = up * -1.0f;

        mathmorra::Matrix4 translations = translations.Translate(
            0.0f,
            down.y_ * speed_ * time,
            0.0f);

        //Transform Matrix4 / Vector3
        camera_position_ = translations.Transpose() * camera_position_;

    }

    float pos[3] = { camera_position_.x_, camera_position_.y_, camera_position_.z_ };
    camera->SetPosition(pos);

    mathmorra::Vector2 mouse = SufferManager::instance().GetMousePosition();

    float angleX = (mouse.x_ / (WINDOW_WIDTH)) * 6.28f;
    float angleY = (mouse.y_ / (WINDOW_HEIGHT)) * 6.28f;


    //MOUSE CONTROL - QUATERNIONS
    mathmorra::Vector3 x = mathmorra::Vector3(1.0f, 0.0f, 0.0f);
    mathmorra::Vector3 y = mathmorra::Vector3(0.0f, 1.0f, 0.0f);

    mathmorra::Quaternion q = q.EulerAngles(x, angleY);
    mathmorra::Quaternion p = p.EulerAngles(y, angleX);

    mathmorra::Quaternion quaternion = quaternion.Multiply(p, q);

    camera_forward_ = { 0.0f, 0.0f, -1.0f };
    camera_forward_ = quaternion.RotateVectorByQuaternion(camera_forward_, quaternion);

    camera->SetViewDirection(-camera_forward_);

}

void Suffer::Camera::SetSensibility(float new_sensibility){
    sensibility_ = new_sensibility;
}

void Suffer::Camera::SetSpeed(float new_speed){
    speed_ = new_speed;
}

Suffer::Camera::~Camera() {

}

void Suffer::Camera::Update(){

    if (Suffer::IsKeyDown(k_F1)) {
        fps_movement_ = !fps_movement_;
    }

    camera_right_ = mathmorra::Vector3::Normalized(
        mathmorra::Vector3::CrossProduct(camera_direction_, camera_up_)
    );

    camera_up_ = mathmorra::Vector3::CrossProduct(camera_right_, camera_direction_);

    projection_matrix_ = projection_matrix_.PerspectiveMatrix(
        field_of_view_, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.01f, 15000.0f);

    view_matrix_ = mathmorra::Matrix4(
        mathmorra::Vector4(camera_right_,    0.0f),
        mathmorra::Vector4(camera_up_,       0.0f),
        mathmorra::Vector4(camera_forward_,  0.0f),
        mathmorra::Vector4(camera_position_, 1.0f)
    );

    view_matrix_.GetInverse(&view_matrix_);
}
