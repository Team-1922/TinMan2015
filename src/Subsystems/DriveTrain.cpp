#include "DriveTrain.h"
#include "../RobotMap.h"
#include "../Commands/ArcadeDrive.h"
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
	SetDefaultCommand(new ArcadeDrive());
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

void DriveTrain::TankDrivePeriodic(Joystick* stick)
{
		//get axes
		float leftVal = stick->GetRawAxis(1);
		float rightVal = stick->GetRawAxis(5);


		//set the motors
		frontLeft->Set(leftVal);
		rearLeft->Set(leftVal);
		frontRight->Set(rightVal);
		rearRight->Set(rightVal);










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
