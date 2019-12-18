

#include "system_animation.h"
#include "audio.h"
#include "suffermanager.h"
#include "internal_suffermanager.h"
#include "common_definitions.h"
#include "component_animation.h"
#include <math.h>
#include "time.h"

void Suffer::SystemAnimation::Execute(GameObject* go){


	if (!go->HasComponent(Suffer::Component::kComponentKind_Transform)) return;
	if (!go->HasComponent(Suffer::Component::kComponentKind_Animation)) return;

	auto component_a = go->GetComponent(Suffer::Component::ComponentKind::kComponentKind_Animation);
	Suffer::AnimationComponent* component_animation = reinterpret_cast<Suffer::AnimationComponent*>(component_a);

	auto component_ = go->GetComponent(Suffer::Component::ComponentKind::kComponentKind_Transform);
	Suffer::Transform* component = reinterpret_cast<Suffer::Transform*>(component_);
	component->Scale(0.2f, 0.2, 0.2f);
	mathmorra::Vector3 newPosition = component->GetPosition();

	newPosition.y_ += sin((component_animation->frequency_ * Time())) * component_animation->ampl_;

	component->Translate(newPosition);

}
