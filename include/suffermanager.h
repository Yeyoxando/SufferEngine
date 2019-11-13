// Pablo Bano Benito <banyobe@esat-alumni.com>

#ifndef __SUFFER_MANAGER_H__
#define __SUFFER_MANAGER_H__

#include <ref_ptr.h>
#include <render_manager.h>
#include <resource_manager.h>
#include <audio_manager.h>
#include <scoped_array.h>
#include <thread.h>
#include <material.h>
#include "vector2.h"


// --------------------------------------------------------------//

namespace Suffer {

  class Scene;
	class SufferManager {

	public:
		friend class Audio3D;
		friend class Audio2D;
		friend class Interface;

		static SufferManager& instance();

		bool Init();
		bool Run();
		bool Step(double time_step);
		bool Finish();

		double DeltaTime();

    mathmorra::Vector2 GetMousePosition();

		// Subsystems
    AudioManager audio_manager_;
		RenderManager render_manager_;
		ResourceManager resource_manager_;

	protected:

		SufferManager();
		virtual ~SufferManager();

	private:

		SufferManager(const SufferManager&);

		void Input();
		void Update();
		void Draw();

		// DisplayLists Stuff
		void Audio();
		void PrepareAudio();

    void SetMousePosition();

    Scene* GetCurrentScene();

		// Threads
		ref_ptr<Thread> logic_;
		ref_ptr<Thread> input_;
		ref_ptr<Thread> audio_;

    mathmorra::Vector2 mouse_position_;

		struct Data;
		Data* data_;
	};

}

// --------------------------------------------------------------//


#endif // __SUFFER_MANAGER_H__
