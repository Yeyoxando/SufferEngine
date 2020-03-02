
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
#include "component_light.h"

// --------------------------------------------------------------//

int main(int argc, char* argv[]) {

  suffer.Init();
  
  Suffer::ref_ptr<Suffer::SystemAudio> audio_system_;
  audio_system_.alloc();
  suffer.AddSystem(audio_system_.get());

  Suffer::ref_ptr<Suffer::Scene> scene;
  scene.alloc();

  // Textures
  Suffer::ref_ptr<Suffer::ResourceManager::Texture> albedo_texture;
  albedo_texture.alloc();
  albedo_texture->SetTextureFilter(Suffer::ResourceManager::Texture::kTextureFilter_Nearest, Suffer::ResourceManager::Texture::kTextureFilter_Nearest);
  albedo_texture->SetTextureWrap(Suffer::ResourceManager::Texture::kTextureWrap_ClampToEdge, Suffer::ResourceManager::Texture::kTextureWrap_ClampToEdge);
  albedo_texture->LoadTextureData("../../../resources/images/box_2.png");

  Suffer::ref_ptr<Suffer::ResourceManager::Texture> albedo_texture2;
  albedo_texture2.alloc();
  albedo_texture2->SetTextureFilter(Suffer::ResourceManager::Texture::kTextureFilter_Linear, Suffer::ResourceManager::Texture::kTextureFilter_Linear);
  albedo_texture2->SetTextureWrap(Suffer::ResourceManager::Texture::kTextureWrap_ClampToEdge, Suffer::ResourceManager::Texture::kTextureWrap_ClampToEdge);
  albedo_texture2->LoadTextureData("../../../resources/images/earth.jpg");

  Suffer::ref_ptr<Suffer::ResourceManager::Texture> specular_texture_box;
  specular_texture_box.alloc();
  specular_texture_box->SetTextureFilter(Suffer::ResourceManager::Texture::kTextureFilter_Linear, Suffer::ResourceManager::Texture::kTextureFilter_Linear);
  specular_texture_box->SetTextureWrap(Suffer::ResourceManager::Texture::kTextureWrap_ClampToEdge, Suffer::ResourceManager::Texture::kTextureWrap_ClampToEdge);
  specular_texture_box->LoadTextureData("../../../resources/images/box_2_spec.png");

  Suffer::ref_ptr<Suffer::ResourceManager::Texture> specular_texture;
  specular_texture.alloc();
  specular_texture->SetTextureFilter(Suffer::ResourceManager::Texture::kTextureFilter_Linear, Suffer::ResourceManager::Texture::kTextureFilter_Linear);
  specular_texture->SetTextureWrap(Suffer::ResourceManager::Texture::kTextureWrap_ClampToEdge, Suffer::ResourceManager::Texture::kTextureWrap_ClampToEdge);
  specular_texture->LoadTextureData("../../../resources/images/earth_specular.jpg");


  // -------------------------------- COMPONENTS STUFF TESTS ------------------------------//

  Suffer::ref_ptr<Suffer::GameObject> go_sphere;
  Suffer::ref_ptr<Suffer::GameObject> go_sphere2;
  go_sphere.alloc();
  go_sphere2.alloc();

  Suffer::ref_ptr<Suffer::GeometryComponent> geometry_component_sphere;
  geometry_component_sphere.alloc();
  geometry_component_sphere->SetDrawMode(Suffer::GeometryComponent::kDrawMode_Triangles);
  geometry_component_sphere->CreateGeometryWithShape(Suffer::GeometryComponent::kBasicShapes_Sphere);
  go_sphere->AddComponent(geometry_component_sphere.get());
  go_sphere2->AddComponent(geometry_component_sphere.get());


  Suffer::ref_ptr<Suffer::MaterialComponent> material_component_cube;
  material_component_cube.alloc();
  Suffer::ref_ptr<Suffer::MaterialComponent::DefaultParams> material_params_cube;
  material_params_cube.alloc();
  material_params_cube->color_ = mathmorra::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
  material_params_cube->albedo_texture_id_ = albedo_texture->id_;
  material_params_cube->specular_texture_id_ = specular_texture->id_;
  material_component_cube->SetParams(material_params_cube.get());


  Suffer::ref_ptr<Suffer::MaterialComponent> material_component_sphere;
  material_component_sphere.alloc();
  Suffer::ref_ptr<Suffer::MaterialComponent::DefaultParams> material_params_sphere;
  material_params_sphere.alloc();
  material_params_sphere->color_ = mathmorra::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
  material_params_sphere->albedo_texture_id_ = albedo_texture2->id_;
  material_params_sphere->specular_texture_id_ = specular_texture->id_;
  material_component_sphere->SetParams(material_params_sphere.get());
  go_sphere->AddComponent(material_component_sphere.get());
  go_sphere2->AddComponent(material_component_sphere.get());

  Suffer::ref_ptr<Suffer::Transform> transform_component_sphere_;
  transform_component_sphere_.alloc();
  transform_component_sphere_->Translate(mathmorra::Vector3(0.0f, 0.0f, 0.0f));
  transform_component_sphere_->Rotate(mathmorra::Vector3(90.0f, 0.0f, 0.0f));
  go_sphere->AddComponent(transform_component_sphere_.get());

  Suffer::ref_ptr<Suffer::Transform> transform_component_sphere_2;
  transform_component_sphere_2.alloc();
  transform_component_sphere_2->Translate(mathmorra::Vector3(0.0f, 0.0f, 0.0f));
  transform_component_sphere_2->Rotate(mathmorra::Vector3(90.0f, 0.0f, 0.0f));
  go_sphere2->AddComponent(transform_component_sphere_2.get());


  // -------------------------------------------------------------------------------------//

  Suffer::ref_ptr<Suffer::GameObject> go_quad;
  go_quad.alloc();

  Suffer::ref_ptr<Suffer::GeometryComponent> geometry_component2;
  geometry_component2.alloc();
  geometry_component2->SetDrawMode(Suffer::GeometryComponent::kDrawMode_Triangles);
  geometry_component2->CreateGeometryWithShape(Suffer::GeometryComponent::kBasicShapes_Quad);
  go_quad->AddComponent(geometry_component2.get());

  Suffer::ref_ptr<Suffer::MaterialComponent> material_component2;
  material_component2.alloc();
  Suffer::ref_ptr<Suffer::MaterialComponent::PhongParams> material_params2;
  material_params2.alloc();
  material_params2->color_ = mathmorra::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
  material_component2->SetParams(material_params_sphere.get());


  go_quad->AddComponent(material_component_cube.get());

  Suffer::ref_ptr<Suffer::Transform> transform_component_2;
  transform_component_2.alloc();
  transform_component_2->Scale(mathmorra::Vector3(5.0f, 5.0f, 5.0f));
  transform_component_2->Translate(mathmorra::Vector3(0.0f, 0.0f, 10.0f));
  transform_component_2->Rotate(mathmorra::Vector3(0.0f, 0.0f, 0.0f));
  go_quad->AddComponent(transform_component_2.get());


   
  Suffer::ref_ptr<Suffer::LightComponent> light_component2;
  light_component2.alloc();

  light_component2->Init(Suffer::LightComponent::kLightKind_Point);
  light_component2->SetDirection(mathmorra::Vector3(0.0f, 0.0f, 1.0f));
  light_component2->SetIntensity(15.0f);
  light_component2->SetLinear(1.0f);
  light_component2->SetConstant(0.0f);
  light_component2->SetQuadratic(0.0f);
  light_component2->SetAmbient(1.0f, 1.0f, 1.0f);
  light_component2->SetDiffuse(1.0f, 1.0f, 1.0f);
  light_component2->SetSpecular(1.0f, 1.0f, 1.0f);
  go_quad->AddComponent(light_component2.get());




  // SCRIPTING TESTS
  Suffer::ref_ptr<Suffer::ScriptComponent> script_component_;
  script_component_.alloc();
  go_quad->AddComponent(script_component_.get());
  script_component_->AttachScript("../../../src/lua/lua_test_update.lua");

  Suffer::ref_ptr<Suffer::ScriptComponent> script_component_sphere;
  script_component_sphere.alloc();
  go_sphere->AddComponent(script_component_sphere.get());
  script_component_sphere->AttachScript("../../../src/lua/lua_test_update_2.lua");


  Suffer::ref_ptr<Suffer::ScriptComponent> script_component_sphere2;
  script_component_sphere2.alloc();
  go_sphere2->AddComponent(script_component_sphere2.get());
  script_component_sphere2->AttachScript("../../../src/lua/lua_test_update_3.lua");


  Suffer::ref_ptr<Suffer::Audio3D> audio_component_;
  audio_component_.alloc();
  go_sphere->AddComponent(audio_component_.get());

  // -------------------------------------------------------------------------------------//

  go_quad->SetName("Quad");
  go_sphere->SetName("Sphere");
  go_sphere2->SetName("Sphere 2");

  go_quad->AddChild(go_sphere);
  go_sphere->AddChild(go_sphere2);


  u32 childs = go_quad->NumberChildsRecursively(go_quad.get());

  scene->AddGameObject(go_sphere);
  scene->AddGameObject(go_quad);
  scene->AddGameObject(go_sphere2);


  suffer.SetScene(scene);


  suffer.Run();

  suffer.Finish();

  return 0;

}

// --------------------------------------------------------------//

#endif