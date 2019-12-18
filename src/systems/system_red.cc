#include "system_red.h"
#include "component_material.h"
#include "draw_geometry.h"
#include "component_geometry.h"
#include "component_material.h"
#include "suffermanager.h"
#include "internal_suffermanager.h"

void Suffer::SystemRed::Execute(GameObject * go){


	if (active_) {
		if (!go->HasComponent(Suffer::Component::kComponentKind_Red)) return;
		if (!go->HasComponent(Suffer::Component::kComponentKind_Transform)) return;

		auto mat_component = go->GetComponent(Suffer::Component::kComponentKind_Material);
		Suffer::Material* material = reinterpret_cast<Suffer::Material*>(mat_component);

		material->current_params_->color_ = mathmorra::Vector4(1.0f, 0.0f, 0.0f, 1.0f);


		auto component = go->GetComponent(Suffer::Component::ComponentKind::kComponentKind_Transform);
		Suffer::Transform* transform_component = reinterpret_cast<Suffer::Transform*>(component);

		ref_ptr<DrawGeometry> draw_geometry;

		draw_geometry.alloc();
		draw_geometry.get()->SetData(go);

		draw_geometry.get()->SetModelMatrix(transform_component->GetModelMatrix());

		draw_geometry.get()->SetViewMatrix(suffer.GetCurrentScene()->GetMainCamera()->ViewMatrix());
		draw_geometry.get()->SetProjectionMatrix(suffer.GetCurrentScene()->GetMainCamera()->ProjectionMatrix());

		dl_.AddCommand(draw_geometry.get());
	}
}
