#include "system_red_render.h"
#include "draw_geometry.h"
#include "suffermanager.h"
#include "scene.h"
#include "common_definitions.h"
#include "component_material.h"

Suffer::SystemRedRender::SystemRedRender(){



}

void Suffer::SystemRedRender::Execute(GameObject * go){
  if (!is_active_) return;

  if (go == nullptr) assert(false && "NULL GameObject");
  if (!go->HasComponent(Component::ComponentKind::kComponentKind_Transform)) return;
  if (!go->HasComponent(Component::ComponentKind::kComponentKind_Geometry)) return;
  if (!go->HasComponent(Component::ComponentKind::kComponentKind_RedRender)) return;

  auto component = go->GetComponent(Suffer::Component::ComponentKind::kComponentKind_Transform);
  Suffer::Transform* transform_component = reinterpret_cast<Suffer::Transform*>(component);

  if (!go->HasComponent(Component::kComponentKind_Material)) {

    ref_ptr<Material> material_component;
    material_component.alloc();
    ref_ptr<Material::UnlitParams> material_params;
    material_params.alloc();

    material_params->color_ = mathmorra::Vector4(1.0f, 0.0f, 0.0f, 1.0f);
    material_component->SetParams(material_params.get());
    go->AddComponent(material_component.get());

  }

  // Add draw command
  ref_ptr<DrawGeometry> draw_geometry;

  draw_geometry.alloc();
  draw_geometry.get()->SetData(go);

  draw_geometry.get()->SetModelMatrix(transform_component->GetModelMatrix());

  draw_geometry.get()->SetViewMatrix(suffer.GetCurrentScene()->GetMainCamera()->ViewMatrix());
  draw_geometry.get()->SetProjectionMatrix(suffer.GetCurrentScene()->GetMainCamera()->ProjectionMatrix());

  assert(draw_geometry.get() != nullptr && "Invalid created command");

  dl_.AddCommand(draw_geometry.get());


}

Suffer::SystemRedRender::~SystemRedRender(){



}
