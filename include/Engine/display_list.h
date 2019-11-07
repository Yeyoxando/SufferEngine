/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 11-02-2019
* DisplayLists Header
* Base structure extracted from px_render.h (Pplux)
*/

#ifndef __DISPLAY_LIST_H__
#define __DISPLAY_LIST_H__

#include <referenced.h>
#include <audio.h>
#include <ref_ptr.h>
#include <command.h>
#include <vector>

namespace Suffer {

class DisplayList : public Referenced {
	friend class RenderManager;

public:
	enum DisplayListType {
		kDisplayListType_Render = 0,
		kDisplayListType_Audio = 1,
		kDisplayListType_NONE = 20 // MAX for enum.
	};

	// Constructors
	DisplayList();
	~DisplayList();
	
	// Copy-Constructors
	DisplayList(const DisplayList&) = delete;
	DisplayList(DisplayList&& d)
		: dl_commands_(d.dl_commands_) {
		d.dl_commands_.clear();
		d.dl_type_ = kDisplayListType_NONE;
	}
	DisplayList& operator=(DisplayList&& d);
	
	// DL Functions
	void reset();
	void clear();
	u32 size();

	void SetDisplayListType(DisplayListType dl_type);
	DisplayListType GetDisplayListType();

	void addCommand(const ref_ptr<Command> cmd);


private:
	DisplayListType dl_type_;
	std::vector<ref_ptr<Command>> dl_commands_;

};

}
#endif // __DISPLAY_LIST_H__
