#include "ShovelRotation.h"
#include "../RobotMap.h"
#include "SmartDashboard/SmartDashboard.h"
#include "LiveWindow/LiveWindow.h"
#include "../Commands/ShovelJoyControlled.h"
#include "../Utilities.h"

ShovelRotation::ShovelRotation() :
		PIDSubsystem("ShovelRotation", 1.0, 0.0, 0.0)
{
	m_pMotor = new Talon(RobotMap::Shovel::shovelPivotMotor);
	m_pPot = new OzPotentiometer(
			RobotMap::Shovel::potentiometer, 5.0, 0.0); // stick with voltage readout for right now
	m_pShovelPivotLim = new OzLimitSwitch(RobotMap::Shovel::shovelPivotLimSwitch);

	SetInputRange(0.0, 5.0); // range of values returned from the potentiometer
	SetOutputRange(-0.25, 0.25); // start with the motor range

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
	SAFE_DELETE(m_pShovelPivotLim);
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

	//this only matters on the practice bot
	if(m_pShovelPivotLim->Get() && output < 0.0f)
		return;

	m_pMotor->Set(output);
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
