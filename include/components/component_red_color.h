
#ifndef __COMPONENT_RED_COLOR_H__
#define __COMPONENT_RED_COLOR_H__

#include "component.h"
#include <referenced.h>

namespace Suffer {

  class RedColorComponent : public Component {

  public:
    
    RedColorComponent() : Component(kComponentKind_RedRender) {}

  protected:
    virtual ~RedColorComponent();

  private:

  };

}

#endif //  __COMPONENT_RED_COLOR_H__