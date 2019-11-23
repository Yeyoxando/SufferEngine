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

namespace Suffer {

  // ----------------------------------------------------------------------- //

  /**
    * @brief: Command to draw GameObjects with Geometry and Material
    */
	class DrawGeometry : public Command {

	public:
		DrawGeometry();

    /**
      * @brief: Sets the command with the info of the GameObject
      * @param: GameObject to get info
      */
		void SetData(GameObject* go);

    /**
      * @brief: Sets GameObject model matrix
      * @param: model matrix calculated in GameObject
      */
    void SetModelMatrix(mathmorra::Matrix4 model);
    /**
      * @brief: Sets Camera view matrix
      * @param: view matrix calculated in camera
      */
    void SetViewMatrix(mathmorra::Matrix4 view);
    /**
      * @brief: Sets camera projection matrix
      * @param: projection matrix calculated in camera
      */
    void SetProjectionMatrix(mathmorra::Matrix4 projection);

	protected:
		virtual ~DrawGeometry();

  private:

    /**
      * @brief: Executes the command with all necessary things to draw the GameObject
      */
		virtual void Execute() const override;

		struct Data;
		Data* data_;

  };

  // ----------------------------------------------------------------------- //

} // End of Suffer namespace

#endif // __DRAW_GEOMETRY_H__
