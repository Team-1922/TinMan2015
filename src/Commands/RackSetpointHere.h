#ifndef RackSetpointHere_H
#define RackSetpointHere_H

#include "../CommandBase.h"
#include "WPILib.h"

class RackSetpointHere: public CommandBase
{
public:
	RackSetpointHere();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
