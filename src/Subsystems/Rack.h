#ifndef RACK_MOTOR_H
#define RACK_MOTOR_H

#include "../OzPotentiometer.h"
#include "Commands/Subsystem.h"
#include "WPILib.h"

class Rack: public Subsystem
{

private:
	//the motor that rotates the rack
	SpeedController* m_pRotate;
	Encoder* 		 m_pEncoder;

	//the motor that extends and retracts the rack
	SpeedController* m_pExtendRetract;

	Solenoid*        m_pClaw;
	DigitalInput*    m_pLimitBackStop;

public:
	Rack();
	~Rack();

	void InitDefaultCommand();

	void doNothing(){}

	/*
	 * Motor and Limit Switch Accessor Functions
	 */

	void setMotor(float level);
	void setMotorRate(float degPerSecond);
	float getMotor(){return m_pRotate->Get();}

	void setExtendMotor(float level);
	float getExtendMotor(){return m_pExtendRetract->Get();}

	bool getBackStop(){return m_pLimitBackStop->Get();}

	void setClaw(bool on){return m_pClaw->Set(on);}
	bool getClaw(){return m_pClaw->Get();}

	/*
	 * Encoder Control Functions
	 */
	void resetEncoder(){m_pEncoder->Reset();}

	/*
	 * Encoder Accessor Functions
	 */

	//NOTE: to get this in degrees or degrees/s use getEncDistance and getEncRate

	double	getEncCount()		{return double(m_pEncoder->Get());  		}
	int		getEncRawCount()	{return m_pEncoder->GetRaw();				}
	double 	getEncDistance()	{return m_pEncoder->GetDistance();			}
	double 	getEncRate()		{return m_pEncoder->GetRate();				}
	bool 	getEncDirection()	{return m_pEncoder->GetDirection();			}
	bool 	getEncStopped()		{return m_pEncoder->GetStopped();			}


};

#endif
