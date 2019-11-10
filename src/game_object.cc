#include <game_object.h>
#include <draw_geometry.h>
#include <matrix4.h>
#include <suffermanager.h>

// --------------------------------------------------- //

Suffer::GameObject::GameObject() {

	transform_.scale = glm::vec3(1.0f, 1.0f, 1.0f);
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

Suffer::ref_ptr<Suffer::Command> Suffer::GameObject::GetDrawCommand(){
	ref_ptr<DrawGeometry> draw_geometry;

	draw_geometry.alloc();
	draw_geometry.get()->SetData(this);

  mathmorra::Matrix4 model_matrix;

  mathmorra::Matrix4 translation_mat;
  translation_mat = translation_mat.Translate(transform_.position.x, transform_.position.y, transform_.position.z);
  
  mathmorra::Matrix4 rotation_mat_x;
  mathmorra::Matrix4 rotation_mat_y;
  mathmorra::Matrix4 rotation_mat_z;
  rotation_mat_x = rotation_mat_x.RotateX(transform_.rotation.x);
  rotation_mat_y = rotation_mat_y.RotateY(transform_.rotation.y);
  rotation_mat_z = rotation_mat_z.RotateZ(transform_.rotation.z);

  rotation_mat_z = rotation_mat_z.Multiply(rotation_mat_y);
  rotation_mat_z = rotation_mat_z.Multiply(rotation_mat_x);

  mathmorra::Matrix4 scale_mat;
  scale_mat = scale_mat.Scale(transform_.scale.x, transform_.scale.y, transform_.scale.z);
  
  model_matrix = translation_mat * rotation_mat_z * scale_mat;

  draw_geometry.get()->SetModelMatrix(model_matrix);


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
