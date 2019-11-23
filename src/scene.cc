// Author: Diego Ochando Torres <ochandoto@esat-alumni.com>

#include <scene.h>
#include <game_object.h>
#include <suffermanager.h>
#include <resource_manager.h>
#include <clear.h>
#include "common_definitions.h"
#include "math_utils.h"
#include "draw_geometry.h"

#define vertex_buffer ResourceManager::VertexBuffer
#define index_buffer ResourceManager::IndexBuffer

// --------------------------------------------------- //

Suffer::Scene::Scene(){

  current_gameobjects_ = std::vector<ref_ptr<GameObject>>(0);

}

// --------------------------------------------------- //

Suffer::Scene::Scene(const Suffer::Scene&){

}

// --------------------------------------------------- //

Suffer::Scene::~Scene(){

}

// --------------------------------------------------- //

void Suffer::Scene::Init() {

	ref_ptr<Geometry> geometry;
	geometry.alloc();
	
  ref_ptr < ResourceManager::Texture> albedo_texture;
  albedo_texture.alloc();
  albedo_texture->SetTextureFilter(ResourceManager::Texture::kTextureFilter_Nearest, ResourceManager::Texture::kTextureFilter_Nearest);
  albedo_texture->SetTextureWrap(ResourceManager::Texture::kTextureWrap_ClampToEdge, ResourceManager::Texture::kTextureWrap_ClampToEdge);
  albedo_texture->LoadTextureData("../../../resources/images/box.jpg");
	
	ref_ptr<MaterialInstance> material;
	material.alloc();
  material->SetMaterialParamsType(MaterialInstance::kParams_Default);
  material->SetColor(mathmorra::Vector4(1.0f, 1.0f, 1.0f, 1.0f ));
  material->SetAlbedoTexture(albedo_texture);

	ref_ptr<GameObject> go;
	go.alloc();
	go->SetGeometry(geometry);
  go->GetGeometry()->SetDrawMode(Geometry::kDrawMode_Triangles);
	go->SetMaterial(material);
  go->SetName("Cube");

  go->Translate(mathmorra::Vector3(-1.0f, 0.0f, 0.0f));
  go->GetGeometry()->CreateGeometryWithShape(Geometry::kBasicShapes_Cube);
	
	AddGameObject(go);



  // Camera
  main_camera_.alloc();




  ref_ptr < ResourceManager::Texture> albedo_texture2;
  albedo_texture2.alloc();
  albedo_texture2->SetTextureFilter(ResourceManager::Texture::kTextureFilter_Linear, ResourceManager::Texture::kTextureFilter_Linear);
  albedo_texture2->SetTextureWrap(ResourceManager::Texture::kTextureWrap_ClampToEdge, ResourceManager::Texture::kTextureWrap_ClampToEdge);
  albedo_texture2->LoadTextureData("../../../resources/images/earth.jpg");
  
  ref_ptr<MaterialInstance> material2;
  material2.alloc();
  material2->SetMaterialParamsType(MaterialInstance::kParams_Default);
  material2->SetMaterialParamsType(MaterialInstance::kParams_Default);
  material2->SetColor(mathmorra::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
  material2->SetAlbedoTexture(albedo_texture2);
  
  ref_ptr<GameObject> go2;
  ref_ptr<Geometry> geometry2;

  go2.alloc();
  geometry2.alloc();

  go2->SetGeometry(geometry2);
  go2->GetGeometry()->SetDrawMode(Geometry::kDrawMode_Triangles);

  go2->SetMaterial(material2);
  go2->Translate(mathmorra::Vector3(1.0f, 0.0f, 0.0f));
  go2->SetName("Sphere");
  go2->GetGeometry()->CreateGeometryWithShape(Geometry::kBasicShapes_Sphere);
  
  AddGameObject(go2);

}

// --------------------------------------------------- //

void Suffer::Scene::Step(float time_step){

	// Logic
  main_camera_.get()->Update();
  if(main_camera_->FPS()) main_camera_->CameraMovement(main_camera_);
	PrepareDraw();

}

// --------------------------------------------------- //

void Suffer::Scene::PrepareDraw(){

	DisplayList frame_dl;

  // Clear command
	ref_ptr<Clear> clear_cmd;

	clear_cmd.alloc();
	clear_cmd.get()->SetClearColor(mathmorra::Vector4(0.8f));

	frame_dl.AddCommand(clear_cmd.get());


  // Gameobject adds itself to displaylist
	for (u32 i = 0; i < current_gameobjects_.size(); ++i) {
    current_gameobjects_.at(i).get()->AddDrawCommand(frame_dl, main_camera_->ViewMatrix(), main_camera_->ProjectionMatrix());
	}


  // Send DL to render manager
	suffer.render_manager_.AddToRenderQueue(std::move(frame_dl));

}

void Suffer::Scene::AddGameObject(ref_ptr<GameObject> gameobject){

  current_gameobjects_.push_back(gameobject);

}

// --------------------------------------------------- //

