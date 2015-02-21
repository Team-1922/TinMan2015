#ifndef RackExtend_H
#define RackExtend_H

#include "../CommandBase.h"
#include "WPILib.h"

class RackExtend: public CommandBase
{
public:
	RackExtend();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
