#include <game_object.h>

// --------------------------------------------------- //

GameObject::GameObject(){

	transform_.scale = glm::vec3(0.0f, 0.0f, 0.0f);
	transform_.position = glm::vec3(0.0f, 0.0f, 0.0f);
	transform_.rotation = glm::vec3(0.0f, 0.0f, 0.0f);

}

// --------------------------------------------------- //

GameObject::GameObject(const GameObject& go){

}

// --------------------------------------------------- //

GameObject::~GameObject(){

}

// --------------------------------------------------- //

void GameObject::Draw(){
	// Call to DisplayList.add
}

// --------------------------------------------------- //
