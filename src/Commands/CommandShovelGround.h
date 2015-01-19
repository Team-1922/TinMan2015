#ifndef CommandShovelGround_H
#define CommandShovelGround_H

#include "../CommandBase.h"
#include "WPILib.h"

class CommandShovelGround: public CommandBase
{
public:
	CommandShovelGround();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
