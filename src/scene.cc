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
  go->GetGeometry()->SetDrawMode(Geometry::kDrawMode_LineStrip);
	go->SetMaterial(material);
  go->SetName("Cube");
	
	//AddGameObject(go);






  main_camera_.alloc();





  // SPHERE STUFF
  const int number_points = 25, number_revolutions = 25;

  ref_ptr<Suffer::ResourceManager::VertexBuffer> vert_buff_2;
  ref_ptr<Suffer::ResourceManager::IndexBuffer> ind_buff_2;
  vert_buff_2.alloc();
  ind_buff_2.alloc();

  vert_buff_2->format_ = Suffer::ResourceManager::VertexBuffer::kVertexFormat_3P_3N_2UV;

  Array<u16> sphere_indices;
  Array<mathmorra::Vector3> normals;
  Array<mathmorra::Vector3> sphere_points;



  normals.alloc(number_points* number_revolutions);
  sphere_points.alloc(number_points* number_revolutions);
  sphere_indices.alloc((number_points - 1)* (number_revolutions - 1) * 6);

  int index = 0;
  int radius = 1.0f;

  vertex_buffer::Vertex sphere_vertices[(number_revolutions * number_points)];

  for (int i = 0; i < number_points; ++i) {

      float latitude = ThiefUtils::Math::Map(i, 0, number_revolutions - 1, -ThiefUtils::Math::fPI / 2, ThiefUtils::Math::fPI / 2);

      for (int j = 0; j < number_revolutions; ++j) {

          float longitude = ThiefUtils::Math::Map(j, 0, number_revolutions - 1, -ThiefUtils::Math::fPI, ThiefUtils::Math::fPI);

          sphere_points[i * number_revolutions + j].x_ = radius * cos(longitude) * cos(latitude);
          sphere_points[i * number_revolutions + j].y_ = radius * sin(longitude) * cos(latitude);
          sphere_points[i * number_revolutions + j].z_ = radius * sin(latitude);

          normals[i * number_revolutions + j] = sphere_points[i * number_revolutions + j];
          normals[i * number_revolutions + j].Normalize();

          mathmorra::Vector2 uv;

          uv.x_ = (float)j / number_revolutions;
          uv.y_ = (float)i / number_points;

          sphere_vertices[(i * number_revolutions + j)] = vertex_buffer::Vertex(
              sphere_points[i * number_revolutions + j].x_,
              sphere_points[i * number_revolutions + j].y_,
              sphere_points[i * number_revolutions + j].z_, 
              normals[i * number_revolutions + j].x_,
              normals[i * number_revolutions + j].y_,
              normals[i * number_revolutions + j].z_,
              uv.x_,
              uv.y_);

      }

  }


  for (int i = 0; i < number_points - 1; ++i) {

      for (int j = 0; j < number_revolutions - 1; ++j) {

          sphere_indices[index++] = i * number_revolutions + j;
          sphere_indices[index++] = (i + 1) * number_revolutions + j;
          sphere_indices[index++] = i * number_revolutions + j + 1;

          sphere_indices[index++] = i * number_revolutions + j + 1;
          sphere_indices[index++] = (i + 1) * number_revolutions + j;
          sphere_indices[index++] = (i + 1) * number_revolutions + j + 1;

      }

  }

  suffer.resource_manager_.UploadVertexData(vert_buff_2, sphere_vertices, (number_revolutions * number_points));
  suffer.resource_manager_.UploadIndexData(ind_buff_2, &sphere_indices[0], sphere_indices.sizeInBytes());
  
  ref_ptr<Geometry> geometry2;
  geometry2.alloc();
  geometry2->SetBuffers(vert_buff_2, ind_buff_2);


  ref_ptr < ResourceManager::Texture> albedo_texture2;
  albedo_texture2.alloc();
  suffer.resource_manager_.LoadTextureData(albedo_texture2, "../../../resources/images/earth.jpg");
  
  ref_ptr<MaterialInstance> material2;
  material2.alloc();
  material2->SetMaterialParamsType(MaterialInstance::kParams_Default);
  material2->SetColor(mathmorra::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
  material2->SetAlbedoTexture(albedo_texture2);
  
  
  ref_ptr<GameObject> go2;
  go2.alloc();
  go2->SetGeometry(geometry2);
  go2->GetGeometry()->SetDrawMode(Geometry::kDrawMode_Triangles);
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

