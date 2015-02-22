#ifndef ShovelRotation_H
#define ShovelRotation_H

#include "Commands/PIDSubsystem.h"
#include "WPILib.h"
#include "../OzPotentiometer.h"
#include "../OzLimitSwitch.h"

class ShovelRotation: public PIDSubsystem
{
	//the motor that rotates the shovel
	SpeedController* m_pMotor;
	OzPotentiometer* m_pPot;
	//OzLimitSwitch*   m_pShovelPivotLim;

	OzLimitSwitch* m_pLimitRotationForward;
	OzLimitSwitch* m_pLimitRotationBackward;

public:
	ShovelRotation();
	~ShovelRotation();

	double ReturnPIDInput();
	void UsePIDOutput(double output);
	void InitDefaultCommand();

	// current Potentiometer reading
	float GetPotVoltage();

	//get the limit switch state for the practice bot
	//bool GetBackLimSwitch(){return m_pShovelPivotLim->Get();}
	bool GetLimRotationForward(){return m_pLimitRotationForward->Get();}
	bool GetLimRotationBackward(){return m_pLimitRotationBackward->Get();}

	//tick the potentiometer
	void TickPotentiometer();
};

#endif
