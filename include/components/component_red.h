#ifndef __COMPONENT_RED_H__
#define __COMPONENT_RED_H__

#include "component.h"
#include "vector3.h"
#include "matrix4.h"

namespace Suffer {

	class RedComponent : public Component {
		friend class SystemRed;
	public:
		RedComponent() : Component(kComponentKind_Red) {};


	protected:

		~RedComponent() {};

	};

} // End of Suffer namespace

#endif
