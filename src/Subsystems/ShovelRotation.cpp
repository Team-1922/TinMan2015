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
			RobotMap::Shovel::potentiometer, 1.0, 0.0); // stick with voltage readout for right now

	SetInputRange(0.0, 5.0); // range of values returned from the potentiometer
	SetOutputRange(-1.0, 1.0); // start with the motor range

	// Use these to get going:
	// SetSetpoint() -  Sets where the PID controller should move the system
	//                  to
	// Enable() - Enables the PID controller.
}

ShovelRotation::~ShovelRotation()
{
	SAFE_DELETE(m_pMotor);
	SAFE_DELETE(m_pPot);
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
	return m_pPot->PIDGet();
}

void ShovelRotation::TickPotentiometer()
{
	m_pPot->Tick();
}
