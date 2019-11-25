// LUA
#include "lua.hpp"
#include <cstdlib>
#include <cassert>


#include "game_object.h"

struct Suffer::GameObject::Data {

    // LUA Stuff
    lua_State* _script = nullptr;
    static GameObject* GetReference(lua_State* L);
    void BeginLUA(const char* luaCodeFile);
    void CheckLuaError(int status);

    void RotateL(float x, float y, float z);
    void TranslateL(float x, float y, float z);

    static int lua_Rotate(lua_State* L);
    static int lua_Translate(lua_State* L);
    static int lua_Scale(lua_State* L);
    static int lua_SetPredefinedGeometry(lua_State* L);
    static int lua_SetDrawMode(lua_State* L);

    char* lua_file_;
    GameObject* reference;
    bool lua_error_;

};