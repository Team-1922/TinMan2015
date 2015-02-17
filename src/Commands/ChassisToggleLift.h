#ifndef ChassisToggleLift_H
#define ChassisToggleLift_H

#include "../CommandBase.h"
#include "WPILib.h"

class ChassisToggleLift: public CommandBase
{
public:
	ChassisToggleLift();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
