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
  vert_buff_->format_ = Suffer::ResourceManager::VertexBuffer::kVertexFormat_3P_3N_2UV;
  ind_buff_.alloc();

	float vertices[] = {
    //Vertex                  //Normals              //Uvs
       //Face1
       1.0f,  1.0f,  1.0f,    1.0f,  0.0f,  0.0f,     0.0f, 1.0f,// 0
       1.0f, -1.0f,  1.0f,    1.0f,  0.0f,  0.0f,     0.0f, 0.0f,// 1
       1.0f, -1.0f, -1.0f,    1.0f,  0.0f,  0.0f,     1.0f, 0.0f,// 2
       1.0f,  1.0f, -1.0f,    1.0f,  0.0f,  0.0f,     1.0f, 1.0f,// 3
      //Face2                                    
      -1.0f,  1.0f, -1.0f,    0.0f,  0.0f, -1.0f,     0.0f, 1.0f,// 4
      -1.0f, -1.0f, -1.0f,    0.0f,  0.0f, -1.0f,     0.0f, 0.0f,// 5
       1.0f, -1.0f, -1.0f,    0.0f,  0.0f, -1.0f,     1.0f, 0.0f,// 6
       1.0f,  1.0f, -1.0f,    0.0f,  0.0f, -1.0f,     1.0f, 1.0f,// 7
      //Face3
      -1.0f,  1.0f,  1.0f,    -1.0f,  0.0f,  0.0f,    0.0f, 1.0f,// 8
      -1.0f, -1.0f,  1.0f,    -1.0f,  0.0f,  0.0f,    0.0f, 0.0f,// 9
      -1.0f, -1.0f, -1.0f,    -1.0f,  0.0f,  0.0f,    1.0f, 0.0f,// 10
      -1.0f,  1.0f, -1.0f,    -1.0f,  0.0f,  0.0f,    1.0f, 1.0f,// 11
      //Face4
      -1.0f,  1.0f,  1.0f,    0.0f,  0.0f,  1.0f,     0.0f, 1.0f,// 12
      -1.0f, -1.0f,  1.0f,    0.0f,  0.0f,  1.0f,     0.0f, 0.0f,// 13
       1.0f, -1.0f,  1.0f,    0.0f,  0.0f,  1.0f,     1.0f, 0.0f,// 14
       1.0f,  1.0f,  1.0f,    0.0f,  0.0f,  1.0f,     1.0f, 1.0f,// 15
      //Face5
      -1.0f,  1.0f, -1.0f,    0.0f,  1.0f,  0.0f,     0.0f, 1.0f,// 16
      -1.0f,  1.0f,  1.0f,    0.0f,  1.0f,  0.0f,     0.0f, 0.0f,// 17
       1.0f,  1.0f,  1.0f,    0.0f,  1.0f,  0.0f,     1.0f, 0.0f,// 18
       1.0f,  1.0f, -1.0f,    0.0f,  1.0f,  0.0f,     1.0f, 1.0f,// 19
      //Face6
      -1.0f, -1.0f, -1.0f,    0.0f, -1.0f,  0.0f,     0.0f, 1.0f,// 20
      -1.0f, -1.0f,  1.0f,    0.0f, -1.0f,  0.0f,     0.0f, 0.0f,// 21
       1.0f, -1.0f,  1.0f,    0.0f, -1.0f,  0.0f,     1.0f, 0.0f,// 22
       1.0f, -1.0f, -1.0f,    0.0f, -1.0f,  0.0f,     1.0f, 1.0f,// 23

	};

  u16 indices[]{ 			
         0,  1,  2,  2,  3,  0,
         6,  5,  4,  4,  7,  6,
        10,  9,  8,  8, 11, 10,
        12, 13, 14, 14, 15, 12,
        16, 17, 18, 18, 19, 16,
        22, 21, 20, 20, 23, 22
  };

	suffer.resource_manager_.UploadVertexData(vert_buff_, vertices, 192);
  suffer.resource_manager_.UploadIndexData(ind_buff_, indices, 36);

	ref_ptr<Geometry> geometry;
	geometry.alloc();
	geometry->SetBuffers(vert_buff_, ind_buff_);
	
  ref_ptr < ResourceManager::Texture> albedo_texture;
  albedo_texture.alloc();
  suffer.resource_manager_.LoadTextureData(albedo_texture, "../../../resources/images/test.jpg");
	
	ref_ptr<MaterialInstance> material;
	material.alloc();
  material->SetMaterialParamsType(MaterialInstance::kParams_Default);
  material->SetColor(mathmorra::Vector4(1.0f, 1.0f, 1.0f, 1.0f ));
  material->SetAlbedoTexture(albedo_texture);

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
  vert_buff_2->format_ = Suffer::ResourceManager::VertexBuffer::kVertexFormat_3P_3N_2UV;
  ind_buff_2.alloc();
  
  float vertices2[] = {
      0.0f,  0.5f, -1.0f,  0.0f, 0.0f, 1.0f,   0.5f, 1.0f,
      0.5f, -0.5f, -1.0f,  0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
     -0.5f, -0.5f, -1.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
  };
  
  u16 indices2[]{ 0, 2, 1};
  
  suffer.resource_manager_.UploadVertexData(vert_buff_2, vertices2, 24);
  suffer.resource_manager_.UploadIndexData(ind_buff_2, indices2, 3);
  
  ref_ptr<Geometry> geometry2;
  geometry2.alloc();
  geometry2->SetBuffers(vert_buff_2, ind_buff_2);


  ref_ptr < ResourceManager::Texture> albedo_texture2;
  albedo_texture2.alloc();
  suffer.resource_manager_.LoadTextureData(albedo_texture2, "../../../resources/images/supercube.png");
  
  ref_ptr<MaterialInstance> material2;
  material2.alloc();
  material2->SetMaterialParamsType(MaterialInstance::kParams_Default);
  material2->SetColor(mathmorra::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
  material2->SetAlbedoTexture(albedo_texture2);
  
  
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

