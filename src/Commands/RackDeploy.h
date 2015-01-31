#ifndef RackDeploy_H
#define RackDeploy_H

#include "../CommandBase.h"
#include "WPILib.h"

class RackDeploy: public CommandBase
{
public:
	RackDeploy();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
