/*
* Author: Diego Ochando Torres <ochandoto@esat-alumni.com>
* Date: 11-02-2019
* DisplayLists Header
*/

#ifndef __DISPLAY_LIST_H__
#define __DISPLAY_LIST_H__

#include <referenced.h>
#include <audio.h>
#include <ref_ptr.h>
#include <command.h>
#include <vector>

namespace Suffer {

  /**
    * @brief:
    */
class DisplayList : public Referenced {
	friend class RenderManager;
  friend class AudioManager;

public:
  /**
    * @brief:
    */
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

  /**
    * @brief:
    */
	DisplayList(DisplayList&& d)
		: dl_commands_(std::move(d.dl_commands_)) {
		dl_type_ = std::move(d.dl_type_);
	}
  /**
    * @brief:
    */
	DisplayList& operator=(DisplayList&& d);
	
	// DL Functions
  /**
    * @brief:
    */
	void reset();
  /**
    * @brief:
    */
	void clear();
  /**
    * @return:
    */
	u32 size();

  /**
    * @brief:
    * @param:
    */
	void SetDisplayListType(DisplayListType dl_type);
  /**
    * @return:
    */
	DisplayListType GetDisplayListType();

  /**
    * @brief:
    * @param:
    */
	void addCommand(const ref_ptr<Command> cmd);


private:
	DisplayListType dl_type_;
	std::vector<ref_ptr<Command>> dl_commands_;

};

}
#endif // __DISPLAY_LIST_H__
