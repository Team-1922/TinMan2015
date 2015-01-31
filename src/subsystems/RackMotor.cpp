#include "RackMotor.h"
#include "../Commands/RackJoyControlled.h"
#include "../RobotMap.h"
#include "../Utilities.h"

RackMotor::RackMotor() :
	Subsystem("rackMotor")
{
	m_pMotor = new Jaguar(RobotMap::Rack::motorLoc);
	m_pPotentiometer = new OzPotentiometer(RobotMap::Rack::potentiometerLoc,
										RobotMap::Rack::potentiometerMinVal,
										RobotMap::Rack::potentiometerMaxVal,
										RobotMap::Rack::potentiometerTurnCount);

	m_pEncoder = new Encoder(RobotMap::Rack::encoderLoc1,
							RobotMap::Rack::encoderLoc2, true,
							RobotMap::Rack::encodingType);

	m_pEncoder->SetMaxPeriod(RobotMap::Rack::encoderMinRate);
}

RackMotor::~RackMotor()
{
	SAFE_DELETE(m_pEncoder);
	SAFE_DELETE(m_pPotentiometer);
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

float RackMotor::getPotentiometer()
{
	return m_pPotentiometer->GetAngle();
}

float RackMotor::getPotentiometerRaw()
{
	float potVal = m_pPotentiometer->Get();

	return (potVal);
}
