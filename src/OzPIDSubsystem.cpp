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

OzPIDSubsystem::OzPIDSubsystem(const char *name, OzPIDDerivLevelVector pidf, unsigned char nDeriv) :
  Subsystem(name)
{
	m_controller = new OzPIDController(pidf, this, this, 0.05f, nDeriv);
}

OzPIDSubsystem::OzPIDSubsystem(const char *name, OzPIDDerivLevelVector pidf,
  double period, unsigned char nDeriv) :
  Subsystem(name)
{
	m_controller = new OzPIDController(pidf, this, this, period, nDeriv);
}

OzPIDSubsystem::OzPIDSubsystem(OzPIDDerivLevelVector pidf, unsigned char nDeriv) :
  Subsystem("OzPIDSubsystem")
{
	m_controller = new OzPIDController(pidf, this, this, 0.05f, nDeriv);
}

OzPIDSubsystem::OzPIDSubsystem(OzPIDDerivLevelVector pidf, double period, unsigned char nDeriv) :
		Subsystem("OzPIDSubsystem")
{
	m_controller = new OzPIDController(pidf, this, this, period, nDeriv);
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
	m_controller->SetSetpointChain(setpointChain);
}

float OzPIDSubsystem::GetPosition()
{
	return ReturnPIDInput();
}

float OzPIDSubsystem::GetnPosition(unsigned char n)
{
	return m_controller->GetnPosition(n);
}

float OzPIDSubsystem::GetnSetpoint(unsigned char n)
{
	//don't lock the OzPIDController more than we have to
	if(n == 0)
		return GetPosition();

	return m_controller->GetnSetpoint(n);
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
void OzPIDSubsystem::SetAbsolutenTolerance(float absValue, unsigned char n)
{
	m_controller->SetAbsolutenTolerance(absValue, n);
}

 /*
  * Set the percentage error which is considered tolerable for use with
  * OnTarget.
  * @param percentage error which is tolerable
  */
void OzPIDSubsystem::SetPercentnTolerance(float percent, unsigned char n)
{
	m_controller->SetPercentnTolerance(percent, n);
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


