#include <scene.h>
#include <game_object.h>
#include <suffermanager.h>

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

	EDK3::ref_ptr<Geometry> geometry;
	geometry.alloc();
	SufferManager::instance().SetPredefiniedShape(geometry, Geometry::kBasicShapes_Cube);

	EDK3::ref_ptr<Material> material;
	material.alloc();
	SufferManager::instance().SetPredefiniedMaterial(material, Material::kBasicMaterials_Default);

	go->SetGeometry(geometry);
	go->SetMaterial(material);

	go_.push_back(go);
}

// --------------------------------------------------- //

void Scene::PrepareDraw(){

	SufferManager::instance().render_mutex.lock();

	for (int i = 0; i < go_.size(); ++i) {
		go_.at(i).get()->Draw();
	}

	SufferManager::instance().render_mutex.unlock();

}

// --------------------------------------------------- //

