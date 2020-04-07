/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 02-12-2019
* ComponentScript Source
*/

#include "component_script.h"
#include "internal_component_script.h"

// --------------------------------------------------- //

Suffer::ScriptComponent::ScriptComponent() : Component(Component::kComponentKind_Script) {
 
  initialized_ = false;
  script_attached_ = false;
  data_ = new ScriptData();
  game_object_reference_ = nullptr;

}

// --------------------------------------------------- //

void Suffer::ScriptComponent::AttachScript(char* script_path){

  assert(script_path != nullptr && "Invalid script.");
  assert(game_object_reference_ != nullptr && "Invalid GameObject.");

  data_->state_ = luaL_newstate();

  luaL_openlibs(data_->state_);


  // PUSH FUNCTIONS FOR LUA
  //lua_pushcfunction(data_->state_, data_->lua_Update);    // +1
  //lua_setglobal(data_->state_, "Update");                 // -1

  lua_pushcfunction(data_->state_, data_->lua_Rotate); // +1
  lua_setglobal(data_->state_, "Rotate");              // -1

  lua_pushcfunction(data_->state_, data_->lua_Scale); // +1
  lua_setglobal(data_->state_, "Scale");              // -1

  lua_pushcfunction(data_->state_, data_->lua_Translate); // +1
  lua_setglobal(data_->state_, "Translate");              // -1

  lua_pushcfunction(data_->state_, data_->lua_AddComponent); // +1
  lua_setglobal(data_->state_, "AddComponent");              // -1

  lua_pushcfunction(data_->state_, data_->lua_RemoveComponent); // +1
  lua_setglobal(data_->state_, "RemoveComponent");              // -1

  lua_pushcfunction(data_->state_, data_->lua_SetGeometry); // +1
  lua_setglobal(data_->state_, "SetGeometry");              // -1

  lua_pushcfunction(data_->state_, data_->lua_SetDrawMode); // +1
  lua_setglobal(data_->state_, "SetDrawMode");              // -1

  lua_pushcfunction(data_->state_, data_->lua_PlayAudio); // +1
  lua_setglobal(data_->state_, "PlayAudio");              // -1

  lua_register(data_->state_, "Update", data_->lua_Update);
  
  lua_pushstring(data_->state_, "THIS");
  lua_pushlightuserdata(data_->state_, game_object_reference_);
  lua_settable(data_->state_, LUA_REGISTRYINDEX);
  
  //data_->reference = data_->GetReference(data_->state_);
  //data_->execute_lua_ = true;

  u8 status = luaL_dofile(data_->state_, script_path);

  if (status) {
      const char* error = lua_tostring(data_->state_, -1);
      printf("ERROR: %s\n", error);
      assert(!status);
      lua_pop(data_->state_, 1);
      return;
  }

  script_attached_ = true;

}

// --------------------------------------------------- //

void Suffer::ScriptComponent::Update(){

  data_->lua_Update(data_->state_);

}

// --------------------------------------------------- //

void Suffer::ScriptComponent::Start(){

  data_->lua_Start(data_->state_);
  initialized_ = true;
  data_->go_reference_ = reference_;

}

void Suffer::ScriptComponent::Reload(char* new_path){

    data_->lua_Reload(data_->state_, new_path);

}

// --------------------------------------------------- //

Suffer::ScriptComponent::~ScriptComponent(){

  if (data_->state_ != nullptr) {
    if (game_object_reference_ != nullptr) {
        lua_close(data_->state_);
        data_->state_ = nullptr;
    }
  }

  if (data_ == nullptr) return;
  delete data_;
  data_ = nullptr;

}

// --------------------------------------------------- //