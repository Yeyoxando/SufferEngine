// LUA
#include "lua.hpp"
#include <cstdlib>
#include <cassert>

#include "game_object.h"
#include "component_transform.h"

// --------------------------------------------------- //

struct Suffer::ScriptComponent::ScriptData {

  ScriptData() {
    state_ = nullptr;
  }

  ~ScriptData(){}

  lua_State* state_;
  GameObject* go_reference_;

  static GameObject* GetReference(lua_State* L);

  static int lua_Start(lua_State* L);
  static int lua_Update(lua_State* L);

  // TRANSFORM Tests
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

  lua_getglobal(L, "Update");
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

  lua_getglobal(L, "Start");
  lua_call(L, 0, 0);

  return 0;

}

// --------------------------------------------------- //

int Suffer::ScriptComponent::ScriptData::lua_Scale(lua_State* L){
  return 0;
}

// --------------------------------------------------- //

int Suffer::ScriptComponent::ScriptData::lua_Rotate(lua_State* L){

  if (!GetReference(L)->HasComponent(Suffer::Component::kComponentKind_Transform)) return -1;

  Component* transform_component = GetReference(L)->GetComponent(Suffer::Component::kComponentKind_Transform);
  Suffer::Transform* transform = reinterpret_cast<Suffer::Transform*>(transform_component);

  int arguments = lua_gettop(L);

  // TODO: WATCH THIS
  //if (arguments != 3) {
  //  return luaL_error(L, "Invalid call expected three argument.");
  //}

  float x = lua_tonumber(L, 1);
  float y = lua_tonumber(L, 2);
  float z = lua_tonumber(L, 3);

  transform->Rotate(x, y, z);

  //GetReference(L)->data_->RotateL(x, y, z);

  lua_pop(L, 1);
  return 0;

}

// --------------------------------------------------- //

int Suffer::ScriptComponent::ScriptData::lua_Translate(lua_State* L){
  return 0;
}

Suffer::GameObject* Suffer::ScriptComponent::ScriptData::GetReference(lua_State* L){

  lua_pushstring(L, "THIS");
  lua_gettable(L, LUA_REGISTRYINDEX);
  const void* raw_ptr = lua_topointer(L, -1);

  GameObject* ptr = reinterpret_cast<GameObject*>(const_cast<void*>(raw_ptr));
  return ptr;

}

// --------------------------------------------------- //