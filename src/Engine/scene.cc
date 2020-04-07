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

  main_camera_.alloc();
  current_gameobjects_ = std::vector<ref_ptr<GameObject>>(0);

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

void Suffer::Scene::RemoveGameObject(GameObject* game_object){

    if (game_object == nullptr) return;

    std::vector <ref_ptr<GameObject>>::iterator game_objects_iterator;

    game_objects_iterator = std::find(current_gameobjects_.begin(), current_gameobjects_.end(), game_object);
    current_gameobjects_.erase(game_objects_iterator);

}

// --------------------------------------------------- //

