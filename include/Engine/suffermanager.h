// Pablo Bano Benito <banyobe@esat-alumni.com>

#ifndef __SUFFER_MANAGER_H__
#define __SUFFER_MANAGER_H__

#include <ref_ptr.h>
#include <render_manager.h>
#include <resource_manager.h>
#include <light_manager.h>
#include <audio_manager.h>
#include <scoped_array.h>
#include "thread.h"
#include "vector2.h"
#include "input.h"
#include "system_transform.h"
#include "system_render.h"
#include "system_script.h"
#include "system_light.h"
#include "system_audio.h"
#include "system_hierarchy.h"


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
    friend class GameObject;
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

    mathmorra::Vector2 GetWindowSize();
    void SetWindowSize(int width, int height);

    bool Running();


    u32 number_of_game_objects_;

		// Subsystems
    AudioManager audio_manager_;
    InputManager input_manager_;
		RenderManager render_manager_;
		ResourceManager resource_manager_;
		LightManager light_manager_;

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

    void PreparePostproccess();

		// Threads
		ref_ptr<Thread> logic_;
		ref_ptr<Thread> input_;
		ref_ptr<Thread> audio_;

    mathmorra::Vector2 mouse_position_;
    std::vector<ref_ptr<System>> systems_;
    std::vector<ref_ptr<GameObject>> entities_;
    
    ref_ptr<SystemLight>     light_system_;
    ref_ptr<SystemAudio>     audio_system_;
    ref_ptr<SystemRender>    render_system_;
    ref_ptr<SystemScript>    script_system_;
    ref_ptr<SystemTransform> transform_system_;
    ref_ptr<SystemHierarchy> hierarchy_system_;


    //Framebuffers
    ref_ptr<ResourceManager::FrameBuffer> draw_frame_buffer_;
    ref_ptr<ResourceManager::FrameBuffer> black_white_frame_buffer_;
    ref_ptr<ResourceManager::FrameBuffer> brga_frame_buffer_;
    ref_ptr<ResourceManager::FrameBuffer> argb_frame_buffer_;
    ref_ptr<ResourceManager::FrameBuffer> rbga_frame_buffer_;
    ref_ptr<ResourceManager::FrameBuffer> hblur_frame_buffer_;
    ref_ptr<ResourceManager::FrameBuffer> inverted_colors_frame_buffer_;
    ref_ptr<ResourceManager::FrameBuffer> contrast_frame_buffer_;
    ref_ptr<ResourceManager::FrameBuffer> gbra_frame_buffer_;
    ref_ptr<ResourceManager::FrameBuffer> render_to_texture_frame_buffer_;

    s32 post_process_id_;
    
		struct Data;
		Data* data_;

	};

  // ----------------------------------------------------------------------- //

} // End of Suffer namespace

#endif // __SUFFER_MANAGER_H__
