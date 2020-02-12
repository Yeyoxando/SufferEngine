/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 02-12-2019
* ComponentScript Source
*/

#include "component_script.h"
#include "internal_component_script.h"

// --------------------------------------------------- //

Suffer::ScriptComponent::ScriptComponent() : Component(Component::kComponentKind_Script) {
 
  script_attached_ = false;
  data_ = new ScriptData();

}

// --------------------------------------------------- //

void Suffer::ScriptComponent::AttachScript(const char* script_path){

  assert(script_path == nullptr && "Invalid script");
  data_->state_ = luaL_newstate();

  luaL_openlibs(data_->state_);


  // PUSH FUNCTIONS FOR LUA
  lua_pushcfunction(data_->state_, data_->lua_Update);    // +1
  lua_setglobal(data_->state_, "Update");                 // -1
  
  lua_pushstring(data_->state_, "THIS");
  lua_pushlightuserdata(data_->state_, this);
  lua_settable(data_->state_, LUA_REGISTRYINDEX);
  
  //data_->reference = data_->GetReference(data_->state_);
  //data_->execute_lua_ = true;

  script_attached_ = true;

}

// --------------------------------------------------- //

void Suffer::ScriptComponent::Update(){

  data_->lua_Update(data_->state_);

}

// --------------------------------------------------- //

Suffer::ScriptComponent::~ScriptComponent(){

  if (data_ == nullptr) return;
  delete data_;
  data_ = nullptr;

}

// --------------------------------------------------- //