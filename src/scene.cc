// Author: Diego Ochando Torres <ochandoto@esat-alumni.com>

#include <scene.h>
#include <game_object.h>
#include <suffermanager.h>
#include <resource_manager.h>
#include <clear.h>
#include "common_definitions.h"
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

  ref_ptr<vertex_buffer> vert_buff_;
  ref_ptr<index_buffer> ind_buff_;
  vert_buff_.alloc();
  vert_buff_->format_ = vertex_buffer::kVertexFormat_3P_3N_2UV;
  ind_buff_.alloc();

  vertex_buffer::Vertex vertices[] = {
                            //Vertex               //Normals              //Uvs
      //Face1 
      vertex_buffer::Vertex(1.0f,  1.0f,  1.0f,    1.0f,  0.0f,  0.0f,     0.0f, 1.0f),// 0  
      vertex_buffer::Vertex(1.0f, -1.0f,  1.0f,    1.0f,  0.0f,  0.0f,     0.0f, 0.0f),// 1
      vertex_buffer::Vertex(1.0f, -1.0f, -1.0f,    1.0f,  0.0f,  0.0f,     1.0f, 0.0f),// 2
      vertex_buffer::Vertex(1.0f,  1.0f, -1.0f,    1.0f,  0.0f,  0.0f,     1.0f, 1.0f),// 3
      //Face2                                                                        
      vertex_buffer::Vertex(-1.0f,  1.0f, -1.0f,   0.0f,  0.0f, -1.0f,     0.0f, 1.0f),// 4
      vertex_buffer::Vertex(-1.0f, -1.0f, -1.0f,   0.0f,  0.0f, -1.0f,     0.0f, 0.0f),// 5
      vertex_buffer::Vertex(1.0f, -1.0f, -1.0f,    0.0f,  0.0f, -1.0f,     1.0f, 0.0f),// 6
      vertex_buffer::Vertex(1.0f,  1.0f, -1.0f,    0.0f,  0.0f, -1.0f,     1.0f, 1.0f),// 7
      //Face3                                                                       
      vertex_buffer::Vertex(-1.0f,  1.0f,  1.0f,  -1.0f,  0.0f,  0.0f,     0.0f, 1.0f),// 8
      vertex_buffer::Vertex(-1.0f, -1.0f,  1.0f,  -1.0f,  0.0f,  0.0f,     0.0f, 0.0f),// 9
      vertex_buffer::Vertex(-1.0f, -1.0f, -1.0f,  -1.0f,  0.0f,  0.0f,     1.0f, 0.0f),// 10
      vertex_buffer::Vertex(-1.0f,  1.0f, -1.0f,  -1.0f,  0.0f,  0.0f,     1.0f, 1.0f),// 11
      //Face4                                                                        
      vertex_buffer::Vertex(-1.0f,  1.0f,  1.0f,   0.0f,  0.0f,  1.0f,     0.0f, 1.0f),// 12
      vertex_buffer::Vertex(-1.0f, -1.0f,  1.0f,   0.0f,  0.0f,  1.0f,     0.0f, 0.0f),// 13
      vertex_buffer::Vertex(1.0f, -1.0f,  1.0f,    0.0f,  0.0f,  1.0f,     1.0f, 0.0f),// 14
      vertex_buffer::Vertex(1.0f,  1.0f,  1.0f,    0.0f,  0.0f,  1.0f,     1.0f, 1.0f),// 15
      //Face5                                                                       
      vertex_buffer::Vertex(-1.0f,  1.0f, -1.0f,   0.0f,  1.0f,  0.0f,     0.0f, 1.0f),// 16
      vertex_buffer::Vertex(-1.0f,  1.0f,  1.0f,   0.0f,  1.0f,  0.0f,     0.0f, 0.0f),// 17
      vertex_buffer::Vertex(1.0f,  1.0f,  1.0f,    0.0f,  1.0f,  0.0f,     1.0f, 0.0f),// 18
      vertex_buffer::Vertex(1.0f,  1.0f, -1.0f,    0.0f,  1.0f,  0.0f,     1.0f, 1.0f),// 19
      //Face6                                                                       
      vertex_buffer::Vertex(-1.0f, -1.0f, -1.0f,   0.0f, -1.0f,  0.0f,     0.0f, 1.0f),// 20
      vertex_buffer::Vertex(-1.0f, -1.0f,  1.0f,   0.0f, -1.0f,  0.0f,     0.0f, 0.0f),// 21
      vertex_buffer::Vertex(1.0f, -1.0f,  1.0f,    0.0f, -1.0f,  0.0f,     1.0f, 0.0f),// 22
      vertex_buffer::Vertex(1.0f, -1.0f, -1.0f,    0.0f, -1.0f,  0.0f,     1.0f, 1.0f),// 23

	};

  index_buffer::Triangle indices[]{
    // Face 1
    index_buffer::Triangle(0,  1,  2),  index_buffer::Triangle(2,  3,  0),
    // Face 2
    index_buffer::Triangle(6,  5,  4),  index_buffer::Triangle(4,  7,  6),
    // Face 3
    index_buffer::Triangle(10,  9,  8), index_buffer::Triangle(8, 11, 10),
    // Face 4
    index_buffer::Triangle(12, 13, 14), index_buffer::Triangle(14, 15, 12),
    // Face 5
    index_buffer::Triangle(16, 17, 18), index_buffer::Triangle(18, 19, 16),
    // Face 6
    index_buffer::Triangle(22, 21, 20), index_buffer::Triangle(20, 23, 22),
  };

	suffer.resource_manager_.UploadVertexData(vert_buff_, vertices, 24);
  suffer.resource_manager_.UploadIndexData(ind_buff_, indices, 12);

	ref_ptr<Geometry> geometry;
	geometry.alloc();
	geometry->SetBuffers(vert_buff_, ind_buff_);
	
  ref_ptr < ResourceManager::Texture> albedo_texture;
  albedo_texture.alloc();
  albedo_texture->SetTextureFilter(ResourceManager::Texture::kTextureFilter_Nearest, ResourceManager::Texture::kTextureFilter_Nearest);
  albedo_texture->SetTextureWrap(ResourceManager::Texture::kTextureWrap_ClampToEdge, ResourceManager::Texture::kTextureWrap_ClampToEdge);
  suffer.resource_manager_.LoadTextureData(albedo_texture, "../../../resources/images/box.jpg");
	
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

