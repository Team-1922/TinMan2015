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
		//TODO: get these optimal positions

		//The lengthening and shortening of the rack are controlled by the thumbpad
		const int extendRack = 6;
		const int retractRack = 4;

		//these are for selecting which subsystem the joystick is controlling
		const int rackJoyControlled = 7;
		const int shovelJoyControlled = 9;
		const int rackShovelCombined = 11;

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
		const float pot90DegreeVoltage = 1.0f;

#ifdef COMP_BOT // TinMan X
		const float voltageStack = 0.0f; // voltage for when the shovel is in position for stacking
		const float voltageFlat = 0.0f; // voltage for when the shovel is horizontal
		const float voltageDump = 0.0f; // voltage for when the shovel is placing totes on the rack
		const float voltageStore = 0.0f; // voltage for when the shovel is in the stored position (all the way back)
#else // Scarecrow
		const float voltageStack = 0.0f; // voltage for when the shovel is in position for stacking
		const float voltageFlat = 0.0f; // voltage for when the shovel is horizontal
		const float voltageDump = 0.0f; // voltage for when the shovel is placing totes on the rack
		const float voltageStore = 0.0f; // voltage for when the shovel is in the stored position (all the way back)
#endif
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
		const int rackMotLimSwitchForward = 5;//(DI)
		const int rackMotLimSwitchBack = 6;//(DI)
		const int rackClawSolenoid[2] = {2,3};//(SOL)
		//2:close; 3:open
		const int potentiometer = 1;//(AI)
		//const int rackEncChannelA = 6;//(DI)
		//const int rackEncChannelB = 7;//(DI)

		//GEARING: 81000:264:
		const int gearing = 81000/264;

		//the speed of the motor (Free)
		const float rackMotorRPM = 5310;

		const int rackMotorMaxSpeed = 15;//degrees/s

		const int potDegree = 360;
		const float potDegreeOffset = -180; //degrees off horizontal, aka all the way forwards


#ifdef COMP_BOT // TinMan X
		const float voltageStack = 0.0f; // voltage for when the shovel is in position for stacking
		const float voltageVertical = 0.0f; // voltage for when the shovel is horizontal
		const float voltageDump = 0.0f; // voltage for when the shovel is placing totes on the rack
		const float voltagePickContainer = 0.0f; // voltage for when the shovel is in the stored position (all the way back)
#else // Scarecrow
		const float voltageStack = 0.0f; // voltage for when the shovel is in position for stacking
		const float voltageVertical = 0.0f; // voltage for when the shovel is horizontal
		const float voltageDump = 0.0f; // voltage for when the shovel is placing totes on the rack
		const float voltagePickContainer = 0.0f; // voltage for when the shovel is in the stored position (all the way back)
#endif



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
}
