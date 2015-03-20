/*
 * OzPIDSubsystem.h
 *
 *  Created on: Mar 16, 2015
 *      Author: Kevin
 */

#ifndef OZPIDSUBSYSTEM_H_
#define OZPIDSUBSYSTEM_H_


#include "Commands/Subsystem.h"
#include "OzPIDController.h"
#include "PIDSource.h"
#include "PIDOutput.h"


/**
 * This class is designed to handle the case where there is a {@link Subsystem}
 * which uses a single {@link PIDController} almost constantly (for instance,
 * an elevator which attempts to stay at a constant height).
 *
 * <p>It provides some convenience methods to run an internal {@link PIDController}.
 * It also allows access to the internal {@link PIDController} in order to give total control
 * to the programmer.</p>
 *
 */
class OzPIDSubsystem : public Subsystem, public PIDOutput, public PIDSource
{
public:
	OzPIDSubsystem(const char *name, OzPIDDerivLevelVector pidf, unsigned char nDeriv);
	OzPIDSubsystem(const char *name, OzPIDDerivLevelVector pidf, double period, unsigned char nDeriv);
	OzPIDSubsystem(OzPIDDerivLevelVector pidf, unsigned char nDeriv);
	OzPIDSubsystem(OzPIDDerivLevelVector pidf, double period, unsigned char nDeriv);
	virtual ~OzPIDSubsystem();

	void Enable();
	void Disable();

	void SetSetpointChain(OzPIDSetpointChain setpointChain);
	//void SetSetpointRelative(double deltaSetpoint);
	void SetInputRange(float minimumInput, float maximumInput);
	void SetOutputRange(float minimumOutput, float maximumOutput);
	OzPIDSetpointChain GetSetpointChain();

	//gets the current "position" of the nth Derivative, where 0 is just the PID source,
	//and 3 is the third derivative of the PID source
	float GetPosition();

	float GetnPosition(unsigned char n);
	float GetnSetpoint(unsigned char n);

	virtual void SetAbsolutenTolerance(float absValue, unsigned char n = 0);
	virtual void SetPercentnTolerance(float percent, unsigned char n = 0);
	virtual bool OnTarget();

protected:
	friend OzPIDController;

	// PIDOutput interface
	virtual void PIDWrite(float output);

	// PIDSource interface
	virtual double PIDGet();

	OzPIDController *GetPIDController();

	virtual double ReturnPIDInput() = 0;
	virtual void UsePIDOutput(double output) = 0;

private:
	/** The internal {@link OzPIDController} */
	OzPIDController *m_controller;

public:
	virtual void InitTable(ITable* table);
	virtual std::string GetSmartDashboardType();
};

#endif
