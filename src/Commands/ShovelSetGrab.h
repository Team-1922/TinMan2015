#ifndef ShovelSetGrab_H
#define ShovelSetGrab_H

#include "../CommandBase.h"
#include "WPILib.h"

class ShovelSetGrab: public CommandBase
{
	bool m_on;
public:
	ShovelSetGrab(bool on);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
