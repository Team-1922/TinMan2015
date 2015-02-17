#include "RackRotation.h"
#include "../RobotMap.h"
#include "SmartDashboard/SmartDashboard.h"
#include "LiveWindow/LiveWindow.h"

RackRotation::RackRotation() :
		PIDSubsystem("RackRotation", 1.0, 0.0, 0.0)
{

	m_pMotor = new Talon(RobotMap::Rack::rackPivotMotor);
	m_pPot = new OzPotentiometer(
			RobotMap::Rack::potentiometer, 1.0, 0.0); // stick with voltage readout for right now

	SetInputRange(-2.5, 2.5); // range of values returned from the potentiometer
	SetOutputRange(-1.0, 1.0); // start with the motor range

//			RobotMap::Rack::potDegree,
//		    RobotMap::Rack::potDegreeOffset);

	// Use these to get going:
	// SetSetpoint() -  Sets where the PID controller should move the system
	//                  to
	// Enable() - Enables the PID controller.
}

double RackRotation::ReturnPIDInput()
{
	// Return your input value for the PID loop
	// e.g. a sensor, like a potentiometer:
	// yourPot->SetAverageVoltage() / kYourMaxVoltage;	
	return m_pPot->PIDGet();

}

void RackRotation::UsePIDOutput(double output)
{
	// Use output to drive your system, like a motor
	// e.g. yourMotor->Set(output);
	m_pMotor->set(output);
}

void RackRotation::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	setDefaultCommand(new RackJoyControlled());
}

double RackRotation::getPotVoltage()
{
	return m_pPot->PIDGet();
}

