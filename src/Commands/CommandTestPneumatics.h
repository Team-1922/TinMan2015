#ifndef CommandTestPneumatics_H
#define CommandTestPneumatics_H

#include "../CommandBase.h"
#include "WPILib.h"

class CommandTestPneumatics: public CommandBase
{
public:
	CommandTestPneumatics();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
