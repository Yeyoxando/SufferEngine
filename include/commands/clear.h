/*
 * Author: Diego Ochando Torres <ochandoto@esat-alumni.com>
 * Date: 15-10-2019
 * Clear Command Header
 */

#ifndef __CLEAR_H__
#define __CLEAR_H__

#include <command.h>
#include "vector4.h"
#include <glm.hpp>

// --------------------------------------------------- //

namespace Suffer {

	class Clear : public Command {

	public:
		Clear();
		~Clear();

		void SetClearColor(mathmorra::Vector4 color) { color_ = color; }

	protected:
		virtual void Execute() const override;


	private:
		mathmorra::Vector4 color_;
	};

}
// --------------------------------------------------- //

#endif // __CLEAR_H__
