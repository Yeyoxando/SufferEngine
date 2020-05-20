
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
    ground_texture->LoadTextureData("../../../resources/images/texture_01.png");

    Suffer::ref_ptr<Suffer::ResourceManager::Texture> ground_specular_texture;
    ground_specular_texture.alloc();
    ground_specular_texture->SetTextureFilter(Suffer::ResourceManager::Texture::kTextureFilter_Linear, Suffer::ResourceManager::Texture::kTextureFilter_Linear);
    ground_specular_texture->SetTextureWrap(Suffer::ResourceManager::Texture::kTextureWrap_Repeat, Suffer::ResourceManager::Texture::kTextureWrap_Repeat);
    ground_specular_texture->LoadTextureData("../../../resources/images/texture_01_spec.png");

    Suffer::ref_ptr<Suffer::ResourceManager::Texture> ground_normal_map_texture;
    ground_normal_map_texture.alloc();
    ground_normal_map_texture->SetTextureFilter(Suffer::ResourceManager::Texture::kTextureFilter_Linear, Suffer::ResourceManager::Texture::kTextureFilter_Linear);
    ground_normal_map_texture->SetTextureWrap(Suffer::ResourceManager::Texture::kTextureWrap_Repeat, Suffer::ResourceManager::Texture::kTextureWrap_Repeat);
    ground_normal_map_texture->LoadTextureData("../../../resources/images/brick_normal_map.png");




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


    // --------------------------- MATERIALS ------------------------------- //


    // Ground material
    Suffer::ref_ptr<Suffer::MaterialComponent> material_ground;
    material_ground.alloc();
    Suffer::ref_ptr<Suffer::MaterialComponent::BlinnPhongParams> material_params_ground;
    material_params_ground.alloc();
    material_params_ground->color_ = mathmorra::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
    material_params_ground->tiling_ = mathmorra::Vector2(1.0f, 1.0f);
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
    material_params_grass->SetNormalMap(grass_normal_map_texture.get());
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

    // -- Rock --
    Suffer::ref_ptr<Suffer::GameObject> go_rock;
    go_rock.alloc();
    go_rock->SetName("Rock");

    Suffer::ref_ptr<Suffer::Transform> transform_component_rock;
    transform_component_rock.alloc();
    transform_component_rock->Translate(mathmorra::Vector3(5.0f, 2.0f, -2.0f));
    transform_component_rock->Rotate(mathmorra::Vector3(0.0f, ThiefUtils::Math::Radians(-125.0f), 0.0f));
    transform_component_rock->Scale(mathmorra::Vector3(1.0f, 1.0f, 1.0f));

    go_rock->AddComponent(transform_component_rock.get());
    go_rock->AddComponent(geometry_component_rock.get());
    go_rock->AddComponent(material_rock.get());


    // -- Mario --
    Suffer::ref_ptr<Suffer::GameObject> go_mario;
    go_mario.alloc();
    go_mario->SetName("Mario");

    Suffer::ref_ptr<Suffer::Transform> transform_component_mario;
    transform_component_mario.alloc();
    transform_component_mario->Translate(mathmorra::Vector3(0.0f, 0.0f, 2.0f));
    transform_component_mario->Rotate(mathmorra::Vector3(0.0f, 0.0f, 0.0f));
    transform_component_mario->Scale(mathmorra::Vector3(0.3f, 0.3f, 0.3f));

    Suffer::ref_ptr<Suffer::ScriptComponent> script;
    script.alloc();

    go_mario->AddComponent(transform_component_mario.get());
    go_mario->AddComponent(geometry_component_mario.get());
    go_mario->AddComponent(material_mario.get());
    go_mario->AddComponent(script.get());

    script->AttachScript("../../../src/lua/lua_test_update.lua");


    Suffer::ref_ptr<Suffer::GameObject> empty_sphere_;
    empty_sphere_.alloc();
    empty_sphere_->SetName("Empty sphere");

    Suffer::ref_ptr<Suffer::Transform> transform_empty_sphere_;
    transform_empty_sphere_.alloc();

    Suffer::ref_ptr<Suffer::GeometryComponent> empty_sphere_geometry_;
    empty_sphere_geometry_.alloc();
    empty_sphere_geometry_->CreateGeometryWithShape(Suffer::GeometryComponent::kBasicShapes_Sphere);

    empty_sphere_->AddComponent(material_ground.get());
    empty_sphere_->AddComponent(empty_sphere_geometry_.get());
    empty_sphere_->AddComponent(transform_empty_sphere_.get());

    Suffer::Transform* transform_empty_sphere_comp = static_cast<Suffer::Transform*>(empty_sphere_->GetComponent(Suffer::Component::kComponentKind_Transform));
    transform_empty_sphere_comp->Translate(mathmorra::Vector3(0.0f, 20.0f, 0.0f));







    Suffer::ref_ptr<Suffer::GameObject> empty_cube_;
    empty_cube_.alloc();
    empty_cube_->SetName("Empty sphere");

    Suffer::ref_ptr<Suffer::Transform> transform_empty_cube_;
    transform_empty_cube_.alloc();

    Suffer::ref_ptr<Suffer::GeometryComponent> empty_cube_geometry_;
    empty_cube_geometry_.alloc();
    empty_cube_geometry_->CreateGeometryWithShape(Suffer::GeometryComponent::kBasicShapes_Cube);

    empty_cube_->AddComponent(material_ground.get());
    empty_cube_->AddComponent(empty_cube_geometry_.get());
    empty_cube_->AddComponent(transform_empty_cube_.get());

    Suffer::Transform* transform_empty_cube_comp = static_cast<Suffer::Transform*>(empty_cube_->GetComponent(Suffer::Component::kComponentKind_Transform));
    transform_empty_cube_comp->Translate(mathmorra::Vector3(50.0f, 20.0f, 0.0f));

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
    scene->AddGameObject(audio_sphere_);
    scene->AddGameObject(go_terrain);
    scene->AddGameObject(go_point_light);
    scene->AddGameObject(go_directional_light);
    scene->AddGameObject(go_spot_light);
    scene->AddGameObject(go_rock);
    scene->AddGameObject(go_mario);
    scene->AddGameObject(empty_sphere_);
    scene->AddGameObject(empty_cube_);
    scene->SetSkybox(skybox);


    // Execute engine
    suffer.SetScene(scene);
    suffer.Run();

    suffer.Finish();

    return 0;

}

// --------------------------------------------------------------//

#endif