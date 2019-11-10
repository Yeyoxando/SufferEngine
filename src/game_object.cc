#include <game_object.h>
#include <draw_geometry.h>
#include <suffermanager.h>

// --------------------------------------------------- //

Suffer::GameObject::GameObject() {

	transform_.scale = glm::vec3(0.0f, 0.0f, 0.0f);
	transform_.position = glm::vec3(0.0f, 0.0f, 0.0f);
	transform_.rotation = glm::vec3(0.0f, 0.0f, 0.0f);

}

// --------------------------------------------------- //

Suffer::GameObject::GameObject(const GameObject& go) {

	this->geometry_ = go.geometry_;
	this->material_ = go.material_;

}

// --------------------------------------------------- //

Suffer::ref_ptr<Suffer::Material> Suffer::GameObject::GetMaterial() {
	return material_;
}

// --------------------------------------------------- //

Suffer::ref_ptr<Suffer::Geometry> Suffer::GameObject::GetGeometry() {
	return geometry_;
}

// --------------------------------------------------- //

void Suffer::GameObject::SetMaterial(ref_ptr<Material> new_material) {

#ifdef ASSERT
	assert(new_material); // "newMaterial was NULL"
#endif
	material_ = new_material;
}

// --------------------------------------------------- //

void Suffer::GameObject::SetGeometry(ref_ptr<Geometry> new_geometry) {
#ifdef ASSERT
	assert(new_geometry); // "newGeometry was NULL"
#endif
	geometry_ = new_geometry;
}

const Suffer::ref_ptr<Suffer::Command> Suffer::GameObject::GetDrawCommand(){
	ref_ptr<DrawGeometry> draw_geometry;

	draw_geometry.alloc();
	draw_geometry.get()->SetData(this);
	
	return draw_geometry.get();
}

// --------------------------------------------------- //

Suffer::Transform Suffer::GameObject::GetTransform() {
	return transform_;
}

// --------------------------------------------------- //

Suffer::GameObject::~GameObject() {

}

// --------------------------------------------------- //
