#ifndef CommandShovelDump_H
#define CommandShovelDump_H

#include "../CommandBase.h"
#include "WPILib.h"

class CommandShovelDump: public CommandBase
{
public:
	CommandShovelDump();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
