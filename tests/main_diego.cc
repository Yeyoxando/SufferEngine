
#include <common_definitions.h>
#if !defined _MAIN_PABLO_ && defined _MAIN_DIEGO_

#include <suffermanager.h>
#include "ref_ptr.h"
#include "stdlib.h"
#include "scene.h"
#include "game_object.h"
#include "resource_manager.h"
#include "component.h"
#include "system.h"
#include "scoped_array.h"
#include "system_transform.h"
#include "system_animation.h"
#include "component_transform.h"
#include "component_geometry.h"
#include "component_red_color.h"
#include "component_blue_color.h"
#include "component_animation.h"

// --------------------------------------------------------------//

int main(int argc, char* argv[]) {

  suffer.Init();

  Suffer::ref_ptr<Suffer::SystemAnimation> animation_system;
  animation_system.alloc();

  suffer.AddSystem(animation_system.get());

  Suffer::ref_ptr<Suffer::Scene> scene;
  scene.alloc();

  Array<Suffer::ref_ptr<Suffer::GameObject>> go_cube;
  go_cube.alloc(100);

  Array<Suffer::ref_ptr<Suffer::GeometryComponent>> geometry_components;
  geometry_components.alloc(100);

  Array<Suffer::ref_ptr<Suffer::Transform>> transform_components;
  transform_components.alloc(100);

  Array<Suffer::ref_ptr<Suffer::BlueColorComponent>> blues_components;
  blues_components.alloc(50);
  Array<Suffer::ref_ptr<Suffer::RedColorComponent>> reds_components;
  reds_components.alloc(50);

  for (u32 i = 0; i < 10; ++i) {
    for (u32 j = 0; j < 10; ++j) {
      go_cube[i + (j * 10)].alloc();

      transform_components[i + (j * 10)].alloc();
      transform_components[i + (j * 10)]->Translate((i * 3.0f) - 15.0f, (j * 3.0f) - 15.0f, 0.0f);
      go_cube[i + (j * 10)]->AddComponent(transform_components[i + (j * 10)].get());

      geometry_components[i + (j * 10)].alloc();
      geometry_components[i + (j * 10)]->SetDrawMode(Suffer::GeometryComponent::kDrawMode_Triangles);
      geometry_components[i + (j * 10)]->CreateGeometryWithShape(Suffer::GeometryComponent::kBasicShapes_Cube);
      go_cube[i + (j * 10)]->AddComponent(geometry_components[i + (j * 10)].get());

      if ((i + (j * 10)) < 50) {
        blues_components[i + (j * 10)].alloc();
        go_cube[i + (j * 10)]->AddComponent(blues_components[i + (j * 10)].get());
      }
      else {
        reds_components[(i + (j * 10)) - 50].alloc();
        go_cube[i + (j * 10)]->AddComponent(reds_components[(i + (j * 10)) - 50].get());
      }

      go_cube[i + (j * 10)]->SetName("Cube");

      scene->AddGameObject(go_cube[i + (j * 10)]);

    }
  }
  


  Array<Suffer::ref_ptr<Suffer::AnimationComponent>> animation_components;
  animation_components.alloc(20);

  for (u32 i = 0; i < 20; ++i) {
    animation_components[i].alloc();

    int random = rand()%100;

    if (!go_cube[random]->HasComponent(Suffer::Component::kComponentKind_Animation)) {
      animation_components[i]->amplitude_ = 0.2f;
      animation_components[i]->frequency_ = 1.0f;
      go_cube[random]->AddComponent(animation_components[i].get());
    }
  }

  suffer.SetScene(scene);


  suffer.Run();

  suffer.Finish();

  return 0;

}

// --------------------------------------------------------------//

#endif