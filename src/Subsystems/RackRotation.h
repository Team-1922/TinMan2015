#ifndef RackRotation_H
#define RackRotation_H

#include "Commands/PIDSubsystem.h"
#include "WPILib.h"
#include "../OzPotentiometer.h"

class RackRotation: public PIDSubsystem
{

private:
	//the motor that rotates the rack
	SpeedController* m_pMotor;
	OzPotentiometer* m_pPot;

	DigitalInput*    m_pLimitRotationForward;
	DigitalInput*    m_pLimitRotationBackward;


public:
	RackRotation();
	~RackRotation();

	double ReturnPIDInput();
	void UsePIDOutput(double output);
	void InitDefaultCommand();


	// current Potentiometer reading
	float GetPotVoltage();

	//tick the potentiometer
	void TickPotentiometer();
};

#endif
