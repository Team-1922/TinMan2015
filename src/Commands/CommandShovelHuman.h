#ifndef CommandShovelHuman_H
#define CommandShovelHuman_H

#include "../CommandBase.h"
#include "WPILib.h"

class CommandShovelHuman: public CommandBase
{
public:
	CommandShovelHuman();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
