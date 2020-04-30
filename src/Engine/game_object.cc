/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 10-12-2019
* GameObject Source (Transform)
*/

#include <game_object.h>
#include <draw_geometry.h>
#include <matrix4.h>
#include <imgui.h>
#include "interface.h"
#include <suffermanager.h>
#include "internal_interface.h"
#include "component_geometry.h"
#include "component_light.h"
#include "component_child.h"
#include "component_material.h"

// --------------------------------------------------- //

Suffer::GameObject::GameObject() {

  name_ = "GameObject";
  childs_.clear();
  //suffer.entities_.push_back(this);
  id_ = suffer.number_of_game_objects_;
  suffer.number_of_game_objects_++;

}

// --------------------------------------------------- //

Suffer::GameObject::~GameObject() {

}

// --------------------------------------------------- //

bool Suffer::GameObject::operator!=(const GameObject& go){
    return false;
}

// --------------------------------------------------- //

Suffer::GameObject::GameObject(const GameObject& go) {

}

// --------------------------------------------------- //

Suffer::Component* Suffer::GameObject::GetComponent(Component::ComponentKind component){

  if (!HasComponent(component)) return nullptr;
  s32 component_id = (s32)component;
  auto search = components_.find(component_id);
  return static_cast<Suffer::Component*>(search->second.get());

}

// --------------------------------------------------- //

bool Suffer::GameObject::HasComponent(Component::ComponentKind component){

  // TODO: how to solve user components issue.
  s32 component_id = (s32)component;
  auto search = components_.find(component_id);
  if (search == components_.end()) return false;
  return true;

}

// --------------------------------------------------- //

void Suffer::GameObject::AddComponent(ref_ptr<Component> new_component){

  assert(new_component.get() != nullptr);
  if (new_component.get() == nullptr) return;
  if(HasComponent(new_component->kind_)) 
    assert(false && "The GameObject already has a component of this kind");

  if (new_component->kind_ == Component::ComponentKind::kComponentKind_Invalid) 
    assert(false && "Invalid ComponentKind.");

  new_component->game_object_reference_ = this;

  if (new_component->kind_ == Component::ComponentKind::kComponentKind_Light) {
      LightComponent* light = static_cast<LightComponent*>(new_component.get());
      if (!light->initialized_) {
          printf("CRITICAL ERROR: The LIGHT has not been initialized.\n");
          printf("Miss calling Init() function in the component?\n");
          abort();
      }
      light->SetActive(true);
  }
  
  components_.insert(std::pair<s32, ref_ptr<Component>>((s32)new_component->kind_, 
                                                        new_component));

}

// --------------------------------------------------- //

void Suffer::GameObject::RemoveComponent(Component::ComponentKind component){

  if (!HasComponent(component))
    assert(false && "The GameObject does not have a component of this kind");

  if (component == Component::ComponentKind::kComponentKind_Invalid)
    assert(false && "Invalid ComponentKind.");

  //if (component == Component::ComponentKind::kComponentKind_Light)
  //    suffer.light_manager_.lights_.clear(0);

  components_.erase(component);

}

// --------------------------------------------------- //

void Suffer::GameObject::AddChild(ref_ptr<GameObject> child){

    assert(child != nullptr && "ERROR: NULL Child!");
    if (child == nullptr) return;

    Suffer::ref_ptr<ChildComponent> child_component_;
    child_component_.alloc();
    child_component_->parent_reference_ = this;
    child->AddComponent(child_component_.get());

    childs_.push_back(child);

}

// --------------------------------------------------- //

const char* Suffer::GameObject::Name(){
    return name_;
}

// --------------------------------------------------- //

void Suffer::GameObject::SetName(const char* name){
    name_ = (char*)name;
}

// --------------------------------------------------- //

Suffer::GameObject* Suffer::GameObject::GetChild(u32 child) {
    std::list<ref_ptr<GameObject>>::iterator it = childs_.begin();
    std::advance(it, child);
    return it->get();
}

// --------------------------------------------------- //

u32 Suffer::GameObject::NumberChilds(){
    return childs_.size();
}

// --------------------------------------------------- //

u32 Suffer::GameObject::NumberChildsRecursively(GameObject* go){

    u32 number_of_childs = go->NumberChilds();
    u32 result = 0;
    u32 total_game_objects = 0;

    for (u32 i = 0; i < number_of_childs; ++i) {
        result = go->NumberChildsRecursively(go->GetChild(i));
    }

    total_game_objects += go->NumberChilds();

    return total_game_objects;

}

// --------------------------------------------------- //

u32 Suffer::GameObject::ID(){
    return id_;
}

// --------------------------------------------------- //

void Suffer::GameObject::SetArchetype(Archetype new_archetype){

    switch (new_archetype){
        case Suffer::GameObject::kArchetype_Invalid:
            break;
        case Suffer::GameObject::kArchetype_Drawable: {
            if (!HasComponent(Suffer::Component::kComponentKind_Transform)) {
                Suffer::ref_ptr<Transform> transform_component_;
                transform_component_.alloc();
                AddComponent(transform_component_.get());
            }
            if (!HasComponent(Suffer::Component::kComponentKind_Material)) {
                Suffer::ref_ptr<MaterialComponent> material_component_;
                material_component_.alloc();

                Suffer::ref_ptr<Suffer::MaterialComponent::BlinnPhongParams> material_params;
                material_params.alloc();
                material_params->color_ = mathmorra::Vector4(1.0f, 0.5f, 1.0f, 1.0f);
                material_component_->SetParams(material_params.get());

                AddComponent(material_component_.get());
            }
            if (!HasComponent(Suffer::Component::kComponentKind_Geometry)) {
                Suffer::ref_ptr<GeometryComponent> geometry_component_;
                geometry_component_.alloc();
                geometry_component_->SetDrawMode(Suffer::GeometryComponent::kDrawMode_Triangles);
                geometry_component_->CreateGeometryWithShape(Suffer::GeometryComponent::kBasicShapes_Cube);
                AddComponent(geometry_component_.get());
            }
            break;
        }
        default:
            break;
    }

}

// --------------------------------------------------- //

void Suffer::GameObject::Step(float delta_time){

    // Updates

    // Logic

}

// --------------------------------------------------- //

void Suffer::GameObject::Destroy(){

    // Destroy Himself
    std::map <s32, ref_ptr<Component>>::iterator components_iterator_;
    Array<Component::ComponentKind> components_to_delete_;
    components_to_delete_.alloc(components_.size());

    u16 index = 0;
    for (components_iterator_ = components_.begin();
         components_iterator_ != components_.end(); 
         ++components_iterator_) {

       auto type = components_iterator_->second->kind_;
       components_to_delete_[index] = components_iterator_->second->kind_;

       index++;

    }

    for (u16 i = 0; i < index; ++i) {
        RemoveComponent(components_to_delete_[i]);
    }

    //suffer.GetCurrentScene()->RemoveGameObject(this);
    //suffer.entities_.erase(suffer.entities_.begin() + id_);

}
