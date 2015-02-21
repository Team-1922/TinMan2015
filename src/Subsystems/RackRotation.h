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
	OzPotentiometer* m_pPot;
	//OzLimitSwitch*   m_pLimitBackStop;

	OzLimitSwitch*    m_pLimitRotationForward;
	OzLimitSwitch*    m_pLimitRotationBackward;


public:
	RackRotation();
	~RackRotation();

	double ReturnPIDInput();
	void UsePIDOutput(double output);
	void InitDefaultCommand();


	// current Potentiometer reading
	float GetPotVoltage();

	//get the limit switch state for the practice bot
	bool GetLimRotationForward(){return m_pLimitRotationForward->Get();}
	bool GetLimRotationBackward(){return m_pLimitRotationBackward->Get();}


	//tick the potentiometer
	void TickPotentiometer();
};

#endif
