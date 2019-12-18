#ifndef __SYSTEM_BLUE_H__
#define __SYSTEM_BLUE_H__

#include "system.h"
#include "game_object.h"

// --------------------------------------------------- //

namespace Suffer {

	class SystemBlue : public System {

		friend class SufferManager;
		friend class Scene;

	public:
		SystemBlue() {};

	protected:
		virtual void Execute(GameObject* go) override;

	private:
		~SystemBlue() {};

		DisplayList dl_;

	};

}

// --------------------------------------------------- //

#endif