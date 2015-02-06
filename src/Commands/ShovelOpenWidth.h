#ifndef ShovelOpenWidth_H
#define ShovelOpenWidth_H

#include "../CommandBase.h"
#include "WPILib.h"

class ShovelOpenWidth: public CommandBase
{
public:
	ShovelOpenWidth();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
