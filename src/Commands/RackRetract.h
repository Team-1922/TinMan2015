#ifndef RackRetract_H
#define RackRetract_H

#include "../CommandBase.h"
#include "WPILib.h"

class RackRetract: public CommandBase
{
public:
	RackRetract();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
