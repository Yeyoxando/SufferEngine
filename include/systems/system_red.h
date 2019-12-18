#ifndef __SYSTEM_RED_H__
#define __SYSTEM_RED_H__

#include "system.h"
#include "game_object.h"

// --------------------------------------------------- //

namespace Suffer {

	class SystemRed : public System {

		friend class SufferManager;
		friend class Scene;

	public:
		SystemRed() {};

	protected:
		virtual void Execute(GameObject* go) override;

	private:
		~SystemRed() {};

		DisplayList dl_;
	};

}

// --------------------------------------------------- //

#endif