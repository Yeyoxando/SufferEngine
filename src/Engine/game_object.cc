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
#include "internal_game_object.h"
#include "component_geometry.h"

// --------------------------------------------------- //

Suffer::GameObject::GameObject() {

  data_ = new Data();

  name_ = "GameObject";
  data_->lua_error_ = false;

}

// --------------------------------------------------- //

Suffer::GameObject::~GameObject() {
    if (data_ == nullptr) return;
    delete data_;
    data_ = nullptr;
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

  if(HasComponent(new_component->kind_)) 
    assert(false && "The GameObject already has a component of this kind");

  if (new_component->kind_ == Component::ComponentKind::kComponentKind_Invalid) 
    assert(false && "Invalid ComponentKind.");

  new_component->game_object_reference_ = this;
  
  components_.insert(std::pair<s32, ref_ptr<Component>>((s32)new_component->kind_, 
                                                        new_component));

}

// --------------------------------------------------- //

void Suffer::GameObject::RemoveComponent(Component::ComponentKind component){

  if (!HasComponent(component))
    assert(false && "The GameObject does not have a component of this kind");

  if (component == Component::ComponentKind::kComponentKind_Invalid)
    assert(false && "Invalid ComponentKind.");

  components_.erase(component);

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

Suffer::GameObject* Suffer::GameObject::Data::GetReference(lua_State* L) {
    
    lua_pushstring(L, "THIS");
    lua_gettable(L, LUA_REGISTRYINDEX);
    const void* raw_ptr = lua_topointer(L, -1);
    
    GameObject* ptr = reinterpret_cast<GameObject*>(const_cast<void*>(raw_ptr));
    if (ptr->data_ == nullptr) return nullptr;
    return ptr;

}

// --------------------------------------------------- //

void Suffer::GameObject::StartUpLUA(const char* luaCodeFile){

    data_->lua_file_ = (char*)luaCodeFile;
    assert(data_->_script == nullptr && "Invalid script");
    data_->_script = luaL_newstate();

    luaL_openlibs(data_->_script);


    // PUSH FUNCTIONS FOR LUA
    lua_pushcfunction(data_->_script, data_->lua_Rotate);    // +1
    lua_setglobal(data_->_script, "Rotate");                 // -1

    lua_pushcfunction(data_->_script, data_->lua_Translate); // +1
    lua_setglobal(data_->_script, "Translate");              // -1

    lua_pushcfunction(data_->_script, data_->lua_Scale);     // +1
    lua_setglobal(data_->_script, "Scale");                  // -1

    lua_pushcfunction(data_->_script, data_->lua_SetDrawMode);     // +1
    lua_setglobal(data_->_script, "SetDrawMode");                  // -1

    lua_pushcfunction(data_->_script, data_->lua_SetPredefinedGeometry);     // +1
    lua_setglobal(data_->_script, "SetPredefinedGeometry");                  // -1



    lua_pushstring(data_->_script, "THIS");
    lua_pushlightuserdata(data_->_script, this);
    lua_settable(data_->_script, LUA_REGISTRYINDEX);

    data_->reference = data_->GetReference(data_->_script);

    data_->execute_lua_ = true;

}

// --------------------------------------------------- //


// --------------------------------------------------- //

Suffer::GameObject* Suffer::GameObject::GetChild(u32 child){
    // TODO: Expand this
    return &GameObject();
}

// --------------------------------------------------- //

u32 Suffer::GameObject::NumberChilds(){
    return 0;
}

// --------------------------------------------------- //

u32 Suffer::GameObject::NumberChildsRecursively(GameObject* go){

    u32 number_of_childs = go->NumberChilds();
    u32 result = 0;

    for (u32 i = 0; i < number_of_childs; ++i) {
        result = go->NumberChildsRecursively(go->GetChild(i));
    }

    return result;

}

// --------------------------------------------------- //

void Suffer::GameObject::Step(float delta_time){

    // Updates
    if (!data_->lua_error_ && data_->execute_lua_) {
      int status = luaL_dofile(data_->_script, data_->lua_file_);
      data_->CheckLuaError(status);
    }

    // Logic

}

// --------------------------------------------------- //

void Suffer::GameObject::Destroy(){
    // Destroy Himself
}

// --------------------------------------------------------------- //
/*
           _     _   _  ___         _____ _          __  __
          | |   | | | |/ _ \       /  ___| |        / _|/ _|
          | |   | | | / /_\ \      \ `--.| |_ _   _| |_| |_
          | |   | | | |  _  |       `--. \ __| | | |  _|  _|
          | |___| |_| | | | |      /\__/ / |_| |_| | | | |
          \_____/\___/\_| |_/      \____/ \__|\__,_|_| |_|
*/
// --------------------------------------------------------------- //

int Suffer::GameObject::Data::lua_Rotate(lua_State* L) {

    int arguments = lua_gettop(L);
    if (arguments != 3) {
        return luaL_error(L, "Invalid call expected three argument.");
    }
    float x = lua_tonumber(L, 1);
    float y = lua_tonumber(L, 2);
    float z = lua_tonumber(L, 3);

    GetReference(L)->data_->RotateL(x, y, z);

    lua_pop(L, 1);
    return 0;

}

// --------------------------------------------------------------- //

int Suffer::GameObject::Data::lua_Translate(lua_State* L){

    int arguments = lua_gettop(L);
    if (arguments != 3) {
        return luaL_error(L, "Invalid call, expected three arguments.");
    }
    float x = lua_tonumber(L, 1);
    float y = lua_tonumber(L, 2);
    float z = lua_tonumber(L, 3);

    GetReference(L)->data_->TranslateL(x, y, z);

    lua_pop(L, 1);
    return 0;

}

// --------------------------------------------------------------- //

int Suffer::GameObject::Data::lua_Scale(lua_State* L){

    int arguments = lua_gettop(L);
    if (arguments != 3) {
        return luaL_error(L, "Invalid call, expected three arguments");
    }

    float x = lua_tonumber(L, 1);
    float y = lua_tonumber(L, 2);
    float z = lua_tonumber(L, 3);

    if (GetReference(L)->HasComponent(Component::kComponentKind_Transform)) {
        Transform* transform = reinterpret_cast<Transform*>(
            GetReference(L)->GetComponent(Component::kComponentKind_Transform));
        transform->Scale(mathmorra::Vector3(x, y, z));
    }

    lua_pop(L, 1);
    return 0;

}

// --------------------------------------------------------------- //

int Suffer::GameObject::Data::lua_SetPredefinedGeometry(lua_State* L){

  auto geometry_component = GetReference(L)->GetComponent(Suffer::Component::kComponentKind_Geometry);
  GeometryComponent* geometry_ = reinterpret_cast<GeometryComponent*>(geometry_component);

    int arguments = lua_gettop(L);
    if (arguments != 2) {
        return luaL_error(L, "Invalid call, expected one argument");
    }

    const char* x = lua_tostring(L, 1);

    GeometryComponent::BasicShapes new_shape = GeometryComponent::BasicShapes::kBasicShapes_Triangle;
    
    if (!strcmp(x, "Triangle")) new_shape = GeometryComponent::BasicShapes::kBasicShapes_Triangle;
    if (!strcmp(x, "Quad"))     new_shape = GeometryComponent::BasicShapes::kBasicShapes_Quad;
    if (!strcmp(x, "Cube"))     new_shape = GeometryComponent::BasicShapes::kBasicShapes_Cube;
    if (!strcmp(x, "Sphere"))   new_shape = GeometryComponent::BasicShapes::kBasicShapes_Sphere;

    geometry_->CreateGeometryWithShape(new_shape);

    lua_pop(L, 1);
    return 0;

}

// --------------------------------------------------------------- //

int Suffer::GameObject::Data::lua_SetDrawMode(lua_State* L){

  auto geometry_component = GetReference(L)->GetComponent(Suffer::Component::kComponentKind_Geometry);
  GeometryComponent* geometry_ = reinterpret_cast<GeometryComponent*>(geometry_component);

    int arguments = lua_gettop(L);
    if (arguments != 2) {
        return luaL_error(L, "Invalid call, expected one argument");
    }

    const char* x = lua_tostring(L, 1);

    GeometryComponent::DrawMode draw_mode = GeometryComponent::DrawMode::kDrawMode_Lines;

    if (!strcmp(x, "Lines"))     draw_mode = GeometryComponent::DrawMode::kDrawMode_Lines;
    if (!strcmp(x, "LineLoop"))  draw_mode = GeometryComponent::DrawMode::kDrawMode_LineLoop;
    if (!strcmp(x, "Points"))    draw_mode = GeometryComponent::DrawMode::kDrawMode_Points;
    if (!strcmp(x, "Triangles")) draw_mode = GeometryComponent::DrawMode::kDrawMode_Triangles;

    geometry_->SetDrawMode(draw_mode);

    lua_pop(L, 1);
    return 0;

}

// --------------------------------------------------------------- //

void Suffer::GameObject::Data::CheckLuaError(int status) {

    if (status) {
        const char* error = lua_tostring(_script, -1);
        Interface::log.AddLog("\n[" _error_ "] [%s]", error);
        lua_error_ = true;
    }

}

// --------------------------------------------------------------- //

void Suffer::GameObject::Data::RotateL(float x, float y, float z) {

    if (reference->HasComponent(Component::kComponentKind_Transform)) {
      Transform* transform = reinterpret_cast<Transform*>(
      reference->GetComponent(Component::kComponentKind_Transform));
      transform->Rotate(mathmorra::Vector3(transform->GetRotation()) + 
                        mathmorra::Vector3(x, y, z));
    }

}

// --------------------------------------------------------------- //

void Suffer::GameObject::Data::TranslateL(float x, float y, float z){

    if (reference->HasComponent(Component::kComponentKind_Transform)) {
        Transform* transform = reinterpret_cast<Transform*>(
        reference->GetComponent(Component::kComponentKind_Transform));
        transform->Translate(/*mathmorra::Vector3(transform->GetPosition()) + 
                             */mathmorra::Vector3(x, y, z));
    }

}

// --------------------------------------------------------------- //