#ifndef ShovelJoyControlled_H
#define ShovelJoyControlled_H

#include "../CommandBase.h"
#include "WPILib.h"

class ShovelJoyControlled: public CommandBase
{
public:
	ShovelJoyControlled();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
