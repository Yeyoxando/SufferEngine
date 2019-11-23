/*
 * Author: Diego Ochando Torres <ochandoto@esat-alumni.com>
 * Date: 15-10-2019
 * Clear Command Header
 */

#ifndef __CLEAR_H__
#define __CLEAR_H__

#include "command.h"
#include "vector4.h"

namespace Suffer {

  // ----------------------------------------------------------------------- //

  /**
   * @brief: Command to clear screen
   */
	class Clear : public Command {

	public:
		Clear();
		~Clear();

    /**
     * @brief: Set color to clear screen.
     * @param: clear color.
     */
		void SetClearColor(mathmorra::Vector4 color) { color_ = color; }

	protected:

    /**
     * @brief: Executes the command to clear the screen
     */
		virtual void Execute() const override;


	private:
		mathmorra::Vector4 color_;

  };

  // ----------------------------------------------------------------------- //

} // End of Suffer namespace

#endif // __CLEAR_H__
