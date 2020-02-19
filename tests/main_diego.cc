
#include <common_definitions.h>
#if !defined _MAIN_PABLO_ && defined _MAIN_DIEGO_

#include <suffermanager.h>
#include "ref_ptr.h"
#include "scene.h"
#include "game_object.h"
#include "component_transform.h"
#include "resource_manager.h"
#include "component.h"
#include "system.h"
#include "system_transform.h"
#include "system_audio.h"
#include "system_render.h"
#include "component_geometry.h"
#include "component_material.h"
#include "component_script.h"

// --------------------------------------------------------------//

int main(int argc, char* argv[]) {

  suffer.Init();

  Suffer::ref_ptr<Suffer::ResourceManager::FrameBuffer> frame_buffer_;
  frame_buffer_.alloc();
  frame_buffer_->InitFrameBuffer(WINDOW_WIDTH, WINDOW_HEIGHT);
  suffer.render_manager_.SetFrameBuffer(frame_buffer_.get());
  
  Suffer::ref_ptr<Suffer::SystemAudio> audio_system_;
  audio_system_.alloc();
  suffer.AddSystem(audio_system_.get());

  Suffer::ref_ptr<Suffer::Scene> scene;
  scene.alloc();

  Suffer::ref_ptr<Suffer::LightManager::DirectionalLight> directional_light_;
  directional_light_.alloc();


  // Textures
  Suffer::ref_ptr<Suffer::ResourceManager::Texture> albedo_texture;
  albedo_texture.alloc();
  albedo_texture->SetTextureFilter(Suffer::ResourceManager::Texture::kTextureFilter_Nearest, Suffer::ResourceManager::Texture::kTextureFilter_Nearest);
  albedo_texture->SetTextureWrap(Suffer::ResourceManager::Texture::kTextureWrap_ClampToEdge, Suffer::ResourceManager::Texture::kTextureWrap_ClampToEdge);
  albedo_texture->LoadTextureData("../../../resources/images/box.jpg");

  Suffer::ref_ptr<Suffer::ResourceManager::Texture> albedo_texture2;
  albedo_texture2.alloc();
  albedo_texture2->SetTextureFilter(Suffer::ResourceManager::Texture::kTextureFilter_Linear, Suffer::ResourceManager::Texture::kTextureFilter_Linear);
  albedo_texture2->SetTextureWrap(Suffer::ResourceManager::Texture::kTextureWrap_ClampToEdge, Suffer::ResourceManager::Texture::kTextureWrap_ClampToEdge);
  albedo_texture2->LoadTextureData("../../../resources/images/earth.jpg");


  Suffer::ref_ptr<Suffer::GameObject> go_cube;
  go_cube.alloc();

  // -------------------------------- COMPONENTS STUFF TESTS ------------------------------//

  Suffer::ref_ptr<Suffer::GeometryComponent> geometry_component;
  geometry_component.alloc();
  geometry_component->SetDrawMode(Suffer::GeometryComponent::kDrawMode_Triangles);
  geometry_component->CreateGeometryWithShape(Suffer::GeometryComponent::kBasicShapes_Cube);
  go_cube->AddComponent(geometry_component.get());

  Suffer::ref_ptr<Suffer::MaterialComponent> material_component;
  material_component.alloc();
  Suffer::ref_ptr<Suffer::MaterialComponent::DefaultParams> material_params;
  material_params.alloc();
  material_params->albedo_texture_id_ = albedo_texture->id_;
  material_params->color_ = mathmorra::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
  material_component->SetParams(material_params.get());
  

  go_cube->AddComponent(material_component.get());

  Suffer::ref_ptr<Suffer::Transform> transform_component_;
  transform_component_.alloc();
  //go_cube->AddComponent(transform_component_.get());

  auto component_ = go_cube->GetComponent(Suffer::Component::ComponentKind::kComponentKind_Transform);
  Suffer::Transform* component = reinterpret_cast<Suffer::Transform*>(component_);

  // -------------------------------------------------------------------------------------//
    //go_cube->StartUpLUA("../../../src/lua/lua_code_cube.txt");
  //TODO: REMOVE THIS: go_cube->SetGeometry(geometry);
  //TODO: REMOVE THIS: go_cube->SetMaterial(material);

  go_cube->SetName("Cube");

  //component->Translate(mathmorra::Vector3(-3.0f, 0.0f, 0.0f));



  Suffer::ref_ptr<Suffer::GameObject> go_sphere;
  go_sphere.alloc();
  //go_sphere->StartUpLUA("../../../src/lua/lua_code_sphere.txt");



  // -------------------------------- COMPONENTS STUFF TESTS ------------------------------//

  Suffer::ref_ptr<Suffer::GeometryComponent> geometry_component_sphere;
  geometry_component_sphere.alloc();
  geometry_component_sphere->SetDrawMode(Suffer::GeometryComponent::kDrawMode_Triangles);
  geometry_component_sphere->CreateGeometryWithShape(Suffer::GeometryComponent::kBasicShapes_Sphere);
  go_sphere->AddComponent(geometry_component_sphere.get());

  Suffer::ref_ptr<Suffer::MaterialComponent> material_component_sphere;
  material_component_sphere.alloc();
  Suffer::ref_ptr<Suffer::MaterialComponent::DefaultParams> material_params2;
  material_params2.alloc();
  material_params2->color_ = mathmorra::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
  material_params2->albedo_texture_id_ = albedo_texture2->id_;
  material_component_sphere->SetParams(material_params2.get());
  go_sphere->AddComponent(material_component_sphere.get());

  Suffer::ref_ptr<Suffer::Transform> transform_component_sphere_;
  transform_component_sphere_.alloc();
  go_sphere->AddComponent(transform_component_sphere_.get());


  // SCRIPTING TESTS

  Suffer::ref_ptr<Suffer::ScriptComponent> script_component_;
  script_component_.alloc();
  go_sphere->AddComponent(script_component_.get());
  script_component_->AttachScript("../../../src/lua/lua_test_update.txt");

  Suffer::ref_ptr<Suffer::ScriptComponent> script_component_cube;
  script_component_cube.alloc();
  go_cube->AddComponent(script_component_cube.get());
  script_component_cube->AttachScript("../../../src/lua/lua_test_update_cube.txt");
  //go_sphere->StartUpLUA("../../../src/lua/lua_test_update.txt");

  Suffer::ref_ptr<Suffer::Audio3D> audio_component_;
  audio_component_.alloc();
  go_sphere->AddComponent(audio_component_.get());

  auto audio_ = go_sphere->GetComponent(Suffer::Component::ComponentKind::kComponentKind_Audio);
  Suffer::Audio3D* source = reinterpret_cast<Suffer::Audio3D*>(audio_);
  source->Load("../../../resources/audio/plonk_wet.ogg");
  source->Play3D();
  source->SetLooping(true);

  // -------------------------------------------------------------------------------------//


  go_sphere->SetName("Sphere");

  scene->AddGameObject(go_sphere);
  scene->AddGameObject(go_cube);


  suffer.SetScene(scene);


  suffer.Run();

  suffer.Finish();

  return 0;

}

// --------------------------------------------------------------//

#endif