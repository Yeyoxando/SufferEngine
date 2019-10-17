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

void GameObject::SetMaterial(EDK3::ref_ptr<Material> newMaterial) {

#ifdef ASSERT
	assert(newMaterial); // "newMaterial was NULL"
#endif
	material_ = newMaterial;
}

// --------------------------------------------------- //

void GameObject::SetGeometry(EDK3::ref_ptr<Geometry> newGeometry) {
#ifdef ASSERT
	assert(newGeometry); // "newGeometry was NULL"
#endif
	geometry_ = newGeometry;
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

u32 Geometry::NumberElements() {
	return number_elements_;
}

// --------------------------------------------------- //

u32 Geometry::Indices() {
	return indices_;
}

// --------------------------------------------------- //

Geometry::Geometry() {
	number_elements_ = 0;
	indices_ = 0;
}

// --------------------------------------------------- //

Geometry::~Geometry() {

}

// --------------------------------------------------- //

glm::vec4 Material::GetColor() {
	return color_;
}

// --------------------------------------------------- //

void Material::SetColor(glm::vec4 newColor) {
	color_ = newColor;
}

// --------------------------------------------------- //

Material::Material() {
	color_ = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
}

// --------------------------------------------------- //