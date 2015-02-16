/*
 * RobotMap.h
 *
 *  Created on: Jan 14, 2015
 *      Author: Kevin
 */

#ifndef ROBOTMAP_H_
#define ROBOTMAP_H_

#include "WPILib.h"

//uncomment this to use the locations from the test robot
//#define TEST_ROBOT


#ifdef TEST_ROBOT

#include <cmath>
namespace RobotMap
{
	namespace Controls
	{
		//the locations of the controllers and joysticks
		const int driverJoy1 = 0;
		const int driverJoy2 = 1;
		const int operatorJoy = 2;
		const int controller = 3;

		const int deployRack = 3;
		const int retractRack = 4;


		//these two MUST add up to 1.0f
		const float throttleFactor = 0.8f;//how much the throttle affects speed
		const float stearingFactor = 0.2f;//how much stearing direction affects speed
	}

	namespace Rack
	{
		//the angles of each of the positions in degrees
		const float extendAngle = 135;
		const float raiseAngle  = 90;
		const float flatAngle   = 0;

		//the number of turns
		const float potentiometerTurnCount 	= 0.75f;

		//the minimum bound of potentiometer
		const float potentiometerMinVal 	= 145.776f;

		//the maximum bound of potentiometer
		const float potentiometerMaxVal 	= 223.2f;

		//the range of the two above values
		const float potentiometerRange		= fabs(potentiometerMaxVal - potentiometerMinVal);

		//the location of the rack motor
		const int   motorLoc = 4;
		const int   potentiometerLoc = 1;

		//encoder locations (There are two of them)
		const int encoderLoc1 = 1;//TODO: what are these
		const int encoderLoc2 = 2;

		//this is the type of encoder, maybe 4X is not what we want, but for now
		const Encoder::EncodingType encodingType = Encoder::k4X;

		//DistancePerPulse; this is directly related to the gearing ratio, potentially if we
		//	want to account for that in our usage
		const float encoderDPP = 0;//we are not currently using this

		//this is an encoder value to tell the robot when to consider the motor "stopped" when the speed is so low
		const float encoderMinRate = 1;//RPM
	}

	//the drive train constants
	namespace DriveTrain
	{

		//the locations of the motors
		const int frontLeft  = 0;
		const int rearLeft   = 1;
		const int frontRight = 2;
		const int rearRight  = 3;

	}

	namespace Shovel
	{
		//the angles of each of the positions in degrees
		const float dumpAngle   = 90;  // dump onto the rack
		const float groundAngle = 0;   // when the shovel is flat on the ground in front of the robot
		const float humanAngle  = 45;  // target angle of the shovel for collecting from the human station
		const float liftAngle   = -30; // angle below the ground, used for when the robot is trying to place the totes on the stack and needs to adjust the flat to below the ground plane
		const float storeAngle  = 135; // for putting the shovel away (tucked along the side of the robot)

		//the motor location for the shovel
		const int motorLoc = 5;

		//the number of turns
		const float potentiometerTurnCount 	= 0.75f;//TODO: get real values for a different potentiometer

		//the minimum bound of potentiometer
		const float potentiometerMinVal 	= 145.776f;

		//the maximum bound of potentiometer
		const float potentiometerMaxVal 	= 223.2f;

		//the range of the two above values
		const float potentiometerRange		= fabs(potentiometerMaxVal - potentiometerMinVal);

		const int   potentiometerLoc = 1;

		const int	solenoidId = 1;

	}
}

#else

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

		extern const int potTurnCoun;
		extern const int potDegree;
		extern const float potDegreeOffset; //degrees off horizontal, aka all the way forwards


		//GEARING: 480:1  TODO:?
		extern const int gearing;

		//shovel rpm (Free)
		extern const int shovelMotorRPM;

		extern const int shovelMotorMaxSpeed;//degrees/s
	}

	namespace Rack
	{
	//TODO: remember this should be 5
		extern const int rackPivotMotor;//CIM Motor (PWM)
		extern const int rackExtendRack;//(PWM)
		extern const int rackClawSolenoid;//(SOL)
		extern const int rackMotLimSwitch;//(DI)
		extern const int potentiometer;//(AI)
		//const int rackEncChannelA = 6;//(DI)
		//const int rackEncChannelB = 7;//(DI)

		//GEARING: 81000:264:
		extern const int gearing;

		//the speed of the motor (Free)
		extern const float rackMotorRPM;

		extern const int rackMotorMaxSpeed;//degrees/s

		extern const int potTurnCount;
		extern const int potDegree;
		extern const float potDegreeOffset; //degrees off horizontal, aka all the way forwards


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
#endif

#endif /* ROBOTMAP_H_ */
