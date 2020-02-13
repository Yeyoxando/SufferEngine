/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 11-28-2019
* SystemTransform Source
*/

#include "system_transform.h"

// --------------------------------------------------- //

Suffer::SystemTransform::SystemTransform(){

}

// --------------------------------------------------- //

Suffer::SystemTransform::~SystemTransform(){

}

// --------------------------------------------------- //

void Suffer::SystemTransform::Execute(GameObject* go){
    
    if (go == nullptr) assert(false && "NULL GameObject");
    if (!go->HasComponent(Component::ComponentKind::kComponentKind_Transform)) return;

    auto component_ = go->GetComponent(Suffer::Component::ComponentKind::kComponentKind_Transform);
    Suffer::Transform* transform_component = reinterpret_cast<Suffer::Transform*>(component_);

    mathmorra::Matrix4 translation_mat;
    translation_mat = translation_mat.Translate(
        transform_component->position_.x_,
        transform_component->position_.y_,
        transform_component->position_.z_);

    mathmorra::Matrix4 rotation_mat_x;
    mathmorra::Matrix4 rotation_mat_y;
    mathmorra::Matrix4 rotation_mat_z;
    rotation_mat_x = rotation_mat_x.RotateX(transform_component->rotation_.x_);
    rotation_mat_y = rotation_mat_y.RotateY(transform_component->rotation_.y_);
    rotation_mat_z = rotation_mat_z.RotateZ(transform_component->rotation_.z_);

    mathmorra::Matrix4 scale_mat;
    scale_mat = scale_mat.Scale(
        transform_component->scale_.x_,
        transform_component->scale_.y_,
        transform_component->scale_.z_);

    transform_component->model_ = scale_mat * (rotation_mat_x * rotation_mat_y * rotation_mat_z) * translation_mat;

}

// --------------------------------------------------- //