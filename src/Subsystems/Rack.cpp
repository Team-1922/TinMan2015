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
	float desiredSpeedRPM = (degPerSecond)/60;
	float currSpeedRPM = (currSpeedDPS)/60;

	//see documentation for motorConstSpeed for more information
	float normalizedValue = Utilities::motorConstSpeed(desiredSpeedRPM, currSpeedRPM, m_speedCompounded,
			RobotMap::Rack::gearing, RobotMap::Rack::rackMotorMaxSpeed);

	setMotor(normalizedValue);
}

void Rack::setExtendMotor(float level)
{
	m_pExtendRetract->Set(level);
}

void Rack::InitDefaultCommand()
{
	SetDefaultCommand(new RackJoyControlled());
}
