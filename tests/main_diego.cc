
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
#include "component_child.h"
#include "math_utils.h"

// --------------------------------------------------------------//

int main(int argc, char* argv[]) {

  suffer.Init();

  Suffer::ref_ptr<Suffer::Scene> scene;
  scene.alloc();

  // Textures
  Suffer::ref_ptr<Suffer::ResourceManager::Texture> albedo_texture;
  albedo_texture.alloc();
  albedo_texture->SetTextureFilter(Suffer::ResourceManager::Texture::kTextureFilter_Nearest, Suffer::ResourceManager::Texture::kTextureFilter_Nearest);
  albedo_texture->SetTextureWrap(Suffer::ResourceManager::Texture::kTextureWrap_ClampToEdge, Suffer::ResourceManager::Texture::kTextureWrap_ClampToEdge);
  albedo_texture->LoadTextureData("../../../resources/images/box_2.png");

  Suffer::ref_ptr<Suffer::ResourceManager::Texture> specular_texture_box;
  specular_texture_box.alloc();
  specular_texture_box->SetTextureFilter(Suffer::ResourceManager::Texture::kTextureFilter_Linear, Suffer::ResourceManager::Texture::kTextureFilter_Linear);
  specular_texture_box->SetTextureWrap(Suffer::ResourceManager::Texture::kTextureWrap_ClampToEdge, Suffer::ResourceManager::Texture::kTextureWrap_ClampToEdge);
  specular_texture_box->LoadTextureData("../../../resources/images/box_2_spec.png");


  // -------------------------------- COMPONENTS STUFF TESTS ------------------------------//

  Suffer::ref_ptr<Suffer::GameObject> go_cube;
  go_cube.alloc();

  Suffer::ref_ptr<Suffer::GeometryComponent> geometry_component_cube;
  geometry_component_cube.alloc();
  geometry_component_cube->SetDrawMode(Suffer::GeometryComponent::kDrawMode_Triangles);
  geometry_component_cube->CreateGeometryWithShape(Suffer::GeometryComponent::kBasicShapes_Cube);
  go_cube->AddComponent(geometry_component_cube.get());

  Suffer::ref_ptr<Suffer::MaterialComponent> material_component_cube;
  material_component_cube.alloc();
  Suffer::ref_ptr<Suffer::MaterialComponent::DefaultParams> material_params_cube;
  material_params_cube.alloc();
  material_params_cube->color_ = mathmorra::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
  material_params_cube->albedo_texture_id_ = albedo_texture->id_;
  material_params_cube->specular_texture_id_ = specular_texture_box->id_;
  material_component_cube->SetParams(material_params_cube.get());
  go_cube->AddComponent(material_component_cube.get());

  Suffer::ref_ptr<Suffer::Transform> transform_component_cube;
  transform_component_cube.alloc();
  transform_component_cube->Translate(mathmorra::Vector3(0.0f, 1.0f, 0.0f));
  transform_component_cube->Rotate(mathmorra::Vector3(0.0f, 0.0f, 0.0f));
  go_cube->AddComponent(transform_component_cube.get());


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
  material_params2->color_ = mathmorra::Vector4(0.0f, 1.0f, 0.0f, 1.0f);
  material_component2->SetParams(material_params2.get());
  go_quad->AddComponent(material_component2.get());

  Suffer::ref_ptr<Suffer::Transform> transform_component_2;
  transform_component_2.alloc();
  transform_component_2->Scale(mathmorra::Vector3(20.0f, 20.0f, 20.0f));
  transform_component_2->Translate(mathmorra::Vector3(0.0f, 0.0f, 0.0f));
  transform_component_2->Rotate(mathmorra::Vector3(ThiefUtils::Math::Radians(-90.0f), 0.0f, 0.0f));
  go_quad->AddComponent(transform_component_2.get());

  // -------------------------------------------------------------------------------------//
   
  Suffer::ref_ptr<Suffer::GameObject> go_light;
  go_light.alloc();

  Suffer::ref_ptr<Suffer::GeometryComponent> geometry_component3;
  geometry_component3.alloc();
  geometry_component3->SetDrawMode(Suffer::GeometryComponent::kDrawMode_Triangles);
  geometry_component3->CreateGeometryWithShape(Suffer::GeometryComponent::kBasicShapes_Cube);
  go_light->AddComponent(geometry_component3.get());

  Suffer::ref_ptr<Suffer::MaterialComponent> material_component3;
  material_component3.alloc();
  Suffer::ref_ptr<Suffer::MaterialComponent::PhongParams> material_params3;
  material_params3.alloc();
  material_params3->color_ = mathmorra::Vector4(1.0f, 0.5f, 1.0f, 1.0f);
  material_component3->SetParams(material_params3.get());
  go_light->AddComponent(material_component3.get());

  Suffer::ref_ptr<Suffer::Transform> transform_component_3;
  transform_component_3.alloc();
  transform_component_3->Scale(mathmorra::Vector3(1.0f, 1.0f, 1.0f));
  transform_component_3->Translate(mathmorra::Vector3(5.0f, 5.0f, 5.0f));
  transform_component_3->Rotate(mathmorra::Vector3(ThiefUtils::Math::Radians(-90.0f), 0.0f, ThiefUtils::Math::Radians(180.0f)));
  go_light->AddComponent(transform_component_3.get());

  Suffer::ref_ptr<Suffer::LightComponent> light_component;
  light_component.alloc();

  light_component->Init(Suffer::LightComponent::kLightKind_Point);
  light_component->SetDirection(mathmorra::Vector3(0.0f, 0.0f, 1.0f));
  light_component->SetIntensity(1.0f);
  light_component->SetAmbient(0.5f, 0.5f, 0.5f);
  light_component->SetDiffuse(1.0f, 1.0f, 1.0f);
  light_component->SetSpecular(1.0f, 1.0f, 1.0f);
  go_light->AddComponent(light_component.get());

  // -------------------------------------------------------------------------------------//


  Suffer::ref_ptr<Suffer::Transform> transform_component_4;
  transform_component_4.alloc();
  transform_component_4->Scale(mathmorra::Vector3(1.0f, 1.0f, 1.0f));
  transform_component_4->Translate(mathmorra::Vector3(0.0f, 5.0f, 0.0f));

  //Suffer::ref_ptr<Suffer::ScriptComponent> script_component_;
  //script_component_.alloc();
  //go_rotator->AddComponent(script_component_.get());
  //script_component_->AttachScript("../../../src/lua/lua_rotator.lua");

  //go_rotator->AddChild(go_light);

  // -------------------------------------------------------------------------------------//

  Suffer::ref_ptr<Suffer::ScriptComponent> script;
  script.alloc();
  go_cube->AddComponent(script.get());
  script->AttachScript("../../../src/lua/lua_test_update.lua");

  //Suffer::ref_ptr<Suffer::Audio3D> audio_component_;
  //audio_component_.alloc();
  //audio_component_->Load("../../../resources/audio/crossfade/wing_cap.ogg");
  //audio_component_->SetLooping(true);
  //audio_component_->Play3D();
  //go_cube->AddComponent(audio_component_.get());

  go_quad->SetName("Quad");
  go_cube->SetName("Cube");
  go_light->SetName("DirectionalLight");

  scene->AddGameObject(go_cube);
  scene->AddGameObject(go_quad);
  scene->AddGameObject(go_light);


  suffer.SetScene(scene);


  suffer.Run();

  suffer.Finish();

  return 0;

}

// --------------------------------------------------------------//

#endif