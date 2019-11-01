/*
 * Author: Pablo Bano Benito <banyobe@esat-alumni.com>
 * Date: 10-12-2019
 * Interface Header
 */

#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include <data_types.h>
#include <audio.h>

 // Forward declaration for the Engine LOG
struct ExampleAppLog;

// Information for the LOG
#define _error_ "ERROR"
#define _warning_ "WARNING"
#define _information_ "INFO"
#define _engine_ "ENGINE"
#define _audio_ "AUDIO"
#define _debug_ "DEBUG"

class Interface {

public:
	Interface();
	~Interface();

	// Deleted functions
	Interface(const Interface&) = delete;
	Interface& operator=(const Interface&) = delete;

	void Init();
	void Update();
	void End();

	private:

	// Tools
	void DrawMenuBar();
	void CreateDock(bool* p_open);
	void ResetDock();
	void OpenWindows();
	void ChangeEditorStyle();
	
	// Engine Interface Structure
	void Hierarchy();
	void Log();
	void Inspector();
	void Project();
	void Audio(Audio3D* sound);
	void Game(s8 tex);

	// Windows that can be opened
	void Options();

	enum InterfaceStyle {
		kDefault = 0,
		kDark,
		kRed,
		kWhite,
		kRayTeak,
		kCommodore64,
		kNONE = 20
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

};

#endif // __INTERFACE_H__
