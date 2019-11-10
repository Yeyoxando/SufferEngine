#include <scene.h>
#include <game_object.h>
#include <suffermanager.h>
#include <clear.h>
#include "draw_geometry.h"

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

  ref_ptr<SufferManager::VertexBuffer> vert_buff_;
  ref_ptr<SufferManager::IndexBuffer> ind_buff_;
  vert_buff_.alloc();
  ind_buff_.alloc();

	float vertices[] = {
       //Face1
       1.0f,  1.0f,  1.0f,
       1.0f, -1.0f,  1.0f,
       1.0f, -1.0f, -1.0f,
       1.0f,  1.0f, -1.0f,
      //Face2
      -1.0f,  1.0f, -1.0f,
      -1.0f, -1.0f, -1.0f,
       1.0f, -1.0f, -1.0f,
       1.0f,  1.0f, -1.0f,
      //Face3
      -1.0f,  1.0f,  1.0f,
      -1.0f, -1.0f,  1.0f,
      -1.0f, -1.0f, -1.0f,
      -1.0f,  1.0f, -1.0f,
      //Face4
      -1.0f,  1.0f,  1.0f,
      -1.0f, -1.0f,  1.0f,
       1.0f, -1.0f,  1.0f,
       1.0f,  1.0f,  1.0f,
      //Face5
      -1.0f,  1.0f, -1.0f,
      -1.0f,  1.0f,  1.0f,
       1.0f,  1.0f,  1.0f,
       1.0f,  1.0f, -1.0f,
      //Face6
      -1.0f, -1.0f, -1.0f,
      -1.0f, -1.0f,  1.0f,
       1.0f, -1.0f,  1.0f,
       1.0f, -1.0f, -1.0f,
	};

  u16 indices[]{ 			
         0,  1,  2,  2,  3,  0,
         6,  5,  4,  4,  7,  6,
        10,  9,  8,  8, 11, 10,
        12, 13, 14, 14, 15, 12,
        16, 17, 18, 18, 19, 16,
        22, 21, 20, 20, 23, 22
  };

	SufferManager::instance().UploadVertexData(vert_buff_, vertices, 72);
	SufferManager::instance().UploadIndexData(ind_buff_, indices, 36);

	ref_ptr<Geometry> geometry;
	geometry.alloc();
	geometry->SetBuffers(vert_buff_, ind_buff_);
	
	
	ref_ptr<Material> material;
	material.alloc();
  material->SetMaterialType(Material::kBasicMaterials_Default);
  material->material_settings_->material_params_.default_params_.SetColor(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

	ref_ptr<GameObject> go;
	go.alloc();
	go->SetGeometry(geometry);
	go->SetMaterial(material);
	
	AddGameObject(go);






  main_camera_.alloc();







  ref_ptr<SufferManager::VertexBuffer> vert_buff_2;
  ref_ptr<SufferManager::IndexBuffer> ind_buff_2;
  vert_buff_2.alloc();
  ind_buff_2.alloc();

  float vertices2[] = {
      0.0f,  0.5f, -1.0f,
      0.5f, -0.5f, -1.0f,
     -0.5f, -0.5f, -1.0f
  };

  u16 indices2[]{ 0, 2, 1};

  SufferManager::instance().UploadVertexData(vert_buff_2, vertices2, 9);
  SufferManager::instance().UploadIndexData(ind_buff_2, indices2, 3);

  ref_ptr<Geometry> geometry2;
  geometry2.alloc();
  geometry2->SetBuffers(vert_buff_2, ind_buff_2);


  ref_ptr<Material> material2;
  material2.alloc();
  material2->SetMaterialType(Material::kBasicMaterials_Default);
  material2->material_settings_->material_params_.default_params_.SetColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));


  ref_ptr<GameObject> go2;
  go2.alloc();
  go2->SetGeometry(geometry2);
  go2->SetMaterial(material2);
  go2->SetPosition(glm::vec3(0.0f, 0.0f, -0.1f));


  AddGameObject(go2);

}

void Suffer::Scene::Step(float time_step){
	// Logic
  main_camera_.get()->Update();
  if(main_camera_->fps_movement_) main_camera_->CameraMovement(main_camera_);
	PrepareDraw();
}

// --------------------------------------------------- //

void Suffer::Scene::PrepareDraw(){

	DisplayList frame_dl;
	ref_ptr<Clear> clear_cmd;

	clear_cmd.alloc();
	clear_cmd.get()->SetClearColor(glm::vec4(0.8f));


	frame_dl.addCommand(clear_cmd.get());

	for (u32 i = 0; i < current_gameobjects_.size(); ++i) {
		ref_ptr<Command> cmd = current_gameobjects_.at(i).get()->GetDrawCommand();

    DrawGeometry* draw_cmd = reinterpret_cast<DrawGeometry*>(cmd.get());

    draw_cmd->SetViewMatrix(main_camera_->ViewMatrix());
    draw_cmd->SetProjectionMatrix(main_camera_->ProjectionMatrix());

		frame_dl.addCommand(draw_cmd);
	}



	SufferManager::instance().render_manager_.AddToRenderQueue(std::move(frame_dl));

}

void Suffer::Scene::AddGameObject(ref_ptr<GameObject> gameobject){
  current_gameobjects_.push_back(gameobject);
}

// --------------------------------------------------- //

