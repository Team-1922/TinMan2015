#ifndef SwitchJoyRack_H
#define SwitchJoyRack_H

#include "../CommandBase.h"
#include "WPILib.h"

class SwitchJoyRack: public CommandBase
{
public:
	SwitchJoyRack();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
