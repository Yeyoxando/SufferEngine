
#include <common_definitions.h>
#if defined _MAIN_PABLO_ && !defined _MAIN_DIEGO_


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
#include <time.h>
#include "component_light.h"

// --------------------------------------------------------------//

int main(int argc, char* argv[]) {

    suffer.Init();

    Suffer::ref_ptr<Suffer::SystemAudio> audio_system_;
    audio_system_.alloc();
    suffer.AddSystem(audio_system_.get());

    Suffer::ref_ptr<Suffer::Scene> scene;
    scene.alloc();

    //Suffer::ref_ptr<Suffer::LightManager::PointLight> point_light;
    //point_light.alloc();
    //point_light->SetIntensity(20.0f);
    //point_light->SetAmbient(0.0f, 0.0f, 1.0f);
    //point_light->SetDiffuse(0.0f, 0.0f, 1.0f);
    //point_light->SetSpecular(0.0f, 0.0f, 1.0f);
    //point_light->SetColor(0.0f, 0.0f, 1.0f);
    //point_light->SetLinear(1.0f);
    //point_light->SetConstant(1.0f);
    //point_light->SetQuadratic(1.0f);

    //Suffer::ref_ptr<Suffer::LightManager::DirectionalLight> directional_light_;
    //directional_light_.alloc();
    //directional_light_->SetIntensity(1.0f);
    //directional_light_->SetAmbient(0.5f, 0.5f, 0.5f);
    //directional_light_->SetDiffuse(0.5f, 0.5f, 0.5f);
    //directional_light_->SetSpecular(0.5f, 0.5f, 0.5f);
    //directional_light_->SetDirection(mathmorra::Vector3(0.0f, 0.0f, 1.0f));
    //
    //Suffer::ref_ptr<Suffer::LightManager::SpotLight> spot_light_;
    //spot_light_.alloc();
    //spot_light_->SetPosition(mathmorra::Vector3(0.0f, 0.0f, -5.0f));
    //spot_light_->SetDirection(mathmorra::Vector3(0.0f, 0.0f, 1.0f));
    //spot_light_->SetIntensity(1.0f);
    //spot_light_->SetAmbient(0.5f, 0.5f, 0.5f);
    //spot_light_->SetDiffuse(1.0f, 1.0f, 1.0f);
    //spot_light_->SetSpecular(1.0f, 1.0f, 1.0f);
    //spot_light_->SetColor(0.0f, 0.0f, 1.0f);
    //spot_light_->SetLinear(1.0f);
    //spot_light_->SetConstant(0.09f);
    //spot_light_->SetQuadratic(0.032f);
    //spot_light_->SetCutOff(0.9978f);
    //spot_light_->SetOuterCutOff(0.99f);
    //
    //Suffer::ref_ptr<Suffer::LightManager::PointLight> point;
    //point.alloc();
    //point->SetDirection(mathmorra::Vector3(0.0f, 0.0f, 1.0f));
    //point->SetIntensity(20.0f);
    //point->SetAmbient(0.0f, 1.0f, 1.0f);
    //point->SetDiffuse(0.0f, 1.0f, 1.0f);
    //point->SetSpecular(0.0f, 1.0f, 1.0f);
    //point->SetPosition(mathmorra::Vector3(rand() % 20, rand() % 20, rand() % 20));
    //point->SetLinear(1.0f);
    //point->SetConstant(0.09f);
    //point->SetQuadratic(0.032f);

    //Suffer::ref_ptr<Suffer::LightManager::PointLight> point2;
    //point2.alloc();
    //point2->SetDirection(mathmorra::Vector3(0.0f, 0.0f, 1.0f));
    //point2->SetIntensity(30.0f);
    //point2->SetAmbient(0.0f, 0.0f, 1.0f);
    //point2->SetDiffuse(0.0f, 0.0f, 1.0f);
    //point2->SetSpecular(0.0f, 0.0f, 1.0f);
    //point2->SetPosition(mathmorra::Vector3(rand() % 50, rand() % 50, rand() % 50));
    //point2->SetLinear(1.0f);
    //point2->SetConstant(0.09f);
    //point2->SetQuadratic(0.032f);


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
    albedo_texture2->LoadTextureData("../../../resources/images/box_2.png");

    Suffer::ref_ptr<Suffer::ResourceManager::Texture> specular_texture;
    specular_texture.alloc();
    specular_texture->SetTextureFilter(Suffer::ResourceManager::Texture::kTextureFilter_Linear, Suffer::ResourceManager::Texture::kTextureFilter_Linear);
    specular_texture->SetTextureWrap(Suffer::ResourceManager::Texture::kTextureWrap_ClampToEdge, Suffer::ResourceManager::Texture::kTextureWrap_ClampToEdge);
    specular_texture->LoadTextureData("../../../resources/images/box_2_spec.png");



    // -------------------------------- COMPONENTS STUFF TESTS ------------------------------//

    Suffer::ref_ptr<Suffer::GameObject> go_cube[20];
    Suffer::ref_ptr<Suffer::ScriptComponent> script_component_[20];
    Suffer::ref_ptr<Suffer::Transform> transform_component_[20];
    Suffer::ref_ptr<Suffer::GeometryComponent> geometry_component;
    geometry_component.alloc();
    geometry_component->SetDrawMode(Suffer::GeometryComponent::kDrawMode_Triangles);
    geometry_component->CreateGeometryWithShape(Suffer::GeometryComponent::kBasicShapes_Cube);
    Suffer::ref_ptr<Suffer::MaterialComponent> material_component;
    material_component.alloc();
    Suffer::ref_ptr<Suffer::MaterialComponent::PhongParams> material_params;
    material_params.alloc();
    material_params->color_ = mathmorra::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
    material_component->SetParams(material_params.get());

    Suffer::ref_ptr<Suffer::MaterialComponent> material_component_sphere;
    material_component_sphere.alloc();

    Suffer::ref_ptr<Suffer::MaterialComponent::DefaultParams> material_params_sphere;
    material_params_sphere.alloc();
    material_params_sphere->color_ = mathmorra::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
    material_params_sphere->albedo_texture_id_ = albedo_texture2->id_;
    material_params_sphere->specular_texture_id_ = specular_texture->id_;
    material_component_sphere->SetParams(material_params_sphere.get());

    Suffer::ref_ptr<Suffer::MaterialComponent> material_component2;
    material_component2.alloc();
    Suffer::ref_ptr<Suffer::MaterialComponent::PhongParams> material_params2;
    material_params2.alloc();
    material_params2->color_ = mathmorra::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
    material_component2->SetParams(material_params_sphere.get());

    Suffer::ref_ptr<Suffer::LightComponent> light_component;
    Suffer::ref_ptr<Suffer::LightComponent> light_component2;
    light_component.alloc();
    light_component2.alloc();


    for (int i = 0; i < 20; ++i) {
        go_cube[i].alloc();
        script_component_[i].alloc();
        transform_component_[i].alloc();
        transform_component_[i].get()->Translate(mathmorra::Vector3(rand() % 50, rand() % 50, rand() % 50));
        transform_component_[i].get()->Scale(mathmorra::Vector3(5.0f, 5.0f, 5.0f));
        go_cube[i]->AddComponent(geometry_component.get());
        go_cube[i]->AddComponent(material_component2.get());
        go_cube[i]->AddComponent(transform_component_[i].get());
        go_cube[i]->AddComponent(script_component_[i].get());
        script_component_[i]->AttachScript("../../../src/lua/lua_test_update.txt");
        scene->AddGameObject(go_cube[i]);
        go_cube[i]->SetName("Cube");

    }

    light_component2->Init(Suffer::LightComponent::kLightKind_Point);
    light_component2->SetDirection(mathmorra::Vector3(0.0f, 0.0f, 1.0f));
    light_component2->SetIntensity(20.0f);
    light_component2->SetAmbient(0.0f, 1.0f, 1.0f);
    light_component2->SetDiffuse(0.0f, 1.0f, 1.0f);
    light_component2->SetSpecular(0.0f, 1.0f, 1.0f);
    go_cube[5]->AddComponent(light_component2.get());

    // -------------------------------- COMPONENTS STUFF TESTS ------------------------------//

    Suffer::ref_ptr<Suffer::GameObject> go_sphere;
    go_sphere.alloc();

    Suffer::ref_ptr<Suffer::GeometryComponent> geometry_component_sphere;
    geometry_component_sphere.alloc();
    geometry_component_sphere->SetDrawMode(Suffer::GeometryComponent::kDrawMode_Triangles);
    geometry_component_sphere->CreateGeometryWithShape(Suffer::GeometryComponent::kBasicShapes_Sphere);
    go_sphere->AddComponent(geometry_component_sphere.get());
    light_component->Init(Suffer::LightComponent::kLightKind_Point);


    go_sphere->AddComponent(light_component.get());

    light_component->SetDirection(mathmorra::Vector3(0.0f, 0.0f, 1.0f));
    light_component->SetIntensity(20.0f);
    light_component->SetAmbient(0.0f, 1.0f, 1.0f);
    light_component->SetDiffuse(0.0f, 1.0f, 1.0f);
    light_component->SetSpecular(0.0f, 1.0f, 1.0f);
    light_component->SetPosition(mathmorra::Vector3(rand() % 20, rand() % 20, rand() % 20));

    Suffer::ref_ptr<Suffer::ScriptComponent> script_component_2;
    script_component_2.alloc();
    go_sphere->AddComponent(script_component_2.get());
    script_component_2->AttachScript("../../../src/lua/lua_test_update_cube.lua");

    go_sphere->AddComponent(material_component.get());

    Suffer::ref_ptr<Suffer::Transform> transform_component_sphere_;
    transform_component_sphere_.alloc();
    //transform_component_sphere_->Translate(point->Position());
    transform_component_sphere_->Rotate(mathmorra::Vector3(90.0f, 0.0f, 0.0f));
    transform_component_sphere_->Translate(mathmorra::Vector3(10.0f, 10.0f, 10.0f));
    go_sphere->AddComponent(transform_component_sphere_.get());


    // -------------------------------------------------------------------------------------//

    Suffer::ref_ptr<Suffer::GameObject> go_quad;
    go_quad.alloc();

    Suffer::ref_ptr<Suffer::GeometryComponent> geometry_component2;
    geometry_component2.alloc();
    geometry_component2->SetDrawMode(Suffer::GeometryComponent::kDrawMode_Triangles);
    geometry_component2->CreateGeometryWithShape(Suffer::GeometryComponent::kBasicShapes_Quad);
    go_quad->AddComponent(geometry_component2.get());




    go_quad->AddComponent(material_component2.get());

    Suffer::ref_ptr<Suffer::Transform> transform_component_2;
    transform_component_2.alloc();
    transform_component_2->Scale(mathmorra::Vector3(5.0f, 5.0f, 5.0f));
    transform_component_2->Translate(mathmorra::Vector3(0.0f, 0.0f, 10.0f));
    transform_component_2->Rotate(mathmorra::Vector3(0.0f, 0.0f, 0.0f));
    go_quad->AddComponent(transform_component_2.get());

    go_quad->SetName("Quad");




    // SCRIPTING TESTS

    //Suffer::ref_ptr<Suffer::ScriptComponent> script_component_;
    //script_component_.alloc();
    //go_sphere->AddComponent(script_component_.get());
    //go_quad->AddComponent(script_component_.get());
    //script_component_->AttachScript("../../../src/lua/lua_test_update.txt");

    Suffer::ref_ptr<Suffer::ScriptComponent> script_component_cube;
    script_component_cube.alloc();
    //go_cube->AddComponent(script_component_cube.get());
    script_component_cube->AttachScript("../../../src/lua/lua_test_update_cube.lua");

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


    suffer.SetScene(scene);


    suffer.Run();

    suffer.Finish();

    return 0;

}

// --------------------------------------------------------------//

#endif