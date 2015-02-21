/*
 * RobotMap.h
 *
 *  Created on: Jan 14, 2015
 *      Author: Kevin
 */

#ifndef ROBOTMAP_H_
#define ROBOTMAP_H_

#include "WPILib.h"

enum OperatorMode
{
	kRack = 0,
	kShovel = 1,
	kBoth = 2
};

namespace RobotMap
{
	namespace Controls
	{
		//the locations of the controllers and joysticks
		extern const int driverJoy1;
		extern const int driverJoy2;
		extern const int operatorJoy;
		extern const int controller;

		//these two MUST add up to 1.0f
		extern const float throttleFactor;//how much the throttle affects speed
		extern const float stearingFactor;//how much stearing direction affects speed

		//the controls on the operator joystick
		//TODO: get these optimal positions

		//these extend or retract the rack, NOTE: these are to be held to adjust the rack
		extern const int extendRack;
		extern const int retractRack;

		//these are for selecting which subsystem the joystick is controlling
		extern const int rackJoyControlled;
		extern const int shovelJoyControlled;
		extern const int rackShovelCombined;

		//controls for changing the width of the shovel and rack
		extern const int shovelWidthToggle;
		extern const int rackClawToggle;
		extern const int chassisLiftToggle;

		//the current mode
		extern OperatorMode currOpMode;// = kRack;


	}

	//the drive train constants
	namespace DriveTrain
	{

		//the locations of the motors
		extern const int frontLeft;
		extern const int rearLeft;
		extern const int frontRight;
		extern const int rearRight;

		//motor encoders
		extern const int leftEncA;
		extern const int leftEncB;
		extern const int rightEncA;
		extern const int rightEncB;


		namespace Encoder
		{
			//information to give encoders

			//not quite sure if this is right, but this is what was used in the exampled
			extern const ::Encoder::EncodingType encodingType;

			//the number of encoder pulses per rotation TODO:
			extern const int pulsesPerRotation;

			//GEARING TODO:
			extern const int gearing;//this is if the encoder is attached to the wheel axle

			//the gearing of the encoders (I will assume both gearings are the same), converts pulses to RPM
			//GEARING IS AS FOLLOWED TODO:
			extern const float distancePerPulse;
		}

	}

	namespace Chassis
	{
		//solnoids for lifting the chassis up
		extern const int chassisLiftSol;//SOL
	}

	namespace Shovel
	{
		extern const int potentiometer;//potentiometer(AI)
		extern const int shovelPivotMotor;//(4)Motor (PWM)
		extern const int shovelWideRight;//limit switch (DI)
		extern const int shovelWideLeft;//limit switch (DI)
		extern const int shovelPivotLimSwitch;//limit switch (DI)
		extern const int shovelWidthSol;//solenoid (SOL)
		extern const int shovelLimitRotationForward;//(DI)
		extern const int shovelLimitRotationBackward;//(DI)


		extern const int potTurnCoun;
		extern const int potDegree;
		extern const float potDegreeOffset; //degrees off horizontal, aka all the way forwards
		extern const float voltageStack; // voltage for when the shovel is in position for stacking
		extern const float voltageFlat; // voltage for when the shovel is horizontal
		extern const float voltageDump; // voltage for when the shovel is placing totes on the rack
		extern const float voltageStore; // voltage for when the shovel is in the stored position (all the way back)


		//the voltage difference in a 90 degree region; used in slave control TODO
		extern const float pot90DegreeVoltage;

		//GEARING: 480:1  TODO:?
		extern const int gearing;

		//shovel rpm (Free)
		//extern const int shovelMotorRPM;

		//extern const int shovelMotorMaxSpeed;//degrees/s
	}

	namespace Rack
	{
	//TODO: remember this should be 5
		extern const int rackPivotMotor;//CIM Motor (PWM)
		extern const int rackExtendRack;//(PWM)
		extern const int rackClawSolenoid;//(SOL)
		extern const int rackMotLimSwitchExtended;//(DI)
		extern const int rackMotLimSwitchRetracted;//(DI)
		extern const int rackLimitRotationForward;//(DI)
		extern const int rackLimitRotationBackward;//(DI)
		extern const int potentiometer;//(AI)
		//const int rackEncChannelA = 6;//(DI)
		//const int rackEncChannelB = 7;//(DI)

		//GEARING: 81000:264:
		extern const int gearing;

		//the speed of the motor (Free)
		//extern const float rackMotorRPM;

		//extern const int rackMotorMaxSpeed;//degrees/s

		extern const int potTurnCount;
		extern const int potDegree;
		extern const float potDegreeOffset; //degrees off horizontal, aka all the way forwards

		extern const float voltageStack; // voltage for when the shovel is in position for stacking
		extern const float voltageVertical; // voltage for when the shovel is horizontal
		extern const float voltageDump; // voltage for when the shovel is placing totes on the rack
		extern const float voltagePickContainer; // voltage for when the shovel is in the stored position (all the way back)



		/*namespace Encoder
		{
			//this contains information for the encoder to get useful information i.e. degrees per second

			//not quite sure if this is right, but this is what was used in the example
			const ::Encoder::EncodingType encodingType = ::Encoder::k4X;

			//the number of encoder pulses per rotation TODO:
			const int pulsesPerRotation = 500;

			//This converts the pulses to degrees per second
			const float distancePerPulse = 1.0f/float(gearing*pulsesPerRotation);
		}*/
	}

	//the maximum percentage change of the velocity of the rack or shovel in a cycle
	extern const float maxRPMDelta;//1.5%

	//polling rate of the potentiometer
	extern const float minPollWait;//0.05 seconds

}

#endif /* ROBOTMAP_H_ */
