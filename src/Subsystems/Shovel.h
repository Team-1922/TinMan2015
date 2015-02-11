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
	OzPotentiometer* m_pPotentiometer;
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

	/*
	 * Potentiometer Control
	 */

	//returns the current angle of the potentiometer relative to shovel in down (flat) position
	float getPotentiometer();

	//returns the speed of the shovel movement in degrees/s (signed)
	float getTurnRate();

	// this is used to get rate information from the potentiometer, call this once per cycle
	void tickPotentiometer();



	/*
	 * Motor Control
	 */

	void  setMotor(float val);
	void  setMotorRate(float degPerSecond);


	/*
	 * Solenoid Control
	 */

	void extendShelf() { setSolenoid(true); }
	void retractShelf() { setSolenoid(false); }

private:
	void setSolenoid(bool setting);

	//void retractShelf();
	//void extendShelf();

};

#endif
