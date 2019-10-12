/*
 * Author: Pablo Bano Benito <banyobe@esat-alumni.com>
 * Date: 10-12-2019
 * GameObject Header (Material, Transform, Geometry)
 */

#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include <glm.hpp>
#include <data_types.h>

// --------------------------------------------------- //

struct Transform {
	glm::vec3 scale;
	glm::vec3 position;
	glm::vec3 rotation;
};

// --------------------------------------------------- //

class Material /*: public Referenced*/ {

// This constructor will be protected when we add the ref_ptr class
public:
	Material() {};
	~Material() {};

public:
	// Methods
};

// --------------------------------------------------- //

class Geometry /*: public Referenced*/ {

// This constructor will be protected when we add the ref_ptr class
public:
	Geometry() {};
	~Geometry() {};

private:

	// Attributes
	u16 number_elements_;
	u16 indices_;

	// Methods

};

// --------------------------------------------------- //

class GameObject /*: public Referenced*/ {

public:

	GameObject();
	~GameObject();

private:
	// Attributes
	// TODO: This attributes will be a ref_ptr Template (constructor protected)
	Material material_;
	Geometry geometry_;

	Transform transform_;


	// Methods
	// TODO: Call to DISPLAY_LIST add
	void Draw();

};

// --------------------------------------------------- //

#endif // __GAME_OBJECT_H__
