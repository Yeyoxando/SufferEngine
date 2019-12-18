#include "system_animation.h"
#include "component_animation.h"
#include "time.h"

Suffer::SystemAnimation::SystemAnimation(){



}

void Suffer::SystemAnimation::Execute(GameObject * go){

  if (go == nullptr) assert(false && "NULL GameObject");
  if (!go->HasComponent(Component::ComponentKind::kComponentKind_Transform)) return;
  if (!go->HasComponent(Component::ComponentKind::kComponentKind_Animation)) return;


  auto component = go->GetComponent(Suffer::Component::ComponentKind::kComponentKind_Transform);
  Transform* transform_component = reinterpret_cast<Transform*>(component);

  component = go->GetComponent(Suffer::Component::ComponentKind::kComponentKind_Animation);
  AnimationComponent* animation_component = reinterpret_cast<AnimationComponent*>(component);

  float* pos = transform_component->GetPosition();
  transform_component->Translate(pos[0], pos[1] + (sinf(Time() * animation_component->frequency_) * animation_component->amplitude_), pos[2]);
  
}

Suffer::SystemAnimation::~SystemAnimation(){



}
