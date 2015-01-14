#ifndef COMMANDRAISE_H
#define COMMANDRAISE

#include "../CommandBase.h"
#include "WPILib.h"

class CommandRackRaise: public CommandBase
{
public:
	CommandRackRaise();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};


#endif
