#ifndef SwitchJoyCombined_H
#define SwitchJoyCombined_H

#include "../CommandBase.h"
#include "WPILib.h"

class SwitchJoyCombined: public CommandBase
{
public:
	SwitchJoyCombined();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
