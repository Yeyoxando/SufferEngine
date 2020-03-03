
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
#include "component_light.h"
#include "component.h"
#include "audio.h"

const u16 number_cubes = 2;

// --------------------------------------------------------------//

int main(int argc, char* argv[]) {

    suffer.Init();

    Suffer::ref_ptr<Suffer::Scene> scene;
    scene.alloc();

    // Textures
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

    Suffer::ref_ptr<Suffer::ResourceManager::Texture> earth_texture;
    earth_texture.alloc();
    earth_texture->SetTextureFilter(Suffer::ResourceManager::Texture::kTextureFilter_Linear, Suffer::ResourceManager::Texture::kTextureFilter_Linear);
    earth_texture->SetTextureWrap(Suffer::ResourceManager::Texture::kTextureWrap_ClampToEdge, Suffer::ResourceManager::Texture::kTextureWrap_ClampToEdge);
    earth_texture->LoadTextureData("../../../resources/images/earth.jpg");

    Suffer::ref_ptr<Suffer::ResourceManager::Texture> earth_specular_texture;
    earth_specular_texture.alloc();
    earth_specular_texture->SetTextureFilter(Suffer::ResourceManager::Texture::kTextureFilter_Linear, Suffer::ResourceManager::Texture::kTextureFilter_Linear);
    earth_specular_texture->SetTextureWrap(Suffer::ResourceManager::Texture::kTextureWrap_ClampToEdge, Suffer::ResourceManager::Texture::kTextureWrap_ClampToEdge);
    earth_specular_texture->LoadTextureData("../../../resources/images/earth_specular.jpg");


    // GameObjects and Components
    Suffer::ref_ptr<Suffer::GameObject> go_cubes[number_cubes];
    Suffer::ref_ptr<Suffer::GeometryComponent> geometry_component_spheres[number_cubes];
    Suffer::ref_ptr<Suffer::Transform> transform_component_cubes[number_cubes];


    // Default Materials / Params
    Suffer::ref_ptr<Suffer::MaterialComponent> material_component_cube;
    material_component_cube.alloc();
    Suffer::ref_ptr<Suffer::MaterialComponent::DefaultParams> material_params_cube;
    material_params_cube.alloc();
    material_params_cube->color_ = mathmorra::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
    material_params_cube->albedo_texture_id_ = box_texture->id_;
    material_params_cube->specular_texture_id_ = box_specular_texture->id_;
    material_component_cube->SetParams(material_params_cube.get());

    for (int i = 0; i < number_cubes; ++i) {
        // GameObjects
        go_cubes[i].alloc();

        // Geometry
        geometry_component_spheres[i].alloc();
        geometry_component_spheres[i]->SetDrawMode(Suffer::GeometryComponent::kDrawMode_LineLoop);
        geometry_component_spheres[i]->CreateGeometryWithShape(Suffer::GeometryComponent::kBasicShapes_Cube);
        go_cubes[i]->AddComponent(geometry_component_spheres[i].get());

        // Transform
        transform_component_cubes[i].alloc();
        transform_component_cubes[i]->Translate(mathmorra::Vector3(-10.0f + (rand() % 10),
                                                                   -10.0f + (rand()%10),
                                                                   -10.0f + (rand()%10)));
        transform_component_cubes[i]->Rotate(mathmorra::Vector3(0.0f, 0.0f, 0.0f));
        go_cubes[i]->AddComponent(transform_component_cubes[i].get());

        // Script
        Suffer::ref_ptr<Suffer::ScriptComponent> script_component_;
        script_component_.alloc();
        go_cubes[i]->AddComponent(script_component_.get());
        script_component_->AttachScript("../../../src/lua/lua_test_update.lua");

        // Material
        go_cubes[i]->AddComponent(material_component_cube.get());

        // Miscellaneous stuff
        go_cubes[i]->SetName("Cube");


        scene->AddGameObject(go_cubes[i]);

    }

    for (int i = 0; i < number_cubes; ++i) {

        int one = rand() % number_cubes;
        int two = rand() % number_cubes;

        while (one == two) {
            one = rand() % number_cubes;
            two = rand() % number_cubes;
        }

        if (!go_cubes[two]->HasComponent(Suffer::Component::ComponentKind::kComponentKind_Child)) {
            go_cubes[one]->AddChild(go_cubes[two]);
        }

    }

    // -------------------------------------------------------------------------------------//

    Suffer::ref_ptr<Suffer::Audio3D> audio_component_;
    audio_component_.alloc();
    audio_component_->Load("../../../resources/audio/tavern.ogg");
    audio_component_->SetLooping(true);
    audio_component_->Play3D();
    go_cubes[1]->AddComponent(audio_component_.get());

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
    go_cubes[rand()% number_cubes]->AddComponent(light_component2.get());


    suffer.SetScene(scene);


    suffer.Run();

    suffer.Finish();

    return 0;

}

// --------------------------------------------------------------//

#endif