
#include "../Commands/RaceDrive.h"
#include "../Commands/TankDrive.h"
#include "DriveTrain.h"
#include "../RobotMap.h"
#include "../Utilities.h"

DriveTrain::DriveTrain() :
		Subsystem("DriveTrain")
{
	m_pFrontLeft = new Talon(RobotMap::DriveTrain::frontLeft);
	//m_pRearLeft = new Talon(RobotMap::DriveTrain::rearLeft);
	m_pFrontRight = new Talon(RobotMap::DriveTrain::frontRight);
	//m_pRearRight = new Talon(RobotMap::DriveTrain::rearRight);
	m_pLeftEncoder = new Encoder(
			RobotMap::DriveTrain::leftEncA,
			RobotMap::DriveTrain::leftEncB, true,
			RobotMap::DriveTrain::Encoder::encodingType);
	m_pRightEncoder = new Encoder(
			RobotMap::DriveTrain::rightEncA,
			RobotMap::DriveTrain::rightEncB, true,
			RobotMap::DriveTrain::Encoder::encodingType);

	//setup the left encoder
	m_pLeftEncoder->SetDistancePerPulse(RobotMap::DriveTrain::Encoder::distancePerPulse);
	m_pLeftEncoder->SetMinRate(0.1);//0.1 in/s

	//setup the right encoder
	m_pRightEncoder->SetDistancePerPulse(RobotMap::DriveTrain::Encoder::distancePerPulse);
	m_pRightEncoder->SetMinRate(0.1);//0.1 in/s

	//configure the PID system (NOTE: i use 1000 inches as the maximum because there should be no limit, but autonomous is not that long
	/*SetInputRange(0.0, 1000.0f); // range of values returned from the potentiometer
	SetOutputRange(-RobotMap::DriveTrain::PID::extremeMotorVal,
			RobotMap::DriveTrain::PID::extremeMotorVal); // start with the motor range
	SetAbsoluteTolerance(2.0f);//tolerance of about 2 inches

	// Use these to get going:
	// SetSetpoint() -  Sets where the PID controller should move the system
	//                  to
	// Enable() - Enables the PID controller.
	LiveWindow::GetInstance()->AddActuator("Drive Train", "PID", GetPIDController());

	//setup to stay still by default, HOWEVER PID doesn't do anything in teleop mode
	Enable();
	SetSetpoint(ReturnPIDInput());*/
}

DriveTrain::~DriveTrain()
{
	//make sure the motors are off before destroying;
	StopMotors();

	SAFE_DELETE(m_pFrontLeft);
	//SAFE_DELETE(m_pRearLeft);
	SAFE_DELETE(m_pFrontRight);
	//SAFE_DELETE(m_pRearRight);

	SAFE_DELETE(m_pLeftEncoder);
	SAFE_DELETE(m_pRightEncoder);
}

void DriveTrain::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	SetDefaultCommand(new TankDrive());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.


void DriveTrain::ArcadeDrivePeriodic(Joystick* stick)
{
	//flip the axes
	float yAxis = stick->GetX();
	float xAxis = -stick->GetY();//INVERT the x axis, maybe

	//manual arcade drive control
	float left = yAxis + xAxis;
	float right = yAxis - xAxis;

	//invert the motors
	left = -left;
	right = -right;

	//set the motors
	setLeft(left);
	setRight(right);
}

void DriveTrain::RaceDrivePeriodic(Joystick* stick)
{

	//get axes
	float forwardVal = stick->GetRawAxis(3); //right trig
	float reverseVal = stick->GetRawAxis(2); //left trig
	float turnVal = stick->GetRawAxis(4); //right x axis

	float throttleFactored = RobotMap::Controls::throttleFactor * (forwardVal - reverseVal);
	float turnValFactored = RobotMap::Controls::stearingFactor * turnVal;

	float left  = (throttleFactored + turnValFactored);
	float right = -(throttleFactored - turnValFactored);

	//set the motors
	setLeft(left);
	setRight(right);

}

void DriveTrain::TankDrivePeriodic(Joystick* stick1, Joystick* stick2)
{
	//TODO: these might not need to be inverted
	float left = stick1->GetY();
	float right = -stick2->GetY();

	setLeft(left);
	setRight(right);
}


void DriveTrain::setLeft(float val)
{
#ifdef COMP_BOT
	m_pFrontLeft->Set(-val);
	//m_pRearLeft->Set(-val);
#else
	m_pFrontLeft->Set(val);
	//m_pRearLeft->Set(val);
#endif
}

void DriveTrain::setRight(float val)
{
#ifdef COMP_BOT
	m_pFrontRight->Set(-val);
	//m_pRearRight->Set(-val);
#else
	m_pFrontRight->Set(val);
	//m_pRearRight->Set(val);
#endif
}

void DriveTrain::StopMotors()
{
	m_pFrontLeft->Set(0);
	//m_pRearLeft->Set(0);
	m_pFrontRight->Set(0);
	//m_pRearRight->Set(0);
}

void DriveTrain::DriveStraight(float motorVal)
{
	setLeft(-motorVal);
	setRight(motorVal);
}

double DriveTrain::ReturnPIDInput()
{
	//rely on the left encoder for distence, i need to figure out how turning will work with only one input
	return getEncDistanceLeft();
}

void DriveTrain::UsePIDOutput(double output)
{
	//don't follow PID in Teleop mode
	//if(RobotMap::Mode) since there are no encoders, NEVER use PID output
		return;

	if(m_isRotating)
	{
		//when rotating, the output is for the left motors, but to turn in place, set the right motor to the opposite
		setLeft(output);
		setRight(-output);
	}
	else
	{
		DriveStraight(output);
	}
}
