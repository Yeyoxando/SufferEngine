
#include <common_definitions.h>
#if defined _MAIN_PABLO_ && !defined _MAIN_DIEGO_

#include <suffermanager.h>
#include "ref_ptr.h"
#include "scene.h"
#include "geometry.h"
#include "material.h"
#include "game_object.h"
#include "component_transform.h"
#include "resource_manager.h"
#include "component.h"
#include "system.h"
#include "system_transform.h"
#include "system_blue.h"
#include "system_red.h"
#include "system_render.h"
#include "component_geometry.h"
#include "component_material.h"
#include "component_blue.h"
#include "component_red.h"
#include "system_animation.h"
#include "component_animation.h"
#include <time.h>

// --------------------------------------------------------------//

int main(int argc, char* argv[]) {

	suffer.Init();
	Suffer::ref_ptr<Suffer::Scene> scene;
	scene.alloc();

	Suffer::ref_ptr<Suffer::SystemAnimation> system_anim;
	system_anim.alloc();
	suffer.AddSystem(system_anim.get());

	// Textures
	Suffer::ref_ptr<Suffer::ResourceManager::Texture> albedo_texture;
	albedo_texture.alloc();
	albedo_texture->SetTextureFilter(Suffer::ResourceManager::Texture::kTextureFilter_Nearest, Suffer::ResourceManager::Texture::kTextureFilter_Nearest);
	albedo_texture->SetTextureWrap(Suffer::ResourceManager::Texture::kTextureWrap_ClampToEdge, Suffer::ResourceManager::Texture::kTextureWrap_ClampToEdge);

	Array<Suffer::ref_ptr<Suffer::GameObject>> cubes;
	cubes.alloc(NUMBER_CUBES);

	Suffer::ref_ptr<Suffer::GeometryComponent> geometry_component;
	geometry_component.alloc();
	geometry_component->SetDrawMode(Suffer::GeometryComponent::kDrawMode_Triangles);
	geometry_component->CreateGeometryWithShape(Suffer::GeometryComponent::kBasicShapes_Cube);

	Suffer::ref_ptr<Suffer::Material> material_component;
	material_component.alloc();
	Suffer::ref_ptr<Suffer::Material::UnlitParams> material_params;
	material_params.alloc();
	material_params->color_ = mathmorra::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	material_component->SetParams(material_params.get());
	Array<Suffer::ref_ptr<Suffer::Transform>> transform_component_;
	transform_component_.alloc(NUMBER_CUBES);

	Suffer::ref_ptr<Suffer::RedComponent> red_component;
	Suffer::ref_ptr<Suffer::BlueComponent> blue_component;
	Suffer::ref_ptr<Suffer::AnimationComponent> anim;

	red_component.alloc();
	blue_component.alloc();
	anim.alloc();

	int random;
	for (int i = 0; i < NUMBER_CUBES; ++i) {
		random = rand() % 10;
		transform_component_[i].alloc();
		cubes[i].alloc();
		cubes[i]->AddComponent(geometry_component.get());
		cubes[i]->AddComponent(material_component.get());
		cubes[i]->AddComponent(transform_component_[i].get());
		if (random & 1) {
			cubes[i]->AddComponent(anim.get());
		}
		if (i < 50) {
			cubes[i]->AddComponent(red_component.get());
		}
		else {
			cubes[i]->AddComponent(blue_component.get());
		}

		scene->AddGameObject(cubes[i]);
	}

	int cube = 0;
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			auto component_ = cubes[cube]->GetComponent(Suffer::Component::ComponentKind::kComponentKind_Transform);
			Suffer::Transform* component = reinterpret_cast<Suffer::Transform*>(component_);
			component->Scale(0.2f, 0.2, 0.2f);
			component->Translate(mathmorra::Vector3(5.0f * j, 5.0f * i, 0.0f));
			++cube;
		}
	}







	suffer.SetScene(scene);


	suffer.Run();

	suffer.Finish();

	return 0;

}

// --------------------------------------------------------------//

#endif