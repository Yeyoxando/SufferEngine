#include <scene.h>
#include <game_object.h>
#include <suffermanager.h>
#include <clear.h>

// --------------------------------------------------- //

Scene::Scene(){
	go_ = std::vector<ref_ptr<GameObject>>(0);
}

// --------------------------------------------------- //

Scene::Scene(const Scene&){

}

// --------------------------------------------------- //

Scene::~Scene(){

}

// --------------------------------------------------- //

void Scene::Init() {
	ref_ptr<GameObject> go;
	go.alloc();
	ref_ptr<GameObject> go2;
	go2.alloc();


	ref_ptr<Geometry> geometry;
	geometry.alloc();
	//SufferManager::instance().SetPredefiniedShape(geometry, Geometry::kBasicShapes_Cube);

	ref_ptr<Geometry> geometry2;
	geometry2.alloc();
	//SufferManager::instance().SetPredefiniedShape(geometry2, Geometry::kBasicShapes_Triangle);

	
	ref_ptr<Material> material;
	material.alloc();
	//SufferManager::instance().SetPredefiniedMaterial(material, Material::kBasicMaterials_Default);

	go->SetGeometry(geometry);
	go->SetMaterial(material);
	
	go2->SetGeometry(geometry2);
	go2->SetMaterial(material);

	//go_.push_back(go);
	go_.push_back(go2);
}

void Scene::Step(float time_step){
	// Logic

	PrepareDraw();
}

// --------------------------------------------------- //

void Scene::PrepareDraw(){

	DisplayList frame_dl;
	ref_ptr<Clear> clear_cmd;

	clear_cmd.alloc();
	clear_cmd.get()->SetClearColor(glm::vec4(0.8f));


	frame_dl.addCommand(clear_cmd.get());

	for (int i = 0; i < go_.size(); ++i) {
		const ref_ptr<Command> draw_cmd = go_.at(i).get()->GetDrawCommand();
		frame_dl.addCommand(draw_cmd);
	}



	SufferManager::instance().render_manager_.AddToRenderQueue(std::move(frame_dl));

}

// --------------------------------------------------- //

