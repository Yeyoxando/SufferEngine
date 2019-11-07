/*
 * Author: Diego Ochando Torres <ochandoto@esat-alumni.com>
 * Date: 15-10-2019
 * Command Header
 */

#ifndef __COMMAND_H__
#define __COMMAND_H__

#include <referenced.h>

using namespace Suffer;

// --------------------------------------------------- //

class Command : public virtual Referenced {

public: 
	virtual void Execute() const = 0;

	enum CommandType {
		kRender = 0,
		kAudio = 1,
		kNONE = 20 // MAX for enum.
	};

	CommandType GetCommandType() const { return cmd_type_; }
protected:
	CommandType cmd_type_;
	
	Command();
	virtual ~Command();
};

// --------------------------------------------------- //

#endif // __COMMAND_H__
