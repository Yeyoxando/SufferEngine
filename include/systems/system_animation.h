#ifndef __SYSTEM_ANIMATION_H__
#define __SYSTEM_ANIMATION_H__

#include "system.h"
#include "game_object.h"

// --------------------------------------------------- //

namespace Suffer {

	class SystemAnimation : public System {

		friend class SufferManager;
		friend class Scene;

	public:
		SystemAnimation() {};

	protected:
		virtual void Execute(GameObject* go) override;

	private:
		~SystemAnimation() {};

		DisplayList dl_;
	};

}

// --------------------------------------------------- //

#endif