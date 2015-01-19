#ifndef CommandShovelLift_H
#define CommandShovelLift_H

#include "../CommandBase.h"
#include "WPILib.h"

class CommandShovelLift: public CommandBase
{
public:
	CommandShovelLift();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
