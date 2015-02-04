#include "Commands/RaceDrive.h"
#include "DriveTrain.h"
#include "../RobotMap.h"
#include "../Utilities.h"

DriveTrain::DriveTrain() :
		Subsystem("DriveTrainSubsystem"),
		frontLeft(new Talon(RobotMap::DriveTrain::frontLeft)),
		rearLeft(new Talon(RobotMap::DriveTrain::rearLeft)),
		frontRight(new Talon(RobotMap::DriveTrain::frontRight)),
		rearRight(new Talon(RobotMap::DriveTrain::rearRight))
{

}

DriveTrain::~DriveTrain()
{
	//make sure the motors are off before destroying;
	StopMotors();

	SAFE_DELETE(frontLeft);
	SAFE_DELETE(rearLeft);
	SAFE_DELETE(frontRight);
	SAFE_DELETE(rearRight);
}

void DriveTrain::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	SetDefaultCommand(new RaceDrive());
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
	frontLeft->Set(left);
	rearLeft->Set(left);
	frontRight->Set(right);
	rearRight->Set(right);
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
	frontLeft->Set(left);
	rearLeft->Set(left);
	frontRight->Set(right);
	rearRight->Set(right);

}

void DriveTrain::TankDrivePeriodic(Joystick* stick1, Joystick* stick2)
{
	//TODO: these might not need to be inverted
	float rightValues = -stick1->GetY();
	float leftValues = -stick2->GetY();

	frontLeft->Set(leftValues);
	rearLeft->Set(leftValues);
	frontRight->Set(rightValues);
	rearRight->Set(rightValues);
}

void DriveTrain::StopMotors()
{
	frontLeft->Set(0);
	rearLeft->Set(0);
	frontRight->Set(0);
	rearRight->Set(0);
}

void DriveTrain::DriveStraight(float motorVal){

	frontLeft->Set(motorVal);
		rearLeft->Set(motorVal);
		frontRight->Set(motorVal);
		rearRight->Set(motorVal);



}
