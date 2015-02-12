#ifndef RackToggleClaw_H
#define RackToggleClaw_H

#include "../CommandBase.h"
#include "WPILib.h"

class RackToggleClaw: public CommandBase
{
public:
	RackToggleClaw();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
