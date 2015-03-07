#include "Rack.h"
#include "../Commands/RackJoyControlled.h"
#include "../RobotMap.h"
#include "../Utilities.h"

Rack::Rack() :
	Subsystem("Rack")
{
	//m_pClaw = new OzSolenoid(RobotMap::Rack::rackClawSolenoid[0], RobotMap::Rack::rackClawSolenoid[1]);
	m_pExtendRetract = new Talon(RobotMap::Rack::rackExtendRack);

}

Rack::~Rack()
{
	SAFE_DELETE(m_pExtendRetract);
	//SAFE_DELETE(m_pClaw);


}

void Rack::setExtendMotor(float level)
{
	m_pExtendRetract->Set(level);
}

void Rack::InitDefaultCommand()
{
//	SetDefaultCommand(new RackJoyControlled());
}
