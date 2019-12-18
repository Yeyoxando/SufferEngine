
#ifndef __COMPONENT_BLUE_COLOR_H__
#define __COMPONENT_BLUE_COLOR_H__

#include "component.h"
#include <referenced.h>

namespace Suffer {

  class BlueColorComponent : public Component {

  public:

    BlueColorComponent() : Component(kComponentKind_BlueRender) {}

  protected:
    virtual ~BlueColorComponent();

  private:

  };

}

#endif //  __COMPONENT_BLUE_COLOR_H__