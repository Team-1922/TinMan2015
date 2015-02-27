#include "RackRotation.h"
#include "../RobotMap.h"
#include "SmartDashboard/SmartDashboard.h"
#include "LiveWindow/LiveWindow.h"
#include "../Commands/RackJoyControlled.h"
#include "../Utilities.h"
#include "../OzLimitSwitch.h"

#include <cmath>

RackRotation::RackRotation() :
		PIDSubsystem("RackRotation", RobotMap::Rack::PID::P, RobotMap::Rack::PID::I, RobotMap::Rack::PID::D)
{

	m_pMotor = new Talon(RobotMap::Rack::rackPivotMotor);
	m_pPot = new AnalogPotentiometer(
			RobotMap::Rack::potentiometer, 5.0f, 0.0f); // stick with voltage readout for right now

#ifndef COMP_BOT
	m_pLimitRotationForward = new OzLimitSwitch(RobotMap::Rack::rackLimitRotationForward);
	m_pLimitRotationBackward = new OzLimitSwitch(RobotMap::Rack::rackLimitRotationBackward);
#endif

	SetInputRange(0.0, 5.0); // range of values returned from the potentiometer
	SetOutputRange(-RobotMap::Rack::PID::extremeMotorVal, RobotMap::Rack::PID::extremeMotorVal); // start with the motor range
	SetAbsoluteTolerance(0.08);



//			RobotMap::Rack::potDegree,
//		    RobotMap::Rack::potDegreeOffset);

	// Use these to get going:
	// SetSetpoint() -  Sets where the PID controller should move the system
	//                  to
	// Enable() - Enables the PID controller.
	LiveWindow::GetInstance()->AddActuator("Rack", "PID", GetPIDController());

	Enable();

	SetSetpoint(GetPotVoltage());
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

/*#ifndef COMP_BOT
	//mind limit switches, NOTE: this only matters on the practice bot
	if(m_pLimitRotationBackward->Get() && output > 0.0f)
		return;

	//since rotating backwards is actually the forwards direction of the motor, change the inequality
	if(m_pLimitRotationForward->Get() && output < 0.0f)
		return;
#endif*/

	// if the target location is the "dump" location don't try to drive the motor - it could be driven past the store location by weight on the rack and
	// compressing the spring

	//TODO: this isn't working with live window
	/*if (Utilities::isEqual(GetSetpoint(),RobotMap::Rack::voltageDump, RobotMap::Rack::dumpEpsilon) && (GetPotVoltage() < RobotMap::Rack::voltageDump))
	{
		// if it is past the dump location and that is where want to be don't try to drive the motors
		return;
	}*/

	//if the shovel is past the dump position, and the reed switches are open, and the setpoint is past vertical, don't go
	//if((CommandBase::shovelRotation->GetPotVoltage() < RobotMap::Shovel::voltageDump + 0.15f) && CommandBase::shovelRotation->GetReed() && GetSetpoint() < (RobotMap::Rack::voltageStack + 0.15f))
	//	m_pMotor->Set(0);//stop the rack (this will

	//give it less power as it reaches the top; NOTE: this is not good math, but hey; it works
	float badAngle = GetPotVoltage() - RobotMap::Rack::voltageDump;
	float trueAngle = badAngle * 90.0f;

	if((output < 0.0f && trueAngle < 90.0f) || (output > 0.0f && trueAngle > 90.0f))
	{
		output *= fabs(cosf(DEGREES_TO_RADIANS(badAngle))) + 0.03 /*Make sure it goes at least a little bit*/;
	}
	else
	{
#ifdef COMP_BOT
		//TODO: get these values
		/*if(GetPotVoltage < 1.9f)
		{
			output = 0.1f;//backdrive a little bit
		}
		else if(GetPotVoltage() > 2.9)
		{
			output = -0.1f;
		}*/
#else
#endif

	}


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
