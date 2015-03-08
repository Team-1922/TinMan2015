#ifndef ShovelToggleGrab_H
#define ShovelToggleGrab_H

#include "../CommandBase.h"
#include "WPILib.h"

class ShovelToggleGrab: public CommandBase
{
public:
	ShovelToggleGrab();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
