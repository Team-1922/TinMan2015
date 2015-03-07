#include "Shovel.h"
#include "../RobotMap.h"
#include "../Commands/ShovelWheelsJoyControlled.h"
#include "../Utilities.h"

Shovel::Shovel():
	Subsystem("Shovel")
{
	/*m_pRotate = new Talon(RobotMap::Shovel::shovelPivotMotor);
	m_pPotentiometer = new OzPotentiometer(
			RobotMap::Shovel::potentiometer,
			RobotMap::Shovel::potDegree,
		    RobotMap::Shovel::potDegreeOffset);*/
	m_pWidthSolenoid = new OzSolenoid(RobotMap::Shovel::shovelWidthSol[0], RobotMap::Shovel::shovelWidthSol[1]);
	//m_pShovelWideRight = new DigitalInput(RobotMap::Shovel::shovelWideRight);
	//m_pShovelWideLeft = new DigitalInput(RobotMap::Shovel::shovelWideLeft);

	m_pSuckWheelLeft = new Talon(RobotMap::Shovel::suckWheelLeft);
	m_pSuckWheelRight = new Talon(RobotMap::Shovel::suckWheelRight);
}

Shovel::~Shovel()
{
	//SAFE_DELETE(m_pRotate);
	//SAFE_DELETE(m_pPotentiometer);
	SAFE_DELETE(m_pWidthSolenoid);
	//SAFE_DELETE(m_pShovelWideRight);
	//SAFE_DELETE(m_pShovelWideLeft);
	SAFE_DELETE(m_pSuckWheelLeft);
	SAFE_DELETE(m_pSuckWheelRight);
}

void Shovel::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	SetDefaultCommand(new ShovelWheelsJoyControlled());
	//TODO: default command
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Shovel::SetSuckWheels(float val)
{
	SetSuckWheelLeft(val);
	SetSuckWheelRight(val);
}

void Shovel::SetSuckWheelLeft(float val)
{
	m_pSuckWheelLeft->Set(val);
}

void Shovel::SetSuckWheelRight(float val)
{
	m_pSuckWheelRight->Set(val);
}

void Shovel::RotateTote(float val)
{
	SetSuckWheelLeft(val);
	SetSuckWheelRight(-val);
}

bool Shovel::isOpen()
{
	return m_pWidthSolenoid->Get();
}


void Shovel::setSolenoid(bool setting)
{
	if (!m_pWidthSolenoid->IsBlackListed()) {  // isBlackListed() == true means that the solenoid is shorted/not working properly
		m_pWidthSolenoid->Set(setting);
	}
	else {
		// TODO: dump a message to the driver station so the operator/driver knows there is a problem
	}
}

