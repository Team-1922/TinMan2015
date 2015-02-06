#ifndef ShovelCloseWidth_H
#define ShovelCloseWidth_H

#include "../CommandBase.h"
#include "WPILib.h"

class ShovelCloseWidth: public CommandBase
{
public:
	ShovelCloseWidth();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
