#ifndef COMMAND_RACK_FLAT_H
#define COMMAND_RACK_FLAT_H

#include "../CommandBase.h"
#include "WPILib.h"

class CommandRackFlat: public CommandBase
{
public:
	CommandRackFlat();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};


#endif
