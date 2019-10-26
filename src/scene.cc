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

	EDK3::ref_ptr<Geometry> geometry;
	geometry.alloc();
	geometry.get()->SetShape(Geometry::kBasicShapes_Triangle);

	go->SetGeometry(geometry);


	EDK3::ref_ptr<Material> material;
	material.alloc();
	material->SetMaterial(Material::kBasicMaterials_Default);

	go->SetMaterial(material);

	go_.push_back(go);
}

// --------------------------------------------------- //

void Scene::PrepareDraw(){

	for (int i = 0; i < go_.size(); ++i) {
		go_.at(i).get()->Draw();
	}

}

// --------------------------------------------------- //

