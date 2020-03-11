/*
 * Author: Diego Ochando Torres <ochandoto@esat-alumni.com>
 * Date: 03-03-2020
 * Draw Depth command Header
 */

#ifndef __DRAW_POINT_DEPTH_H__
#define __DRAW_POINT_DEPTH_H__

#include "command.h"
#include "game_object.h"
#include "ref_ptr.h"
#include "matrix4.h"

namespace Suffer {

  // ----------------------------------------------------------------------- //

  /**
   * @brief: Command to draw GameObjects depth for shadows
   */
  class DrawPointDepth : public Command {
    friend class RenderManager;
  public:
      DrawPointDepth();

    /**
     * @brief: Sets the command with the info of the GameObject
     * @param: GameObject to get info
     */
    void SetData(GameObject* go, mathmorra::Vector3 light_position, float far_plane);

    /**
     * @brief: Sets GameObject model matrix
     * @param: model matrix calculated in GameObject
     */
    void SetMatrices(mathmorra::Matrix4 model, mathmorra::Matrix4 view_mat[6]);

  protected:
    virtual ~DrawPointDepth();

  private:

    /**
     * @brief: Executes the command with all necessary things to draw the GameObject depth from light view point
     */
    virtual void Execute() const override;

    struct Data;
    Data* data_;

  };

  // ----------------------------------------------------------------------- //

} // End of Suffer namespace

#endif // __DRAW_POINT_DEPTH_H__
