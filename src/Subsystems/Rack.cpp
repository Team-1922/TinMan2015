#include <Subsystems/Rack.h>
#include "../Commands/RackJoyControlled.h"
#include "../RobotMap.h"
#include "../Utilities.h"

Rack::Rack() :
	Subsystem("Rack")
{
	m_pMotor = new Jaguar(RobotMap::Rack::rackPivotMotor);

	m_pEncoder = new Encoder(RobotMap::Rack::RackEncChannelA,
							RobotMap::Rack::RackEncChannelB, true,
							RobotMap::Rack::encodingType);

	m_pEncoder->SetMaxPeriod(1);
}

Rack::~Rack()
{
	SAFE_DELETE(m_pEncoder);
	SAFE_DELETE(m_pMotor);
}

void Rack::setMotor(float level)
{
	m_pMotor->Set(level);
}

void Rack::InitDefaultCommand()
{
	SetDefaultCommand(new RackJoyControlled());
}
