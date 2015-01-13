#ifndef COMMANDFLAT_H
#define COMMANDFLAT_H

#include "../CommandBase.h"
#include "WPILib.h"

class CommandFlat: public CommandBase
{
public:
	CommandFlat();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};


#endif
