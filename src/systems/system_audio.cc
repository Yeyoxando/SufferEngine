/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 12-05-2019
* SystemAudio Source
*/

#include "system_audio.h"
#include "audio.h"

Suffer::SystemAudio::SystemAudio(){

}

void Suffer::SystemAudio::Execute(GameObject* go){

  assert(go != nullptr && "NULL GameObject");
  if (!go->HasComponent(Suffer::Component::kComponentKind_Audio)) return;
  if (!go->HasComponent(Suffer::Component::kComponentKind_Transform)) return;

  auto audio_component_ = go->GetComponent(Suffer::Component::kComponentKind_Audio);
  auto transform_component_ = go->GetComponent(Suffer::Component::kComponentKind_Transform);

  Suffer::Audio3D* audio_source_ = reinterpret_cast<Suffer::Audio3D*>(audio_component_);
  Suffer::Transform* transform_ = reinterpret_cast<Suffer::Transform*>(transform_component_);

  audio_source_->SetSoundPosition(transform_->GetPosition());

  // Velocity - Doppler Effect
  

}

Suffer::SystemAudio::~SystemAudio(){

}

