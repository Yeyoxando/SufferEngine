/*
* Author: Diego Ochando Torres <ochandoto@esat-alumni.com>
* Date: 05-12-2019
* SystemRender Header
*/

#ifndef __SYSTEM_RENDER_H__
#define __SYSTEM_RENDER_H__

#include "system.h"
#include "display_list.h"

// --------------------------------------------------- //

namespace Suffer {

  class SystemRender : public System {

    friend class SufferManager;
    friend class Scene;

  public:
    SystemRender();

  protected:
    virtual void Execute(GameObject* go) override;

  private:
    ~SystemRender();

    DisplayList dl_;

  };

}

// --------------------------------------------------- //

#endif // __SYSTEM_RENDER_H__