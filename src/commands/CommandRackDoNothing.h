#ifndef COMMAND_RACK_DO_NOTHING_H
#define COMMAND_RACK_DO_NOTHING_H

#include "../CommandBase.h"
#include "WPILib.h"

class CommandRackDoNothing: public CommandBase
{
public:
	CommandRackDoNothing();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
