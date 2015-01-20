#ifndef CommandDriveStraight_H
#define CommandDriveStraight_H

#include "../CommandBase.h"
#include "WPILib.h"

class CommandDriveStraight: public CommandBase
{
public:
	CommandDriveStraight();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
