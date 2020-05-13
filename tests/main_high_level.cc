
#include <common_definitions.h>
#if defined _MAIN_HIGHLEVEL_

#include <suffermanager.h>
#include <glfw3.h>
#include <audio.h>
#include "chrono.h"
#include "ref_ptr.h"
#include "audio_commands.h"
#include "system_audio.h"
#include "component_geometry.h"
#include "component_material.h"
#include "scene.h"
#include "audio.h"

// --------------------------------------------------------------//

int main(int argc, char* argv[]) {

	suffer.Init();

  Suffer::ref_ptr<Suffer::SystemAudio> audio_system_;
  audio_system_.alloc();
  suffer.AddSystem(audio_system_.get());

  Suffer::ref_ptr<Suffer::Scene> scene;
  scene.alloc();





  Suffer::ref_ptr<Suffer::ResourceManager::Texture> albedo_texture2;
  albedo_texture2.alloc();
  albedo_texture2->SetTextureFilter(Suffer::ResourceManager::Texture::kTextureFilter_Linear, Suffer::ResourceManager::Texture::kTextureFilter_Linear);
  albedo_texture2->SetTextureWrap(Suffer::ResourceManager::Texture::kTextureWrap_ClampToEdge, Suffer::ResourceManager::Texture::kTextureWrap_ClampToEdge);
  albedo_texture2->LoadTextureData("../../../resources/images/earth.jpg");



  Suffer::ref_ptr<Suffer::GameObject> go_sphere[9];

  Suffer::ref_ptr<Suffer::GeometryComponent> geometry_component_sphere;
  geometry_component_sphere.alloc();
  geometry_component_sphere->SetDrawMode(Suffer::GeometryComponent::kDrawMode_Points);
  geometry_component_sphere->CreateGeometryWithShape(Suffer::GeometryComponent::kBasicShapes_Sphere);

  Suffer::ref_ptr<Suffer::MaterialComponent> material_component_sphere;
  material_component_sphere.alloc();
  Suffer::ref_ptr<Suffer::MaterialComponent::BlinnPhongParams> material_params2;
  material_params2.alloc();
  material_params2->color_ = mathmorra::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
  material_params2->SetAlbedoTexture(albedo_texture2.get());
  material_params2->specular_strength_ = 0.2f;
  material_component_sphere->SetParams(material_params2.get());

  for (u32 i = 0; i < 9; ++i) {

    go_sphere[i].alloc();

    Suffer::ref_ptr<Suffer::Transform> transform_component_sphere_;
    transform_component_sphere_.alloc();

    go_sphere[i]->AddComponent(geometry_component_sphere.get());
    go_sphere[i]->AddComponent(material_component_sphere.get());
    go_sphere[i]->AddComponent(transform_component_sphere_.get());
    go_sphere[i]->SetName("Sphere");
    scene->AddGameObject(go_sphere[i]);

  }


  //go_sphere[0]->AddComponent(suffer.one.get());
  //go_sphere[1]->AddComponent(suffer.two.get());
  //
  //go_sphere[2]->AddComponent(suffer.samples_[0].get());
  //go_sphere[3]->AddComponent(suffer.samples_[1].get());
  //go_sphere[4]->AddComponent(suffer.samples_[2].get());
  //go_sphere[5]->AddComponent(suffer.samples_[3].get());
  //
  //go_sphere[6]->AddComponent(suffer.branching_a_.get());
  //go_sphere[7]->AddComponent(suffer.branching_b_.get());
  //go_sphere[8]->AddComponent(suffer.branching_transition_.get());
  //
  //
  //go_sphere[0]->StartUpLUA("../../../src/lua/lua_code_sphere_crossfade_1.txt");
  //go_sphere[1]->StartUpLUA("../../../src/lua/lua_code_sphere_crossfade_2.txt");
  //
  //go_sphere[2]->StartUpLUA("../../../src/lua/lua_code_sphere_layering_1.txt");
  //go_sphere[3]->StartUpLUA("../../../src/lua/lua_code_sphere_layering_2.txt");
  //go_sphere[4]->StartUpLUA("../../../src/lua/lua_code_sphere_layering_3.txt");
  //go_sphere[5]->StartUpLUA("../../../src/lua/lua_code_sphere_layering_4.txt");
  //
  //go_sphere[6]->StartUpLUA("../../../src/lua/lua_code_sphere_branching_1.txt");
  //go_sphere[7]->StartUpLUA("../../../src/lua/lua_code_sphere_branching_2.txt");
  //go_sphere[8]->StartUpLUA("../../../src/lua/lua_code_sphere_branching_3.txt");




  // -------------------------------------------------------------------------------------//





  suffer.SetScene(scene);

	suffer.Run();

	suffer.Finish();

	return 0;

}
 
// --------------------------------------------------------------//

#endif