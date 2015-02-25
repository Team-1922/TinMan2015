#ifndef ShovelRackRotate_H
#define ShovelRackRotate_H

#include "../CommandBase.h"
#include "WPILib.h"

class ShovelRackRotate: public CommandBase
{
private:
	double m_shovelSetpoint;
	double m_rackSetpoint;

public:
	ShovelRackRotate(double shovelSetpoint, double rackSetpoint);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
