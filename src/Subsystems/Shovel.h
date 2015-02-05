#ifndef Shovel_H
#define Shovel_H

#include "Commands/Subsystem.h"
#include "../OzPotentiometer.h"
#include "../RobotMap.h"
#include "WPILib.h"

class Shovel: public Subsystem
{
private:

	SpeedController* m_pRotate;
	AnalogPotentiometer* m_pPotentiometer;
	Solenoid* m_pWidthSolenoid;

	DigitalInput* m_pShovelWideRight;
	DigitalInput* m_pShovelWideLeft;
	DigitalInput* m_pShovelPivotLim;

	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	Shovel();
	~Shovel();

	void InitDefaultCommand();

	void  doNothing(){}
	float getPotentiometer();
	void  setMotor(float val);
	//float getAngle();

	//float degreesOffOfDump()   { return RobotMap::Shovel::dumpAngle   - getAngle(); }
	//float degreesOffOfGround() { return RobotMap::Shovel::groundAngle - getAngle(); }
	//float degreesOffOfHuman()  { return RobotMap::Shovel::humanAngle  - getAngle(); }
	//float degreesOffOfLift()   { return RobotMap::Shovel::liftAngle   - getAngle(); }
	//float degreesOffOfStore()  { return RobotMap::Shovel::storeAngle  - getAngle(); }



	void extendShelf() { setSolenoid(true); }
	void retractShelf() { setSolenoid(false); }

private:
	void setSolenoid(bool setting);

	//void retractShelf();
	//void extendShelf();

};

#endif
