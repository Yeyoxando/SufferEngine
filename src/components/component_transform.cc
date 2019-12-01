/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 11-28-2019
* ComponentTransform Source
*/

#include "component_transform.h"

// --------------------------------------------------- //

Suffer::TransformComponent::TransformComponent(){

  Init();

}
// --------------------------------------------------- //

void Suffer::TransformComponent::Scale(float x, float y, float z){
    scale_ = { x, y ,z };
}

// --------------------------------------------------- //

void Suffer::TransformComponent::Scale(mathmorra::Vector3 scale){
    scale_ = scale;
}

// --------------------------------------------------- //

void Suffer::TransformComponent::Rotate(float x, float y, float z){
    rotation_ = { x, y, z };
}

// --------------------------------------------------- //

void Suffer::TransformComponent::Translate(mathmorra::Vector3 position){
    position_ = position;
}

float* Suffer::TransformComponent::GetScale(){
    return &scale_.x_;
}

// --------------------------------------------------- //

float* Suffer::TransformComponent::GetRotation(){
    return &rotation_.x_;
}

// --------------------------------------------------- //

float* Suffer::TransformComponent::GetPosition(){
    return &position_.x_;
}

mathmorra::Matrix4 Suffer::TransformComponent::GetModelMatrix(){
    return model_;
}

// --------------------------------------------------- //

void Suffer::TransformComponent::Rotate(mathmorra::Vector3 rotation){
    rotation_ = rotation;
}

// --------------------------------------------------- //

void Suffer::TransformComponent::Translate(float x, float y, float z){
    position_ = { x, y, z };
}

// --------------------------------------------------- //

void Suffer::TransformComponent::Init(){

    kind_ = Component::kComponentKind_Transform;

    position_ = { 0.0f, 0.0f, 0.0f };
    scale_ = { 1.0f, 1.0f, 1.0f };
    rotation_ = { 0.0f, 0.0f, 0.0f };

    up_ = { 0.0f, 1.0f, 0.0f };
    right_ = { 1.0f, 0.0f, 0.0f };
    forward_ = mathmorra::Vector3::CrossProduct(up_, right_);

}

// --------------------------------------------------- //

Suffer::TransformComponent::~TransformComponent(){

}

// --------------------------------------------------- //
