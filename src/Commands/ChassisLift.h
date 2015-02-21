#ifndef ChassisLift_H
#define ChassisLift_H

#include "../CommandBase.h"
#include "WPILib.h"

class ChassisLift: public CommandBase
{
private:
	bool m_lift;
public:
	ChassisLift(bool lift);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
