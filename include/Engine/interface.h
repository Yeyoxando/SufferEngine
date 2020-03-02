/*
 * Author: Pablo Bano Benito <banyobe@esat-alumni.com>
 * Date: 10-12-2019
 * Interface Header
 */

#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include <data_types.h>
#include <audio.h>
#include "scene.h"

 // Forward declaration for the Engine LOG
struct ExampleAppLog;

// Information for the LOG
#define _error_ "ERROR"
#define _warning_ "WARNING"
#define _information_ "INFO"
#define _engine_ "ENGINE"
#define _audio_ "AUDIO"
#define _debug_ "DEBUG"

namespace Suffer {
	class Interface {

	public:
		Interface();
		~Interface();

		// Deleted functions
		Interface(const Interface&) = delete;
		Interface& operator=(const Interface&) = delete;

		void Init();
		void Update();
		void Render();
		void End();

	private:

		// Tools
		void DrawMenuBar();
		void CreateDock(bool* p_open);
		void ResetDock();
		void OpenWindows();
		void ChangeEditorStyle();

		// Engine Interface Structure
		void Hierarchy(Scene* current_scene_); // Hierarchy window
		void Log();                            // LOG engine window
		void Inspector();                      // GameObjects inspector
		void Project();                        // Project folder
		void Lighting(Scene* current_scene);   // Lights customization

    /**
     * @brief: Processes the sound passed by parameter in the interface
     * @param: the audio source that will be processed.
     */
		void Audio(Audio3D* sound);

    /**
     * @brief: render the texture in the Game window in the interface
     * @param: the texture that will be rendered
     */
		void Game(s32 tex);

		// Windows that can be opened
		void Options();

		void SearchChilds(u16 index, GameObject* go);

		enum InterfaceStyle {
      kInterfaceStyle_Invalid = -1,
      kInterfaceStyle_Default,
      kInterfaceStyle_Dark,
      kInterfaceStyle_Red,
      kInterfaceStyle_White,
      kInterfaceStyle_RayTeak,
      kInterfaceStyle_Commodore64,
		};

		// Style Customization

	public:
		InterfaceStyle style_;
		static ExampleAppLog log;

	private:

		const char* styles[5] = {
			"Suffer Default",
			"Dark",
			"Red",
			"White",
			"RayTeak"
		};

    const char* lights[3] = {
      "Directional",
      "Point",
      "Spot"
    };

    const char* geometries[4] = {
			"Triangle",
			"Quad",
			"Cube",
			"Sphere"
    };

		struct Data;
		Data* _ptr;

		// Bools (for the windows)
		bool options_window_;
		bool is_log_opened_;
		bool is_hierarchy_opened_;
		bool is_inspector_opened_;
		bool is_project_window_opened_;
		bool is_game_window_opened_;
		bool is_audio_window_opened_;
		bool is_lighting_window_opened_;

		u32 game_object_selected_;
		u32 game_objects_id_;

	};

}

#endif // __INTERFACE_H__
