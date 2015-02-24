#include "RackRotation.h"
#include "../RobotMap.h"
#include "SmartDashboard/SmartDashboard.h"
#include "LiveWindow/LiveWindow.h"
#include "../Commands/RackJoyControlled.h"
#include "../Utilities.h"
#include "../OzLimitSwitch.h"


RackRotation::RackRotation() :
		PIDSubsystem("RackRotation", 15.0, 0.0, 0.0)
{

	m_pMotor = new Talon(RobotMap::Rack::rackPivotMotor);
	m_pPot = new AnalogPotentiometer(
			RobotMap::Rack::potentiometer, 5.0f, 0.0f); // stick with voltage readout for right now

#ifndef COMP_BOT
	m_pLimitRotationForward = new OzLimitSwitch(RobotMap::Rack::rackLimitRotationForward);
	m_pLimitRotationBackward = new OzLimitSwitch(RobotMap::Rack::rackLimitRotationBackward);
#endif

	SetInputRange(0.0, 5.0); // range of values returned from the potentiometer
	SetOutputRange(-0.35, 0.35); // start with the motor range
	SetAbsoluteTolerance(0.03);



//			RobotMap::Rack::potDegree,
//		    RobotMap::Rack::potDegreeOffset);

	// Use these to get going:
	// SetSetpoint() -  Sets where the PID controller should move the system
	//                  to
	// Enable() - Enables the PID controller.
	LiveWindow::GetInstance()->AddActuator("Rack", "PID", GetPIDController());

	Enable();
}

RackRotation::~RackRotation()
{
	SAFE_DELETE(m_pMotor);
	SAFE_DELETE(m_pPot);

#ifndef COMP_BOT
	SAFE_DELETE(m_pLimitRotationForward);
	SAFE_DELETE(m_pLimitRotationBackward);
#endif
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

#ifndef COMP_BOT
	//mind limit switches, NOTE: this only matters on the practice bot
	if(m_pLimitRotationBackward->Get() && output > 0.0f)
		return;

	//since rotating backwards is actually the forwards direction of the motor, change the inequality
	if(m_pLimitRotationForward->Get() && output < 0.0f)
		return;
#endif

	// if the target location is the "dump" location don't try to drive the motor - it could be driven past the store location by weight on the rack and
	// compressing the spring

	//TODO: this isn't working with live window
	/*if (Utilities::isEqual(GetSetpoint(),RobotMap::Rack::voltageDump, RobotMap::Rack::dumpEpsilon) && (GetPotVoltage() < RobotMap::Rack::voltageDump))
	{
		// if it is past the dump location and that is where want to be don't try to drive the motors
		return;
	}*/

	m_pMotor->Set(output);
}

void RackRotation::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new RackJoyControlled());
}

float RackRotation::GetPotVoltage()
{
	return m_pPot->Get();
}

void RackRotation::TickPotentiometer()
{
	//m_pPot->Tick();
}
