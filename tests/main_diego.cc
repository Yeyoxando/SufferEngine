
#include <common_definitions.h>
#if !defined _MAIN_PABLO_ && !defined _MAIN_LIGHTS_ && defined _MAIN_DIEGO_

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

  // --------------------------- TEXTURES ------------------------------- //
  // Rock textures
  Suffer::ref_ptr<Suffer::ResourceManager::Texture> rock_texture;
  rock_texture.alloc();
  rock_texture->SetTextureFilter(Suffer::ResourceManager::Texture::kTextureFilter_Linear, Suffer::ResourceManager::Texture::kTextureFilter_Linear);
  rock_texture->SetTextureWrap(Suffer::ResourceManager::Texture::kTextureWrap_ClampToEdge, Suffer::ResourceManager::Texture::kTextureWrap_ClampToEdge);
  rock_texture->LoadTextureData("../../../resources/images/albedo_rock03.jpg");

  // Box textures
  Suffer::ref_ptr<Suffer::ResourceManager::Texture> box_texture;
  box_texture.alloc();
  box_texture->SetTextureFilter(Suffer::ResourceManager::Texture::kTextureFilter_Nearest, Suffer::ResourceManager::Texture::kTextureFilter_Nearest);
  box_texture->SetTextureWrap(Suffer::ResourceManager::Texture::kTextureWrap_ClampToEdge, Suffer::ResourceManager::Texture::kTextureWrap_ClampToEdge);
  box_texture->LoadTextureData("../../../resources/images/box_2.png");

  Suffer::ref_ptr<Suffer::ResourceManager::Texture> box_specular_texture;
  box_specular_texture.alloc();
  box_specular_texture->SetTextureFilter(Suffer::ResourceManager::Texture::kTextureFilter_Linear, Suffer::ResourceManager::Texture::kTextureFilter_Linear);
  box_specular_texture->SetTextureWrap(Suffer::ResourceManager::Texture::kTextureWrap_ClampToEdge, Suffer::ResourceManager::Texture::kTextureWrap_ClampToEdge);
  box_specular_texture->LoadTextureData("../../../resources/images/box_2_spec.png");

  // Ground textures
  Suffer::ref_ptr<Suffer::ResourceManager::Texture> ground_texture;
  ground_texture.alloc();
  ground_texture->SetTextureFilter(Suffer::ResourceManager::Texture::kTextureFilter_Nearest, Suffer::ResourceManager::Texture::kTextureFilter_Nearest);
  ground_texture->SetTextureWrap(Suffer::ResourceManager::Texture::kTextureWrap_Repeat, Suffer::ResourceManager::Texture::kTextureWrap_Repeat);
  ground_texture->LoadTextureData("../../../resources/images/floor_.png");

  Suffer::ref_ptr<Suffer::ResourceManager::Texture> ground_specular_texture;
  ground_specular_texture.alloc();
  ground_specular_texture->SetTextureFilter(Suffer::ResourceManager::Texture::kTextureFilter_Linear, Suffer::ResourceManager::Texture::kTextureFilter_Linear);
  ground_specular_texture->SetTextureWrap(Suffer::ResourceManager::Texture::kTextureWrap_Repeat, Suffer::ResourceManager::Texture::kTextureWrap_Repeat);
  ground_specular_texture->LoadTextureData("../../../resources/images/floor_spec.png");

  //Skybox textures
  Suffer::ref_ptr<Suffer::ResourceManager::Cubemap> skybox_cubemap;
  skybox_cubemap.alloc();
  skybox_cubemap->LoadCubemapTextureData("../../../resources/images/skybox/sky_right.jpg",
                                          "../../../resources/images/skybox/sky_left.jpg", 
                                          "../../../resources/images/skybox/sky_top.jpg", 
                                          "../../../resources/images/skybox/sky_bottom.jpg", 
                                          "../../../resources/images/skybox/sky_front.jpg", 
                                          "../../../resources/images/skybox/sky_back.jpg");

  // --------------------------- MATERIALS ------------------------------- //

  // Box material
  Suffer::ref_ptr<Suffer::MaterialComponent> material_box;
  material_box.alloc();
  Suffer::ref_ptr<Suffer::MaterialComponent::BlinnPhongParams> material_params_box;
  material_params_box.alloc();
  material_params_box->color_ = mathmorra::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
  material_params_box->SetAlbedoTexture(rock_texture.get());
  //material_params_box->SetSpecularTexture(box_specular_texture.get());
  //material_params_box->SetReflectionTexture(box_specular_texture.get(), 1.0f);
  material_box->SetParams(material_params_box.get());

  // Ground material
  Suffer::ref_ptr<Suffer::MaterialComponent> material_ground;
  material_ground.alloc();
  Suffer::ref_ptr<Suffer::MaterialComponent::BlinnPhongParams> material_params_ground;
  material_params_ground.alloc();
  material_params_ground->color_ = mathmorra::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
  material_params_ground->tiling_ = mathmorra::Vector2(5.0f, 5.0f);
  material_params_ground->SetAlbedoTexture(ground_texture.get());
  material_params_ground->SetSpecularTexture(ground_specular_texture.get());
  material_ground->SetParams(material_params_ground.get());

  // White material
  Suffer::ref_ptr<Suffer::MaterialComponent> material_white;
  material_white.alloc();
  Suffer::ref_ptr<Suffer::MaterialComponent::BlinnPhongParams> material_params_white;
  material_params_white.alloc();
  material_params_white->color_ = mathmorra::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
  material_white->SetParams(material_params_white.get());

  // --------------------------- GEOMETRIES ------------------------------ //

  // Cube
  Suffer::ref_ptr<Suffer::GeometryComponent> geometry_component_cube;
  geometry_component_cube.alloc();
  geometry_component_cube->SetDrawMode(Suffer::GeometryComponent::kDrawMode_Triangles);
  geometry_component_cube->CreateGeometryWithShape(Suffer::GeometryComponent::kBasicShapes_Cube);

  // Quad
  Suffer::ref_ptr<Suffer::GeometryComponent> geometry_component_quad;
  geometry_component_quad.alloc();
  geometry_component_quad->SetDrawMode(Suffer::GeometryComponent::kDrawMode_Triangles);
  geometry_component_quad->CreateGeometryWithShape(Suffer::GeometryComponent::kBasicShapes_Quad);

  // Sphere
  Suffer::ref_ptr<Suffer::GeometryComponent> geometry_component_sphere;
  geometry_component_sphere.alloc();
  geometry_component_sphere->SetDrawMode(Suffer::GeometryComponent::kDrawMode_Triangles);
  geometry_component_sphere->CreateGeometryWithShape(Suffer::GeometryComponent::kBasicShapes_Sphere);

  // OBJ
  Suffer::ref_ptr<Suffer::GeometryComponent> geometry_component_obj;
  geometry_component_obj.alloc();
  geometry_component_obj->SetDrawMode(Suffer::GeometryComponent::kDrawMode_Triangles);
  geometry_component_obj->CreateGeometryWithOBJ("../../../resources/models/rock_03.obj");

  // ----------------------------- LIGHTS -------------------------------- //
  // Directional
  Suffer::ref_ptr<Suffer::LightComponent> directional_light_component;
  directional_light_component.alloc();
  directional_light_component->Init(Suffer::LightComponent::kLightKind_Directional);
  directional_light_component->SetDirection(mathmorra::Vector3(0.0f, -1.0f, 0.0f));
  directional_light_component->SetIntensity(0.1f);
  directional_light_component->SetAmbient(0.2f, 0.2f, 0.2f);
  directional_light_component->SetDiffuse(0.6f, 0.6f, 0.6f);
  directional_light_component->SetSpecular(1.0f, 1.0f, 1.0f);
  directional_light_component->SetActive(true);
  
  // Point
  Suffer::ref_ptr<Suffer::LightComponent> point_light_component;
  point_light_component.alloc();
  point_light_component->Init(Suffer::LightComponent::kLightKind_Point);
  point_light_component->SetDirection(mathmorra::Vector3(0.0f, 0.0f, 1.0f));
  point_light_component->SetIntensity(8.0f);
  point_light_component->SetAmbient(0.5f, 0.5f, 0.5f);
  point_light_component->SetDiffuse(1.0f, 1.0f, 1.0f);
  point_light_component->SetSpecular(1.0f, 1.0f, 1.0f);
  point_light_component->SetActive(true);

  // Spot
  Suffer::ref_ptr<Suffer::LightComponent> spot_light_component;
  spot_light_component.alloc();
  spot_light_component->Init(Suffer::LightComponent::kLightKind_Spot);
  spot_light_component->SetDirection(mathmorra::Vector3(1.0f, -0.5f, 0.0f));
  spot_light_component->SetIntensity(10.0f);
  spot_light_component->SetAmbient(0.5f, 0.5f, 0.5f);
  spot_light_component->SetDiffuse(1.0f, 1.0f, 1.0f);
  spot_light_component->SetSpecular(1.0f, 1.0f, 1.0f);
  spot_light_component->SetActive(true);
  spot_light_component->SetCutOff(0.910f);
  spot_light_component->SetOuterCutOff(0.820f);
  spot_light_component->SetConstant(0.0f);
  spot_light_component->SetLinear(0.474f);
  spot_light_component->SetQuadratic(0.0f);

  // -------------------------- GAMEOBJECTS -------------------------------//

  // -- Ground --
  Suffer::ref_ptr<Suffer::GameObject> go_ground;
  go_ground.alloc();
  go_ground->SetName("Ground");

  Suffer::ref_ptr<Suffer::Transform> transform_component_ground;
  transform_component_ground.alloc();
  transform_component_ground->Scale(mathmorra::Vector3(50.0f, -50.0f, 50.0f));
  transform_component_ground->Translate(mathmorra::Vector3(0.0f, 0.0f, 0.0f));
  transform_component_ground->Rotate(mathmorra::Vector3(ThiefUtils::Math::Radians(-90.0f), 0.0f, 0.0f));

  go_ground->AddComponent(transform_component_ground.get());
  go_ground->AddComponent(geometry_component_quad.get());
  go_ground->AddComponent(material_ground.get());

  // -- Point Light --
  Suffer::ref_ptr<Suffer::GameObject> go_point_light;
  go_point_light.alloc();
  go_point_light->SetName("PointLight");

  Suffer::ref_ptr<Suffer::Transform> transform_component_point_light;
  transform_component_point_light.alloc();
  transform_component_point_light->Scale(mathmorra::Vector3(1.0f, 1.0f, 1.0f));
  transform_component_point_light->Translate(mathmorra::Vector3(5.0f, 0.0f, 5.0f));
  transform_component_point_light->Rotate(mathmorra::Vector3(ThiefUtils::Math::Radians(-90.0f), 0.0f, ThiefUtils::Math::Radians(180.0f)));

  go_point_light->AddComponent(transform_component_point_light.get());
  go_point_light->AddComponent(geometry_component_sphere.get());
  go_point_light->AddComponent(material_white.get());
  go_point_light->AddComponent(point_light_component.get());

  // -- Directional light --
  Suffer::ref_ptr<Suffer::GameObject> go_directional_light;
  go_directional_light.alloc();
  go_directional_light->SetName("DirectionalLight");

  go_directional_light->SetArchetype(Suffer::GameObject::kArchetype_Drawable);

  Suffer::Transform* transform = static_cast<Suffer::Transform*>(go_directional_light->GetComponent(Suffer::Component::kComponentKind_Transform));
  transform->Translate(mathmorra::Vector3(-5.0f, 5.0f, -5.0f));

  go_directional_light->AddComponent(directional_light_component.get());

  // -- Spot light --
  Suffer::ref_ptr<Suffer::GameObject> go_spot_light;
  go_spot_light.alloc();
  go_spot_light->SetName("SpotLight");
  go_spot_light->SetArchetype(Suffer::GameObject::kArchetype_Drawable);

  Suffer::GeometryComponent* geo_comp_spot = static_cast<Suffer::GeometryComponent*>(go_spot_light->GetComponent(Suffer::Component::kComponentKind_Geometry));
  geo_comp_spot->CreateGeometryWithShape(Suffer::GeometryComponent::kBasicShapes_Sphere);

  Suffer::Transform* transform_spot = static_cast<Suffer::Transform*>(go_spot_light->GetComponent(Suffer::Component::kComponentKind_Transform));
  transform_spot->Translate(mathmorra::Vector3(-10.0f, 10.0f, 0.0f));

  go_spot_light->AddComponent(spot_light_component.get());

  // -- Box --
  Suffer::ref_ptr<Suffer::GameObject> go_box;
  go_box.alloc();
  go_box->SetName("Box");

  Suffer::ref_ptr<Suffer::Transform> transform_component_cube;
  transform_component_cube.alloc();
  transform_component_cube->Translate(mathmorra::Vector3(0.0f, 2.0f, 0.0f));
  transform_component_cube->Rotate(mathmorra::Vector3(0.0f, ThiefUtils::Math::Radians(-125.0f), 0.0f));
  transform_component_cube->Scale(mathmorra::Vector3(0.3f, 0.3f, 0.3f));

  Suffer::ref_ptr<Suffer::ScriptComponent> script;
  script.alloc();

  go_box->AddComponent(transform_component_cube.get());
  go_box->AddComponent(geometry_component_obj.get());
  go_box->AddComponent(material_box.get());
  go_box->AddComponent(script.get());

  auto geometry_component = go_box->GetComponent(Suffer::Component::kComponentKind_Geometry);
  Suffer::GeometryComponent* geometry_ = reinterpret_cast<Suffer::GeometryComponent*>(geometry_component);

 //go_box->AddChild(go_point_light.get());
 //go_box->AddChild(go_directional_light.get());

  //script->AttachScript("../../../src/lua/lua_test_update.lua");

  // -------------------------------------------------------------------------------------//


  // Create skybox
  Suffer::ref_ptr<Suffer::Skybox> skybox;
  skybox.alloc();
  skybox->SetCubemap(skybox_cubemap);


  // Set gameobjects and scene things
  scene->AddGameObject(go_box);
  scene->AddGameObject(go_ground);
  scene->AddGameObject(go_point_light);
  scene->AddGameObject(go_directional_light);
  scene->AddGameObject(go_spot_light);
  scene->SetSkybox(skybox);


  // Execute engine
  suffer.SetScene(scene);
  suffer.Run();

  suffer.Finish();

  return 0;

}

// --------------------------------------------------------------//

#endif