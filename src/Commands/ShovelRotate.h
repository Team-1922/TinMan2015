#ifndef ShovelRotate_H
#define ShovelRotate_H

#include "../CommandBase.h"
#include "WPILib.h"

class ShovelRotate: public CommandBase
{
private:
	double m_setPoint;
public:
	ShovelRotate(double setPoint);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
