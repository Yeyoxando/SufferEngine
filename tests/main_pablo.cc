
#include <common_definitions.h>
#if defined _MAIN_PABLO_

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
    ground_texture->LoadTextureData("../../../resources/images/brick_normal.jpg");

    Suffer::ref_ptr<Suffer::ResourceManager::Texture> ground_specular_texture;
    ground_specular_texture.alloc();
    ground_specular_texture->SetTextureFilter(Suffer::ResourceManager::Texture::kTextureFilter_Linear, Suffer::ResourceManager::Texture::kTextureFilter_Linear);
    ground_specular_texture->SetTextureWrap(Suffer::ResourceManager::Texture::kTextureWrap_Repeat, Suffer::ResourceManager::Texture::kTextureWrap_Repeat);
    ground_specular_texture->LoadTextureData("../../../resources/images/wall_spec.jpg");

    Suffer::ref_ptr<Suffer::ResourceManager::Texture> ground_normal_map_texture;
    ground_normal_map_texture.alloc();
    ground_normal_map_texture->SetTextureFilter(Suffer::ResourceManager::Texture::kTextureFilter_Linear, Suffer::ResourceManager::Texture::kTextureFilter_Linear);
    ground_normal_map_texture->SetTextureWrap(Suffer::ResourceManager::Texture::kTextureWrap_Repeat, Suffer::ResourceManager::Texture::kTextureWrap_Repeat);
    ground_normal_map_texture->LoadTextureData("../../../resources/images/brick_normal_map2.png");



    // Wood floor texture
    Suffer::ref_ptr<Suffer::ResourceManager::Texture> wood_floor_texture_;
    wood_floor_texture_.alloc();
    wood_floor_texture_->SetTextureFilter(Suffer::ResourceManager::Texture::kTextureFilter_Linear, Suffer::ResourceManager::Texture::kTextureFilter_Linear);
    wood_floor_texture_->SetTextureWrap(Suffer::ResourceManager::Texture::kTextureWrap_Repeat, Suffer::ResourceManager::Texture::kTextureWrap_Repeat);
    wood_floor_texture_->LoadTextureData("../../../resources/images/floor/wood_albedo.jpg");

    Suffer::ref_ptr<Suffer::ResourceManager::Texture> wood_floor_specular_texture;
    wood_floor_specular_texture.alloc();
    wood_floor_specular_texture->SetTextureFilter(Suffer::ResourceManager::Texture::kTextureFilter_Linear, Suffer::ResourceManager::Texture::kTextureFilter_Linear);
    wood_floor_specular_texture->SetTextureWrap(Suffer::ResourceManager::Texture::kTextureWrap_Repeat, Suffer::ResourceManager::Texture::kTextureWrap_Repeat);
    wood_floor_specular_texture->LoadTextureData("../../../resources/images/floor/wood_specular.jpg");

    Suffer::ref_ptr<Suffer::ResourceManager::Texture> wood_floor_normal_map_texture;
    wood_floor_normal_map_texture.alloc();
    wood_floor_normal_map_texture->SetTextureFilter(Suffer::ResourceManager::Texture::kTextureFilter_Linear, Suffer::ResourceManager::Texture::kTextureFilter_Linear);
    wood_floor_normal_map_texture->SetTextureWrap(Suffer::ResourceManager::Texture::kTextureWrap_Repeat, Suffer::ResourceManager::Texture::kTextureWrap_Repeat);
    wood_floor_normal_map_texture->LoadTextureData("../../../resources/images/floor/wood_normal_map_2.jpg");



    // Grass textures
    Suffer::ref_ptr<Suffer::ResourceManager::Texture> grass_texture;
    grass_texture.alloc();
    grass_texture->SetTextureFilter(Suffer::ResourceManager::Texture::kTextureFilter_Linear, Suffer::ResourceManager::Texture::kTextureFilter_Linear);
    grass_texture->SetTextureWrap(Suffer::ResourceManager::Texture::kTextureWrap_Repeat, Suffer::ResourceManager::Texture::kTextureWrap_Repeat);
    grass_texture->LoadTextureData("../../../resources/images/ground_textures/grass_albedo.jpg");

    Suffer::ref_ptr<Suffer::ResourceManager::Texture> grass_specular_texture;
    grass_specular_texture.alloc();
    grass_specular_texture->SetTextureFilter(Suffer::ResourceManager::Texture::kTextureFilter_Linear, Suffer::ResourceManager::Texture::kTextureFilter_Linear);
    grass_specular_texture->SetTextureWrap(Suffer::ResourceManager::Texture::kTextureWrap_Repeat, Suffer::ResourceManager::Texture::kTextureWrap_Repeat);
    grass_specular_texture->LoadTextureData("../../../resources/images/ground_textures/grass_specular.jpg");

    Suffer::ref_ptr<Suffer::ResourceManager::Texture> grass_normal_map_texture;
    grass_normal_map_texture.alloc();
    grass_normal_map_texture->SetTextureFilter(Suffer::ResourceManager::Texture::kTextureFilter_Linear, Suffer::ResourceManager::Texture::kTextureFilter_Linear);
    grass_normal_map_texture->SetTextureWrap(Suffer::ResourceManager::Texture::kTextureWrap_Repeat, Suffer::ResourceManager::Texture::kTextureWrap_Repeat);
    grass_normal_map_texture->LoadTextureData("../../../resources/images/ground_textures/grass_normal_map.jpg");



    // Box textures
    Suffer::ref_ptr<Suffer::ResourceManager::Texture> box_texture;
    box_texture.alloc();
    box_texture->SetTextureFilter(Suffer::ResourceManager::Texture::kTextureFilter_Linear, Suffer::ResourceManager::Texture::kTextureFilter_Linear);
    box_texture->SetTextureWrap(Suffer::ResourceManager::Texture::kTextureWrap_Repeat, Suffer::ResourceManager::Texture::kTextureWrap_Repeat);
    box_texture->LoadTextureData("../../../resources/images/box/box_albedo.png");

    Suffer::ref_ptr<Suffer::ResourceManager::Texture> box_normal_map_texture;
    box_normal_map_texture.alloc();
    box_normal_map_texture->SetTextureFilter(Suffer::ResourceManager::Texture::kTextureFilter_Linear, Suffer::ResourceManager::Texture::kTextureFilter_Linear);
    box_normal_map_texture->SetTextureWrap(Suffer::ResourceManager::Texture::kTextureWrap_Repeat, Suffer::ResourceManager::Texture::kTextureWrap_Repeat);
    box_normal_map_texture->LoadTextureData("../../../resources/images/box/box_normal_map_2.jpg");




    //Skybox textures
    Suffer::ref_ptr<Suffer::ResourceManager::Cubemap> skybox_cubemap;
    skybox_cubemap.alloc();
    skybox_cubemap->LoadCubemapTextureData("../../../resources/images/skybox/sky/miramar_rt.tga",
        "../../../resources/images/skybox/sky/miramar_lf.tga",
        "../../../resources/images/skybox/sky/miramar_up.tga",
        "../../../resources/images/skybox/sky/miramar_dn.tga",
        "../../../resources/images/skybox/sky/miramar_bk.tga",
        "../../../resources/images/skybox/sky/miramar_ft.tga");

    // --------------------------- AUDIO_COMPONENTS ------------------------------- //

    Suffer::ref_ptr<Suffer::Audio3D> audio_3d_;
    audio_3d_.alloc();
    audio_3d_->Load("../../../resources/audio/tavern.ogg");
    audio_3d_->Play3D();
    audio_3d_->SetPaused(true);

    Suffer::ref_ptr<Suffer::Audio3D> audio_3d_jazz;
    audio_3d_jazz.alloc();
    audio_3d_jazz->Load("../../../resources/audio/simple_jazz.ogg");
    audio_3d_jazz->Play3D();
    audio_3d_jazz->SetGain(5.0f);


    // --------------------------- MATERIALS ------------------------------- //

    // Box
    Suffer::ref_ptr<Suffer::MaterialComponent> material_box;
    material_box.alloc();
    Suffer::ref_ptr<Suffer::MaterialComponent::BlinnPhongParams> material_params_box;
    material_params_box.alloc();
    material_params_box->color_ = mathmorra::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
    material_params_box->tiling_ = mathmorra::Vector2(1.0f, 1.0f);
    material_params_box->SetAlbedoTexture(box_texture.get());
    material_params_box->SetNormalMap(box_normal_map_texture.get());
    material_box->AddParams(material_params_box.get());


    // Wood floor
    Suffer::ref_ptr<Suffer::MaterialComponent> material_wood_floor;
    material_wood_floor.alloc();
    Suffer::ref_ptr<Suffer::MaterialComponent::BlinnPhongParams> material_params_wood_floor;
    material_params_wood_floor.alloc();
    material_params_wood_floor->color_ = mathmorra::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
    material_params_wood_floor->tiling_ = mathmorra::Vector2(1.0f, 1.0f);
    material_params_wood_floor->SetAlbedoTexture(wood_floor_texture_.get());
    material_params_wood_floor->SetSpecularTexture(wood_floor_specular_texture.get());
    material_params_wood_floor->SetNormalMap(wood_floor_normal_map_texture.get());
    material_wood_floor->AddParams(material_params_wood_floor.get());


    // Ground material
    Suffer::ref_ptr<Suffer::MaterialComponent> material_ground;
    material_ground.alloc();
    Suffer::ref_ptr<Suffer::MaterialComponent::BlinnPhongParams> material_params_ground;
    material_params_ground.alloc();
    material_params_ground->color_ = mathmorra::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
    material_params_ground->tiling_ = mathmorra::Vector2(3.0f, 3.0f);
    material_params_ground->SetAlbedoTexture(ground_texture.get());
    material_params_ground->SetSpecularTexture(ground_specular_texture.get());
    material_params_ground->SetNormalMap(ground_normal_map_texture.get());
    material_ground->AddParams(material_params_ground.get());


    // Grass material
    Suffer::ref_ptr<Suffer::MaterialComponent> material_grass;
    material_grass.alloc();
    Suffer::ref_ptr<Suffer::MaterialComponent::BlinnPhongParams> material_params_grass;
    material_params_grass.alloc();
    material_params_grass->color_ = mathmorra::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
    material_params_grass->tiling_ = mathmorra::Vector2(30.0f, 30.0f);
    material_params_grass->SetAlbedoTexture(grass_texture.get());
    material_params_grass->SetSpecularTexture(grass_specular_texture.get());
    //material_params_grass->SetNormalMap(grass_normal_map_texture.get());
    material_grass->AddParams(material_params_grass.get());

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

    // Sphere - LINES (For audio)
    Suffer::ref_ptr<Suffer::GeometryComponent> sphere_lines_geometry_;
    sphere_lines_geometry_.alloc();
    sphere_lines_geometry_->SetDrawMode(Suffer::GeometryComponent::kDrawMode_Lines);
    sphere_lines_geometry_->CreateGeometryWithShape(Suffer::GeometryComponent::kBasicShapes_Sphere);

    // Terrain
    Suffer::ref_ptr<Suffer::GeometryComponent> geometry_component_terrain;
    geometry_component_terrain.alloc();
    geometry_component_terrain->SetDrawMode(Suffer::GeometryComponent::kDrawMode_Triangles);
    geometry_component_terrain->CreateTerrainGeometry(0.096f, 21.0f, 64.0f, 100, 100);

    // Mario OBJ and MTL
    Suffer::ref_ptr<Suffer::MaterialComponent> material_mario;
    material_mario.alloc();
    Suffer::ref_ptr<Suffer::GeometryComponent> geometry_component_mario;
    geometry_component_mario.alloc();
    geometry_component_mario->SetDrawMode(Suffer::GeometryComponent::kDrawMode_Triangles);
    geometry_component_mario->CreateGeometryWithOBJAndMTL("../../../resources/models/SuperMairo64.obj",
        *material_mario.get(), "../../../resources/materials/", "../../../resources/images/Mario64/");

    // Rock OBJ And MTL
    Suffer::ref_ptr<Suffer::MaterialComponent> material_rock;
    material_rock.alloc();
    Suffer::ref_ptr<Suffer::GeometryComponent> geometry_component_rock;
    geometry_component_rock.alloc();
    geometry_component_rock->SetDrawMode(Suffer::GeometryComponent::kDrawMode_Triangles);
    geometry_component_rock->CreateGeometryWithOBJAndMTL("../../../resources/models/rock_03.obj",
        *material_rock.get(), "../../../resources/materials/", "../../../resources/images/");

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

    // Point_Walls
    Suffer::ref_ptr<Suffer::LightComponent> point_light_walls_component;
    point_light_walls_component.alloc();
    point_light_walls_component->Init(Suffer::LightComponent::kLightKind_Point);
    point_light_walls_component->SetDirection(mathmorra::Vector3(0.0f, 0.0f, 1.0f));
    point_light_walls_component->SetIntensity(8.0f);
    point_light_walls_component->SetPosition(-150.0f, 0.0f, -100.0f);
    point_light_walls_component->SetAmbient(0.5f, 0.5f, 0.5f);
    point_light_walls_component->SetDiffuse(1.0f, 1.0f, 1.0f);
    point_light_walls_component->SetSpecular(1.0f, 1.0f, 1.0f);
    point_light_walls_component->SetActive(true);

    // Spot
    Suffer::ref_ptr<Suffer::LightComponent> spot_light_component;
    spot_light_component.alloc();
    spot_light_component->Init(Suffer::LightComponent::kLightKind_Spot);
    spot_light_component->SetDirection(mathmorra::Vector3(0.0f, -0.3f, -1.0f));
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

    // Simple_Box
    Suffer::ref_ptr<Suffer::GameObject> box_cube_;
    box_cube_.alloc();
    box_cube_->SetName("Simple box");
    box_cube_->SetArchetype(Suffer::GameObject::kArchetype_Drawable);
    box_cube_->RemoveComponent(Suffer::Component::kComponentKind_Material);
    box_cube_->AddComponent(material_box.get());

    Suffer::Transform* box_transform_component = static_cast<Suffer::Transform*>(box_cube_->GetComponent(Suffer::Component::kComponentKind_Transform));
    box_transform_component->Translate(mathmorra::Vector3(-200.0f, -25.0f, -150.0f));
    box_transform_component->Rotate(mathmorra::Vector3(0.0f, ThiefUtils::Math::Radians(-180.0f), 0.0f));
    box_transform_component->Scale(mathmorra::Vector3(2.0f, 2.0f, 2.0f));


    // Mutiple_Boxes
    Suffer::ref_ptr<Suffer::GameObject> multiple_boxes_;
    multiple_boxes_.alloc();
    multiple_boxes_->SetName("Simple boxes");
    multiple_boxes_->SetArchetype(Suffer::GameObject::kArchetype_Drawable);
    multiple_boxes_->RemoveComponent(Suffer::Component::kComponentKind_Material);
    multiple_boxes_->AddComponent(material_box.get());

    Suffer::Transform* boxes_transform_component = static_cast<Suffer::Transform*>(multiple_boxes_->GetComponent(Suffer::Component::kComponentKind_Transform));
    boxes_transform_component->Translate(mathmorra::Vector3(-180.0f, -45.0f, -180.0f));
    boxes_transform_component->Rotate(mathmorra::Vector3(0.0f, ThiefUtils::Math::Radians(-180.0f), 0.0f));
    boxes_transform_component->Scale(mathmorra::Vector3(5.0f, 5.0f, 5.0f));

    Suffer::MaterialComponent* boxes_material_component = static_cast<Suffer::MaterialComponent*>(multiple_boxes_->GetComponent(Suffer::Component::kComponentKind_Material));
    Suffer::MaterialComponent::BlinnPhongParams* blinn_ = reinterpret_cast<Suffer::MaterialComponent::BlinnPhongParams*>(boxes_material_component->CurrentParams());
    blinn_->tiling_ = 2;



    // Sphere for PoingLightWalls
    Suffer::ref_ptr<Suffer::GameObject> sphere_point_light_;
    sphere_point_light_.alloc();
    sphere_point_light_->SetName("Point_Light_Walls");
    sphere_point_light_->SetArchetype(Suffer::GameObject::kArchetype_Drawable);
    sphere_point_light_->AddComponent(point_light_walls_component.get());

    Suffer::ref_ptr<Suffer::ScriptComponent> rotate_light;
    rotate_light.alloc();
    sphere_point_light_->AddComponent(rotate_light.get());
    rotate_light->AttachScript("../../../src/lua/lua_rotator_2.lua");

    Suffer::Transform* light_transform_component = static_cast<Suffer::Transform*>(sphere_point_light_->GetComponent(Suffer::Component::kComponentKind_Transform));
    light_transform_component->Translate(mathmorra::Vector3(-200.0f, 0.0f, -150.0f));
    light_transform_component->Rotate(mathmorra::Vector3(0.0f, ThiefUtils::Math::Radians(-180.0f), 0.0f));
    light_transform_component->Scale(mathmorra::Vector3(2.0f, 2.0f, 2.0f));

    Suffer::GeometryComponent* light_geometry_component = static_cast<Suffer::GeometryComponent*>(sphere_point_light_->GetComponent(Suffer::Component::kComponentKind_Geometry));
    light_geometry_component->CreateGeometryWithShape(Suffer::GeometryComponent::kBasicShapes_Sphere);



    // Floor_1
    Suffer::ref_ptr<Suffer::GameObject> floor_1;
    floor_1.alloc();
    floor_1->SetName("Floor_1");
    floor_1->SetArchetype(Suffer::GameObject::kArchetype_Drawable);
    floor_1->RemoveComponent(Suffer::Component::ComponentKind::kComponentKind_Geometry);
    floor_1->RemoveComponent(Suffer::Component::ComponentKind::kComponentKind_Material);
    floor_1->AddComponent(geometry_component_quad.get());
    floor_1->AddComponent(material_wood_floor.get());

    Suffer::Transform* transform_floor_1_nm_ = static_cast<Suffer::Transform*>(floor_1->GetComponent(Suffer::Component::kComponentKind_Transform));
    transform_floor_1_nm_->Translate(mathmorra::Vector3(-200.0f, -50.0f, -150));
    transform_floor_1_nm_->Rotate(mathmorra::Vector3(ThiefUtils::Math::Radians(-90.0f), 0.0f, 0.0f));
    transform_floor_1_nm_->Scale(mathmorra::Vector3(50.0f, 50.0f, 30.0f));


    // -- Quad1 --
    Suffer::ref_ptr<Suffer::GameObject> quad_1_nm;
    quad_1_nm.alloc();
    quad_1_nm->SetName("Wall_1");
    quad_1_nm->SetArchetype(Suffer::GameObject::kArchetype_Drawable);
    quad_1_nm->RemoveComponent(Suffer::Component::ComponentKind::kComponentKind_Geometry);
    quad_1_nm->RemoveComponent(Suffer::Component::ComponentKind::kComponentKind_Material);
    quad_1_nm->AddComponent(geometry_component_quad.get());
    quad_1_nm->AddComponent(material_ground.get());

    Suffer::Transform* transform_quad_1_nm_ = static_cast<Suffer::Transform*>(quad_1_nm->GetComponent(Suffer::Component::kComponentKind_Transform));
    transform_quad_1_nm_->Translate(mathmorra::Vector3(-200.0f, 0.0f, -200.0f));
    transform_quad_1_nm_->Rotate(mathmorra::Vector3(0.0f, ThiefUtils::Math::Radians(180), 0.0f));
    transform_quad_1_nm_->Scale(mathmorra::Vector3(50.0f, 50.0f, 30.0f));


    // -- Quad2 --
    Suffer::ref_ptr<Suffer::GameObject> quad_2_nm;
    quad_2_nm.alloc();
    quad_2_nm->SetName("Wall_2");
    quad_2_nm->SetArchetype(Suffer::GameObject::kArchetype_Drawable);
    quad_2_nm->RemoveComponent(Suffer::Component::ComponentKind::kComponentKind_Geometry);
    quad_2_nm->RemoveComponent(Suffer::Component::ComponentKind::kComponentKind_Material);
    quad_2_nm->AddComponent(geometry_component_quad.get());
    quad_2_nm->AddComponent(material_ground.get());

    Suffer::Transform* transform_quad_2_nm_ = static_cast<Suffer::Transform*>(quad_2_nm->GetComponent(Suffer::Component::kComponentKind_Transform));
    transform_quad_2_nm_->Translate(mathmorra::Vector3(-150.0f, 0.0f, -150.0f));
    transform_quad_2_nm_->Rotate(mathmorra::Vector3(0.0f, ThiefUtils::Math::Radians(-90.0f), 0.0f));
    transform_quad_2_nm_->Scale(mathmorra::Vector3(-50.0f, -50.0f, 30.0f));



    // -- Quad3 --
    Suffer::ref_ptr<Suffer::GameObject> quad_nm;
    quad_nm.alloc();
    quad_nm->SetName("Wall_3");
    quad_nm->SetArchetype(Suffer::GameObject::kArchetype_Drawable);
    quad_nm->RemoveComponent(Suffer::Component::ComponentKind::kComponentKind_Geometry);
    quad_nm->RemoveComponent(Suffer::Component::ComponentKind::kComponentKind_Material);
    quad_nm->AddComponent(geometry_component_quad.get());
    quad_nm->AddComponent(material_ground.get());

    Suffer::Transform* transform_quad_nm_ = static_cast<Suffer::Transform*>(quad_nm->GetComponent(Suffer::Component::kComponentKind_Transform));
    transform_quad_nm_->Translate(mathmorra::Vector3(-250.0f, 0.0f, -150.0f));
    transform_quad_nm_->Rotate(mathmorra::Vector3(0.0f, ThiefUtils::Math::Radians(90.0f), 0.0f));
    transform_quad_nm_->Scale(mathmorra::Vector3(-50.0f, -50.0f, 30.0f));


    // -- AudioSphere --
    Suffer::ref_ptr<Suffer::GameObject> audio_sphere_;
    audio_sphere_.alloc();
    audio_sphere_->SetName("Audio_Sphere");
    audio_sphere_->SetArchetype(Suffer::GameObject::kArchetype_Drawable);
    audio_sphere_->RemoveComponent(Suffer::Component::ComponentKind::kComponentKind_Geometry);
    audio_sphere_->AddComponent(sphere_lines_geometry_.get());
    audio_sphere_->AddComponent(audio_3d_.get());

    Suffer::Transform* transform_audio_sphere_ = static_cast<Suffer::Transform*>(audio_sphere_->GetComponent(Suffer::Component::kComponentKind_Transform));
    transform_audio_sphere_->Translate(mathmorra::Vector3(0.0f, 0.0f, 0.0f));
    transform_audio_sphere_->Scale(mathmorra::Vector3(100.0f, 100.0f, 100.0f));

    Suffer::MaterialComponent* material_audio_sphere_ = static_cast<Suffer::MaterialComponent*>(audio_sphere_->GetComponent(Suffer::Component::kComponentKind_Material));
    material_audio_sphere_->CurrentParams()->color_ = mathmorra::Vector4(1.0f, 1.0f, 1.0f, 1.0f);



    // -- AudioSphere_2 --
    Suffer::ref_ptr<Suffer::GameObject> audio_sphere_2;
    audio_sphere_2.alloc();
    audio_sphere_2->SetName("Jazz_Music_Sphere");
    audio_sphere_2->SetArchetype(Suffer::GameObject::kArchetype_Drawable);
    audio_sphere_2->RemoveComponent(Suffer::Component::ComponentKind::kComponentKind_Geometry);
    audio_sphere_2->AddComponent(sphere_lines_geometry_.get());
    audio_sphere_2->AddComponent(audio_3d_jazz.get());

    Suffer::Transform* transform_audio_sphere_2 = static_cast<Suffer::Transform*>(audio_sphere_2->GetComponent(Suffer::Component::kComponentKind_Transform));
    transform_audio_sphere_2->Translate(mathmorra::Vector3(-200.0f, 0.0f, -150.0f));
    transform_audio_sphere_2->Scale(mathmorra::Vector3(110.0f, 110.0, 110.0f));

    Suffer::MaterialComponent* material_audio_sphere_2 = static_cast<Suffer::MaterialComponent*>(audio_sphere_2->GetComponent(Suffer::Component::kComponentKind_Material));
    material_audio_sphere_2->CurrentParams()->color_ = mathmorra::Vector4(1.0f, 1.0f, 1.0f, 1.0f);



    // -- Terrain --
    Suffer::ref_ptr<Suffer::GameObject> go_terrain;
    go_terrain.alloc();
    go_terrain->SetName("Terrain");

    Suffer::ref_ptr<Suffer::Transform> transform_component_terrain;
    transform_component_terrain.alloc();
    transform_component_terrain->Translate(-50.0f, 0.0f, -50.0f);


    go_terrain->AddComponent(transform_component_terrain.get());
    go_terrain->AddComponent(geometry_component_terrain.get());
    go_terrain->AddComponent(material_grass.get());


    // -- Point Light --
    Suffer::ref_ptr<Suffer::GameObject> go_point_light;
    go_point_light.alloc();
    go_point_light->SetName("PointLight");

    Suffer::ref_ptr<Suffer::Transform> transform_component_point_light;
    transform_component_point_light.alloc();
    transform_component_point_light->Scale(mathmorra::Vector3(1.0f, 1.0f, 1.0f));
    transform_component_point_light->Translate(mathmorra::Vector3(5.0f, 5.0f, 5.0f));
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
    transform->Translate(mathmorra::Vector3(-10.0f, 5.0f, -5.0f));

    go_directional_light->AddComponent(directional_light_component.get());
    go_directional_light->RemoveComponent(Suffer::Component::kComponentKind_Material);

    // -- Spot light --
    Suffer::ref_ptr<Suffer::GameObject> go_spot_light;
    go_spot_light.alloc();
    go_spot_light->SetName("SpotLight");
    go_spot_light->SetArchetype(Suffer::GameObject::kArchetype_Drawable);

    Suffer::GeometryComponent* geo_comp_spot = static_cast<Suffer::GeometryComponent*>(go_spot_light->GetComponent(Suffer::Component::kComponentKind_Geometry));
    geo_comp_spot->CreateGeometryWithShape(Suffer::GeometryComponent::kBasicShapes_Sphere);

    Suffer::Transform* transform_spot = static_cast<Suffer::Transform*>(go_spot_light->GetComponent(Suffer::Component::kComponentKind_Transform));
    transform_spot->Translate(mathmorra::Vector3(-200.0f, 0.0f, -100.0f));

    go_spot_light->AddComponent(spot_light_component.get());


    // -- Mario --
    Suffer::ref_ptr<Suffer::GameObject> go_mario;
    go_mario.alloc();
    go_mario->SetName("Mario");

    Suffer::ref_ptr<Suffer::Transform> transform_component_mario;
    transform_component_mario.alloc();
    transform_component_mario->Translate(mathmorra::Vector3(0.0f, -2.0f, 2.0f));
    transform_component_mario->Rotate(mathmorra::Vector3(0.0f, ThiefUtils::Math::Radians(180.0f), 0.0f));
    transform_component_mario->Scale(mathmorra::Vector3(0.3f, 0.3f, 0.3f));

    Suffer::ref_ptr<Suffer::ScriptComponent> script;
    script.alloc();

    go_mario->AddComponent(transform_component_mario.get());
    go_mario->AddComponent(geometry_component_mario.get());
    go_mario->AddComponent(material_mario.get());

    Suffer::ref_ptr<Suffer::ScriptComponent> script_rotator;
    script_rotator.alloc();
    go_point_light->AddComponent(script_rotator.get());
    script_rotator->AttachScript("../../../src/lua/lua_rotator.lua");


    // -------------------------------------------------------------------------------------//


    // Create skybox
    Suffer::ref_ptr<Suffer::Skybox> skybox;
    skybox.alloc();
    skybox->SetCubemap(skybox_cubemap);


    // Set gameobjects and scene things
    scene->AddGameObject(box_cube_);
    scene->AddGameObject(multiple_boxes_);
    scene->AddGameObject(sphere_point_light_);
    scene->AddGameObject(floor_1);
    scene->AddGameObject(quad_1_nm);
    scene->AddGameObject(quad_2_nm);
    scene->AddGameObject(quad_nm);
    scene->AddGameObject(audio_sphere_);
    scene->AddGameObject(audio_sphere_2);
    scene->AddGameObject(go_terrain);
    scene->AddGameObject(go_point_light);
    scene->AddGameObject(go_directional_light);
    scene->AddGameObject(go_spot_light);
    scene->AddGameObject(go_mario);
    scene->SetSkybox(skybox);


    // Execute engine
    suffer.SetScene(scene);
    suffer.Run();

    suffer.Finish();

    return 0;

}

// --------------------------------------------------------------//

#endif