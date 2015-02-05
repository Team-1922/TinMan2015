#include "Shovel.h"
#include "../RobotMap.h"
#include "../Commands/ShovelJoyControlled.h"
#include "utilities.h"

Shovel::Shovel():
	Subsystem("Shovel")
{
	m_pRotate = new Talon(RobotMap::Shovel::shovelPivotMotor);
	m_pPotentiometer = new AnalogPotentiometer(
			RobotMap::Shovel::potentiometer,
			RobotMap::Shovel::potDegree/5.0,
		  -(RobotMap::Shovel::potDegree-30));
	m_pWidthSolenoid = new Solenoid(RobotMap::Shovel::shovelWidthSol);
	m_pShovelWideRight = new DigitalInput(RobotMap::Shovel::shovelWideRight);
	m_pShovelWideLeft = new DigitalInput(RobotMap::Shovel::shovelWideLeft);
	m_pShovelPivotLim = new DigitalInput(RobotMap::Shovel::shovelPivotLimSwitch);

}

Shovel::~Shovel()
{
	SAFE_DELETE(m_pRotate);
	SAFE_DELETE(m_pPotentiometer);
	SAFE_DELETE(m_pWidthSolenoid);
	SAFE_DELETE(m_pShovelWideRight);
	SAFE_DELETE(m_pShovelWideLeft);
	SAFE_DELETE(m_pShovelPivotLim);
}

void Shovel::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	SetDefaultCommand(new ShovelJoyControlled());
	//TODO: default command
}

// Put methods for controlling this subsystem
// here. Call these from Commands.


float Shovel::getPotentiometer()
{
	//get the angle
	return m_pPotentiometer->Get();
}

/*float Shovel::getAngle()
{
	//get the angle
	float potVal = m_pPotentiometer->GetAngle();

	//subtract the offset defined by the 'lift' position
	return potVal - RobotMap::Shovel::liftAngle;
}*/


void  Shovel::setMotor(float val)
{
	m_pRotate->Set(val);
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

