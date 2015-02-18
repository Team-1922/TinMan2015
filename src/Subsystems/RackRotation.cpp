#include "RackRotation.h"
#include "../RobotMap.h"
#include "SmartDashboard/SmartDashboard.h"
#include "LiveWindow/LiveWindow.h"
#include "../Commands/RackJoyControlled.h"
#include "../Utilities.h"

RackRotation::RackRotation() :
		PIDSubsystem("RackRotation", 15.0, 0.0, 0.0)
{

	m_pMotor = new Talon(RobotMap::Rack::rackPivotMotor);
	m_pPot = new OzPotentiometer(
			RobotMap::Rack::potentiometer, 5.0f, 0.0f); // stick with voltage readout for right now

	SetInputRange(0.0, 5.0); // range of values returned from the potentiometer
	SetOutputRange(-0.25, 0.25); // start with the motor range

//			RobotMap::Rack::potDegree,
//		    RobotMap::Rack::potDegreeOffset);

	// Use these to get going:
	// SetSetpoint() -  Sets where the PID controller should move the system
	//                  to
	// Enable() - Enables the PID controller.
	LiveWindow::GetInstance()->AddActuator("Rack", "PID", GetPIDController());
}

RackRotation::~RackRotation()
{
	SAFE_DELETE(m_pMotor);
	SAFE_DELETE(m_pPot);
}

double RackRotation::ReturnPIDInput()
{
	// Return your input value for the PID loop
	// e.g. a sensor, like a potentiometer:
	// yourPot->SetAverageVoltage() / kYourMaxVoltage;	
	return m_pPot->Get();

}

void RackRotation::UsePIDOutput(double output)
{
	// Use output to drive your system, like a motor
	// e.g. yourMotor->Set(output);
	m_pMotor->Set(output);
}

void RackRotation::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	SetDefaultCommand(new RackJoyControlled());
}

float RackRotation::GetPotVoltage()
{
	return m_pPot->Get();
}

void RackRotation::TickPotentiometer()
{
	m_pPot->Tick();
}
