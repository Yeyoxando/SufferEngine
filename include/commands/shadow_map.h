/*
 * Author: Diego Ochando Torres <ochandoto@esat-alumni.com>
 * Date: 27-02-2019
 * Shadow map command Header
 */

#ifndef __SHADOW_MAP_H__
#define __SHADOW_MAP_H__

#include "command.h"
#include "component_light.h"
#include "ref_ptr.h"
#include "matrix4.h"

namespace Suffer {

  // ----------------------------------------------------------------------- //

  /**
   * @brief: Command to calculate shadow map for each light
   */
  class ShadowMap : public Command {

  public:
    ShadowMap();

    void SetData(LightComponent* light);

  protected:
    virtual ~ShadowMap();

  private:

    /**
     * @brief: Executes the command with all necessary things
     */
    virtual void Execute() const override;

    struct Data;
    Data* data_;

  };

}

#endif