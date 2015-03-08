#ifndef ShovelSetCollect_H
#define ShovelSetCollect_H

#include "../CommandBase.h"
#include "WPILib.h"

class ShovelSetCollect: public CommandBase
{
	bool m_on;
public:
	ShovelSetCollect(bool on);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
