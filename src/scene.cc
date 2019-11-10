#include <scene.h>
#include <game_object.h>
#include <suffermanager.h>
#include <clear.h>

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
      0.2f, -0.2f, -1.0f,
      0.2f,  0.2f, -1.0f,
     -0.2f,  0.2f, -1.0f,
     -0.2f, -0.2f, -1.0f,
	};

  u16 indices[]{ 0, 2, 1,
                 2, 3, 0 };

	SufferManager::instance().UploadVertexData(vert_buff_, vertices, 12);
	SufferManager::instance().UploadIndexData(ind_buff_, indices, 6);

	ref_ptr<Geometry> geometry;
	geometry.alloc();
	geometry->SetBuffers(vert_buff_, ind_buff_);
	
	
	ref_ptr<Material> material;
	material.alloc();
  material->SetMaterialType(Material::kBasicMaterials_Default);


	ref_ptr<GameObject> go;
	go.alloc();
	go->SetGeometry(geometry);
	go->SetMaterial(material);
	
	AddGameObject(go);














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


  ref_ptr<GameObject> go2;
  go2.alloc();
  go2->SetGeometry(geometry2);
  go2->SetMaterial(material2);

  AddGameObject(go2);

















}

void Suffer::Scene::Step(float time_step){
	// Logic

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
		const ref_ptr<Command> draw_cmd = current_gameobjects_.at(i).get()->GetDrawCommand();
		frame_dl.addCommand(draw_cmd);
	}



	SufferManager::instance().render_manager_.AddToRenderQueue(std::move(frame_dl));

}

void Suffer::Scene::AddGameObject(ref_ptr<GameObject> gameobject){
  current_gameobjects_.push_back(gameobject);
}

// --------------------------------------------------- //

