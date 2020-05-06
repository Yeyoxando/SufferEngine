/*
 * Author: Diego Ochando Torres <ochandoto@esat-alumni.com>
 * Date: 03-05-2020
 * Draw Skybox command Header
 */

#ifndef __DRAW_SKYBOX_H__
#define __DRAW_SKYBOX_H__

#include "command.h"
#include "skybox.h"
#include "ref_ptr.h"

namespace Suffer {

  // ----------------------------------------------------------------------- //

  /**
   * @brief: Command to draw GameObjects depth for shadows
   */
  class DrawSkybox : public Command {
    friend class RenderManager;
  public:
    DrawSkybox();

    /**
     * @brief: Sets the command with the info of the Skybox to draw
     * @param: Skybox to get info
     */
    void SetData(Skybox* skybox);

  protected:
    virtual ~DrawSkybox();

  private:

    /**
     * @brief: Executes the command with all necessary things to draw the Skybox
     */
    virtual void Execute() const override;

    struct Data;
    Data* data_;

  };

  // ----------------------------------------------------------------------- //

} // End of Suffer namespace

#endif // __DRAW_SKYBOX_H__
