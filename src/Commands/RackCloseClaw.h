#ifndef RackCloseClaw_H
#define RackCloseClaw_H

#include "../CommandBase.h"
#include "WPILib.h"

class RackCloseClaw: public CommandBase
{
public:
	RackCloseClaw();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
