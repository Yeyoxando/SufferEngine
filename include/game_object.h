/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 10-12-2019
* GameObject Header (Material, Transform, Geometry)
*/

#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include <glm.hpp>
#include <geometry.h>
#include <material.h>
#include <data_types.h>
#include <referenced.h>
#include <ref_ptr.h>


using namespace Suffer;

// --------------------------------------------------- //

struct Transform {
	glm::vec3 scale;
	glm::vec3 position;
	glm::vec3 rotation;
};

// --------------------------------------------------- //

class GameObject : public virtual Referenced {

public:

	GameObject();
	GameObject(const GameObject& go);

	// Getters
	Transform GetTransform();
	EDK3::ref_ptr<Material> GetMaterial();
	EDK3::ref_ptr<Geometry> GetGeometry();

	// Setters
	void SetMaterial(EDK3::ref_ptr<Material> new_material);
	void SetGeometry(EDK3::ref_ptr<Geometry> new_geometry);

	void Draw();

protected:
	virtual ~GameObject();

private:
	// Attributes
	Transform transform_;
	EDK3::ref_ptr<Material> material_;
	EDK3::ref_ptr<Geometry> geometry_;

	// Methods

};

// --------------------------------------------------- //

#endif // __GAME_OBJECT_H__