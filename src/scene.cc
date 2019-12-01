// Author: Diego Ochando Torres <ochandoto@esat-alumni.com>

#include "scene.h"
#include "game_object.h"
#include "suffermanager.h"
#include "resource_manager.h"
#include "clear.h"
#include "common_definitions.h"
#include "math_utils.h"
#include "draw_geometry.h"

#define vertex_buffer ResourceManager::VertexBuffer
#define index_buffer ResourceManager::IndexBuffer

// --------------------------------------------------- //

Suffer::Scene::Scene(){

  current_gameobjects_ = std::vector<ref_ptr<GameObject>>(0);
  main_camera_.alloc();

}

// --------------------------------------------------- //

Suffer::Scene::Scene(const Suffer::Scene&){

}

// --------------------------------------------------- //

Suffer::Scene::~Scene(){

}

// --------------------------------------------------- //

void Suffer::Scene::Step(float time_step){

	// Logic
  main_camera_.get()->Update();
  if(main_camera_->FPS()) main_camera_->CameraMovement(main_camera_);

  int size = current_gameobjects_.size();

  for (int i = 0; i < size; ++i) {
      current_gameobjects_[i]->Step(time_step);
  }

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
    suffer.transform_system_.Execute(current_gameobjects_.at(i).get());
    current_gameobjects_.at(i).get()->AddDrawCommand(frame_dl, main_camera_->ViewMatrix(), main_camera_->ProjectionMatrix());
	}

  // Send DL to render manager
	suffer.render_manager_.AddToRenderQueue(std::move(frame_dl));

}

// --------------------------------------------------- //

Suffer::Camera* Suffer::Scene::GetMainCamera(){
    return main_camera_.get();
}

// --------------------------------------------------- //

void Suffer::Scene::AddGameObject(ref_ptr<GameObject> gameobject){

  current_gameobjects_.push_back(gameobject);

}

// --------------------------------------------------- //

