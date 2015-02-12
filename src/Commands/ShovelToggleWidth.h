#ifndef ShovelToggleWidth_H
#define ShovelToggleWidth_H

#include "../CommandBase.h"
#include "WPILib.h"

class ShovelToggleWidth: public CommandBase
{
public:
	ShovelToggleWidth();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
