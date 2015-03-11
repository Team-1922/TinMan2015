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

/*#ifndef COMP_BOT
	m_pLimitRotationForward = new OzLimitSwitch(RobotMap::Rack::rackLimitRotationForward);
	m_pLimitRotationBackward = new OzLimitSwitch(RobotMap::Rack::rackLimitRotationBackward);
#endif*/

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

/*#ifndef COMP_BOT
	SAFE_DELETE(m_pLimitRotationForward);
	SAFE_DELETE(m_pLimitRotationBackward);
#endif*/
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
	/*float badAngle = GetPotVoltage() - RobotMap::Rack::voltageDump;
	float potVoltage = GetPotVoltage();
	float trueAngle = (RobotMap::Rack::voltageDump - potVoltage) * 90.0f;

	//if its within a certain threshold of vertical, then use the REAL angle to use cosine to mitigate oscillation
	if(Utilities::isEqual(RobotMap::Rack::voltageVertical, potVoltage, 0.15))//hopefully this will keep it from shaking at top
	{
		output *= fabs(cosf(DEGREES_TO_RADIANS(trueAngle))) + 0.05;
	}
	if((output < 0.0f && potVoltage > RobotMap::Rack::voltageVertical) || (output > 0.0f && potVoltage < RobotMap::Rack::voltageVertical))
	{
		output *= fabs(cosf(DEGREES_TO_RADIANS(badAngle))) + 0.03;

		//multiply by negative one to invert the throttle; add one to make this go from 0 to two, then divide by two to normalize the value
		float throttle = CommandBase::oi->GetOperatorThrottle();

		output *= throttle;

		//if it is within a range from the bottom (negative, then just stop the rack)
		if(throttle < 0.1)
		{
			SetSetpointRelative(0.0f);
		}
	}
	else
	{
#ifdef COMP_BOT
		if((potVoltage < RobotMap::Rack::voltageBackdriveFront) && (output < 0.0f))
		{
			output = 0.1f;//backdrive a little bit
		}
		else if((potVoltage > RobotMap::Rack::voltageBackdriveRear) && (output > 0.0f))
		{
			output = -0.15f;
		}
#else
#endif

	}*/

	//this makes the operator have control over the max speed of the rack; this is better because all the way down still gives power

	float val = CommandBase::oi->GetOperatorThrottle();

	//change it so the output is between half and full extreme power (0.666667f <= val <= 1.0f)
	val /= 3.0f;
	val += 0.666667f;

	//between min and max load
	output *= val;


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
