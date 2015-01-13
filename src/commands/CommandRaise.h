#ifndef COMMANDRAISE_H
#define COMMANDRAISE

#include "../CommandBase.h"
#include "WPILib.h"

class CommandRaise: public CommandBase
{
public:
	CommandRaise();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};


#endif
