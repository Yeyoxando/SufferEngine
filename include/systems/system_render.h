/*
* Author: Diego Ochando Torres <ochandoto@esat-alumni.com>
* Date: 05-12-2019
* SystemTransform Header
*/

#ifndef __SYSTEM_RENDER_H__
#define __SYSTEM_RENDER_H__

#include "system.h"

// --------------------------------------------------- //

namespace Suffer {

  class SystemTransform : public System {

    friend class SufferManager;
    friend class Scene;

  public:
    SystemTransform();

  protected:
    virtual void Execute(GameObject* go) override;

  private:
    ~SystemTransform();

  };

}

// --------------------------------------------------- //

#endif // __SYSTEM_TRANSFORM_H__