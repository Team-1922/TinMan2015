#ifndef COMMANDEXTEND_H
#define COMMANDEXTEND_H

#include "../CommandBase.h"
#include "WPILib.h"

class CommandExtend: public CommandBase
{
public:
	CommandExtend();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};


#endif
