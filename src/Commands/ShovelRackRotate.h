#ifndef ShovelRackRotate_H
#define ShovelRackRotate_H

#include "../CommandBase.h"
#include "WPILib.h"

class ShovelRackRotate: public CommandBase
{
private:
	double m_setPoint;

public:
	ShovelRackRotate(double setPoint);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
