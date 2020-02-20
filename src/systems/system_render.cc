/*
* Author: Diego Ochando Torres <ochandoto@esat-alumni.com>
* Date: 12-12-2019
* SystemRender Source
*/

#include "system_render.h"
#include "draw_geometry.h"
#include "component_geometry.h"
#include "component_material.h"
#include "suffermanager.h"
#include "clear.h"
#include "internal_suffermanager.h"

// ------------------------------------------------------------------------- //

Suffer::SystemRender::SystemRender(){



}

// ------------------------------------------------------------------------- //

void Suffer::SystemRender::Execute(GameObject * go){

  //Add clear at the beginning
  if (dl_.Size() <= 0) {
    ref_ptr<Clear> clear_cmd;

    clear_cmd.alloc();

    clear_cmd.get()->SetClearColor(mathmorra::Vector4(0.5f));

    dl_.AddCommand(clear_cmd.get());
  }

  if (go == nullptr) assert(false && "NULL GameObject");
  if (!go->HasComponent(Component::ComponentKind::kComponentKind_Transform)) return;
  if (!go->HasComponent(Component::ComponentKind::kComponentKind_Geometry)) return;
  if (!go->HasComponent(Component::ComponentKind::kComponentKind_Material)) return;

  auto component = go->GetComponent(Suffer::Component::ComponentKind::kComponentKind_Transform);
  Suffer::Transform* transform_component = reinterpret_cast<Suffer::Transform*>(component);

  // Add draw command
  ref_ptr<DrawGeometry> draw_geometry;

  draw_geometry.alloc();
  draw_geometry.get()->SetData(go);

  draw_geometry.get()->SetModelMatrix(transform_component->GetModelMatrix());

  draw_geometry.get()->SetViewMatrix(suffer.GetCurrentScene()->GetMainCamera()->ViewMatrix());
  draw_geometry.get()->SetProjectionMatrix(suffer.GetCurrentScene()->GetMainCamera()->ProjectionMatrix());

  dl_.AddCommand(draw_geometry.get());


  // User need to call AddToRenderQueue after all elements are in displayList

}

// ------------------------------------------------------------------------- //

Suffer::SystemRender::~SystemRender(){



}

// ------------------------------------------------------------------------- //
