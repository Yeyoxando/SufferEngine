/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 10-12-2019
* Geometry Header
*/

#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include <data_types.h>
#include <referenced.h>
#include <ref_ptr.h>

using namespace Suffer;

// --------------------------------------------------- //

class Geometry : public virtual Referenced {

public:
	friend class SufferManager;
	friend class DrawGeometry;

	enum BasicShapes {
		kBasicShapes_Triangle = 0,
		kBasicShapes_Quad,
		kBasicShapes_Cube,
		kBasicShapes_NONE = 20
	};

	Geometry();
protected:
	virtual ~Geometry();

private:

	struct Data;
	Data* data_;

	BasicShapes shape_;
	void SetIndicesID(u16 indices_ID);
	void SetVerticesID(u16 vertices_ID);
	void SetNumberElements(u32 number_elements);

	u16 GetIndicesID();
	u16 GetVerticesID();
	u32 GetNumberElements();


	// Methods
	Geometry(const Geometry&);
};

// --------------------------------------------------- //

#endif // __GEOMETRY_H__