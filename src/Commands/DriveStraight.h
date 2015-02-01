#ifndef DriveStraight_H
#define DriveStraight_H

#include "../CommandBase.h"
#include "WPILib.h"

class DriveStraight: public CommandBase
{
public:
	DriveStraight();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
