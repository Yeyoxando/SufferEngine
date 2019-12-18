
#ifndef __COMPONENT_ANIMATION_H__
#define __COMPONENT_ANIMATION_H__

#include "component.h"
#include <referenced.h>

namespace Suffer {

  class AnimationComponent : public Component {

  public:
    AnimationComponent() : Component(kComponentKind_Animation) { amplitude_ = 0.0f; frequency_ = 0.0f; }

    float amplitude_;
    float frequency_;

  protected:
    virtual ~AnimationComponent();

  private:

  };

}

#endif //  __COMPONENT_ANIMATION_H__