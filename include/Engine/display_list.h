/*
* Author: Diego Ochando Torres <ochandoto@esat-alumni.com>
* Date: 11-02-2019
* DisplayLists Header
*/

#ifndef __DISPLAY_LIST_H__
#define __DISPLAY_LIST_H__

#include <vector>
#include "referenced.h"
#include "ref_ptr.h"
#include "command.h"

namespace Suffer {

  // ----------------------------------------------------------------------- //

  /**
   * @brief: List of commands to allow execution from different threads.
   */
  class DisplayList : public Referenced {
	  friend class RenderManager;
    friend class AudioManager;

  public:
    /**
     * @brief: Identifies for what its going to be used this DisplayList.
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
     * @brief: rvalue constructor to allow std::move semantics.
     */
	  DisplayList(DisplayList&& d)
		  : dl_commands_(std::move(d.dl_commands_)) {
		  dl_type_ = std::move(d.dl_type_);
	  }

    /**
     * @brief: rvalue operator= to allow std::semantics.
     */
    DisplayList& operator=(DisplayList&& d);

    void SetDisplayListType(DisplayListType dl_type);
    DisplayListType GetDisplayListType();
	
	  // DL Functions
    /**
     * @brief: leaves the DisplayList like if was created right now.
     */
	  void Reset();
    /**
     * @brief: removes all the content from the DisplayList
     */
	  void Clear();
    /**
     * @return: return number of commands that DisplayList has currently
     */
	  u32 Size();

    /**
     * @brief: Add a new command at the last position of the DisplayList
     * @param: command to add
     */
	  void AddCommand(const ref_ptr<Command> cmd);

    private:
      DisplayListType dl_type_;
      std::vector<ref_ptr<Command>> dl_commands_;

  };

  // ----------------------------------------------------------------------- //

} // End of Suffer namespace

#endif // __DISPLAY_LIST_H__
