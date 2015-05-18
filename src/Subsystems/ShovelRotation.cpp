#include "ShovelRotation.h"
#include "../RobotMap.h"
#include "SmartDashboard/SmartDashboard.h"
#include "LiveWindow/LiveWindow.h"
#include "../Commands/ShovelJoyControlled.h"
#include "../Utilities.h"

ShovelRotation::ShovelRotation() :
		PIDSubsystem("ShovelRotation", RobotMap::Shovel::PID::P, RobotMap::Shovel::PID::I, RobotMap::Shovel::PID::D)
{
	m_pMotor = new Talon(RobotMap::Shovel::shovelPivotMotor);
	m_pPot = new AnalogPotentiometer(
			RobotMap::Shovel::potentiometer, 5.0, 0.0); // stick with voltage readout for right now
	//m_pShovelPivotLim = new OzLimitSwitch(RobotMap::Shovel::shovelPivotLimSwitch);

#ifndef COMP_BOT
	m_pLimitRotationForward = new OzLimitSwitch(RobotMap::Shovel::shovelLimitRotationForward);
	m_pLimitRotationBackward = new OzLimitSwitch(RobotMap::Shovel::shovelLimitRotationBackward);
#endif

	m_pReedLeft  = new DigitalInput(RobotMap::Shovel::shovelWideLeft);
	m_pReedRight = new DigitalInput(RobotMap::Shovel::shovelWideRight);

	SetInputRange(0.0, 5.0); // range of values returned from the potentiometer
	SetOutputRange(-RobotMap::Shovel::PID::extremeMotorVal,
			RobotMap::Shovel::PID::extremeMotorVal); // start with the motor range
	SetAbsoluteTolerance(0.07);

	// Use these to get going:
	// SetSetpoint() -  Sets where the PID controller should move the system
	//                  to
	// Enable() - Enables the PID controller.
	LiveWindow::GetInstance()->AddActuator("Shovel", "PID", GetPIDController());

	Enable();

	SetSetpoint(GetPotVoltage());
}

ShovelRotation::~ShovelRotation()
{
	SAFE_DELETE(m_pMotor);
	SAFE_DELETE(m_pPot);

	SAFE_DELETE(m_pReedLeft);
	SAFE_DELETE(m_pReedRight);

#ifndef COMP_BOT
	SAFE_DELETE(m_pLimitRotationForward);
	SAFE_DELETE(m_pLimitRotationBackward);
#endif

}

double ShovelRotation::ReturnPIDInput()
{
	// Return your input value for the PID loop
	// e.g. a sensor, like a potentiometer:
	// yourPot->SetAverageVoltage() / kYourMaxVoltage;	
	float newTime = Utilities::getTime();
	float deltaTime = newTime - m_OldTime;
	m_OldTime = newTime;
	return m_pPot->PIDGet() / deltaTime;
}

void ShovelRotation::UsePIDOutput(double output)
{
	// Use output to drive your system, like a motor
	// e.g. yourMotor->Set(output);

/*#ifndef COMP_BOT
	//this only matters on the practice bot
	if(m_pLimitRotationBackward->Get() && output > 0.0f)
		return;

	//since rotating backwards is actually the forwards direction of the motor, change the inequality
	if(m_pLimitRotationForward->Get() && output < 0.0f)
		return;
#endif*/


	//TODO: uncomment
	//if the rack SETPOINT OR VOLTAGE is further forwards than vertical, and the reed switches are triggered (shovel open), THEN GO TO FLAT
	//if(( (CommandBase::rackRotation->GetPotVoltage() < RobotMap::Rack::voltageStack + 0.15) || (CommandBase::rackRotation->GetSetpoint() < RobotMap::Rack::voltageStack + 0.15f) ) && GetReed())
	//	SetSetpoint(RobotMap::Shovel::voltageFlat);//NOTE: shovel bends to the will of the rack

	//since the potentiometer goes the opposite direction, invert this value
	float angle = 90.0f * (5.0f - m_pPot->PIDGet());
	if(angle < 1.0f)
	{
		output *= std::max(0.75f, fabsf(cosf(DEGREES_TO_RADIANS(angle))));
	}
	m_pMotor->Set(-output);
}

void ShovelRotation::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//setDefaultCommand(new MySpecialCommand());
	//SetDefaultCommand(new ShovelJoyControlled());
}

float ShovelRotation::GetPotVoltage()
{
	return m_pPot->Get();
}

void ShovelRotation::TickPotentiometer()
{
	//m_pPot->Tick();
}

bool ShovelRotation::GetReed()
{
	return (!m_pReedLeft || !m_pReedRight);
}
