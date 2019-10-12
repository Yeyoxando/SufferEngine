#ifndef __DRAWABLE_H__
#define __DRAWABLE_H__

#include <command.h>

class Drawable : public Command {

public:
	Drawable();
	~Drawable();

protected:
	virtual void Execute() override;

};

#endif // __DRAWABLE_H__
