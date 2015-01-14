#ifndef COMMAND_RACK_EXTEND_H
#define COMMAND_RACK_EXTEND_H

#include "../CommandBase.h"
#include "WPILib.h"

class CommandRackExtend: public CommandBase
{
public:
	CommandRackExtend();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};


#endif
