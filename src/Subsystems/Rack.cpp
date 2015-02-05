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

void Rack::setExtendMotor(float level)
{
	m_pExtendRetract->Set(level);
}

void Rack::InitDefaultCommand()
{
	SetDefaultCommand(new RackJoyControlled());
}
