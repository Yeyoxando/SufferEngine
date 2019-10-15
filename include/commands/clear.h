/*
 * Author: Diego Ochando Torres <ochandoto@esat-alumni.com>
 * Date: 15-10-2019
 * Clear Command Header
 */

#ifndef __CLEAR_H__
#define __CLEAR_H__

#include <command.h>

// --------------------------------------------------- //

class Clear : public Command {

public:
	Clear();
	~Clear();

protected:
	virtual void Execute() override;

};

// --------------------------------------------------- //

#endif // __CLEAR_H__
