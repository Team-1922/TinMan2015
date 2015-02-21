#ifndef ShovelRotation_H
#define ShovelRotation_H

#include "Commands/PIDSubsystem.h"
#include "WPILib.h"
#include "../OzPotentiometer.h"

class ShovelRotation: public PIDSubsystem
{
	//the motor that rotates the shovel
	SpeedController* m_pMotor;
	OzPotentiometer* m_pPot;

	DigitalInput* m_pShovelLimitRotationForward;
	DigitalInput* m_pShovelLimitRotationBackward;

public:
	ShovelRotation();
	~ShovelRotation();

	double ReturnPIDInput();
	void UsePIDOutput(double output);
	void InitDefaultCommand();

	// current Potentiometer reading
	float GetPotVoltage();

	//tick the potentiometer
	void TickPotentiometer();
};

#endif
