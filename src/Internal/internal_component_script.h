// LUA
#include "lua.hpp"
#include <cstdlib>
#include <cassert>

#include "game_object.h"
#include "component_transform.h"
#include "component_geometry.h"
#include "component_material.h"
#include "component_debug_geometry.h"
#include "audio.h"

// --------------------------------------------------- //

struct Suffer::ScriptComponent::ScriptData {

  ScriptData() {
    state_ = nullptr;
    go_reference_ = nullptr;
  }

  ~ScriptData(){
    if (state_ == nullptr) return;
    lua_close(state_);
    state_ = nullptr;
  }

  lua_State* state_;
  GameObject* go_reference_;

  static GameObject* GetReference(lua_State* L);

  static int lua_Start(lua_State* L);
  static int lua_Update(lua_State* L);

  static int lua_AddComponent(lua_State* L);
  static int lua_RemoveComponent(lua_State* L);

  static int lua_SetGeometry(lua_State* L);
  static int lua_SetDrawMode(lua_State* L);
  static int lua_PlayAudio(lua_State* L);

  static int lua_Scale(lua_State* L);
  static int lua_Rotate(lua_State* L);
  static int lua_Translate(lua_State* L);

};

// --------------------------------------------------- //

int Suffer::ScriptComponent::ScriptData::lua_Update(lua_State* L){

  assert(nullptr != L && "NULL Script State.\n");

  if (nullptr == L) {
    printf("NULL Script State.\n");
    return -1;
  }

  u8 function_status = lua_getglobal(L, "Update");
  lua_call(L, 0, 0);

  return 0;

}

// --------------------------------------------------- //

int Suffer::ScriptComponent::ScriptData::lua_Start(lua_State* L){

  assert(nullptr != L && "NULL Script State.\n");

  if (nullptr == L) {
    printf("NULL Script State.\n");
    return -1;
  }

#ifdef DEBUG
  printf("Start!\n");
#endif

  u8 function_status = lua_getglobal(L, "Start");
  lua_call(L, 0, 0);

  return 0;

}

// --------------------------------------------------- //

int Suffer::ScriptComponent::ScriptData::lua_Scale(lua_State* L){
  
  GameObject* game_object_reference = GetReference(L);
  assert(nullptr != game_object_reference);
  if (nullptr == game_object_reference) return -1;

  if (!game_object_reference->HasComponent(Suffer::Component::kComponentKind_Transform)) return -1;

  Component* transform_component = game_object_reference->GetComponent(Suffer::Component::kComponentKind_Transform);
  Suffer::Transform* transform = static_cast<Suffer::Transform*>(transform_component);

  u16 arguments = lua_gettop(L);

  //if (arguments != 3) {
  //  assert(arguments == 3 && "Invalid call expected three arguments.");
  //  return luaL_error(L, "Invalid call expected three arguments.");
  //}

  float x = lua_tonumber(L, 1);
  float y = lua_tonumber(L, 2);
  float z = lua_tonumber(L, 3);

  transform->Scale(x, y, z);

  lua_pop(L, 1);
  return 0;

}

// --------------------------------------------------- //

int Suffer::ScriptComponent::ScriptData::lua_Rotate(lua_State* L){

  GameObject* game_object_reference = GetReference(L);
  assert(nullptr != game_object_reference);
  if (nullptr == game_object_reference) return -1;

  if (!game_object_reference->HasComponent(Suffer::Component::kComponentKind_Transform)) return -1;

  Component* transform_component = game_object_reference->GetComponent(Suffer::Component::kComponentKind_Transform);
  Suffer::Transform* transform = static_cast<Suffer::Transform*>(transform_component);

  u16 arguments = lua_gettop(L);

  //if (arguments != 3) {
  //  assert(arguments == 3 && "Invalid call expected three arguments.");
  //  return luaL_error(L, "Invalid call expected three arguments.");
  //}

  float x = lua_tonumber(L, 1);
  float y = lua_tonumber(L, 2);
  float z = lua_tonumber(L, 3);

  transform->Rotate(x, y, z);

  lua_pop(L, 1);
  return 0;

}

// --------------------------------------------------- //

int Suffer::ScriptComponent::ScriptData::lua_Translate(lua_State* L){
  
  GameObject* game_object_reference = GetReference(L);
  assert(nullptr != game_object_reference);
  if (nullptr == game_object_reference) return -1;

  if (!game_object_reference->HasComponent(Suffer::Component::kComponentKind_Transform)) return -1;

  Component* transform_component = game_object_reference->GetComponent(Suffer::Component::kComponentKind_Transform);
  Suffer::Transform* transform = static_cast<Suffer::Transform*>(transform_component);

  u16 arguments = lua_gettop(L);

  //if (arguments != 3) {
  //  assert(arguments == 3 && "Invalid call expected three arguments.");
  //  return luaL_error(L, "Invalid call expected three arguments.");
  //}

  float x = lua_tonumber(L, 1);
  float y = lua_tonumber(L, 2);
  float z = lua_tonumber(L, 3);

  transform->Translate(x, y, z);

  lua_pop(L, 1);
  return 0;

}

// --------------------------------------------------- //

Suffer::GameObject* Suffer::ScriptComponent::ScriptData::GetReference(lua_State* L){

  lua_pushstring(L, "THIS");
  lua_gettable(L, LUA_REGISTRYINDEX);
  const void* raw_ptr = lua_topointer(L, -1);
  
  GameObject* ptr = static_cast<GameObject*>(const_cast<void*>(raw_ptr));
  return ptr;

}

// --------------------------------------------------- //

int Suffer::ScriptComponent::ScriptData::lua_AddComponent(lua_State* L){

  GameObject* game_object_reference = GetReference(L);
  assert(nullptr != game_object_reference && "The script has not a GameObject attached.");
  if (nullptr == game_object_reference) return -1;

  u8 component_number = (u8)lua_tonumber(L, 1);
  Component::ComponentKind component = static_cast<Component::ComponentKind>(component_number);

  if (game_object_reference->HasComponent(component)) {
    printf("The GameObject already has the component.\n");
    return -1;
  }

  s8 error = 0;

  switch (component){
    case Suffer::Component::kComponentKind_Invalid:
      error = -1;
      break;
    case Suffer::Component::kComponentKind_Transform: {
      Suffer::ref_ptr<Suffer::Transform> component_transform_;
      component_transform_.alloc();
      game_object_reference->AddComponent(component_transform_.get());
      break;
    }
    case Suffer::Component::kComponentKind_DebugGeometry:
      break;
    case Suffer::Component::kComponentKind_Geometry: {
      Suffer::ref_ptr<Suffer::GeometryComponent> component_geometry_;
      component_geometry_.alloc();
      game_object_reference->AddComponent(component_geometry_.get());
      break;
    }
    case Suffer::Component::kComponentKind_Material:
      break;
    case Suffer::Component::kComponentKind_Audio: {
      Suffer::ref_ptr<Suffer::Audio3D> audio_component_;
      audio_component_.alloc();
      game_object_reference->AddComponent(audio_component_.get());
      break;
    }
    default: {
      printf("Invalid component.\n");
      error = -1;
      break;
    }
  }

  return error;

}

// --------------------------------------------------- //

int Suffer::ScriptComponent::ScriptData::lua_RemoveComponent(lua_State* L){

  GameObject* game_object_reference = GetReference(L);
  assert(nullptr != game_object_reference && "The script has not a GameObject attached.");
  if (nullptr == game_object_reference) return -1;

  u8 component_number = (u8)lua_tonumber(L, 1);
  Component::ComponentKind component = static_cast<Component::ComponentKind>(component_number);

  if (!game_object_reference->HasComponent(component)) {
    printf("The GameObject does not have the component.\n");
    return -1;
  }

  s8 error = 0;
  game_object_reference->RemoveComponent(component);

  return error;

}

// --------------------------------------------------- //

int Suffer::ScriptComponent::ScriptData::lua_SetGeometry(lua_State* L){

  GameObject* game_object_reference = GetReference(L);
  assert(nullptr != game_object_reference);
  if (nullptr == game_object_reference) return -1;
  
  if (!game_object_reference->HasComponent(Suffer::Component::kComponentKind_Geometry)) return -1;
  
  auto geometry_component = game_object_reference->GetComponent(Suffer::Component::kComponentKind_Geometry);
  GeometryComponent* geometry_ = static_cast<GeometryComponent*>(geometry_component);
  
  int arguments = lua_gettop(L);
  //if (arguments != 2) {
  //  return luaL_error(L, "Invalid call, expected one argument");
  //}
  
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

// --------------------------------------------------- //

int Suffer::ScriptComponent::ScriptData::lua_SetDrawMode(lua_State* L){

  GameObject* game_object_reference = GetReference(L);
  assert(nullptr != game_object_reference);
  if (nullptr == game_object_reference) return -1;

  if (!game_object_reference->HasComponent(Suffer::Component::kComponentKind_Geometry)) return -1;

  auto geometry_component = game_object_reference->GetComponent(Suffer::Component::kComponentKind_Geometry);
  GeometryComponent* geometry_ = static_cast<GeometryComponent*>(geometry_component);

  int arguments = lua_gettop(L);
  //if (arguments != 2) {
  //  return luaL_error(L, "Invalid call, expected one argument");
  //}

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

// --------------------------------------------------- //

int Suffer::ScriptComponent::ScriptData::lua_PlayAudio(lua_State* L){

  GameObject* game_object_reference = GetReference(L);
  assert(nullptr != game_object_reference);
  if (nullptr == game_object_reference) return -1;

  if (!game_object_reference->HasComponent(Suffer::Component::kComponentKind_Audio)) return -1;

  int arguments = lua_gettop(L);
  //if (arguments != 2) {
  //  return luaL_error(L, "Invalid call, expected one argument");
  //}

  const char* song_path = lua_tostring(L, 1);

  auto audio_ = game_object_reference->GetComponent(Suffer::Component::ComponentKind::kComponentKind_Audio);
  Suffer::Audio3D* source = static_cast<Suffer::Audio3D*>(audio_);

  bool error = false;
  error = source->Load((char*)song_path);
  if (!error) return -1;
  error = source->Play3D();
  if (!error) return -1;
   
}

// --------------------------------------------------- //