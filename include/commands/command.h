/*
 * Author: Diego Ochando Torres <ochandoto@esat-alumni.com>
 * Date: 15-10-2019
 * Command Header
 */

#ifndef __COMMAND_H__
#define __COMMAND_H__

#include <Memory_Management/referenced.h>

namespace Suffer {

  // ----------------------------------------------------------------------- //

  /**
   * @brief: parent class for inherit and create new Commands for Render or Audio.
   */
	class Command : public virtual Referenced {

	public:
    /**
     * @brief: Method to override and create custom commands with different behaviors.
     */
		virtual void Execute() const = 0;

    /**
     * @brief: identifies the kind of the command.
     */
		enum CommandType {
			kCommandType_Invalid = -1,
			kCommandType_Render = 0,
			kCommandType_Audio = 1,
		};


		CommandType GetCommandType() const { return cmd_type_; }

	protected:
		CommandType cmd_type_;

		Command();
		virtual ~Command();

  };

  // ----------------------------------------------------------------------- //

} // End of Suffer namespace

#endif // __COMMAND_H__
