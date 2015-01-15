#include "DriveTrain.h"
#include "../RobotMap.h"

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
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.


void DriveTrain::ArcadeDrive(Joystick* stick)
{
	robDrive.ArcadeDrive(stick);
}
