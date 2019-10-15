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
	virtual void Execute() = 0;

protected:
	Command();
	virtual ~Command();
};

// --------------------------------------------------- //

#endif // __COMMAND_H__
