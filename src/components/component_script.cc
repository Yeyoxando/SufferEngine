/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 02-12-2019
* ComponentScript Source
*/

#include "component_script.h"

Suffer::ScriptComponent::ScriptComponent() : Component(Component::kComponentKind_Script) {
  script_attached_ = false;
}

void Suffer::ScriptComponent::Update(){

}

Suffer::ScriptComponent::~ScriptComponent(){

}