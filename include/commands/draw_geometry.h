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
#include "matrix4.h"

// --------------------------------------------------- //

namespace Suffer {

	class DrawGeometry : public Command {

	public:

		void SetData(GameObject* go);
    void SetModelMatrix(mathmorra::Matrix4 model);
    void SetViewMatrix(mathmorra::Matrix4 view);
    void SetProjectionMatrix(mathmorra::Matrix4 projection);
		void SetGeometry(const ref_ptr<Geometry> geo);
		void SetMaterial(const ref_ptr<MaterialInstance> mat);

		DrawGeometry();

	protected:

		virtual ~DrawGeometry();

		virtual void Execute() const override;

		struct Data;
		Data* data_;

	};

}
// --------------------------------------------------- //

#endif // __DRAW_GEOMETRY_H__
