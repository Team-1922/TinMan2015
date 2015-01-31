#ifndef RackJoyControlled_H
#define RackJoyControlled_H

#include "../CommandBase.h"
#include "WPILib.h"

class RackJoyControlled: public CommandBase
{
public:
	RackJoyControlled();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
