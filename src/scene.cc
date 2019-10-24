#include <scene.h>
#include <game_object.h>

// --------------------------------------------------- //

Scene::Scene(){
	go_ = std::vector<EDK3::ref_ptr<GameObject>>(0);
}

// --------------------------------------------------- //

Scene::Scene(const Scene&){

}

// --------------------------------------------------- //

Scene::~Scene(){

}

// --------------------------------------------------- //

void Scene::Init() {
	EDK3::ref_ptr<GameObject> go;
	go.alloc();


	go_.push_back(go);
}

// --------------------------------------------------- //

void Scene::PrepareDraw(){

	for (int i = 0; i < go_.size(); ++i) {
		go_.at(i).get()->Draw();
	}

}

// --------------------------------------------------- //

