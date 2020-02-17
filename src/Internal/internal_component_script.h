// LUA
#include "lua.hpp"
#include <cstdlib>
#include <cassert>

// --------------------------------------------------- //

struct Suffer::ScriptComponent::ScriptData {

  ScriptData() {
    state_ = nullptr;
  }

  ~ScriptData(){}

  lua_State* state_;

  static int lua_Update(lua_State* L);
  static int lua_Start(lua_State* L);

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