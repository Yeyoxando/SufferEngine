/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 11-28-2019
* ComponentTransform Source
*/

#include "component_transform.h"

Suffer::TransformComponent::TransformComponent(){
    kind_ = Component::kComponentKind_Transform;
    position_ = { 10.0f, 10.0f, 1.0f };
}

Suffer::TransformComponent::~TransformComponent(){

}
