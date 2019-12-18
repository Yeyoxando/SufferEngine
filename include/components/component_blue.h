#ifndef __COMPONENT_BLUE_H__
#define __COMPONENT_BLUE_H__

#include "component.h"
#include "vector3.h"
#include "matrix4.h"

namespace Suffer {

	class BlueComponent : public Component {
		friend class SystemBlue;
	public:
		BlueComponent() : Component(kComponentKind_Blue) {};


	protected:

		~BlueComponent() {};

	};

} // End of Suffer namespace

#endif
