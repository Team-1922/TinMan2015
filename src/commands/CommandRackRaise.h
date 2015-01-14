#ifndef COMMAND_RACK_RAISE_H
#define COMMAND_RACK_RAISE_H

#include "../CommandBase.h"
#include "WPILib.h"

class CommandRackRaise: public CommandBase
{
public:
	CommandRackRaise();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};


#endif
