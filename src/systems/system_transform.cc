/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 11-28-2019
* SystemTransform Source
*/

#include "system_transform.h"
#include "math_utils.h"
#include "quaternion.h"
#include "component_child.h"

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
    Suffer::Transform* transform_component = static_cast<Suffer::Transform*>(component_);

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

    if (!go->HasComponent(Component::kComponentKind_Child)) {
        transform_component->global_position_ = transform_component->position_;
    }

    // Update the Forward vector
    mathmorra::Vector3 x = mathmorra::Vector3(1.0f, 0.0f, 0.0f);
    mathmorra::Vector3 y = mathmorra::Vector3(0.0f, 1.0f, 0.0f);
    mathmorra::Vector3 z = mathmorra::Vector3(0.0f, 0.0f, 1.0f);

    mathmorra::Quaternion qx = qx.EulerAngles(x, -transform_component->rotation_.x_);
    mathmorra::Quaternion qy = qy.EulerAngles(y, -transform_component->rotation_.y_);
    mathmorra::Quaternion qz = qz.EulerAngles(z, -transform_component->rotation_.z_);
    mathmorra::Quaternion quaternion = quaternion.Multiply(qz, qy);
    quaternion = quaternion.Multiply(quaternion, qx);

    quaternion.Normalize();
    transform_component->forward_ = { 0.0f, 0.0f, 1.0f };
    transform_component->forward_ = quaternion.RotateVectorByQuaternion(transform_component->forward_, quaternion);
    transform_component->forward_.Normalize();

    // Also re-calculate the Right and Up vector
    transform_component->right_ = mathmorra::Vector3::CrossProduct(
        transform_component->forward_,
        mathmorra::Vector3(0.0f, 1.0f, 0.0f)
    ).Normalized();

    transform_component->up_ = mathmorra::Vector3::CrossProduct(
        transform_component->right_,
        transform_component->forward_
    ).Normalized();


}

// --------------------------------------------------- //