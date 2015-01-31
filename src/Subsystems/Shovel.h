#ifndef Shovel_H
#define Shovel_H

#include "Commands/Subsystem.h"
#include "../OzPotentiometer.h"
#include "../RobotMap.h"
#include "WPILib.h"

class Shovel: public Subsystem
{
private:

	SpeedController* m_pMotor;
	OzPotentiometer* m_pPotentiometer;
	Solenoid m_solenoid;

	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	Shovel();
	~Shovel();

	void InitDefaultCommand();

	void  doNothing(){}
	float getPotentiometer();
	float getPotentiometerRaw();
	void  setMotor(float val);
	float getAngle();

	float degreesOffOfDump()   { return RobotMap::Shovel::dumpAngle   - getAngle(); }
	float degreesOffOfGround() { return RobotMap::Shovel::groundAngle - getAngle(); }
	float degreesOffOfHuman()  { return RobotMap::Shovel::humanAngle  - getAngle(); }
	float degreesOffOfLift()   { return RobotMap::Shovel::liftAngle   - getAngle(); }
	float degreesOffOfStore()  { return RobotMap::Shovel::storeAngle  - getAngle(); }



	void extendShelf() { setSolenoid(true); }
	void retractShelf() { setSolenoid(false); }

private:
	void setSolenoid(bool setting);

	//void retractShelf();
	//void extendShelf();

};

#endif
