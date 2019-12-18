#ifndef __COMPONENT_ANIMATION_H__
#define __COMPONENT_ANIMATION_H__

#include "component.h"
#include "vector3.h"
#include "matrix4.h"

namespace Suffer {

	class AnimationComponent : public Component {
		friend class SystemRed;
	public:
		AnimationComponent() : Component(kComponentKind_Animation) {
			frequency_ = 2.0f;
			ampl_ = 0.03f;
		};

		float time_;
		float frequency_;
		float ampl_;


	protected:

		~AnimationComponent() {};

	};

} // End of Suffer namespace

#endif
