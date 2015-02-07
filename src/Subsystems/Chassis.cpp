#include "Chassis.h"
#include "../RobotMap.h"

Chassis::Chassis() :
		Subsystem("Chassis")
{
	m_pLiftSolenoid = new Solenoid(RobotMap::Chassis::chassisLiftSol);
}

void Chassis::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
