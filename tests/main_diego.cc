
#include <common_definitions.h>
#if defined _MAIN_DIEGO_

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

  // Ground textures
  Suffer::ref_ptr<Suffer::ResourceManager::Texture> ground_texture;
  ground_texture.alloc();
  ground_texture->SetTextureFilter(Suffer::ResourceManager::Texture::kTextureFilter_Linear, Suffer::ResourceManager::Texture::kTextureFilter_Linear);
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

  // Ground material
  Suffer::ref_ptr<Suffer::MaterialComponent> material_ground;
  material_ground.alloc();
  Suffer::ref_ptr<Suffer::MaterialComponent::BlinnPhongParams> material_params_ground;
  material_params_ground.alloc();
  material_params_ground->color_ = mathmorra::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
  material_params_ground->tiling_ = mathmorra::Vector2(5.0f, 5.0f);
  material_params_ground->SetAlbedoTexture(ground_texture.get());
  material_params_ground->SetSpecularTexture(ground_specular_texture.get());
  material_ground->AddParams(material_params_ground.get());

  // White material
  Suffer::ref_ptr<Suffer::MaterialComponent> material_white;
  material_white.alloc();
  Suffer::ref_ptr<Suffer::MaterialComponent::BlinnPhongParams> material_params_white;
  material_params_white.alloc();
  material_params_white->color_ = mathmorra::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
  material_white->AddParams(material_params_white.get());

  // --------------------------- GEOMETRIES ------------------------------ //

  // Cube
  Suffer::ref_ptr<Suffer::GeometryComponent> geometry_component_cube;
  geometry_component_cube.alloc();
  geometry_component_cube->SetDrawMode(Suffer::GeometryComponent::kDrawMode_Triangles);
  geometry_component_cube->CreateGeometryWithShape(Suffer::GeometryComponent::kBasicShapes_Cube);

  // Sphere
  Suffer::ref_ptr<Suffer::GeometryComponent> geometry_component_sphere;
  geometry_component_sphere.alloc();
  geometry_component_sphere->SetDrawMode(Suffer::GeometryComponent::kDrawMode_Triangles);
  geometry_component_sphere->CreateGeometryWithShape(Suffer::GeometryComponent::kBasicShapes_Sphere);

  // Terrain
  Suffer::ref_ptr<Suffer::GeometryComponent> geometry_component_terrain;
  geometry_component_terrain.alloc();
  geometry_component_terrain->SetDrawMode(Suffer::GeometryComponent::kDrawMode_Triangles);
  geometry_component_terrain->CreateTerrainGeometry(0.0354f, 65.0f, 32.0f);

  // OBJ
  Suffer::ref_ptr<Suffer::MaterialComponent> material_mario;
  material_mario.alloc();
  Suffer::ref_ptr<Suffer::GeometryComponent> geometry_component_obj;
  geometry_component_obj.alloc();
  geometry_component_obj->SetDrawMode(Suffer::GeometryComponent::kDrawMode_Triangles);
  geometry_component_obj->CreateGeometryWithOBJAndMTL("../../../resources/models/SuperMairo64.obj",
      *material_mario.get(), "../../../resources/materials/", "../../../resources/images/Mario64/");

  // Sword OBJ And MTL
  Suffer::ref_ptr<Suffer::MaterialComponent> material_sword;
  material_sword.alloc();
  Suffer::ref_ptr<Suffer::GeometryComponent> geometry_component_sword;
  geometry_component_sword.alloc();
  geometry_component_sword->SetDrawMode(Suffer::GeometryComponent::kDrawMode_Triangles);
  geometry_component_sword->CreateGeometryWithOBJAndMTL("../../../resources/models/sword.obj",
    *material_sword.get(), "../../../resources/materials/", "../../../resources/images/sword/");

  // Rock OBJ And MTL
  Suffer::ref_ptr<Suffer::MaterialComponent> material_rock;
  material_rock.alloc();
  Suffer::ref_ptr<Suffer::GeometryComponent> geometry_component_rock;
  geometry_component_rock.alloc();
  geometry_component_rock->SetDrawMode(Suffer::GeometryComponent::kDrawMode_Triangles);
  geometry_component_rock->CreateGeometryWithOBJAndMTL("../../../resources/models/rock_03.obj",
    *material_rock.get(), "../../../resources/materials/", "../../../resources/images/");

  // Rock 2 OBJ And MTL
  Suffer::ref_ptr<Suffer::MaterialComponent> material_rock2;
  material_rock2.alloc();
  Suffer::ref_ptr<Suffer::GeometryComponent> geometry_component_rock2;
  geometry_component_rock2.alloc();
  geometry_component_rock2->SetDrawMode(Suffer::GeometryComponent::kDrawMode_Triangles);
  geometry_component_rock2->CreateGeometryWithOBJAndMTL("../../../resources/models/rock_23.obj",
    *material_rock2.get(), "../../../resources/materials/", "../../../resources/images/");

  // Rock 3 OBJ And MTL
  Suffer::ref_ptr<Suffer::MaterialComponent> material_rock3;
  material_rock3.alloc();
  Suffer::ref_ptr<Suffer::GeometryComponent> geometry_component_rock3;
  geometry_component_rock3.alloc();
  geometry_component_rock3->SetDrawMode(Suffer::GeometryComponent::kDrawMode_Triangles);
  geometry_component_rock3->CreateGeometryWithOBJAndMTL("../../../resources/models/rock_45.obj",
    *material_rock3.get(), "../../../resources/materials/", "../../../resources/images/");

  // House OBJ And MTL
  Suffer::ref_ptr<Suffer::MaterialComponent> material_house;
  material_house.alloc();
  Suffer::ref_ptr<Suffer::GeometryComponent> geometry_component_house;
  geometry_component_house.alloc();
  geometry_component_house->SetDrawMode(Suffer::GeometryComponent::kDrawMode_Triangles);
  geometry_component_house->CreateGeometryWithOBJAndMTL("../../../resources/models/house.obj",
    *material_house.get(), "../../../resources/materials/", "../../../resources/images/");

  // Chest OBJ And MTL
  Suffer::ref_ptr<Suffer::MaterialComponent> material_chest;
  material_chest.alloc();
  Suffer::ref_ptr<Suffer::GeometryComponent> geometry_component_chest;
  geometry_component_chest.alloc();
  geometry_component_chest->SetDrawMode(Suffer::GeometryComponent::kDrawMode_Triangles);
  geometry_component_chest->CreateGeometryWithOBJAndMTL("../../../resources/models/chest.obj",
    *material_chest.get(), "../../../resources/materials/", "../../../resources/images/chest/");

  // Torch OBJ And MTL
  Suffer::ref_ptr<Suffer::MaterialComponent> material_torch;
  material_torch.alloc();
  Suffer::ref_ptr<Suffer::GeometryComponent> geometry_component_torch;
  geometry_component_torch.alloc();
  geometry_component_torch->SetDrawMode(Suffer::GeometryComponent::kDrawMode_Triangles);
  geometry_component_torch->CreateGeometryWithOBJAndMTL("../../../resources/models/torch.obj",
    *material_torch.get(), "../../../resources/materials/", "../../../resources/images/torch/");

  // ----------------------------- LIGHTS -------------------------------- //
  // Directional
  Suffer::ref_ptr<Suffer::LightComponent> directional_light_component;
  directional_light_component.alloc();
  directional_light_component->Init(Suffer::LightComponent::kLightKind_Directional);
  directional_light_component->SetDirection(mathmorra::Vector3(0.0f, -1.0f, 0.0f));
  directional_light_component->SetIntensity(0.2f);
  directional_light_component->SetAmbient(0.6f, 0.6f, 0.6f);
  directional_light_component->SetDiffuse(0.6f, 0.6f, 0.6f);
  directional_light_component->SetSpecular(1.0f, 1.0f, 1.0f);
  directional_light_component->SetActive(true);
  
  // Point
  Suffer::ref_ptr<Suffer::LightComponent> point_light_component;
  point_light_component.alloc();
  point_light_component->Init(Suffer::LightComponent::kLightKind_Point);
  point_light_component->SetDirection(mathmorra::Vector3(0.0f, 0.0f, 1.0f));
  point_light_component->SetIntensity(12.0f);
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
  spot_light_component->SetConstant(0.449f);
  spot_light_component->SetLinear(0.083f);
  spot_light_component->SetQuadratic(0.086f);
  spot_light_component->SetAngle(90.0f);

  // Spot 2
  Suffer::ref_ptr<Suffer::LightComponent> spot_light_component2;
  spot_light_component2.alloc();
  spot_light_component2->Init(Suffer::LightComponent::kLightKind_Spot);
  spot_light_component2->SetDirection(mathmorra::Vector3(-0.3f, -0.5f, -0.55f));
  spot_light_component2->SetIntensity(10.0f);
  spot_light_component2->SetAmbient(0.5f, 0.5f, 0.5f);
  spot_light_component2->SetDiffuse(1.0f, 1.0f, 1.0f);
  spot_light_component2->SetSpecular(1.0f, 1.0f, 1.0f);
  spot_light_component2->SetActive(true);
  spot_light_component2->SetCutOff(0.910f);
  spot_light_component2->SetOuterCutOff(0.820f);
  spot_light_component2->SetConstant(0.0f);
  spot_light_component2->SetLinear(0.474f);
  spot_light_component2->SetQuadratic(0.0f);
  spot_light_component2->SetAngle(90.0f);

  // -------------------------- GAMEOBJECTS -------------------------------//

  // -- Point Light --
  Suffer::ref_ptr<Suffer::GameObject> go_point_light;
  go_point_light.alloc();
  go_point_light->SetName("PointLight");

  Suffer::ref_ptr<Suffer::Transform> transform_component_point_light;
  transform_component_point_light.alloc();
  transform_component_point_light->Translate(mathmorra::Vector3(0.0f, 185.0f, 0.0f));
  transform_component_point_light->Rotate(mathmorra::Vector3(0.0f, 0.0f, 0.0f));
  transform_component_point_light->Scale(mathmorra::Vector3(10.0f, 10.0f, 10.0f));
  Suffer::ref_ptr<Suffer::ScriptComponent> script_point;
  script_point.alloc();

  go_point_light->AddComponent(transform_component_point_light.get());
  go_point_light->AddComponent(geometry_component_sphere.get());
  go_point_light->AddComponent(material_white.get());
  go_point_light->AddComponent(point_light_component.get());
  go_point_light->AddComponent(script_point.get());

  script_point->AttachScript("../../../src/lua/lua_point.lua");

  // -- Directional light --
  Suffer::ref_ptr<Suffer::GameObject> go_directional_light;
  go_directional_light.alloc();
  go_directional_light->SetName("DirectionalLight");

  go_directional_light->SetArchetype(Suffer::GameObject::kArchetype_Drawable);

  Suffer::Transform* transform = static_cast<Suffer::Transform*>(go_directional_light->GetComponent(Suffer::Component::kComponentKind_Transform));
  transform->Translate(mathmorra::Vector3(-5.0f, 200.0f, -5.0f));

  go_directional_light->AddComponent(directional_light_component.get());

  // -- Spot light --
  Suffer::ref_ptr<Suffer::GameObject> go_spot_light;
  go_spot_light.alloc();
  go_spot_light->SetName("SpotLight");
  go_spot_light->SetArchetype(Suffer::GameObject::kArchetype_Drawable);

  Suffer::GeometryComponent* geo_comp_spot = static_cast<Suffer::GeometryComponent*>(go_spot_light->GetComponent(Suffer::Component::kComponentKind_Geometry));
  geo_comp_spot->CreateGeometryWithShape(Suffer::GeometryComponent::kBasicShapes_Sphere);

  Suffer::Transform* transform_spot = static_cast<Suffer::Transform*>(go_spot_light->GetComponent(Suffer::Component::kComponentKind_Transform));
  transform_spot->Translate(mathmorra::Vector3(80.0f, 20.0f, 0.0f));

  go_spot_light->AddComponent(spot_light_component.get());

  // -- Spot light 2 --
  Suffer::ref_ptr<Suffer::GameObject> go_spot_light2;
  go_spot_light2.alloc();
  go_spot_light2->SetName("SpotLight2");
  go_spot_light2->SetArchetype(Suffer::GameObject::kArchetype_Drawable);

  Suffer::GeometryComponent* geo_comp_spot2 = static_cast<Suffer::GeometryComponent*>(go_spot_light2->GetComponent(Suffer::Component::kComponentKind_Geometry));
  geo_comp_spot2->CreateGeometryWithShape(Suffer::GeometryComponent::kBasicShapes_Sphere);

  Suffer::Transform* transform_spot2 = static_cast<Suffer::Transform*>(go_spot_light2->GetComponent(Suffer::Component::kComponentKind_Transform));
  transform_spot2->Translate(mathmorra::Vector3(-10.0f, -15.0f, -130.0f));

  go_spot_light2->AddComponent(spot_light_component2.get());

  // -- Mario --
  Suffer::ref_ptr<Suffer::GameObject> go_mario;
  go_mario.alloc();
  go_mario->SetName("Mario");

  Suffer::ref_ptr<Suffer::Transform> transform_component_mario;
  transform_component_mario.alloc();
  transform_component_mario->Translate(mathmorra::Vector3(-30.0f, -40.0f, -150.0f));
  transform_component_mario->Rotate(mathmorra::Vector3(0.0f, ThiefUtils::Math::Radians(-125.0f), 0.0f));
  transform_component_mario->Scale(mathmorra::Vector3(0.5f, 0.5f, 0.5f));

  Suffer::ref_ptr<Suffer::ScriptComponent> script;
  script.alloc();

  go_mario->AddComponent(transform_component_mario.get());
  go_mario->AddComponent(geometry_component_obj.get());
  go_mario->AddComponent(material_mario.get());
  go_mario->AddComponent(script.get());

  script->AttachScript("../../../src/lua/lua_test_update.lua");

  // -- Chest --
  Suffer::ref_ptr<Suffer::GameObject> go_chest;
  go_chest.alloc();
  go_chest->SetName("Chest");

  Suffer::ref_ptr<Suffer::Transform> transform_component_chest;
  transform_component_chest.alloc();
  transform_component_chest->Translate(mathmorra::Vector3(-100.0f, -49.0f, -135.0f));
  transform_component_chest->Rotate(mathmorra::Vector3(ThiefUtils::Math::Radians(180.0f), ThiefUtils::Math::Radians(-30.0f), ThiefUtils::Math::Radians(182.0f)));
  transform_component_chest->Scale(mathmorra::Vector3(20.0f, 20.0f, 20.0f));

  go_chest->AddComponent(transform_component_chest.get());
  go_chest->AddComponent(geometry_component_chest.get());
  go_chest->AddComponent(material_chest.get());

  // -- Sword --
  Suffer::ref_ptr<Suffer::GameObject> go_sword;
  go_sword.alloc();
  go_sword->SetName("Sword");

  Suffer::ref_ptr<Suffer::Transform> transform_component_sword;
  transform_component_sword.alloc();
  transform_component_sword->Translate(mathmorra::Vector3(0.0f, 2.0f, 0.0f));
  transform_component_sword->Rotate(mathmorra::Vector3(ThiefUtils::Math::Radians(-5.0f), ThiefUtils::Math::Radians(-125.0f), ThiefUtils::Math::Radians(0.0f)));
  transform_component_sword->Scale(mathmorra::Vector3(0.1f, 0.1f, 0.1f));

  go_sword->AddComponent(transform_component_sword.get());
  go_sword->AddComponent(geometry_component_sword.get());
  go_sword->AddComponent(material_sword.get());

  // -- Rock --
  Suffer::ref_ptr<Suffer::GameObject> go_rock;
  go_rock.alloc();
  go_rock->SetName("Rock");

  Suffer::ref_ptr<Suffer::Transform> transform_component_rock;
  transform_component_rock.alloc();
  transform_component_rock->Translate(mathmorra::Vector3(120.0f, 7.0f, 0.0f));
  transform_component_rock->Rotate(mathmorra::Vector3(ThiefUtils::Math::Radians(10.0f), ThiefUtils::Math::Radians(30.0f), 0.0f));
  transform_component_rock->Scale(mathmorra::Vector3(5.0f, 5.0f, 5.0f));

  go_rock->AddComponent(transform_component_rock.get());
  go_rock->AddComponent(geometry_component_rock.get());
  go_rock->AddComponent(material_rock.get());
  go_rock->AddChild(go_sword);

  // -- Rock 2 --
  Suffer::ref_ptr<Suffer::GameObject> go_rock2;
  go_rock2.alloc();
  go_rock2->SetName("Rock2");

  Suffer::ref_ptr<Suffer::Transform> transform_component_rock2;
  transform_component_rock2.alloc();
  transform_component_rock2->Translate(mathmorra::Vector3(60.0f, -23.0f, 150.0f));
  transform_component_rock2->Rotate(mathmorra::Vector3(ThiefUtils::Math::Radians(5.0f), ThiefUtils::Math::Radians(50.0f), ThiefUtils::Math::Radians(-10.0f)));
  transform_component_rock2->Scale(mathmorra::Vector3(5.0f, 5.0f, 5.0f));

  go_rock2->AddComponent(transform_component_rock2.get());
  go_rock2->AddComponent(geometry_component_rock2.get());
  go_rock2->AddComponent(material_rock2.get());

  // -- Rock 3 --
  Suffer::ref_ptr<Suffer::GameObject> go_rock3;
  go_rock3.alloc();
  go_rock3->SetName("Rock3");

  Suffer::ref_ptr<Suffer::Transform> transform_component_rock3;
  transform_component_rock3.alloc();
  transform_component_rock3->Translate(mathmorra::Vector3(-25.0f, -38.0f, 25.0f));
  transform_component_rock3->Rotate(mathmorra::Vector3(ThiefUtils::Math::Radians(15.0f), ThiefUtils::Math::Radians(50.0f), ThiefUtils::Math::Radians(-20.0f)));
  transform_component_rock3->Scale(mathmorra::Vector3(4.0f, 4.0f, 4.0f));

  go_rock3->AddComponent(transform_component_rock3.get());
  go_rock3->AddComponent(geometry_component_rock3.get());
  go_rock3->AddComponent(material_rock3.get());

  // -- Rock 4 --
  Suffer::ref_ptr<Suffer::GameObject> go_rock4;
  go_rock4.alloc();
  go_rock4->SetName("Rock4");

  Suffer::ref_ptr<Suffer::Transform> transform_component_rock4;
  transform_component_rock4.alloc();
  transform_component_rock4->Translate(mathmorra::Vector3(-200.0f, -2.5f, 50.0f));
  transform_component_rock4->Rotate(mathmorra::Vector3(ThiefUtils::Math::Radians(10.0f), ThiefUtils::Math::Radians(200.0f), ThiefUtils::Math::Radians(10.0f)));
  transform_component_rock4->Scale(mathmorra::Vector3(3.0f, 3.0f, 4.0f));

  go_rock4->AddComponent(transform_component_rock4.get());
  go_rock4->AddComponent(geometry_component_rock.get());
  go_rock4->AddComponent(material_rock.get());

  // -- Rock 5 --
  Suffer::ref_ptr<Suffer::GameObject> go_rock5;
  go_rock5.alloc();
  go_rock5->SetName("Rock5");

  Suffer::ref_ptr<Suffer::Transform> transform_component_rock5;
  transform_component_rock5.alloc();
  transform_component_rock5->Translate(mathmorra::Vector3(200.0f, 4.0f, -120.0f));
  transform_component_rock5->Rotate(mathmorra::Vector3(ThiefUtils::Math::Radians(5.0f), ThiefUtils::Math::Radians(50.0f), ThiefUtils::Math::Radians(-10.0f)));
  transform_component_rock5->Scale(mathmorra::Vector3(2.0f, 4.0f, 4.0f));

  go_rock5->AddComponent(transform_component_rock5.get());
  go_rock5->AddComponent(geometry_component_rock2.get());
  go_rock5->AddComponent(material_rock2.get());

  // -- Rock 6 --
  Suffer::ref_ptr<Suffer::GameObject> go_rock6;
  go_rock6.alloc();
  go_rock6->SetName("Rock6");

  Suffer::ref_ptr<Suffer::Transform> transform_component_rock6;
  transform_component_rock6.alloc();
  transform_component_rock6->Translate(mathmorra::Vector3(50.0f, -27.0f, -210.0f));
  transform_component_rock6->Rotate(mathmorra::Vector3(ThiefUtils::Math::Radians(30.0f), ThiefUtils::Math::Radians(200.0f), ThiefUtils::Math::Radians(-100.0f)));
  transform_component_rock6->Scale(mathmorra::Vector3(3.0f, 5.0f, 4.0f));

  go_rock6->AddComponent(transform_component_rock6.get());
  go_rock6->AddComponent(geometry_component_rock3.get());
  go_rock6->AddComponent(material_rock3.get());

  // -- Rock 7 --
  Suffer::ref_ptr<Suffer::GameObject> go_rock7 ;
  go_rock7.alloc();
  go_rock7->SetName("Rock7");

  Suffer::ref_ptr<Suffer::Transform> transform_component_rock7;
  transform_component_rock7.alloc();
  transform_component_rock7->Translate(mathmorra::Vector3(-125.0f, 30.0f, 205.0f));
  transform_component_rock7->Rotate(mathmorra::Vector3(ThiefUtils::Math::Radians(90.0f), ThiefUtils::Math::Radians(-20.0f), ThiefUtils::Math::Radians(96.0f)));
  transform_component_rock7->Scale(mathmorra::Vector3(8.0f, 8.0f, 8.0f));

  go_rock7->AddComponent(transform_component_rock7.get());
  go_rock7->AddComponent(geometry_component_rock2.get());
  go_rock7->AddComponent(material_rock2.get());

  // -- Rock 8 --
  Suffer::ref_ptr<Suffer::GameObject> go_rock8;
  go_rock8.alloc();
  go_rock8->SetName("Rock8");

  Suffer::ref_ptr<Suffer::Transform> transform_component_rock8;
  transform_component_rock8.alloc();
  transform_component_rock8->Translate(mathmorra::Vector3(-260.0f, 8.0f, -120.0f));
  transform_component_rock8->Rotate(mathmorra::Vector3(ThiefUtils::Math::Radians(15.0f), ThiefUtils::Math::Radians(180.0f), ThiefUtils::Math::Radians(40.0f)));
  transform_component_rock8->Scale(mathmorra::Vector3(6.0f, 5.0f, 6.0f));

  go_rock8->AddComponent(transform_component_rock8.get());
  go_rock8->AddComponent(geometry_component_rock3.get());
  go_rock8->AddComponent(material_rock3.get());

  // -- House --
  Suffer::ref_ptr<Suffer::GameObject> go_house;
  go_house.alloc();
  go_house->SetName("House");

  Suffer::ref_ptr<Suffer::Transform> transform_component_house;
  transform_component_house.alloc();
  transform_component_house->Translate(mathmorra::Vector3(-120.0f, -42.0f, -240.0f));
  transform_component_house->Rotate(mathmorra::Vector3(ThiefUtils::Math::Radians(-2.0f), ThiefUtils::Math::Radians(50.0f), ThiefUtils::Math::Radians(3.0f)));
  transform_component_house->Scale(mathmorra::Vector3(2.0f, 2.0f, 2.0f));

  go_house->AddComponent(transform_component_house.get());
  go_house->AddComponent(geometry_component_house.get());
  go_house->AddComponent(material_house.get());

  // -- Torch --
  Suffer::ref_ptr<Suffer::GameObject> go_torch;
  go_torch.alloc();
  go_torch->SetName("Torch");

  Suffer::ref_ptr<Suffer::Transform> transform_component_torch;
  transform_component_torch.alloc();
  transform_component_torch->Translate(mathmorra::Vector3(-120.0f, -35.5f, 25.0f));
  transform_component_torch->Rotate(mathmorra::Vector3(ThiefUtils::Math::Radians(10.0f), ThiefUtils::Math::Radians(50.0f), ThiefUtils::Math::Radians(-3.0f)));
  transform_component_torch->Scale(mathmorra::Vector3(0.2f, 0.2f, 0.2f));

  go_torch->AddComponent(transform_component_torch.get());
  go_torch->AddComponent(geometry_component_torch.get());
  go_torch->AddComponent(material_torch.get());

  go_torch->AddChild(go_point_light);

  // -------------------------------------------------------------------------------------//


   // -- Terrain --
  Suffer::ref_ptr<Suffer::GameObject> go_terrain;
  go_terrain.alloc();
  go_terrain->SetName("Terrain");

  Suffer::ref_ptr<Suffer::Transform> transform_component_terrain;
  transform_component_terrain.alloc();
  transform_component_terrain->Translate(mathmorra::Vector3(-300.0f, 2.0f, -300.0f));
  transform_component_terrain->Rotate(mathmorra::Vector3(0.0f, 0.0f, 0.0f));
  transform_component_terrain->Scale(mathmorra::Vector3(3.0f, 3.0f, 3.0f));

  go_terrain->AddComponent(transform_component_terrain.get());
  go_terrain->AddComponent(geometry_component_terrain.get());
  go_terrain->AddComponent(material_ground.get());


  // Create skybox
  Suffer::ref_ptr<Suffer::Skybox> skybox;
  skybox.alloc();
  skybox->SetCubemap(skybox_cubemap);


  // Set gameobjects and scene things
  //scene->AddGameObject(go_ground);
  scene->AddGameObject(go_point_light);
  scene->AddGameObject(go_directional_light);
  scene->AddGameObject(go_spot_light);
  scene->AddGameObject(go_spot_light2);
  scene->AddGameObject(go_mario);
  scene->AddGameObject(go_chest);
  scene->AddGameObject(go_sword);
  scene->AddGameObject(go_rock);
  scene->AddGameObject(go_rock2);
  scene->AddGameObject(go_rock3);
  scene->AddGameObject(go_rock4);
  scene->AddGameObject(go_rock5);
  scene->AddGameObject(go_rock6);
  scene->AddGameObject(go_rock7);
  scene->AddGameObject(go_rock8);
  scene->AddGameObject(go_house);
  scene->AddGameObject(go_torch);
  scene->AddGameObject(go_terrain);
  scene->SetSkybox(skybox);


  // Execute engine
  suffer.SetScene(scene);

  //scene->GetMainCamera()->SetSpeed(100.0f);
  suffer.Run();

  suffer.Finish();

  return 0;

}

// --------------------------------------------------------------//

#endif