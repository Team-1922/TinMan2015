#ifndef Shovel_H
#define Shovel_H

#include "Commands/Subsystem.h"
#include "../OzPotentiometer.h"
#include "../OzSolenoid.h"
#include "../OzLimitSwitch.h"
#include "../RobotMap.h"
#include "WPILib.h"

class Shovel: public Subsystem
{
private:

	//SpeedController* m_pRotate;
	//OzPotentiometer* m_pPotentiometer;
	OzSolenoid* m_pWidthSolenoid;
	OzSolenoid* m_pCollectSolenoid;

	//the wheels to suck in the tote/container
	SpeedController* m_pSuckWheelLeft;
	SpeedController* m_pSuckWheelRight;

	//DigitalInput* m_pShovelWideRight;
	//DigitalInput* m_pShovelWideLeft;


	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	Shovel();
	~Shovel();

	void InitDefaultCommand();

	//bool GetShovelWideRight(){return m_pShovelWideRight->Get();}
	//bool GetShovelWideLeft(){return m_pShovelWideLeft->Get();}

	/*
	 * Potentiometer Control
	 */

	//returns the current angle of the potentiometer relative to shovel in down (flat) position
	/*float getPotentiometer();

	//returns the speed of the shovel movement in degrees/s (signed)
	float getTurnRate();

	// this is used to get rate information from the potentiometer, call this once per cycle
	void tickPotentiometer();*/



	/*
	 * Motor Control
	 */

	/*void  setMotor(float val);
	void  setMotorRate(float degPerSecond);
	float getMotor(){return m_pRotate->Get();}*/

	/*
	 * Suck Wheel Control
	 */
	void SetSuckWheels(float val);
	void SetSuckWheelLeft(float val);
	void SetSuckWheelRight(float val);
	void RotateTote(float val);//this has the suck wheels go in different directions to rotate the tote


	/*
	 * Solenoid Control
	 */

	bool getGrabSolenoid() {return m_pWidthSolenoid->Get();}
	void setGrabSolenoid(bool on);

	bool getCollectSolenoid(){return m_pCollectSolenoid->Get();}
	void setCollectSolenoid(bool on){m_pCollectSolenoid->Set(on);}

private:

	//void retractShelf();
	//void extendShelf();

};

#endif
