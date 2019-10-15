/*
 * Author: Diego Ochando Torres <ochandoto@esat-alumni.com>
 * Date: 15-10-2019
 * Clear Command Header
 */

#ifndef __CLEAR_H__
#define __CLEAR_H__

#include <command.h>
#include <glm.hpp>

// --------------------------------------------------- //

class Clear : public Command {

public:
	Clear();
	~Clear();

	void SetClearColor(glm::vec4 color) { color_ = color; }

protected:
	virtual void Execute() override;


private:
	glm::vec4 color_;
};

// --------------------------------------------------- //

#endif // __CLEAR_H__
