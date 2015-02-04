/*
 * RobotMap.h
 *
 *  Created on: Jan 14, 2015
 *      Author: Kevin
 */

#ifndef ROBOTMAP_H_
#define ROBOTMAP_H_

#include <cmath>

//uncomment this to use the locations from the test robot
//#define TEST_ROBOT


#ifdef TEST_ROBOT

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

	//the drive train constants
	namespace DriveTrain
	{

		//the locations of the motors
		const int frontLeft  = 0;
		const int rearLeft   = 1;
		const int frontRight = 2;
		const int rearRight  = 3;

		//motor encoders
		const int leftEncA = 0;
		const int leftEncB = 1;
		const int rightEncA = 2;
		const int rightEncB = 3;

		//solnoids for lifting the chassis up
		const int chassisLiftSol = 0;//SOL

	}

	namespace Shovel
	{
		const int potentiometer = 0;//potentiometer(AI)
		const int shovelPivotMotor = 4;//Motor (PWM)
		const int shovelWideRight = 8;//limit switch (DI)
		const int shovelWideLeft = 9;//limit switch (DI)
		const int shovelPivotLimSwitch = 4;//limit switch (DI)
		const int shovelWidthSol = 2;//solenoid (SOL)

		const int potTurnCount = 1;
		const int potDegree = 360 * potTurnCount;
	}

	namespace Rack
	{
		const int rackPivotMotor = 5;//CIM Motor (PWM)
		const int rackExtendRackMotor = 7;//(PWM)
		const int rackClawSolenoid = 1;//(SOL)
		const int rackMotLimSwitch = 5;//(DI)
		const int rackMotorEncChannelA = 6;//(DI)
		const int rackMotorEncChannelB = 7;//(DI)

		//not quite sure if this is right, but this is what was used in the exampled
		const Encoder::EncodingType encodingType = Encoder::k4X;
	}
}
#endif

#endif /* ROBOTMAP_H_ */
