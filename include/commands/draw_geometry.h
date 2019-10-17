/*
 * Author: Diego Ochando Torres <ochandoto@esat-alumni.com>
 * Date: 15-10-2019
 * Draw Geometry command Header
 */

#ifndef __DRAW_GEOMETRY_H__
#define __DRAW_GEOMETRY_H__

#include <command.h>

// --------------------------------------------------- //

class DrawGeometry : public Command {

public:
	DrawGeometry();
	~DrawGeometry();

protected:
	virtual void Execute() override;

};

// --------------------------------------------------- //

#endif // __DRAW_GEOMETRY_H__
