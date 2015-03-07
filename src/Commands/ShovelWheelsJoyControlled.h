#ifndef ShovelWheelsJoyControlled_H
#define ShovelWheelsJoyControlled_H

#include "../CommandBase.h"
#include "WPILib.h"

class ShovelWheelsJoyControlled: public CommandBase
{
public:
	ShovelWheelsJoyControlled();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
