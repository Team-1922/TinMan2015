#ifndef Chassis_H
#define Chassis_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "../OzSolenoid.h"

class Chassis: public Subsystem
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

	OzSolenoid* m_pLiftSolenoid;
public:
	Chassis();
	void InitDefaultCommand();

	void setSolenoid(bool on){m_pLiftSolenoid->Set(on);}
	bool getSolenoid(){return m_pLiftSolenoid->Get();}
};

#endif
