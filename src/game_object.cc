#include <game_object.h>
#include <draw_geometry.h>
#include <suffermanager.h>

// --------------------------------------------------- //

GameObject::GameObject() {

	transform_.scale = glm::vec3(0.0f, 0.0f, 0.0f);
	transform_.position = glm::vec3(0.0f, 0.0f, 0.0f);
	transform_.rotation = glm::vec3(0.0f, 0.0f, 0.0f);

}

// --------------------------------------------------- //

GameObject::GameObject(const GameObject& go) {

	this->geometry_ = go.geometry_;
	this->material_ = go.material_;

}

// --------------------------------------------------- //

EDK3::ref_ptr<Material> GameObject::GetMaterial() {
	return material_;
}

// --------------------------------------------------- //

EDK3::ref_ptr<Geometry> GameObject::GetGeometry() {
	return geometry_;
}

// --------------------------------------------------- //

void GameObject::SetMaterial(EDK3::ref_ptr<Material> new_material) {

#ifdef ASSERT
	assert(new_material); // "newMaterial was NULL"
#endif
	material_ = new_material;
}

// --------------------------------------------------- //

void GameObject::SetGeometry(EDK3::ref_ptr<Geometry> new_geometry) {
#ifdef ASSERT
	assert(new_geometry); // "newGeometry was NULL"
#endif
	geometry_ = new_geometry;
}

// --------------------------------------------------- //

Transform GameObject::GetTransform() {
	return transform_;
}

// --------------------------------------------------- //

GameObject::~GameObject() {

}

// --------------------------------------------------- //

void GameObject::Draw() {

	EDK3::ref_ptr<DrawGeometry> draw_geometry;

	draw_geometry.alloc();
	draw_geometry.get()->SetData(this);
	SufferManager::instance().AddCommand(draw_geometry.get());

}

// --------------------------------------------------- //