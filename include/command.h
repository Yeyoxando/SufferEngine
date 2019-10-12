#ifndef __COMMAND_H__
#define __COMMAND_H__

class Command {

public: 
	Command();
	~Command();

	virtual void Execute() = 0;

};

#endif // __COMMAND_H__
