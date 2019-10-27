/*
* Author: Diego Ochando Torres <ochandoto@esat-alumni.com>
* Date: 10-12-2019
* Material Header
*/

#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <glm.hpp>
#include <data_types.h>
#include <referenced.h>
#include <ref_ptr.h>

using namespace Suffer;

// --------------------------------------------------- //

class Material : public virtual Referenced {

public:
	friend class SufferManager;
	friend class DrawGeometry;

	enum BasicMaterials {
		kBasicMaterials_Default = 0,
		kBasicMaterials_NONE = 20
	};

	// Getters
	glm::vec4 GetColor();

	// Setters
	void SetColor(glm::vec4 newColor);

	Material();
protected:
	virtual ~Material();

private:

	struct Data;
	Data* data_;

	BasicMaterials material_;

	void SetProgram(u16 program);
	u16 GetProgramID();

	// Methods
	Material(const Material&);
};

// --------------------------------------------------- //

#endif // __MATERIAL_H__