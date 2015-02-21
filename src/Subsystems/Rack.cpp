#include "Rack.h"
#include "../Commands/RackJoyControlled.h"
#include "../RobotMap.h"
#include "../Utilities.h"

Rack::Rack() :
	Subsystem("Rack")
{
	m_pClaw = new OzSolenoid(RobotMap::Rack::rackClawSolenoid[0], RobotMap::Rack::rackClawSolenoid[1]);
	m_pExtendRetract = new Talon(RobotMap::Rack::rackExtendRack);

	m_pLimitBackStopExtended = new DigitalInput(RobotMap::Rack::rackMotLimSwitchExtended);
	m_pLimitBackStopRetracted = new DigitalInput(RobotMap::Rack::rackMotLimSwitchRetracted);
}

Rack::~Rack()
{
	SAFE_DELETE(m_pExtendRetract);
	SAFE_DELETE(m_pClaw);

	SAFE_DELETE(m_pLimitBackStopExtended);
	SAFE_DELETE(m_pLimitBackStopRetracted);

}

void Rack::setExtendMotor(float level)
{
	m_pExtendRetract->Set(level);
}

void Rack::InitDefaultCommand()
{
//	SetDefaultCommand(new RackJoyControlled());
}
