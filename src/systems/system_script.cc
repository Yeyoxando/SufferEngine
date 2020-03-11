/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 02-12-2019
* SystemScript Source
*/

#include "component_script.h"
#include "system_script.h"
//#include "internal_component_script.h"

// --------------------------------------------------- //

Suffer::SystemScript::SystemScript(){

}

// --------------------------------------------------- //

void Suffer::SystemScript::Execute(GameObject* go){

  if (nullptr == go) return;
  if (!go->HasComponent(Suffer::Component::kComponentKind_Script)) return;
  
  Component* script_component = go->GetComponent(Suffer::Component::kComponentKind_Script);
  ScriptComponent* script = static_cast<ScriptComponent*>(script_component);

  if (!script->script_attached_) {
    return;
  }


  // TODO: we have to research about that.
  if (!script->initialized_) {
    script->Start();
    script->reference_ = go;
  }

  script->Update();

}

// --------------------------------------------------- //

Suffer::SystemScript::~SystemScript(){

}

// --------------------------------------------------- //