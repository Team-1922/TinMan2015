/*
 * OzOzPIDController.cpp
 *
 *  Created on: Mar 16, 2015
 *      Author: Kevin
 */

#include "OzPIDController.h"
#include "Notifier.h"
#include "PIDSource.h"
#include "PIDOutput.h"
#include <math.h>
#include <vector>
#include "HAL/cpp/Synchronized.hpp"
#include "HAL/HAL.hpp"

static const char *kP = "p";
static const char *kI = "i";
static const char *kD = "d";
static const char *kF = "f";
static const char *kSetpoint = "setpoint";
static const char *kEnabled = "enabled";


/**
 * Allocate a PID object with the given constants for P, I, D
 * @param Kp the proportional coefficient
 * @param Ki the integral coefficient
 * @param Kd the derivative coefficient
 * @param source The PIDSource object that is used to get values
 * @param output The PIDOutput object that is set to the output value
 * @param period the loop time for doing calculations. This particularly effects calculations of the
 * integral and differental terms. The default is 50ms.
 */
OzPIDController::OzPIDController(float Kp, float Ki, float Kd,
								PIDSource *source, PIDOutput *output,
								float period) :
	m_semaphore (0)
{
	Initialize(Kp, Ki, Kd, 0.0f, source, output, period);
}

/**
 * Allocate a PID object with the given constants for P, I, D
 * @param Kp the proportional coefficient
 * @param Ki the integral coefficient
 * @param Kd the derivative coefficient
 * @param source The PIDSource object that is used to get values
 * @param output The PIDOutput object that is set to the output value
 * @param period the loop time for doing calculations. This particularly effects calculations of the
 * integral and differental terms. The default is 50ms.
 */
OzPIDController::OzPIDController(float Kp, float Ki, float Kd, float Kf,
								PIDSource *source, PIDOutput *output,
								float period) :
	m_semaphore (0)
{
	Initialize(Kp, Ki, Kd, Kf, source, output, period);
}


void OzPIDController::Initialize(float Kp, float Ki, float Kd, float Kf,
								PIDSource *source, PIDOutput *output,
								float period)
{
	m_table = NULL;

	m_semaphore = initializeMutexNormal();

	m_controlLoop = new Notifier(OzPIDController::CallCalculate, this);

	m_P = Kp;
	m_I = Ki;
	m_D = Kd;
	m_F = Kf;

	m_maximumOutput = 1.0;
	m_minimumOutput = -1.0;

	m_maximumInput = 0;
	m_minimumInput = 0;

	m_continuous = false;
	m_enabled = false;
	//m_setpoint = 0;

	m_prevError = 0;
	m_totalError = 0;
	m_tolerance = .05;

	m_result = 0;

	m_pidInput = source;
	m_pidOutput = output;
	m_period = period;

	m_controlLoop->StartPeriodic(m_period);

	static int32_t instances = 0;
	instances++;
	HALReport(HALUsageReporting::kResourceType_PIDController, instances);

	m_toleranceType = kNoTolerance;
}

/**
 * Free the PID object
 */
OzPIDController::~OzPIDController()
{
	takeMutex(m_semaphore);
	deleteMutex(m_semaphore);
	delete m_controlLoop;
}

/**
 * Call the Calculate method as a non-static method. This avoids having to prepend
 * all local variables in that method with the class pointer. This way the "this"
 * pointer will be set up and class variables can be called more easily.
 * This method is static and called by the Notifier class.
 * @param controller the address of the PID controller object to use in the background loop
 */
void OzPIDController::CallCalculate(void *controller)
{
	OzPIDController *control = (OzPIDController*) controller;
	control->Calculate();
}

 /**
  * Read the input, calculate the output accordingly, and write to the output.
  * This should only be called by the Notifier indirectly through CallCalculate
  * and is created during initialization.
  */
void OzPIDController::Calculate()
{
	bool enabled;
	PIDSource *pidInput;
	PIDOutput *pidOutput;

	CRITICAL_REGION(m_semaphore)
	{
		pidInput = m_pidInput;
		pidOutput = m_pidOutput;
		enabled = m_enabled;
		pidInput = m_pidInput;
	}
	END_REGION;

	if (pidInput == NULL) return;
	if (pidOutput == NULL) return;

	if (enabled)
	{
		{
			Synchronized sync(m_semaphore);
      float input = pidInput->PIDGet();
      float result;
      PIDOutput *pidOutput;

			m_error = m_setpoint - input;
			if (m_continuous)
			{
				if (fabs(m_error) > (m_maximumInput - m_minimumInput) / 2)
				{
					if (m_error > 0)
					{
						m_error = m_error - m_maximumInput + m_minimumInput;
					}
					else
					{
						m_error = m_error + m_maximumInput - m_minimumInput;
					}
				}
			}

			if(m_I != 0)
			{
				double potentialIGain = (m_totalError + m_error) * m_I;
				if (potentialIGain < m_maximumOutput)
				{
					if (potentialIGain > m_minimumOutput)
						m_totalError += m_error;
					else
						m_totalError = m_minimumOutput / m_I;
				}
				else
				{
					m_totalError = m_maximumOutput / m_I;
				}
			}

			m_result = m_P * m_error + m_I * m_totalError + m_D * (m_error - m_prevError) + m_setpoint * m_F;
			m_prevError = m_error;

			if (m_result > m_maximumOutput) m_result = m_maximumOutput;
			else if (m_result < m_minimumOutput) m_result = m_minimumOutput;

			pidOutput = m_pidOutput;
			result = m_result;

      pidOutput->PIDWrite(result);
		}
	}
}

/**
 * Set the PID Controller gain parameters.
 * Set the proportional, integral, and differential coefficients.
 * @param p Proportional coefficient
 * @param i Integral coefficient
 * @param d Differential coefficient
 */
void OzPIDController::SetPID(float p, float i, float d)
{
	CRITICAL_REGION(m_semaphore)
	{
		m_P = p;
		m_I = i;
		m_D = d;
	}
	END_REGION;

	if (m_table != NULL) {
		m_table->PutNumber("p", m_P);
		m_table->PutNumber("i", m_I);
		m_table->PutNumber("d", m_D);
	}
}

/**
 * Set the PID Controller gain parameters.
 * Set the proportional, integral, and differential coefficients.
 * @param p Proportional coefficient
 * @param i Integral coefficient
 * @param d Differential coefficient
 * @param f Feed forward coefficient
 */
void OzPIDController::SetPID(float p, float i, float d, float f)
{
	CRITICAL_REGION(m_semaphore)
	{
		m_P = p;
		m_I = i;
		m_D = d;
		m_F = f;
	}
	END_REGION;

	if (m_table != NULL) {
		m_table->PutNumber("p", m_P);
		m_table->PutNumber("i", m_I);
		m_table->PutNumber("d", m_D);
		m_table->PutNumber("f", m_F);
	}
}

/**
 * Get the Proportional coefficient
 * @return proportional coefficient
 */
float OzPIDController::GetP()
{
	CRITICAL_REGION(m_semaphore)
	{
		return m_P;
	}
	END_REGION;
}

/**
 * Get the Integral coefficient
 * @return integral coefficient
 */
float OzPIDController::GetI()
{
	CRITICAL_REGION(m_semaphore)
	{
		return m_I;
	}
	END_REGION;
}

/**
 * Get the Differential coefficient
 * @return differential coefficient
 */
float OzPIDController::GetD()
{
	CRITICAL_REGION(m_semaphore)
	{
		return m_D;
	}
	END_REGION;
}

/**
 * Get the Feed forward coefficient
 * @return Feed forward coefficient
 */
float OzPIDController::GetF()
{
	CRITICAL_REGION(m_semaphore)
	{
		return m_F;
	}
	END_REGION;
}

/**
 * Return the current PID result
 * This is always centered on zero and constrained the the max and min outs
 * @return the latest calculated output
 */
float OzPIDController::Get()
{
	float result;
	CRITICAL_REGION(m_semaphore)
	{
		result = m_result;
	}
	END_REGION;
	return result;
}

/**
 *  Set the PID controller to consider the input to be continuous,
 *  Rather then using the max and min in as constraints, it considers them to
 *  be the same point and automatically calculates the shortest route to
 *  the setpoint.
 * @param continuous Set to true turns on continuous, false turns off continuous
 */
void OzPIDController::SetContinuous(bool continuous)
{
	CRITICAL_REGION(m_semaphore)
	{
		m_continuous = continuous;
	}
	END_REGION;
}

/**
 * Sets the maximum and minimum values expected from the input.
 *
 * @param minimumInput the minimum value expected from the input
 * @param maximumInput the maximum value expected from the output
 */
void OzPIDController::SetInputRange(float minimumInput, float maximumInput)
{
	CRITICAL_REGION(m_semaphore)
	{
		m_minimumInput = minimumInput;
		m_maximumInput = maximumInput;
	}
	END_REGION;

	SetSetpointChain(m_setpoint);
}

/**
 * Sets the minimum and maximum values to write.
 *
 * @param minimumOutput the minimum value to write to the output
 * @param maximumOutput the maximum value to write to the output
 */
void OzPIDController::SetOutputRange(float minimumOutput, float maximumOutput)
{
	CRITICAL_REGION(m_semaphore)
	{
		m_minimumOutput = minimumOutput;
		m_maximumOutput = maximumOutput;
	}
	END_REGION;
}

/**
 * Set the setpoint for the OzPIDController
 * @param setpoint the desired setpoint
 */
void OzPIDController::SetSetpointChain(OzPIDSetpointChain setpointChain)
{
	//do nothing if the setpoint chain is empty
	if(!ASSERT_SETPOINT_CHAIN(setpointChain))
		return;

	CRITICAL_REGION(m_semaphore)
	{
		m_setpoint = setpointChain;
		//for maximumInput and minimumInput, only do testing on the 0th derivative field
		if (m_maximumInput > m_minimumInput)
		{
			if (setpointChain[0] > m_maximumInput)
				m_setpoint[0] = m_maximumInput;
			else if (setpointChain[0] < m_minimumInput)
				m_setpoint[0] = m_minimumInput;
		}
	}
	END_REGION;

	if (m_table != NULL)
	{
		for(unsigned char i = 0; i < setpointChain.size(); ++i)
			m_table->PutNumber("setpoint " + std::to_string(i), m_setpoint[i]);
	}
}

/**
 * Returns the current setpoint chain of the OzPIDController
 * @return the current setpoint chain
 */
OzPIDSetpointChain OzPIDController::GetSetpointChain()
{
	OzPIDSetpointChain setpoint;
	CRITICAL_REGION(m_semaphore)
	{
		setpoint = m_setpoint;
	}
	END_REGION;
	return setpoint;
}

/**
 * Returns the current setpoint of the OzPIDController
 * @return the current setpoint
 */
float OzPIDController::GetCurrentSetpoint()
{
	float setpoint;
	CRITICAL_REGION(m_semaphore)
	{
		setpoint = m_setpoint[m_currentSetpointIndex];
	}
	END_REGION
	return setpoint;
}

/**
 * Returns the current PID input derivative (i.e. position velocity acceleration) depending on current derivative
 */
float OzPIDController::GetCurrentPIDInput()
{

}

/**
 * Retruns the current difference of the input from the setpoint
 * @return the current error
 */
float OzPIDController::GetError()
{
	float error;
	double pidInput;
	CRITICAL_REGION(m_semaphore)
	{
		pidInput = m_pidInput->PIDGet();
	}
	END_REGION;
	error = GetSetpoint() - pidInput;
	return error;
}

/*
 * Set the percentage error which is considered tolerable for use with
 * OnTarget.
 * @param percentage error which is tolerable
 */
void OzPIDController::SetTolerance(float percent)
{
	CRITICAL_REGION(m_semaphore)
	{
		m_toleranceType = kPercentTolerance;
		m_tolerance = percent;
	}
	END_REGION;
}

/*
 * Set the percentage error which is considered tolerable for use with
 * OnTarget.
 * @param percentage error which is tolerable
 */
void OzPIDController::SetPercentTolerance(float percent)
{
	CRITICAL_REGION(m_semaphore)
	{
		m_toleranceType = kPercentTolerance;
		m_tolerance = percent;
	}
	END_REGION;
}

/*
 * Set the absolute error which is considered tolerable for use with
 * OnTarget.
 * @param percentage error which is tolerable
 */
void OzPIDController::SetAbsoluteTolerance(float absTolerance)
{
	CRITICAL_REGION(m_semaphore)
	{
		m_toleranceType = kAbsoluteTolerance;
		m_tolerance = absTolerance;
	}
	END_REGION;
}

/*
 * Return true if the error is within the percentage of the total input range,
 * determined by SetTolerance. This asssumes that the maximum and minimum input
 * were set using SetInput.
 * Currently this just reports on target as the actual value passes through the setpoint.
 * Ideally it should be based on being within the tolerance for some period of time.
 */
bool OzPIDController::OnTarget()
{
	bool temp;
  double error = GetError();
	CRITICAL_REGION(m_semaphore)
	{
		switch (m_toleranceType) {
		case kPercentTolerance:
			temp = fabs(error) < (m_tolerance / 100 * (m_maximumInput - m_minimumInput));
			break;
		case kAbsoluteTolerance:
			temp = fabs(error) < m_tolerance;
			break;
		//TODO: this case needs an error
		case kNoTolerance:
			temp = false;
		}
	}
	END_REGION;
	return temp;
}

/**
 * Begin running the OzPIDController
 */
void OzPIDController::Enable()
{
	CRITICAL_REGION(m_semaphore)
	{
		m_enabled = true;
	}
	END_REGION;

	if (m_table != NULL) {
		m_table->PutBoolean("enabled", true);
	}
}

/**
 * Stop running the OzPIDController, this sets the output to zero before stopping.
 */
void OzPIDController::Disable()
{
	CRITICAL_REGION(m_semaphore)
	{
		m_pidOutput->PIDWrite(0);
		m_enabled = false;
	}
	END_REGION;

	if (m_table != NULL) {
		m_table->PutBoolean("enabled", false);
	}
}

/**
 * Return true if OzPIDController is enabled.
 */
bool OzPIDController::IsEnabled()
{
	bool enabled;
	CRITICAL_REGION(m_semaphore)
	{
		enabled = m_enabled;
	}
	END_REGION;
	return enabled;
}

/**
 * Reset the previous error,, the integral term, and disable the controller.
 */
void OzPIDController::Reset()
{
	Disable();

	CRITICAL_REGION(m_semaphore)
	{
		m_prevError = 0;
		m_totalError = 0;
		m_result = 0;
	}
	END_REGION;
}

std::string OzPIDController::GetSmartDashboardType(){
	return "OzPIDController";
}

void OzPIDController::InitTable(ITable* table){
	if(m_table!=NULL)
		m_table->RemoveTableListener(this);
	m_table = table;
	if(m_table!=NULL){
		m_table->PutNumber(kP, GetP());
		m_table->PutNumber(kI, GetI());
		m_table->PutNumber(kD, GetD());
		m_table->PutNumber(kF, GetF());
		m_table->PutNumber(kSetpoint, GetSetpoint());
		m_table->PutBoolean(kEnabled, IsEnabled());
		m_table->AddTableListener(this, false);
	}
}

ITable* OzPIDController::GetTable(){
	return m_table;
}

void OzPIDController::ValueChanged(ITable* source, const std::string& key, EntryValue value, bool isNew){
	if (key==kP || key==kI || key==kD || key==kF) {
		if (m_P != m_table->GetNumber(kP) || m_I != m_table->GetNumber(kI) || m_D != m_table->GetNumber(kD) || m_F != m_table->GetNumber(kF)  ) {
			SetPID(m_table->GetNumber(kP, 0.0), m_table->GetNumber(kI, 0.0), m_table->GetNumber(kD, 0.0), m_table->GetNumber(kF, 0.0));
		}
	} else if (key==kSetpoint && m_setpoint != value.f) {
		SetSetpoint(value.f);
	} else if (key==kEnabled && m_enabled != value.b) {
		if (value.b) {
			Enable();
		} else {
			Disable();
		}
	}
}

void OzPIDController::UpdateTable() {

}

void OzPIDController::StartLiveWindowMode() {
	Disable();
}

void OzPIDController::StopLiveWindowMode() {

}




