// Pablo Bano Benito <banyobe@esat-alumni.com>

#ifndef __SUFFER_MANAGER_H__
#define __SUFFER_MANAGER_H__

#include <ref_ptr.h>
#include <render_manager.h>
#include <resource_manager.h>
#include <audio_manager.h>
#include <scoped_array.h>
#include "thread.h"
#include "vector2.h"
#include "input.h"
#include "system_transform.h"
#include "system_render.h"

namespace Suffer {

  // ----------------------------------------------------------------------- //

  class Scene;

  /**
   * @brief: Executes Suffer Engine with all the functionality divided in subsystems.
   *         Call Init, Run and Finish in your code to execute the Engine.
   *         You could create an Scene, set it and the Engine will execute it.
   */
	class SufferManager {

	public:
		friend class Audio3D;
		friend class Audio2D;
		friend class Interface;

    /**
     * @brief: static instance of the Engine
     */
		static SufferManager& instance();

    void AddSystem(System* new_system);

    /**
     * @brief: Initializes all the required dependencies for the Engine in order 
     * @return: true if all has started successful
     */
		bool Init();
    
    /**
     * @brief: Main loop of the Engine, executes all needed to use the Engine
     */
    void Run();
    
    /**
     * @brief: Shuts down the Engine
     * @return: true if all has finished successful
     */
    bool Finish();

    // Scene management
    void SetScene(ref_ptr<Scene> scene);
    Scene* GetCurrentScene();

    // Misc getters
		double DeltaTime();

    mathmorra::Vector2 GetMousePosition();
    void SetCursorPosition(mathmorra::Vector2 newPosition);

		// Subsystems
    AudioManager audio_manager_;
    InputManager input_manager_;
		RenderManager render_manager_;
		ResourceManager resource_manager_;

    // High Level Stuff
    ref_ptr<Audio3D> one;
    ref_ptr<Audio3D> two;
    ref_ptr<Audio3D> samples_[MAX_SAMPLES];
    ref_ptr<Audio3D> branching_a_;
    ref_ptr<Audio3D> branching_b_;
    ref_ptr<Audio3D> branching_transition_;
    bool do_once_a = false;
    bool do_once_b = false;
    bool go_to_a;
    bool go_to_transition_;
    u32 audio_mode_;
    // TODO: Delete this

	protected:

		SufferManager();
		virtual ~SufferManager();

	private:

		SufferManager(const SufferManager&);

    /**
     * @brief: Process and catch all the Input 
     */
    void Input();
    
    /**
     * @brief: Updates all the GameObjects of the current Scene
     *         and fills a DisplayList with Render commands.
     *         Executed in logic thread.
     */
    void Step();
		
    /**
     * @brief: Renders the DisplayList calculated from the logic thread.
     *         Executed on main thread.
     */
    void Draw();

    /**
     * @brief: If the DisplayList of Audio Commands is not empty awakes the audio thread to 
     *         process the DisplayList.
     *         Executed in logic thread.
     */
    void PrepareAudio();

		// Threads
		ref_ptr<Thread> logic_;
		ref_ptr<Thread> input_;
		ref_ptr<Thread> audio_;

    mathmorra::Vector2 mouse_position_;
    std::vector<ref_ptr<System>> systems_;
    
    Suffer::ref_ptr<Suffer::SystemRender> render_system_;
    Suffer::ref_ptr<Suffer::SystemTransform> transform_system_;

		struct Data;
		Data* data_;

	};

  // ----------------------------------------------------------------------- //

} // End of Suffer namespace

#endif // __SUFFER_MANAGER_H__
