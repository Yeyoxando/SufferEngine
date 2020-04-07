/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 11-28-2019
* ComponentTransform Source
*/

#include "component_transform.h"

// --------------------------------------------------- //

void Suffer::Transform::Scale(float x, float y, float z){
    scale_ = { x, y ,z };
}

// --------------------------------------------------- //

void Suffer::Transform::Scale(mathmorra::Vector3 scale){
    scale_ = scale;
}

// --------------------------------------------------- //

void Suffer::Transform::Rotate(float x, float y, float z){
    rotation_ = { x, y, z };
}

// --------------------------------------------------- //

void Suffer::Transform::Translate(mathmorra::Vector3 position){
    position_ = position;
}

float* Suffer::Transform::Up(){
    return &up_.x_;
}

float* Suffer::Transform::Right(){
    return &right_.x_;
}

float* Suffer::Transform::Forward(){
    return &forward_.x_;
}

float* Suffer::Transform::GetScale(){
    return &scale_.x_;
}

// --------------------------------------------------- //

float* Suffer::Transform::GetRotation(){
    return &rotation_.x_;
}

// --------------------------------------------------- //

float* Suffer::Transform::GetPosition(){
    return &position_.x_;
}

// --------------------------------------------------- //

float* Suffer::Transform::GetGlobalPosition(){
    return &global_position_.x_;
}

// --------------------------------------------------- //

mathmorra::Matrix4 Suffer::Transform::GetModelMatrix(){
    return model_;
}

// --------------------------------------------------- //

void Suffer::Transform::Rotate(mathmorra::Vector3 rotation){
    rotation_ = rotation;
}

// --------------------------------------------------- //

void Suffer::Transform::Translate(float x, float y, float z){
    position_ = { x, y, z };
}

// --------------------------------------------------- //

void Suffer::Transform::Init() {

    position_ = { 0.0f, 0.0f, 0.0f };
    scale_ = { 1.0f, 1.0f, 1.0f };
    rotation_ = { 0.0f, 0.0f, 0.0f };

    up_ = { 0.0f, 1.0f, 0.0f };
    right_ = { -1.0f, 0.0f, 0.0f };
    forward_ = mathmorra::Vector3::CrossProduct(up_, right_);

}

// --------------------------------------------------- //

Suffer::Transform::~Transform(){

}

// --------------------------------------------------- //
