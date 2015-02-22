#include "ShovelRotation.h"
#include "../RobotMap.h"
#include "SmartDashboard/SmartDashboard.h"
#include "LiveWindow/LiveWindow.h"
#include "../Commands/ShovelJoyControlled.h"
#include "../Utilities.h"

ShovelRotation::ShovelRotation() :
		PIDSubsystem("ShovelRotation", 1.3, 0.0, 0.0)
{
	m_pMotor = new Talon(RobotMap::Shovel::shovelPivotMotor);
	m_pPot = new OzPotentiometer(
			RobotMap::Shovel::potentiometer, 5.0, 0.0); // stick with voltage readout for right now
	//m_pShovelPivotLim = new OzLimitSwitch(RobotMap::Shovel::shovelPivotLimSwitch);

#ifndef COMP_BOT
	m_pLimitRotationForward = new OzLimitSwitch(RobotMap::Shovel::shovelLimitRotationForward);
	m_pLimitRotationBackward = new OzLimitSwitch(RobotMap::Shovel::shovelLimitRotationBackward);
#endif

	SetInputRange(0.0, 5.0); // range of values returned from the potentiometer
	SetOutputRange(-0.4, 0.4); // start with the motor range

	// Use these to get going:
	// SetSetpoint() -  Sets where the PID controller should move the system
	//                  to
	// Enable() - Enables the PID controller.
	LiveWindow::GetInstance()->AddActuator("Shovel", "PID", GetPIDController());
}

ShovelRotation::~ShovelRotation()
{
	SAFE_DELETE(m_pMotor);
	SAFE_DELETE(m_pPot);

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
	return m_pPot->PIDGet();
}

void ShovelRotation::UsePIDOutput(double output)
{
	// Use output to drive your system, like a motor
	// e.g. yourMotor->Set(output);

#ifndef COMP_BOT
	//this only matters on the practice bot
	if(m_pLimitRotationBackward->Get() && output > 0.0f)
		return;

	//since rotating backwards is actually the forwards direction of the motor, change the inequality
	if(m_pLimitRotationForward->Get() && output < 0.0f)
		return;
#endif

	//since the potentiometer goes the opposite direction, invert this value
	m_pMotor->Set(-output);
}

void ShovelRotation::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//setDefaultCommand(new MySpecialCommand());
	SetDefaultCommand(new ShovelJoyControlled());
}

float ShovelRotation::GetPotVoltage()
{
	return m_pPot->Get();
}

void ShovelRotation::TickPotentiometer()
{
	m_pPot->Tick();
}
