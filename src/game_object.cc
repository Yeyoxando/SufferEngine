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

// --------------------------------------------------- //

struct Geometry::Data {
	GLuint indices_ID;
	GLuint vertices_ID;
	u32 number_elements;
};

// --------------------------------------------------- //

void Geometry::SetShape(BasicShapes new_shape){

	shape_ = new_shape;
	SufferManager::instance().SetPredefiniedShape(this, shape_);

}

// --------------------------------------------------- //

Geometry::Geometry() {
	data_ = new Data();

	data_->vertices_ID = 0;
	data_->indices_ID = 0;

	shape_ = kBasicShapes_NONE;
}

// --------------------------------------------------- //

Geometry::~Geometry() {
	if (!data_) return;
	delete data_;
	data_ = nullptr;
}

// --------------------------------------------------- //

void Geometry::SetIndicesID(u16 indices_ID){
	data_->indices_ID = indices_ID;
}

// --------------------------------------------------- //

void Geometry::SetVerticesID(u16 vertices_ID){
	data_->vertices_ID = vertices_ID;
}

// --------------------------------------------------- //

void Geometry::SetNumberElements(u32 number_elements){
	data_->number_elements = number_elements;
}

// --------------------------------------------------- //

u16 Geometry::GetIndicesID(){
	return data_->indices_ID;
}

// --------------------------------------------------- //

u16 Geometry::GetVerticesID(){
	return data_->vertices_ID;
}

// --------------------------------------------------- //

u32 Geometry::GetNumberElements(){
	return data_->number_elements;
}

// --------------------------------------------------- //

// --------------------------------------------------- //

struct Material::Data {
	glm::vec4 color;
	GLuint program_ID;
};

// --------------------------------------------------- //

void Material::SetMaterial(BasicMaterials new_material) {

	material_ = new_material;
	SufferManager::instance().SetPredefiniedMaterial(this, new_material);

}

// --------------------------------------------------- //

glm::vec4 Material::GetColor() {
	return data_->color;
}

// --------------------------------------------------- //

u16 Material::GetProgramID(){
	return data_->program_ID;
}

// --------------------------------------------------- //

// --------------------------------------------------- //

void Material::SetColor(glm::vec4 new_color) {
	data_->color = new_color;
}

// --------------------------------------------------- //

void Material::SetProgram(u16 program){
	data_->program_ID = program;
}

// --------------------------------------------------- //

Material::Material() {
	data_ = new Data();

	data_->color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
}

// --------------------------------------------------- //

Material::~Material() {
	if (!data_) return;
	delete data_;
	data_ = nullptr;
}

// --------------------------------------------------- //