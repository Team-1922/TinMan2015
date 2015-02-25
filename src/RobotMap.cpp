#include "RobotMap.h"


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

		//The lengthening and shortening of the rack are controlled by the thumbpad
		const int extendRack = 6;
		const int retractRack = 4;

		//these are for selecting which subsystem the joystick is controlling
		const int rackJoyControlled = 7;
		const int shovelJoyControlled = 9;
		const int rackShovelCombined = 11;

		//these are the controls for shovel and rack angles
		const int shovelFlat   = 3;
		const int shovelDump   = 5;
		const int rackFlat     = 7;
		const int rackVertical = 9;

		//controls for changing the width of the shovel and rack
		const int shovelWidthToggle = 8;
		const int rackClawToggle = 10;
		const int chassisLiftToggle = 12;

		//the current mode
		OperatorMode currOpMode = kRack;


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

			//GEARING
			const int gearing = 1;//this is if the encoder is attached to the wheel axle

			//the gearing of the encoders (I will assume both gearings are the same), converts pulses to RPM
			//GEARING IS AS FOLLOWED
			const float distancePerPulse = 1.0f/float(pulsesPerRotation*gearing);
		}

	}

	namespace Chassis
	{
		//solnoids for lifting the chassis up
		const int chassisLiftSol[2] = {0,1};//SOL
		//0: lift; 1:normal
	}

	namespace Shovel
	{
		const int potentiometer = 0;//potentiometer(AI)
		const int shovelPivotMotor = 4;//(4)Motor (PWM)
		const int shovelWideRight = 8;//limit switch (DI)
		const int shovelWideLeft = 9;//limit switch (DI)
		const int shovelLimitRotationForward = 4;//(DI)
		const int shovelLimitRotationBackward = 5;//(DI)

		const int shovelWidthSol[2] = {4,5};//solenoid (SOL)
		//4: close; 5: open

		const int potDegree = 360;
		const float potDegreeOffset = 0; //degrees off horizontal, aka all the way forwards

		//the voltage difference in a 90 degree region; used in slave control TODO
		const float pot90DegreeVoltageFromRack = 1.15f;


		//THESE ARE RELATIVE TO THE VOLTAGE OFFSET (NOT YET)
#ifdef COMP_BOT // TinMan X
		//TODO:
		float voltageOffset 				= 0.0f;//this is the voltage value when the rack is in store position
		const float voltageStore 			= 0.0f + voltageOffset; // voltage for when the shovel is in the stored position (all the way back)
		const float voltageDump 			= 0.0f + voltageOffset; // voltage for when the shovel is placing totes on the rack
		const float voltageFlat 			= 0.0f + voltageOffset; // voltage for when the shovel is horizontal
		const float voltageStack 			= 0.0f + voltageOffset; // voltage for when the shovel is in position for stacking

#else // Scarecrow
		//TODO:
		float voltageOffset 				= 0.0f;//this is the voltage value when the rack is in store position
		const float voltageStore 			= 0.0f + voltageOffset; // voltage for when the shovel is in the stored position (all the way back)
		const float voltageDump 			= 3.28f + voltageOffset; // voltage for when the shovel is placing totes on the rack
		const float voltageFlat 			= 4.58f + voltageOffset; // voltage for when the shovel is horizontal
		const float voltageStack 			= 4.58f + voltageOffset; // voltage for when the shovel is in position for stacking
		//TODO: fix voltage stack once we have pneumatics working
#endif


		namespace PID
		{
#ifdef COMP_BOT
			const float P = 1.3f;
			const float I = 0.0f;
			const float D = 0.0f;
			const float extremeMotorVal = 0.6;//the absolute value of the maximum motor value
#else
			const float P = 1.3f;
			const float I = 0.0f;
			const float D = -1.0f;
			const float extremeMotorVal = 0.6;//the absolute value of the maximum motor value
#endif
		}

		bool withinRotationRange(float voltage)
		{
			if (voltage > voltageOffset && voltage < voltageStack) {
				return true;
			}
			else {
				return false;
			}
		}


		//GEARING: 480:1
		const int gearing = 480;

		//shovel rpm (Free)
		const int shovelMotorRPM = 133;

		const int shovelMotorMaxSpeed = 30;//degrees/s
	}

	namespace Rack
	{
		const int rackPivotMotor = 5;//CIM Motor (PWM)
		const int rackExtendRack = 7;//(PWM)
		const int rackClawSolenoid[2] = {2,3};//(SOL)
		//2:close; 3:open
		const int potentiometer = 1;//(AI)
		//const int rackEncChannelA = 6;//(DI)
		//const int rackEncChannelB = 7;//(DI)
		extern const int rackLimitRotationForward = 6;//(DI)
		extern const int rackLimitRotationBackward = 7;//(DI)

		//GEARING: 81000:264:
		const int gearing = 81000/264;

		//the speed of the motor (Free)
		const float rackMotorRPM = 5310;

		const int rackMotorMaxSpeed = 15;//degrees/s

		const int potDegree = 360;
		const float potDegreeOffset = -180; //degrees off horizontal, aka all the way forwards


		//THESE ARE RELATIVE TO THE VOLTAGE OFFSET (NOT YET)
#ifdef COMP_BOT // TinMan X
		//TODO:
		float voltageOffset 				= 0.0f;//this is the voltage value when the rack is in store position
		const float voltageDump 			= 0.0f + voltageOffset; // voltage for when the rack is placing totes on the rack
		const float voltageStack 			= 0.0f + voltageOffset; // voltage for when the rack is in position for stacking
		const float voltagePickContainer 	= 0.0f + voltageOffset; // voltage for when the rack is in the stored position (all the way forward to pick up a container)

		const float dumpEpsilon 			= 5.0f * 0.03; // range for which we consider it to be the same as Zero when comparing the target location to see if it is in the dump position


#else // Scarecrow
		//TODO:
		float voltageOffset 				= 0.0f + voltageOffset;//this is the voltage value when the rack is in store position
		const float voltageDump 			= 3.76f + voltageOffset; // voltage for when the rack is placing totes on the rack
		const float voltageStack 			= 2.64f + voltageOffset; // voltage for when the rack is in position for stacking
		const float voltagePickContainer 	= 0.0f + voltageOffset; // voltage for when the rack is in the stored position (all the way forward to pick up a container)

		const float dumpEpsilon 			= 5.0f * 0.03; // range for which we consider it to be the same as Zero when comparing the target location to see if it is in the dump position

#endif


		namespace PID
		{
#ifdef COMP_BOT
			const float P = 16.0f;
			const float I = 0.0f;
			const float D = -8.0f;
			const float extremeMotorVal = 0.25;//the absolute value of the maximum motor value
#else
			const float P = 16.0f;
			const float I = 0.0f;
			const float D = -8.0f;
			const float extremeMotorVal = 0.75;//the absolute value of the maximum motor value
#endif
		}

		bool withinRotationRange(float voltage)
		{
			if (voltage > voltageOffset && voltage < voltagePickContainer) {
				return true;
			}
			else {
				return false;
			}
		}


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
	const float minPollWait = 0.025;//0.025 seconds

	//Boolean for testing autonomous commands. True for on and false for off.
	bool AutonomousEnabled = 0;
}
