#ifndef RackOpenClaw_H
#define RackOpenClaw_H

#include "../CommandBase.h"
#include "WPILib.h"

class RackOpenClaw: public CommandBase
{
public:
	RackOpenClaw();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
