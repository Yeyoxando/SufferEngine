/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 10-12-2019
* GameObject Source (Transform)
*/

#include <game_object.h>
#include <draw_geometry.h>
#include <matrix4.h>
#include <suffermanager.h>

// --------------------------------------------------- //

Suffer::GameObject::GameObject() {

  transform_.scale_ = { 1.0f, 1.0f, 1.0f };
  transform_.position_ = { 0.0f, 0.0f, 0.0f };
  transform_.rotation_ = { 0.0f, 0.0f, 0.0f };

  transform_.up_ =    { 0.0f, 1.0f, 0.0f };
  transform_.right_ = { 1.0f, 0.0f, 0.0f };
  transform_.forward_ = mathmorra::Vector3::CrossProduct(transform_.up_, 
                                                         transform_.right_);

  name_ = "GameObject";

}

bool Suffer::GameObject::operator!=(const GameObject& go){

    if (transform_.position_ !=  go.transform_.position_ ||
        transform_.scale_    !=  go.transform_.scale_    ||
        transform_.rotation_ !=  go.transform_.rotation_) 
    {
        return false;
    }

    // TODO: expand

}

// --------------------------------------------------- //

Suffer::GameObject::GameObject(const GameObject& go) {

	this->geometry_ = go.geometry_;
	this->material_ = go.material_;

}

// --------------------------------------------------- //

const Suffer::ref_ptr<Suffer::MaterialInstance> Suffer::GameObject::GetMaterial() {
	return material_;
}

// --------------------------------------------------- //

const Suffer::ref_ptr<Suffer::Geometry> Suffer::GameObject::GetGeometry() {
	return geometry_;
}

// --------------------------------------------------- //

void Suffer::GameObject::SetMaterial(ref_ptr<MaterialInstance> new_material) {

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

Suffer::ref_ptr<Suffer::Command> Suffer::GameObject::GetDrawCommand(){

	ref_ptr<DrawGeometry> draw_geometry;

	draw_geometry.alloc();
	draw_geometry.get()->SetData(this);

  mathmorra::Matrix4 model_matrix;

  mathmorra::Matrix4 translation_mat;
  translation_mat = translation_mat.Translate(transform_.position_.x_, 
                                              transform_.position_.y_, 
                                              transform_.position_.z_);
  
  mathmorra::Matrix4 rotation_mat_x;
  mathmorra::Matrix4 rotation_mat_y;
  mathmorra::Matrix4 rotation_mat_z;
  rotation_mat_x = rotation_mat_x.RotateX(transform_.rotation_.x_);
  rotation_mat_y = rotation_mat_y.RotateY(transform_.rotation_.y_);
  rotation_mat_z = rotation_mat_z.RotateZ(transform_.rotation_.z_);

  rotation_mat_z = rotation_mat_z.Multiply(rotation_mat_y);
  rotation_mat_z = rotation_mat_z.Multiply(rotation_mat_x);

  mathmorra::Matrix4 scale_mat;
  scale_mat = scale_mat.Scale(transform_.scale_.x_, 
                              transform_.scale_.y_, 
                              transform_.scale_.z_);
  
  model_matrix = translation_mat * rotation_mat_z * scale_mat;

  draw_geometry.get()->SetModelMatrix(model_matrix);


	return draw_geometry.get();
}

// --------------------------------------------------- //

void Suffer::GameObject::Translate(mathmorra::Vector3 position){
  transform_.position_ = position;
}

const char* Suffer::GameObject::Name(){
    return name_;
}

// --------------------------------------------------- //

void Suffer::GameObject::SetName(const char* name){
    name_ = (char*)name;
}

// --------------------------------------------------- //

Suffer::GameObject* Suffer::GameObject::GetChild(u32 child){
    // TODO: Expand this
    return &GameObject();
}

// --------------------------------------------------- //

u32 Suffer::GameObject::NumberChilds(){
    return 0;
}

// --------------------------------------------------- //

u32 Suffer::GameObject::NumberChildsRecursively(GameObject* go){

    u32 number_of_childs = go->NumberChilds();
    u32 result = 0;

    for (u32 i = 0; i < number_of_childs; ++i) {
        result = go->NumberChildsRecursively(go->GetChild(i));
    }

    return result;

}

// --------------------------------------------------- //

void Suffer::GameObject::Rotate(float x, float y, float z){
    transform_.rotation_ = { x, y, z };
}

// --------------------------------------------------- //

void Suffer::GameObject::Translate(float x, float y, float z){
    transform_.position_ = { x, y, z };
}

// --------------------------------------------------- //

Suffer::Transform Suffer::GameObject::GetTransform() {
	return transform_;
}

// --------------------------------------------------- //

Suffer::GameObject::~GameObject() {

}

// --------------------------------------------------- //

void Suffer::GameObject::Step(float delta_time){

    // Updates
    

    // Logic

}

// --------------------------------------------------- //

void Suffer::GameObject::Destroy(){
    // Destroy Himself
    
}

// --------------------------------------------------- //
