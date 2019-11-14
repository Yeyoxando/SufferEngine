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

  /**
    * @brief:
    */
	class DrawGeometry : public Command {

	public:
    /**
       * @brief: 
       * @param: 
       */
		void SetData(GameObject* go);


    /**
       * @brief: 
       * @param: 
       */
    void SetModelMatrix(mathmorra::Matrix4 model);
    /**
       * @brief: 
       * @param: 
       */
    void SetViewMatrix(mathmorra::Matrix4 view);
    /**
       * @brief: 
       * @param: 
       */
    void SetProjectionMatrix(mathmorra::Matrix4 projection);

		DrawGeometry();

	protected:

		virtual ~DrawGeometry();

  private:
    /**
       * @brief: 
       * @param: 
       */
    void SetGeometry(const ref_ptr<Geometry> geo);
    /**
       * @brief: 
       * @param: 
       */
    void SetMaterial(const ref_ptr<MaterialInstance> mat);


    /**
       * @brief: 
       */
		virtual void Execute() const override;

		struct Data;
		Data* data_;

	};

}
// --------------------------------------------------- //

#endif // __DRAW_GEOMETRY_H__
