#ifndef ShovelJoyControlled_H
#define ShovelJoyControlled_H

#include "../CommandBase.h"
#include "WPILib.h"

class ShovelRackRotate: public CommandBase
{
private:
	double m_setPoint;

public:
	ShovelRackRotate();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
