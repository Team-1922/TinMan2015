#ifndef ShovelRotate_H
#define ShovelRotate_H

#include "../CommandBase.h"
#include "WPILib.h"

class ShovelRotate: public CommandBase
{
private:
	double m_setPoint;
	bool m_holdPosition;
public:
	ShovelRotate(double setPoint, bool holdPosition = true);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
