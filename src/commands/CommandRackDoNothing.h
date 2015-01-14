#ifndef CommandRackDoNothing_H
#define CommandRackDoNothing_H

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
