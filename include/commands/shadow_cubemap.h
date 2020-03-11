/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 03-11-2020
* ShadowCubemap Header
*/

#ifndef __SHADOW_CUBEMAP_H__
#define __SHADOW_CUBEMAP_H__

#include "command.h"
#include "component_light.h"
#include "ref_ptr.h"
#include "matrix4.h"

namespace Suffer {

  // ----------------------------------------------------------------------- //

  /**
   * @brief: Command to calculate shadow map for each light
   */
  class ShadowCubemap : public Command {

  public:
      ShadowCubemap();

    void SetData(LightComponent* light);

  protected:
    virtual ~ShadowCubemap();

  private:

    /**
     * @brief: Executes the command with all necessary things
     */
    virtual void Execute() const override;

    struct Data;
    Data* data_;

  };

}

#endif // __SHADOW_CUBEMAP_H__