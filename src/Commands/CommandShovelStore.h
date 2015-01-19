#ifndef CommandShovelStore_H
#define CommandShovelStore_H

#include "../CommandBase.h"
#include "WPILib.h"

class CommandShovelStore: public CommandBase
{
public:
	CommandShovelStore();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
