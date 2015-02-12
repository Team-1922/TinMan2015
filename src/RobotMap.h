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
		const int driverJoy1 = 0;
		const int driverJoy2 = 1;
		const int operatorJoy = 2;
		const int controller = 3;

		//these two MUST add up to 1.0f
		const float throttleFactor = 0.8f;//how much the throttle affects speed
		const float stearingFactor = 0.2f;//how much stearing direction affects speed

		//the controls on the operator joystick
		//TODO: get these optimal positions

		//these extend or retract the rack, NOTE: these are to be held to adjust the rack
		const int extendRack = 5;
		const int retractRack = 6;

		//these are for selecting which subsystem the joystick is controlling
		const int rackJoyControlled = 7;
		const int shovelJoyControlled = 8;
		const int rackShovelCombined = 9;

		//controls for changing the width of the shovel and rack
		const int shovelWidthToggle = 10;
		const int rackClawToggle = 11;

		//the current mode
		extern OperatorMode currOpMode;// = kRack;


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


		namespace Encoder
		{
			//information to give encoders

			//not quite sure if this is right, but this is what was used in the exampled
			const ::Encoder::EncodingType encodingType = ::Encoder::k4X;

			//the number of encoder pulses per rotation TODO:
			const int pulsesPerRotation = 500;

			//GEARING TODO:
			const int gearing = 1;//this is if the encoder is attached to the wheel axle

			//the gearing of the encoders (I will assume both gearings are the same), converts pulses to RPM
			//GEARING IS AS FOLLOWED TODO:
			const float distancePerPulse = 1.0f/float(pulsesPerRotation*gearing);
		}

	}

	namespace Chassis
	{
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

		const int potTurnCount = 10;
		const int potDegree = 360 * potTurnCount;
		const float potDegreeOffset = 30; //degrees off horizontal, aka all the way forwards


		//GEARING: 480:1  TODO:?
		const int gearing = 480;

		//shovel rpm (Free)
		const int shovelMotorRPM = 133;

		const int shovelMotorMaxSpeed = 30;//degrees/s
	}

	namespace Rack
	{
		const int rackPivotMotor = 5;//CIM Motor (PWM)
		const int rackExtendRack = 7;//(PWM)
		const int rackClawSolenoid = 1;//(SOL)
		const int rackMotLimSwitch = 5;//(DI)
		const int potentiometer = 1;//(AI)
		//const int rackEncChannelA = 6;//(DI)
		//const int rackEncChannelB = 7;//(DI)

		//GEARING: 81000:264:
		const int gearing = 81000/264;

		//the speed of the motor (Free)
		const float rackMotorRPM = 5310;

		const int rackMotorMaxSpeed = 15;//degrees/s

		const int potTurnCount = 10;
		const int potDegree = 360 * potTurnCount;
		const float potDegreeOffset = 0; //degrees off horizontal, aka all the way forwards


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
	const float maxRPMDelta = 0.015;//1.5%

	//polling rate of the potentiometer
	const float minPollWait = 0.05;//0.05 seconds
}
#endif

#endif /* ROBOTMAP_H_ */
