/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 03-11-2020
* HierarchySystem Source
*/

#include "system_hierarchy.h"
#include "component_child.h"
#include "component_transform.h"

Suffer::SystemHierarchy::SystemHierarchy(){

}

Suffer::SystemHierarchy::~SystemHierarchy(){

}

void Suffer::SystemHierarchy::Execute(GameObject* go){

    if (!go->HasComponent(Suffer::Component::kComponentKind_Child)) return;
    if (!go->HasComponent(Suffer::Component::kComponentKind_Transform)) return;

    auto my_child_comp = go->GetComponent(Suffer::Component::ComponentKind::kComponentKind_Child);
    Suffer::ChildComponent* child_component = static_cast<Suffer::ChildComponent*>(my_child_comp);
    GameObject* parent = child_component->parent_reference_;

    if (!parent->HasComponent(Suffer::Component::kComponentKind_Transform)) return;

    auto my_transform = go->GetComponent(Suffer::Component::ComponentKind::kComponentKind_Transform);
    Suffer::Transform* transform_component = static_cast<Suffer::Transform*>(my_transform);
    auto component_ = parent->GetComponent(Suffer::Component::ComponentKind::kComponentKind_Transform);
    Suffer::Transform* parent_transform_component = static_cast<Suffer::Transform*>(component_);
    mathmorra::Matrix4 parent_model = parent_transform_component->GetModelMatrix();
    transform_component->model_ = transform_component->model_ * parent_model;

}