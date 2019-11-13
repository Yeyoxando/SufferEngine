#include <scene.h>
#include <game_object.h>
#include <suffermanager.h>
#include <resource_manager.h>
#include <clear.h>
#include "common_definitions.h"
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

  ref_ptr<Suffer::ResourceManager::VertexBuffer> vert_buff_;
  ref_ptr<Suffer::ResourceManager::IndexBuffer> ind_buff_;
  vert_buff_.alloc();
  vert_buff_->format_ = Suffer::ResourceManager::VertexBuffer::kVertexFormat_3P_3N;
  ind_buff_.alloc();

	float vertices[] = {
    //Vertex
       //Face1
       1.0f,  1.0f,  1.0f,    1.0f,  0.0f,  0.0f,   //0, 1, 2  
       1.0f, -1.0f,  1.0f,    1.0f,  0.0f,  0.0f,   //3, 4, 5  
       1.0f, -1.0f, -1.0f,    1.0f,  0.0f,  0.0f,   //6, 7, 8  
       1.0f,  1.0f, -1.0f,    1.0f,  0.0f,  0.0f,   //9, 10, 11
      //Face2
      -1.0f,  1.0f, -1.0f,    0.0f,  0.0f, -1.0f,//12, 13, 14
      -1.0f, -1.0f, -1.0f,    0.0f,  0.0f, -1.0f,//15, 16, 17
       1.0f, -1.0f, -1.0f,    0.0f,  0.0f, -1.0f,//18, 19, 20
       1.0f,  1.0f, -1.0f,    0.0f,  0.0f, -1.0f,//21, 22, 23
      //Face3
      -1.0f,  1.0f,  1.0f,    -1.0f,  0.0f,  0.0f,//0, 1, 2
      -1.0f, -1.0f,  1.0f,    -1.0f,  0.0f,  0.0f,//6, 7, 8
      -1.0f, -1.0f, -1.0f,    -1.0f,  0.0f,  0.0f,//12, 13, 14
      -1.0f,  1.0f, -1.0f,    -1.0f,  0.0f,  0.0f,//18, 19, 20
      //Face4
      -1.0f,  1.0f,  1.0f,    0.0f,  0.0f,  1.0f,//24, 25, 26
      -1.0f, -1.0f,  1.0f,    0.0f,  0.0f,  1.0f,//30, 31, 32
       1.0f, -1.0f,  1.0f,    0.0f,  0.0f,  1.0f,//36, 37, 38
       1.0f,  1.0f,  1.0f,    0.0f,  0.0f,  1.0f,//42, 43, 44
      //Face5
      -1.0f,  1.0f, -1.0f,    0.0f,  1.0f,  0.0f,//0, 1, 2
      -1.0f,  1.0f,  1.0f,    0.0f,  1.0f,  0.0f,//3, 4, 5
       1.0f,  1.0f,  1.0f,    0.0f,  1.0f,  0.0f,//6, 7, 8
       1.0f,  1.0f, -1.0f,    0.0f,  1.0f,  0.0f,//9, 10, 11
      //Face6
      -1.0f, -1.0f, -1.0f,    0.0f, -1.0f,  0.0f,//12, 13, 14
      -1.0f, -1.0f,  1.0f,    0.0f, -1.0f,  0.0f,//15, 16, 17
       1.0f, -1.0f,  1.0f,    0.0f, -1.0f,  0.0f,//18, 19, 20
       1.0f, -1.0f, -1.0f,    0.0f, -1.0f,  0.0f,//21, 22, 23

	};

  u16 indices[]{ 			
         0,  1,  2,  2,  3,  0,
         6,  5,  4,  4,  7,  6,
        10,  9,  8,  8, 11, 10,
        12, 13, 14, 14, 15, 12,
        16, 17, 18, 18, 19, 16,
        22, 21, 20, 20, 23, 22
  };

	suffer.resource_manager_.UploadVertexData(vert_buff_, vertices, 144);
  suffer.resource_manager_.UploadIndexData(ind_buff_, indices, 36);

	ref_ptr<Geometry> geometry;
	geometry.alloc();
	geometry->SetBuffers(vert_buff_, ind_buff_);
	
	
	ref_ptr<MaterialInstance> material;
	material.alloc();
  material->SetMaterialParamsType(MaterialInstance::kParams_Default);
  material->SetColor(mathmorra::Vector4( 0.5, 0.0f, 1.0f, 1.0f ));

	ref_ptr<GameObject> go;
	go.alloc();
	go->SetGeometry(geometry);
	go->SetMaterial(material);
  go->SetName("Cube");
	
	AddGameObject(go);






  main_camera_.alloc();







  ref_ptr<Suffer::ResourceManager::VertexBuffer> vert_buff_2;
  ref_ptr<Suffer::ResourceManager::IndexBuffer> ind_buff_2;
  vert_buff_2.alloc();
  vert_buff_2->format_ = Suffer::ResourceManager::VertexBuffer::kVertexFormat_3P;
  ind_buff_2.alloc();
  
  float vertices2[] = {
      0.0f,  0.5f, -1.0f,
      0.5f, -0.5f, -1.0f,
     -0.5f, -0.5f, -1.0f,
  };
  
  u16 indices2[]{ 0, 2, 1};
  
  suffer.resource_manager_.UploadVertexData(vert_buff_2, vertices2, 9);
  suffer.resource_manager_.UploadIndexData(ind_buff_2, indices2, 3);
  
  ref_ptr<Geometry> geometry2;
  geometry2.alloc();
  geometry2->SetBuffers(vert_buff_2, ind_buff_2);
  
  
  ref_ptr<MaterialInstance> material2;
  material2.alloc();
  material2->SetMaterialParamsType(MaterialInstance::kParams_Default);
  material2->SetColor(mathmorra::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
  
  
  ref_ptr<GameObject> go2;
  go2.alloc();
  go2->SetGeometry(geometry2);
  go2->SetMaterial(material2);
  go2->Translate(mathmorra::Vector3(0.0f, 0.0f, -0.1f));
  go2->SetName("Triangle");
  
  
  AddGameObject(go2);

}

// --------------------------------------------------- //

void Suffer::Scene::Step(float time_step){
	// Logic
  main_camera_.get()->Update();
  if(main_camera_->fps_movement_) main_camera_->CameraMovement(main_camera_);
	PrepareDraw();
}

// --------------------------------------------------- //

void Suffer::Scene::PrepareDraw(){

	DisplayList frame_dl;

  // Clear command
	ref_ptr<Clear> clear_cmd;

	clear_cmd.alloc();
	clear_cmd.get()->SetClearColor(mathmorra::Vector4(0.8f));

	frame_dl.addCommand(clear_cmd.get());


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

