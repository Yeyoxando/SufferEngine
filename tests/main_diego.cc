
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
    Suffer::ref_ptr<Suffer::ResourceManager::Texture> wall_texture;
    wall_texture.alloc();
    wall_texture->SetTextureFilter(Suffer::ResourceManager::Texture::kTextureFilter_Nearest, Suffer::ResourceManager::Texture::kTextureFilter_Nearest);
    wall_texture->SetTextureWrap(Suffer::ResourceManager::Texture::kTextureWrap_ClampToEdge, Suffer::ResourceManager::Texture::kTextureWrap_ClampToEdge);
    wall_texture->LoadTextureData("../../../resources/images/wall.jpg");

    Suffer::ref_ptr<Suffer::ResourceManager::Texture> wall_specular_texture;
    wall_specular_texture.alloc();
    wall_specular_texture->SetTextureFilter(Suffer::ResourceManager::Texture::kTextureFilter_Linear, Suffer::ResourceManager::Texture::kTextureFilter_Linear);
    wall_specular_texture->SetTextureWrap(Suffer::ResourceManager::Texture::kTextureWrap_ClampToEdge, Suffer::ResourceManager::Texture::kTextureWrap_ClampToEdge);
    wall_specular_texture->LoadTextureData("../../../resources/images/wall_spec.jpg");



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




    Suffer::ref_ptr<Suffer::ResourceManager::Texture> ground_texture;
    ground_texture.alloc();
    ground_texture->SetTextureFilter(Suffer::ResourceManager::Texture::kTextureFilter_Nearest, Suffer::ResourceManager::Texture::kTextureFilter_Nearest);
    ground_texture->SetTextureWrap(Suffer::ResourceManager::Texture::kTextureWrap_ClampToEdge, Suffer::ResourceManager::Texture::kTextureWrap_ClampToEdge);
    ground_texture->LoadTextureData("../../../resources/images/floor_.png");

    Suffer::ref_ptr<Suffer::ResourceManager::Texture> ground_specular_texture;
    ground_specular_texture.alloc();
    ground_specular_texture->SetTextureFilter(Suffer::ResourceManager::Texture::kTextureFilter_Linear, Suffer::ResourceManager::Texture::kTextureFilter_Linear);
    ground_specular_texture->SetTextureWrap(Suffer::ResourceManager::Texture::kTextureWrap_ClampToEdge, Suffer::ResourceManager::Texture::kTextureWrap_ClampToEdge);
    ground_specular_texture->LoadTextureData("../../../resources/images/floor_spec.png");




    Suffer::ref_ptr<Suffer::MaterialComponent> ground_material;
    ground_material.alloc();
    Suffer::ref_ptr<Suffer::MaterialComponent::DefaultParams> ground_material_params;
    ground_material_params.alloc();
    ground_material_params->color_ = mathmorra::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
    ground_material_params->albedo_texture_id_ = ground_texture->id_;
    ground_material_params->specular_texture_id_ = ground_specular_texture->id_;
    ground_material->SetParams(ground_material_params.get());



    Suffer::ref_ptr<Suffer::MaterialComponent> material_wall;
    material_wall.alloc();
    Suffer::ref_ptr<Suffer::MaterialComponent::DefaultParams> material_wall_params;
    material_wall_params.alloc();
    material_wall_params->color_ = mathmorra::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
    material_wall_params->albedo_texture_id_ = wall_texture->id_;
    material_wall_params->specular_texture_id_ = wall_specular_texture->id_;
    material_wall->SetParams(material_wall_params.get());

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
    material_params_cube->albedo_texture_id_ = box_texture->id_;
    material_params_cube->specular_texture_id_ = box_specular_texture->id_;
    material_component_cube->SetParams(material_params_cube.get());
    go_cube->AddComponent(material_component_cube.get());

    Suffer::ref_ptr<Suffer::Transform> transform_component_cube;
    transform_component_cube.alloc();
    transform_component_cube->Translate(mathmorra::Vector3(0.0f, 2.0f, 0.0f));
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
    material_params2->color_ = mathmorra::Vector4(0.8f, 0.8f, 0.8f, 1.0f);
    material_component2->SetParams(material_params2.get());
    go_quad->AddComponent(ground_material.get());

    Suffer::ref_ptr<Suffer::Transform> transform_component_2;
    transform_component_2.alloc();
    transform_component_2->Scale(mathmorra::Vector3(20.0f, -20.0f, 20.0f));
    transform_component_2->Translate(mathmorra::Vector3(0.0f, 0.0f, 0.0f));
    transform_component_2->Rotate(mathmorra::Vector3(ThiefUtils::Math::Radians(90.0f), 0.0f, 0.0f));
    go_quad->AddComponent(transform_component_2.get());




    Suffer::ref_ptr<Suffer::GameObject> go_quad4;
    go_quad4.alloc();
    Suffer::ref_ptr<Suffer::GeometryComponent> geometry_component6;
    geometry_component6.alloc();
    geometry_component6->SetDrawMode(Suffer::GeometryComponent::kDrawMode_Triangles);
    geometry_component6->CreateGeometryWithShape(Suffer::GeometryComponent::kBasicShapes_Quad);
    go_quad4->AddComponent(geometry_component6.get());

    Suffer::ref_ptr<Suffer::MaterialComponent> material_component6;
    material_component6.alloc();
    Suffer::ref_ptr<Suffer::MaterialComponent::PhongParams> material_params6;
    material_params6.alloc();
    material_params6->color_ = mathmorra::Vector4(1.0f, 0.0f, 0.0f, 1.0f);
    material_component6->SetParams(material_params6.get());
    go_quad4->AddComponent(material_wall.get());

    Suffer::ref_ptr<Suffer::Transform> transform_component_7;
    transform_component_7.alloc();
    transform_component_7->Scale(mathmorra::Vector3(20.0f, 20.0f, 20.0f));
    transform_component_7->Translate(mathmorra::Vector3(-20.0f, 20.0f, 0.0f));
    transform_component_7->Rotate(mathmorra::Vector3(0.0f, ThiefUtils::Math::Radians(90.0f), 0.0f));
    go_quad4->AddComponent(transform_component_7.get());




    Suffer::ref_ptr<Suffer::GameObject> go_quad2;
    go_quad2.alloc();

    Suffer::ref_ptr<Suffer::GameObject> go_quad3;
    go_quad3.alloc();
    Suffer::ref_ptr<Suffer::GeometryComponent> geometry_component5;
    geometry_component5.alloc();
    geometry_component5->SetDrawMode(Suffer::GeometryComponent::kDrawMode_Triangles);
    geometry_component5->CreateGeometryWithShape(Suffer::GeometryComponent::kBasicShapes_Quad);
    go_quad3->AddComponent(geometry_component5.get());

    Suffer::ref_ptr<Suffer::MaterialComponent> material_component5;
    material_component5.alloc();
    Suffer::ref_ptr<Suffer::MaterialComponent::PhongParams> material_params5;
    material_params5.alloc();
    material_params5->color_ = mathmorra::Vector4(1.0f, 0.0f, 0.0f, 1.0f);
    material_component5->SetParams(material_params5.get());
    go_quad3->AddComponent(material_wall.get());

    Suffer::ref_ptr<Suffer::Transform> transform_component_6;
    transform_component_6.alloc();
    transform_component_6->Scale(mathmorra::Vector3(20.0f, 20.0f, 20.0f));
    transform_component_6->Translate(mathmorra::Vector3(20.0f, 20.0f, 0.0f));
    transform_component_6->Rotate(mathmorra::Vector3(0.0f, ThiefUtils::Math::Radians(-90.0f), 0.0f));
    go_quad3->AddComponent(transform_component_6.get());


    Suffer::ref_ptr<Suffer::GeometryComponent> geometry_component4;
    geometry_component4.alloc();
    geometry_component4->SetDrawMode(Suffer::GeometryComponent::kDrawMode_Triangles);
    geometry_component4->CreateGeometryWithShape(Suffer::GeometryComponent::kBasicShapes_Quad);
    go_quad2->AddComponent(geometry_component4.get());

    Suffer::ref_ptr<Suffer::MaterialComponent> material_component4;
    material_component4.alloc();
    Suffer::ref_ptr<Suffer::MaterialComponent::PhongParams> material_params4;
    material_params4.alloc();
    material_params4->color_ = mathmorra::Vector4(1.0f, 1.0f, 0.0f, 1.0f);
    material_component4->SetParams(material_params4.get());
    go_quad2->AddComponent(material_wall.get());

    Suffer::ref_ptr<Suffer::Transform> transform_component_5;
    transform_component_5.alloc();
    transform_component_5->Scale(mathmorra::Vector3(20.0f, 20.0f, 20.0f));
    transform_component_5->Translate(mathmorra::Vector3(0.0f, 20.0f, 20.0f));
    transform_component_5->Rotate(mathmorra::Vector3(0.0f, 0.0f, 0.0f));
    go_quad2->AddComponent(transform_component_5.get());

    // -------------------------------------------------------------------------------------//

    Suffer::ref_ptr<Suffer::GameObject> go_light;
    go_light.alloc();

    Suffer::ref_ptr<Suffer::GeometryComponent> geometry_component3;
    geometry_component3.alloc();
    geometry_component3->SetDrawMode(Suffer::GeometryComponent::kDrawMode_Triangles);
    geometry_component3->CreateGeometryWithShape(Suffer::GeometryComponent::kBasicShapes_Sphere);
    go_light->AddComponent(geometry_component3.get());

    Suffer::ref_ptr<Suffer::MaterialComponent> material_component3;
    material_component3.alloc();
    Suffer::ref_ptr<Suffer::MaterialComponent::PhongParams> material_params3;
    material_params3.alloc();
    material_params3->color_ = mathmorra::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
    material_component3->SetParams(material_params3.get());
    go_light->AddComponent(material_component3.get());

    Suffer::ref_ptr<Suffer::Transform> transform_component_3;
    transform_component_3.alloc();
    transform_component_3->Scale(mathmorra::Vector3(1.0f, 1.0f, 1.0f));
    transform_component_3->Translate(mathmorra::Vector3(5.0f, 0.0f, 5.0f));
    transform_component_3->Rotate(mathmorra::Vector3(ThiefUtils::Math::Radians(-90.0f), 0.0f, ThiefUtils::Math::Radians(180.0f)));
    go_light->AddComponent(transform_component_3.get());

    Suffer::ref_ptr<Suffer::LightComponent> light_component;
    light_component.alloc();

    light_component->Init(Suffer::LightComponent::kLightKind_Point);
    light_component->SetDirection(mathmorra::Vector3(0.0f, 0.0f, 1.0f));
    light_component->SetIntensity(8.0f);
    light_component->SetAmbient(0.5f, 0.5f, 0.5f);
    light_component->SetDiffuse(1.0f, 1.0f, 1.0f);
    light_component->SetSpecular(1.0f, 1.0f, 1.0f);
    go_light->AddComponent(light_component.get());
    light_component->SetActive(true);

    // -------------------------------------------------------------------------------------//

    Suffer::ref_ptr<Suffer::GameObject> go_light2;
    go_light2.alloc();

    go_light2->SetArchetype(Suffer::GameObject::kArchetype_Drawable); 

    Suffer::Transform* transform = static_cast<Suffer::Transform*>(go_light2->GetComponent(Suffer::Component::kComponentKind_Transform));
    transform->Translate(mathmorra::Vector3(-5.0f, 5.0f, -5.0f));

    Suffer::ref_ptr<Suffer::LightComponent> light_component2;
    light_component2.alloc();

    light_component2->Init(Suffer::LightComponent::kLightKind_Directional);
    light_component2->SetDirection(mathmorra::Vector3(0.0f, -1.0f, 0.0f));
    light_component2->SetIntensity(0.1f);
    light_component2->SetAmbient(0.2f, 0.2f, 0.2f);
    light_component2->SetDiffuse(0.6f, 0.6f, 0.6f);
    light_component2->SetSpecular(1.0f, 1.0f, 1.0f);
    go_light2->AddComponent(light_component2.get());
    light_component2->SetActive(true);


    Suffer::ref_ptr<Suffer::GameObject> go_sphere;
    go_sphere.alloc();
    go_sphere->SetArchetype(Suffer::GameObject::kArchetype_Drawable);

    Suffer::GeometryComponent* geometry_component_sphere = static_cast<Suffer::GeometryComponent*>(go_sphere->GetComponent(Suffer::Component::kComponentKind_Geometry));
    geometry_component_sphere->CreateGeometryWithShape(Suffer::GeometryComponent::kBasicShapes_Sphere);

    Suffer::Transform* transform_sphere = static_cast<Suffer::Transform*>(go_sphere->GetComponent(Suffer::Component::kComponentKind_Transform));
    transform_sphere->Translate(mathmorra::Vector3(0.0f, 10.0f, 0.0f));

    Suffer::ref_ptr<Suffer::LightComponent> light_sphere;
    light_sphere.alloc();

    light_sphere->Init(Suffer::LightComponent::kLightKind_Spot);
    light_sphere->SetDirection(mathmorra::Vector3(1.0f, -0.5f, 0.0f));
    light_sphere->SetIntensity(10.0f);
    light_sphere->SetAmbient(0.5f, 0.5f, 0.5f);
    light_sphere->SetDiffuse(1.0f, 1.0f, 1.0f);
    light_sphere->SetSpecular(1.0f, 1.0f, 1.0f);
    go_sphere->AddComponent(light_sphere.get());
    light_sphere->SetActive(true);
    light_sphere->SetCutOff(0.910f);
    light_sphere->SetOuterCutOff(0.820f);
    light_sphere->SetConstant(0.0f);
    light_sphere->SetLinear(0.474f);
    light_sphere->SetQuadratic(0.0f);

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

    go_quad->SetName("Floor");
    go_quad2->SetName("Wall");
    go_cube->SetName("Box");
    go_light->SetName("PointLight");
    go_light2->SetName("DirectionalLight");
    go_sphere->SetName("SpotLight");

    go_cube->AddChild(go_light.get());
    go_cube->AddChild(go_light2.get());

    scene->AddGameObject(go_cube);
    scene->AddGameObject(go_quad);
    scene->AddGameObject(go_quad2);
    scene->AddGameObject(go_quad3);
    scene->AddGameObject(go_quad4);
    scene->AddGameObject(go_light);
    scene->AddGameObject(go_light2);
    scene->AddGameObject(go_sphere);

    suffer.SetScene(scene);


    suffer.Run();

    suffer.Finish();

    return 0;

}

// --------------------------------------------------------------//

#endif