#ifndef RaceDrive_H
#define RaceDrive_H

#include "../CommandBase.h"
#include "WPILib.h"

class RaceDrive: public CommandBase
{
public:
	RaceDrive();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
