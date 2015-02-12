#include "Subsystems/Rack.h"
#include "../Commands/RackJoyControlled.h"
#include "../RobotMap.h"
#include "../Utilities.h"

Rack::Rack() :
	Subsystem("Rack")
{
	m_pClaw = new Solenoid(RobotMap::Rack::rackClawSolenoid);
	m_pLimitBackStop = new DigitalInput(RobotMap::Rack::rackMotLimSwitch);
	m_pRotate = new Talon(RobotMap::Rack::rackPivotMotor);
	m_pExtendRetract = new Talon(RobotMap::Rack::rackExtendRack);

	m_pPotentiometer = new OzPotentiometer(
			RobotMap::Rack::potentiometer,
			RobotMap::Rack::potDegree/5.0,
		  -(RobotMap::Rack::potDegree-RobotMap::Rack::potDegreeOffset));
}

Rack::~Rack()
{
	SAFE_DELETE(m_pPotentiometer);
	SAFE_DELETE(m_pExtendRetract);
	SAFE_DELETE(m_pRotate);
	SAFE_DELETE(m_pLimitBackStop);
	SAFE_DELETE(m_pClaw);
}

void Rack::setMotor(float level)
{
	m_pRotate->Set(level);
}

float Rack::getPotentiometer()
{
	//get the angle
	return m_pPotentiometer->Get();
}

//
void Rack::tickPotentiometer()
{
	m_pPotentiometer->Tick();
}

float Rack::getTurnRate()
{
	return m_pPotentiometer->GetTurnRate();
}

void Rack::setMotorRate(float degPerSecond)
{

	setMotor(degPerSecond / (float)RobotMap::Rack::rackMotorMaxSpeed);
	//short circuit this for now
	return;

	float currSpeedDPS = getTurnRate();
	//if(Utilities::isEqual(0.0f, currSpeedDPS, .5f))
	//	currSpeedDPS = degPerSecond;

	//use formula derived with dimensional analysis to convert DPS to RPM of our gearbox
	float desiredSpeedRPM = (degPerSecond*RobotMap::Rack::gearing)/60;
	float currSpeedRPM = (currSpeedDPS*RobotMap::Rack::gearing)/60;

	//take the RPM we need to give the motor to increase the speed to what we want
	float requiredRPM = desiredSpeedRPM - currSpeedRPM;
	float neededPercentageOfDesired = requiredRPM / desiredSpeedRPM;

	//make sure this percentage is not bigger than 1.5 percent, so it doesn't make drastic changes that cause jerking
	//  or damage equipment; HOPEFULLY this fixes the problem of stopping too quickly, or putting to much tork on the motor
	neededPercentageOfDesired = Utilities::clamp<float>(neededPercentageOfDesired, -RobotMap::maxRPMDelta, RobotMap::maxRPMDelta);

	float totalNeededRPM = (1.0f + neededPercentageOfDesired) * desiredSpeedRPM;

	//divide by the rpm to get a value between -1 and 1;
	float normalisedValue = totalNeededRPM / RobotMap::Rack::rackMotorRPM;
	setMotor(normalisedValue);
}

void Rack::setExtendMotor(float level)
{
	m_pExtendRetract->Set(level);
}

void Rack::InitDefaultCommand()
{
	SetDefaultCommand(new RackJoyControlled());
}
