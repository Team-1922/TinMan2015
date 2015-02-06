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

	m_pEncoder = new Encoder(RobotMap::Rack::rackEncChannelA,
							RobotMap::Rack::rackEncChannelB, true,
							RobotMap::Rack::Encoder::encodingType);

	m_pEncoder->SetDistancePerPulse(RobotMap::Rack::Encoder::distancePerPulse);
	m_pEncoder->SetMinRate(0.1);
}

Rack::~Rack()
{
	SAFE_DELETE(m_pEncoder);
	SAFE_DELETE(m_pExtendRetract);
	SAFE_DELETE(m_pRotate);
	SAFE_DELETE(m_pLimitBackStop);
	SAFE_DELETE(m_pClaw);
}

void Rack::setMotor(float level)
{
	m_pRotate->Set(level);
}

void Rack::setMotorRate(float degPerSecond)
{
	float currSpeedDPS = getEncRate();
	if(Utilities::isEqual(0.0f, currSpeedDPS, .5f))
		currSpeedDPS = degPerSecond;

	//use formula derived with dimensional analysis to convert DPS to RPM of our gearbox
	float desiredSpeedRPM = (degPerSecond*RobotMap::Rack::gearing)/60;
	float currSpeedRPM = (currSpeedDPS*RobotMap::Rack::gearing)/60;

	//take the RPM we need to give the motor to increase the speed to what we want
	float requiredRPM = desiredSpeedRPM - currSpeedRPM;
	float neededPercentageOfDesired = requiredRPM / desiredSpeedRPM;

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
