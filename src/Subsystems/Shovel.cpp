#include "Shovel.h"
#include "../RobotMap.h"
#include "../Commands/ShovelJoyControlled.h"
#include "utilities.h"

Shovel::Shovel() :
		Subsystem("ExampleSubsystem"),
		m_pMotor(new Jaguar(RobotMap::Shovel::motorLoc)),
		m_pPotentiometer(new OzPotentiometer(RobotMap::Shovel::potentiometerLoc,
										RobotMap::Shovel::potentiometerMinVal,
										RobotMap::Shovel::potentiometerMaxVal,
										RobotMap::Shovel::potentiometerTurnCount)),
										m_solenoid(RobotMap::Shovel::solenoidId)
{

}

Shovel::~Shovel()
{
	SAFE_DELETE(m_pMotor);
	SAFE_DELETE(m_pPotentiometer);
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
	return getAngle();
}

float Shovel::getPotentiometerRaw()
{
	return m_pPotentiometer->Get();
}

float Shovel::getAngle()
{
	//get the angle
	float potVal = m_pPotentiometer->GetAngle();

	//subtract the offset defined by the 'lift' position
	return potVal - RobotMap::Shovel::liftAngle;
}


void  Shovel::setMotor(float val)
{
	m_pMotor->Set(val);
}


void Shovel::setSolenoid(bool setting)
{
	if (!m_solenoid.IsBlackListed()) {  // isBlackListed() == true means that the solenoid is shorted/not working properly
		m_solenoid.Set(setting);
	}
	else {
		// TODO: dump a message to the driver station so the operator/driver knows there is a problem
	}
}

