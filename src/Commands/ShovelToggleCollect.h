#ifndef ShovelToggleCollect_H
#define ShovelToggleCollect_H

#include "../CommandBase.h"
#include "WPILib.h"

class ShovelToggleCollect: public CommandBase
{
public:
	ShovelToggleCollect();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
