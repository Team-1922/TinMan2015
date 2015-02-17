#ifndef RackPIDController_H
#define RackPIDController_H

#include "Commands/PIDSubsystem.h"
#include "WPILib.h"
#include "OzPotentiometer.h"

class RackRotation: public PIDSubsystem
{

private:
	//the motor that rotates the rack
	SpeedController* m_pMotor;
	OzPotentiometer* m_pPot;


public:
	RackRotation();
	double ReturnPIDInput();
	void UsePIDOutput(double output);
	void InitDefaultCommand();

	// current Potentiometer reading
	float GetPotVoltage();

	//tick the potentiometer
	void TickPotentiometer();
};

#endif
