#ifndef WasteTime_H
#define WasteTime_H

#include "../CommandBase.h"
#include "WPILib.h"

//this is just a wait command
class WasteTime: public CommandBase
{
public:
	WasteTime(float howMuch);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
