#ifndef RACK_MOTOR_H
#define RACK_MOTOR_H

#include "../OzPotentiometer.h"
#include "Commands/Subsystem.h"
#include "WPILib.h"

class Rack: public Subsystem
{

private:
	SpeedController* m_pMotor;
	Encoder* 		 m_pEncoder;

public:
	Rack();
	~Rack();

	void InitDefaultCommand();

	void doNothing(){}
	void setMotor(float level);
	float getMotor(){return m_pMotor->Get();}

	/*
	 * Encoder Control Functions
	 */
	void resetEncoder(){m_pEncoder->Reset();}

	/*
	 * Encoder Accessor Functions
	 */

	double	getEncCount()		{return double(m_pEncoder->Get()) / 500.0;  }
	int		getEncRawCount()	{return m_pEncoder->GetRaw();				}
	//double 	getEncDistance()	{return m_pEncoder->GetDistance();	}
	double 	getEncRate()		{return m_pEncoder->GetRate()/500.0;		}
	bool 	getEncDirection()	{return m_pEncoder->GetDirection();			}
	bool 	getEncStopped()		{return m_pEncoder->GetStopped();			}


};

#endif
