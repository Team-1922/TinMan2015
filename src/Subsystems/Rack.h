#ifndef RACK_MOTOR_H
#define RACK_MOTOR_H

#include "../OzPotentiometer.h"
#include "../OzSolenoid.h"
#include "Commands/Subsystem.h"
#include "WPILib.h"

class Rack: public Subsystem
{

private:

	//the motor that extends and retracts the rack
	SpeedController* m_pExtendRetract;

	OzSolenoid*        m_pClaw;
	DigitalInput*    m_pLimitBackStop;

	//keeps track of the current compounded speed (see motorConstSpeed for more information)
	float m_speedCompounded = 0.0f;

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

	bool getBackStop(){return m_pLimitBackStop->Get();}

	void setClaw(bool on){return m_pClaw->Set(on);}
	bool getClaw(){return m_pClaw->Get();}

};

#endif
