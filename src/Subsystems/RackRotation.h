#ifndef RackRotation_H
#define RackRotation_H

#include "Commands/PIDSubsystem.h"
#include "WPILib.h"
#include "../OzPotentiometer.h"
#include "../OzLimitSwitch.h"

class RackRotation: public PIDSubsystem
{

private:
	//the motor that rotates the rack
	SpeedController* m_pMotor;
	AnalogPotentiometer* m_pPot;
	//OzLimitSwitch*   m_pLimitBackStop;

#ifndef COMP_BOT
	OzLimitSwitch*    m_pLimitRotationForward;
	OzLimitSwitch*    m_pLimitRotationBackward;
#endif

public:
	RackRotation();
	~RackRotation();

	double ReturnPIDInput();
	void UsePIDOutput(double output);
	void InitDefaultCommand();


	// current Potentiometer reading
	float GetPotVoltage();

#ifndef COMP_BOT
	//get the limit switch state for the practice bot
	bool GetLimRotationForward(){return m_pLimitRotationForward->Get();}
	bool GetLimRotationBackward(){return m_pLimitRotationBackward->Get();}
#endif

	//tick the potentiometer
	void TickPotentiometer();
};

#endif
