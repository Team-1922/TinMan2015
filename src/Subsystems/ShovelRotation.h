#ifndef ShovelRotation_H
#define ShovelRotation_H

#include "Commands/PIDSubsystem.h"
#include "WPILib.h"
#include "../OzPotentiometer.h"
#include "../OzLimitSwitch.h"

#include "RobotMap.h"


class ShovelRotation: public PIDSubsystem
{
	//the motor that rotates the shovel
	SpeedController* m_pMotor;
	AnalogPotentiometer* m_pPot;
	//OzLimitSwitch*   m_pShovelPivotLim;

	DigitalInput *m_pReedLeft;
	DigitalInput *m_pReedRight;

#ifndef COMP_BOT
	OzLimitSwitch* m_pLimitRotationForward;
	OzLimitSwitch* m_pLimitRotationBackward;
#endif

public:
	ShovelRotation();
	~ShovelRotation();

	double ReturnPIDInput();
	void UsePIDOutput(double output);
	void InitDefaultCommand();

	// current Potentiometer reading
	float GetPotVoltage();

	bool GetReed();//returns true if EITHER are open (shovel is closed)

	//get the limit switch state for the practice bot
	//bool GetBackLimSwitch(){return m_pShovelPivotLim->Get();}
#ifndef COMP_BOT
	bool GetLimRotationForward(){return m_pLimitRotationForward->Get();}
	bool GetLimRotationBackward(){return m_pLimitRotationBackward->Get();}
#endif

	//tick the potentiometer
	void TickPotentiometer();
};

#endif
