#ifndef ShovelJoyControlled_H
#define ShovelJoyControlled_H

#include "../CommandBase.h"
#include "WPILib.h"

class RackRotate: public CommandBase
{
private:
	double m_setPoint;
	bool   m_holdPosition;
public:
	RackRotate(double setPoint, bool holdPosition = true);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
