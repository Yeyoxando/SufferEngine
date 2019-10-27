/*
 * Author: Diego Ochando Torres <ochandoto@esat-alumni.com>
 * Date: 15-10-2019
 * Draw Geometry command Header
 */

#ifndef __DRAW_GEOMETRY_H__
#define __DRAW_GEOMETRY_H__

#include <command.h>
#include <game_object.h>
#include <ref_ptr.h>

// --------------------------------------------------- //

class DrawGeometry : public Command {

public:

	void SetData(GameObject* go);
	void SetTransform(Transform t);
	void SetGeometry(EDK3::ref_ptr<Geometry> geo);
	void SetMaterial(EDK3::ref_ptr<Material> mat);

	DrawGeometry();
protected:

	virtual ~DrawGeometry();

	virtual void Execute() override;

	struct Data;
	Data* data_;
};

// --------------------------------------------------- //

#endif // __DRAW_GEOMETRY_H__
