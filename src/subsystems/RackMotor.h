#ifndef RACK_MOTOR_H
#define RACK_MOTOR_H

#include "../OzPotentiometer.h"
#include "Commands/Subsystem.h"
#include "WPILib.h"

class RackMotor: public Subsystem
{

private:
	SpeedController* m_pMotor;
	OzPotentiometer* m_pPotentiometer;
	Encoder* 		 m_pEncoder;

public:
	RackMotor();
	~RackMotor();

	void InitDefaultCommand();

	void doNothing(){}
	void setMotor(float level);
	float getMotor(){return m_pMotor->Get();}
	float getPotentiometer();
	float getPotentiometerRaw();

	/*
	 * Encoder Control Functions
	 */

	void resetEncoder(){m_pEncoder->Reset();}

	/*
	 * Encoder Accessor Functions
	 */

	int 	getEncCount()		{return m_pEncoder->Get();			}
	int		getEncRawCount()	{return m_pEncoder->GetRaw();		}
	double 	getEncDistance()	{return m_pEncoder->GetDistance();	}
	double 	getEncRate()		{return m_pEncoder->GetRate();		}
	bool 	getEncDirection()	{return m_pEncoder->GetDirection();	}
	bool 	getEncStopped()		{return m_pEncoder->GetStopped();	}


};

#endif
