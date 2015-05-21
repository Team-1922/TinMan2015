#ifndef ShovelRackRotate_H
#define ShovelRackRotate_H

#include "../CommandBase.h"
#include "WPILib.h"

class ShovelRackRotate: public CommandBase
{
private:
	double m_rackSetpoint;

	float m_PrevTime = 0.0f;
	float m_PrevRackAngle = 0.0f;

public:
	ShovelRackRotate(double rackSetpoint);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
