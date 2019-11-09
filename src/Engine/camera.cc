#include <camera.h>

Suffer::Camera::Camera(){

    position_ = glm::vec3(0.0f, 0.0f, 5.0f);
    camera_target_ = glm::vec3(0.0f, 0.0f, 0.0f);
    camera_direction_ = glm::vec3(0.0f, 0.0f, 0.0f);

    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    camera_right_ = glm::normalize(glm::cross(up, camera_direction_));
    camera_up_ = glm::cross(camera_direction_, camera_right_);

}

void Suffer::Camera::SetupPerspective(float fovy, float aspect, float znear, float zfar){

}

void Suffer::Camera::SetPosition(const glm::vec3 position){
    position_ = position;
}

void Suffer::Camera::SetViewDirection(const glm::vec3 view_direction){
    camera_direction_ = view_direction;
}

void Suffer::Camera::SetViewDirection(const float view_direction[3]){
    camera_direction_ = glm::vec3(view_direction[0], view_direction[1], view_direction[2]);
}

void Suffer::Camera::SetPosition(const float position[3]){
    position_ = glm::vec3(position[0], position[1], position[2]);
}

void Suffer::Camera::SetViewTarget(const glm::vec3 target){
    camera_target_ = target;
}

void Suffer::Camera::SetViewTarget(const float target[3]){
    camera_target_ = glm::vec3(target[0], target[1], target[2]);
}

const float* Suffer::Camera::Position() const{
    return &position_.x;
}

const float* Suffer::Camera::Target() const{
    return &camera_target_.x;
}

const float* Suffer::Camera::Up() const{
    return &camera_up_.x;
}

Suffer::Camera::~Camera(){

}

