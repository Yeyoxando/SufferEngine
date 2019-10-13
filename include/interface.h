/*
 * Author: Pablo Bano Benito <banyobe@esat-alumni.com>
 * Date: 10-12-2019
 * Interface Header
 */

#ifndef __INTERFACE_H__
#define __INTERFACE_H__

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
	void Console();
	void Inspector();
	void Project();
	void Game();

	// Windows that can be opened
	void Options();

	enum InterfaceStyle {
		kDefault = 0,
		kDark,
		kWhite,
		kRayTeak,
		kCommodore64,
		kNONE = 20
	};

	// Style Customization
	InterfaceStyle style_;

	const char* styles[4] = {
		"Suffer Default",
		"Dark",
		"White",
		"RayTeak"
	};

	// Bools (for the windows)
	bool options_window_;

};

#endif // __INTERFACE_H__
