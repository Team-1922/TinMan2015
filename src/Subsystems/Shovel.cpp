#include "Shovel.h"
#include "../RobotMap.h"
#include "../Commands/ShovelJoyControlled.h"
#include "utilities.h"

Shovel::Shovel():
	Subsystem("Shovel")
{
	m_pRotate = new Talon(RobotMap::Shovel::shovelPivotMotor);
	m_pPotentiometer = new OzPotentiometer(
			RobotMap::Shovel::potentiometer,
			RobotMap::Shovel::potDegree/5.0,
		  -(RobotMap::Shovel::potDegree-RobotMap::Shovel::potDegreeOffset));
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


//
void Shovel::tickPotentiometer()
{
	m_pPotentiometer->Tick();
}

float Shovel::getTurnRate()
{
	return m_pPotentiometer->GetTurnRate();
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

//almost identical to the function of the rack
void  Shovel::setMotorRate(float degPerSecond)
{

	setMotor(degPerSecond / (float)RobotMap::Shovel::shovelMotorMaxSpeed);
	//short circuit this for now
	return;

	float currSpeedDPS = getTurnRate();
	//if(Utilities::isEqual(0.0f, currSpeedDPS, .5f))
	//	currSpeedDPS = degPerSecond;

	//use formula derived with dimensional analysis to convert DPS to RPM of our gearbox
	float desiredSpeedRPM = (degPerSecond*RobotMap::Shovel::gearing)/60;
	float currSpeedRPM = (currSpeedDPS*RobotMap::Shovel::gearing)/60;

	//take the RPM we need to give the motor to increase the speed to what we want
	float requiredRPM = desiredSpeedRPM - currSpeedRPM;
	float neededPercentageOfDesired = requiredRPM / desiredSpeedRPM;

	//make sure this percentage is not bigger than 1.5 percent, so it doesn't make drastic changes that cause jerking
	//  or damage equipment; HOPEFULLY this fixes the problem of stopping too quickly, or putting to much tork on the motor
	neededPercentageOfDesired = Utilities::clamp<float>(neededPercentageOfDesired, -RobotMap::maxRPMDelta, RobotMap::maxRPMDelta);

	float totalNeededRPM = (1.0f + neededPercentageOfDesired) * desiredSpeedRPM;

	//divide by the rpm to get a value between -1 and 1;
	float normalisedValue = totalNeededRPM / RobotMap::Shovel::shovelMotorRPM;
	setMotor(normalisedValue);
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

