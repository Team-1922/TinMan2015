#include "RackMotor.h"
#include "../Commands/RackJoyControlled.h"
#include "../RobotMap.h"
#include "../Utilities.h"

RackMotor::RackMotor() :
	Subsystem("rackMotor")
{
	m_pMotor = new Jaguar(RobotMap::Rack::rackPivotMotor);

	m_pEncoder = new Encoder(RobotMap::Rack::rackMotorEncChannelA,
							RobotMap::Rack::rackMotorEncChannelB, true,
							RobotMap::Rack::encodingType);

	m_pEncoder->SetMaxPeriod(1);
}

RackMotor::~RackMotor()
{
	SAFE_DELETE(m_pEncoder);
	SAFE_DELETE(m_pMotor);
}

void RackMotor::setMotor(float level)
{
	m_pMotor->Set(level);
}

void RackMotor::InitDefaultCommand()
{
	SetDefaultCommand(new RackJoyControlled());
}
