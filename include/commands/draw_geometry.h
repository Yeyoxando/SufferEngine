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
#include <glm.hpp>

// --------------------------------------------------- //

namespace Suffer {

	class DrawGeometry : public Command {

	public:

		void SetData(GameObject* go);
    void SetModelMatrix(glm::mat4 model);
    void SetViewMatrix(glm::mat4 view);
    void SetProjectionMatrix(glm::mat4 projection);
		void SetGeometry(ref_ptr<Geometry> geo);
		void SetMaterial(ref_ptr<Material> mat);

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
