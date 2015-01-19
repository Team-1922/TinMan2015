#ifndef CommandShovelDoNothing_H
#define CommandShovelDoNothing_H

#include "../CommandBase.h"
#include "WPILib.h"

class CommandShovelDoNothing: public CommandBase
{
public:
	CommandShovelDoNothing();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
