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

	//setup the potentiometer for rate
	m_LastTick = Utilities::getTime();
	m_LastAngle = getPotentiometer();
	tickPotentiometer();
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
	float currTime = Utilities::getTime();

	//don't tick too often
	if (currTime - m_LastTick < RobotMap::Shovel::minPollWait)
		return;

	float currAngle = getPotentiometer();

	//this is in degrees per second
	m_CurrSpeed = (currAngle - m_LastAngle) /
			/*	  --------------------------		*/
				  (currTime - m_LastTick);

	//this would be: change in angle divided by change in time = degrees/s

	//finally update the last tick time
	m_LastTick = currTime;
}

float Shovel::getTurnRate()
{
	return m_CurrSpeed;
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

void  Shovel::setMotorRate(float degPerSecond)
{
	float currSpeedDPS = getTurnRate();
	if(Utilities::isEqual(0.0f, currSpeedDPS, .5f))
		currSpeedDPS = degPerSecond;

	//use formula derived with dimensional analysis to convert DPS to RPM of our gearbox
	float desiredSpeedRPM = (degPerSecond*RobotMap::Shovel::gearing)/60;
	float currSpeedRPM = (currSpeedDPS*RobotMap::Shovel::gearing)/60;

	//take the RPM we need to give the motor to increase the speed to what we want
	float requiredRPM = desiredSpeedRPM - currSpeedRPM;
	float neededPercentageOfDesired = requiredRPM / desiredSpeedRPM;

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

