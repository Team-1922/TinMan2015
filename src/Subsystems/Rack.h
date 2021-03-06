#ifndef RACK_MOTOR_H
#define RACK_MOTOR_H

#include "../OzPotentiometer.h"
#include "../OzSolenoid.h"
#include "../OzLimitSwitch.h"
#include "Commands/Subsystem.h"
#include "WPILib.h"

class Rack: public Subsystem
{

private:

	//the motor that extends and retracts the rack
	SpeedController* m_pExtendRetract;

	//OzSolenoid*        m_pClaw;


public:
	Rack();
	~Rack();

	void InitDefaultCommand();

	void doNothing(){}

	/*
	 * Motor and Limit Switch Accessor Functions
	 */



	void setExtendMotor(float level);
	float getExtendMotor(){return m_pExtendRetract->Get();}


	void setClaw(bool on){/*m_pClaw->Set(on);*/}
	bool getClaw(){return false;/*m_pClaw->Get();*/}

};

#endif
