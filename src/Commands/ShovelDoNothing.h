#ifndef ShovelDoNothing_H
#define ShovelDoNothing_H

#include "../CommandBase.h"
#include "WPILib.h"

class ShovelDoNothing: public CommandBase
{
public:
	ShovelDoNothing();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
