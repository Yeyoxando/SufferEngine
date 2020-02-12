// LUA
#include "lua.hpp"
#include <cstdlib>
#include <cassert>

struct Suffer::ScriptComponent::ScriptData {

  lua_State* state_;

  static int lua_Update(lua_State* L);

};

int Suffer::ScriptComponent::ScriptData::lua_Update(lua_State* L){
  printf("HELLO HELLO!!\n");
  return 0;
}
