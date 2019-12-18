
#ifndef __SYSTEM_ANIMATION_H__
#define __SYSTEM_ANIMATION_H__

#include "system.h"

// --------------------------------------------------- //

namespace Suffer {

  class SystemAnimation : public System {

  public:
    SystemAnimation();

  protected:
    virtual void Execute(GameObject* go) override;

  private:
    ~SystemAnimation();

  };

}

// --------------------------------------------------- //

#endif // __SYSTEM_ANIMATION_H__