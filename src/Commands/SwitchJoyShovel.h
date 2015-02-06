#ifndef SwitchJoyShovel_H
#define SwitchJoyShovel_H

#include "../CommandBase.h"
#include "WPILib.h"

class SwitchJoyShovel: public CommandBase
{
public:
	SwitchJoyShovel();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
