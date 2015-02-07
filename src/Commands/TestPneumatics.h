#ifndef TestPneumatics_com_H
#define TestPneumatics_com_H

#include "../CommandBase.h"
#include "WPILib.h"

class TestPneumatics: public CommandBase
{
public:
	TestPneumatics();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
