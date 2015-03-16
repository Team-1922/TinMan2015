/*
 * OzOzPIDSubsystem.cpp
 *
 *  Created on: Mar 16, 2015
 *      Author: Kevin
 */


#include "OzPIDSubsystem.h"
#include "OzPIDController.h"
#include "float.h"

 // XXX max and min are not used?

OzPIDSubsystem::OzPIDSubsystem(const char *name, double p, double i, double d) :
  Subsystem(name)
{
	m_controller = new OzPIDController(p, i, d, this, this);
}

OzPIDSubsystem::OzPIDSubsystem(const char *name, double p, double i, double d, double f) :
 Subsystem(name)
{
	m_controller = new OzPIDController(p, i, d, f, this, this);
}

OzPIDSubsystem::OzPIDSubsystem(const char *name, double p, double i, double d, double f,
  double period) :
  Subsystem(name)
{
	m_controller = new OzPIDController(p, i, d, f, this, this, period);
}

OzPIDSubsystem::OzPIDSubsystem(double p, double i, double d) :
  Subsystem("OzPIDSubsystem")
{
	m_controller = new OzPIDController(p, i, d, this, this);
}

OzPIDSubsystem::OzPIDSubsystem(double p, double i, double d, double f) :
  Subsystem("OzPIDSubsystem")
{
	m_controller = new OzPIDController(p, i, d, f, this, this);
}

OzPIDSubsystem::OzPIDSubsystem(double p, double i, double d, double f, double period) :
		Subsystem("OzPIDSubsystem")
{
	m_controller = new OzPIDController(p, i, d, f, this, this, period);
}

OzPIDSubsystem::~OzPIDSubsystem()
{
	delete m_controller;
}

void OzPIDSubsystem::Enable()
{
	m_controller->Enable();
}

void OzPIDSubsystem::Disable()
{
	m_controller->Disable();
}


OzPIDController *OzPIDSubsystem::GetPIDController()
{
	return m_controller;
}

void OzPIDSubsystem::SetSetpointChain(OzPIDSetpointChain setpointChain)
{
	m_controller->SetSetpoint(setpoint);
}

void OzPIDSubsystem::SetSetpointRelative(double deltaSetpoint)
{
	SetSetpoint(GetSetpoint() + deltaSetpoint);
}

double OzPIDSubsystem::GetSetpoint()
{
	return m_controller->GetSetpoint();
}

void OzPIDSubsystem::SetInputRange(float minimumInput, float maximumInput)
{
	m_controller->SetInputRange(minimumInput, maximumInput);
}

 /*
  * Set the absolute error which is considered tolerable for use with
  * OnTarget.
  * @param percentage error which is tolerable
  */
void OzPIDSubsystem::SetAbsoluteTolerance(float absValue) {
 m_controller->SetAbsoluteTolerance(absValue);
}

 /*
  * Set the percentage error which is considered tolerable for use with
  * OnTarget.
  * @param percentage error which is tolerable
  */
void OzPIDSubsystem::SetPercentTolerance(float percent)
{
	m_controller->SetPercentTolerance(percent);
}

 /*
  * Return true if the error is within the percentage of the total input range,
  * determined by SetTolerance. This asssumes that the maximum and minimum input
  * were set using SetInput. Use OnTarget() in the IsFinished() method of commands
  * that use this subsystem.
  *
  * Currently this just reports on target as the actual value passes through the setpoint.
  * Ideally it should be based on being within the tolerance for some period of time.
  *
  * @return true if the error is within the percentage tolerance of the input range
  */
bool OzPIDSubsystem::OnTarget()
{
	return m_controller->OnTarget();
}

double OzPIDSubsystem::GetPosition()
{
	return ReturnPIDInput();
}

void OzPIDSubsystem::PIDWrite(float output)
{
	UsePIDOutput(output);
}

double OzPIDSubsystem::PIDGet()
{
	return ReturnPIDInput();
}


std::string OzPIDSubsystem::GetSmartDashboardType()
{
	return "PIDCommand";
}

void OzPIDSubsystem::InitTable(ITable* table)
{
	m_controller->InitTable(table);
	Subsystem::InitTable(table);
}


