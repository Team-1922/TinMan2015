#include "Chassis.h"
#include "../RobotMap.h"

Chassis::Chassis() :
		Subsystem("Chassis")
{
	m_pLiftSolenoid = new OzSolenoid(RobotMap::Chassis::chassisLiftSol[0], RobotMap::Chassis::chassisLiftSol[1]);
}

void Chassis::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
