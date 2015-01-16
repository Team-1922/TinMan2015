#include "DriveTrain.h"
#include "../RobotMap.h"
#include "../Commands/CommandArcadeDrive.h"

DriveTrain::DriveTrain() :
		Subsystem("DriveTrainSubsystem"),
		robDrive(RobotMap::DriveTrain::frontLeft,
				RobotMap::DriveTrain::rearLeft,
				RobotMap::DriveTrain::frontRight,
				RobotMap::DriveTrain::rearRight)
{

}

void DriveTrain::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	SetDefaultCommand(new CommandArcadeDrive());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.


void DriveTrain::ArcadeDrive(Joystick* stick)
{
	robDrive.ArcadeDrive(stick);
}

void DriveTrain::StopMotors()
{
	robDrive.StopMotor();

}
