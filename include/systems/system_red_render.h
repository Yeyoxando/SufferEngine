
#ifndef __SYSTEM_RED_RENDER_H__
#define __SYSTEM_RED_RENDER_H__

#include "system.h"
#include "display_list.h"

// --------------------------------------------------- //

namespace Suffer {

  class SystemRedRender : public System {

    friend class SufferManager;

  public:
    SystemRedRender();

    bool is_active_;

  protected:
    virtual void Execute(GameObject* go) override;

  private:
    ~SystemRedRender();

    DisplayList dl_;

  };

}

// --------------------------------------------------- //

#endif // __SYSTEM_RENDER_H__