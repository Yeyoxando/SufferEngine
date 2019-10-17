/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 10-12-2019
* GameObject Header (Material, Transform, Geometry)
*/

#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include <glm.hpp>
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

class Material : public virtual Referenced {

public:

	// Getters
	glm::vec4 GetColor();

	// Setters
	void SetColor(glm::vec4 newColor);

protected:
	Material();
	virtual ~Material() {};

private:
	// Methods
	Material(const Material&);
	glm::vec4 color_;
};

// --------------------------------------------------- //

class Geometry : public virtual Referenced {

public:

	// Getters
	u32 NumberElements();
	u32 Indices();

protected:
	Geometry();
	virtual ~Geometry();

private:

	// Attributes
	u32 number_elements_;
	u32 indices_;

	// Methods
	Geometry(const Geometry&);

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
	void SetMaterial(EDK3::ref_ptr<Material> newMaterial);
	void SetGeometry(EDK3::ref_ptr<Geometry> newGeometry);

protected:
	virtual ~GameObject();

private:
	// Attributes
	Transform transform_;
	EDK3::ref_ptr<Material> material_;
	EDK3::ref_ptr<Geometry> geometry_;

	// Methods
	void Draw();

};

// --------------------------------------------------- //

#endif // __GAME_OBJECT_H__