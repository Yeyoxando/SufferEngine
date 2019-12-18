
#ifndef __SYSTEM_BLUE_RENDER_H__
#define __SYSTEM_BLUE_RENDER_H__

#include "system.h"
#include "display_list.h"

// --------------------------------------------------- //

namespace Suffer {

  class SystemBlueRender : public System {

    friend class SufferManager;

  public:
    SystemBlueRender();

    bool is_active_;

  protected:
    virtual void Execute(GameObject* go) override;

  private:
    ~SystemBlueRender();

    DisplayList dl_;

  };

}

// --------------------------------------------------- //

#endif // __SYSTEM_BLUE_RENDER_H__