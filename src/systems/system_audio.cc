/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 12-05-2019
* SystemAudio Source
*/

#include "system_audio.h"
#include "audio.h"
#include "suffermanager.h"
#include "internal_suffermanager.h"
#include "common_definitions.h"

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

  // Listener stuff
  const float* listener_position = suffer.GetCurrentScene()->GetMainCamera()->Position();
  const float* listener_target = suffer.GetCurrentScene()->GetMainCamera()->Target();
  const float* listener_up = suffer.GetCurrentScene()->GetMainCamera()->Up();

  audio_source_->SetSoundMinMaxDistance(transform_->GetPosition()[0], transform_->GetScale()[0]);

  audio_source_->SetSoundPosition(transform_->GetPosition());
  audio_source_->SetListenerParameters(
    mathmorra::Vector3(listener_position),
    mathmorra::Vector3(listener_target),
    mathmorra::Vector3(listener_up),
    mathmorra::Vector3(0.0f, 0.0f, 0.0f)
  );

  // Velocity - Doppler Effect
  

}

Suffer::SystemAudio::~SystemAudio(){

}

