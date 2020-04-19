/*
 * Author: Diego Ochando Torres <ochandoto@esat-alumni.com>
 * Date: 24-02-2019
 * Post processing command Header
 */

#ifndef __POSTPROCESSING_H__
#define __POSTPROCESSING_H__

#include "command.h"
#include "game_object.h"
#include "ref_ptr.h"
#include "matrix4.h"

namespace Suffer {

  // ----------------------------------------------------------------------- //

  /**
   * @brief: Command to draw post processes with fixed quad geometry
   */
  class Postprocessing : public Command {
    friend class RenderManager;
  public:
    Postprocessing();

    /**
     * @brief: Indicates which kind of post process is
     */
    enum PostproccessKind {
      kPostproccessKind_Invalid = -1,
      kPostproccessKind_RenderToTexture = 0,
      kPostproccessKind_BlackAndWhite = 1,
    };

    /**
     * @brief: Initializes command data
     * @param: Post process to use
     */
    void SetData(PostproccessKind postpro);

  protected:
    virtual ~Postprocessing();

  private:

    /**
     * @brief: Executes the command with all necessary things to draw with the post process
     */
    virtual void Execute() const override;

    struct Data;
    Data* data_;

  };

  // ----------------------------------------------------------------------- //

} // End of Suffer namespace

#endif // __DRAW_GEOMETRY_H__
