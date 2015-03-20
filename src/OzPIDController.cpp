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
#include <cmath>


namespace OzPID
{

//helper functions for working with the OzPIDDerivLevelVector

//creates a vector with identical p, i, d, and f values of n components
void FillOzPIDDerivLevel(OzPIDDerivLevelVector& vec, float p, float i, float d, float f, float n)
{
	vec.resize(n);

	for(unsigned int j = 0; j < vec.size(); ++j)
	{
		vec[j] = {p,i,d,f};
	}
}

//this takes a vector and modifies the 'n'th component's p, i, d, and f values
void ModifyOzPIDDerivLevel(OzPIDDerivLevelVector& vec, float p, float i, float d, float f, float n)
{
	if(n >= vec.size())
		vec.resize(n);

	vec[n] = {p,i,d,f};
}

//this takes a vector and modifies the 'n'th components p value
void ModifyOzPIDDerivLevelP(OzPIDDerivLevelVector& vec, float p, float n)
{
	if(n >= vec.size())
		vec.resize(n);

	vec[n].p = p;
}

//this takes a vector and modifies the 'n'th components i value
void ModifyOzPIDDerivLevelI(OzPIDDerivLevelVector& vec, float i, float n)
{
	if(n >= vec.size())
		vec.resize(n);

	vec[n].i = i;
}

//this takes a vector and modifies the 'n'th components d value
void ModifyOzPIDDerivLevelD(OzPIDDerivLevelVector& vec, float d, float n)
{
	if(n >= vec.size())
		vec.resize(n);

	vec[n].d = d;
}

//this takes a vector and modifies the 'n'th components f value
void ModifyOzPIDDerivLevelF(OzPIDDerivLevelVector& vec, float f, float n)
{
	if(n >= vec.size())
		vec.resize(n);

	vec[n].f = f;
}

}

static const char *kP = "p";
static const char *kI = "i";
static const char *kD = "d";
static const char *kF = "f";
static const char *kSetpoint = "setpoint";
static const char *kEnabled = "enabled";


/**
 * Allocate a PID object with the given constants for P, I, D
 * @param vec for the PIDF of all of the derivative levels
 * @param source The PIDSource object that is used to get values
 * @param output The PIDOutput object that is set to the output value
 * @param period the loop time for doing calculations. This particularly effects calculations of the
 * integral and differental terms. The default is 50ms.
 */
OzPIDController::OzPIDController(OzPIDDerivLevelVector vec,
								PIDSource *source, PIDOutput *output,
								float period, unsigned char n) :
	m_semaphore (0)
{
	Initialize(vec, source, output, period, n);
}


void OzPIDController::Initialize(OzPIDDerivLevelVector vec,
								PIDSource *source, PIDOutput *output,
								float period, unsigned char n)
{
	m_table = NULL;

	m_semaphore = initializeMutexNormal();

	m_controlLoop = new Notifier(OzPIDController::CallCalculate, this);

	//validate the pidf values
	unsigned int oldSize = vec.size();
	if(n >= vec.size())
		vec.resize(n);

	//fill the empty space with the highest order derivative PIDF values
	for(unsigned int i = oldSize; i < vec.size(); ++i)
	{
		vec[i] = vec[oldSize - 1];
	}

	m_PIDF = vec;

	m_maximumOutput = 1.0;
	m_minimumOutput = -1.0;

	m_maximumInput = 0;
	m_minimumInput = 0;

	m_continuous = false;
	m_enabled = false;
	//m_setpoint = 0;

	m_prevError = 0;
	m_totalError = 0;

	//initialize the tolerances to 0.05, this is not necessary, but is good practice
	m_tolerances.resize(n+1);
	for(unsigned int i = 0; i < m_tolerances.size(); ++i)
		m_tolerances[i] = OzPIDTolerance(0.05f, kNoTolerance);

	m_result = 0;

	m_pidInput = source;
	m_pidOutput = output;
	m_period = period;

	m_prevUpdateClock = clock();

	//initialize the calculated inputs to 0
	m_pidInputCalc.resize(n+1);
	for(unsigned int i = 0; i < m_pidInputCalc.size(); ++i)
		m_pidInputCalc[i] = i;

	m_controlLoop->StartPeriodic(m_period);

	static int32_t instances = 0;
	instances++;
	HALReport(HALUsageReporting::kResourceType_PIDController, instances);
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
	std::vector<float> pidInputDerivOld;
	std::vector<float> pidInputDerivNew;
	clock_t prevUpdateTime;
	clock_t currUpdateTime = clock();


	CRITICAL_REGION(m_semaphore)
	{
		pidInput = m_pidInput;
		pidOutput = m_pidOutput;
		enabled = m_enabled;
		pidInput = m_pidInput;
		pidInputDerivOld = m_pidInputCalc;
		prevUpdateTime = m_prevUpdateClock;
		m_prevUpdateClock = currUpdateTime;
	}
	END_REGION;

	if (pidInput == NULL) return;
	if (pidOutput == NULL) return;


	if (enabled)
	{
		{
			Synchronized sync(m_semaphore);

			//first, calculate the new derivatives
			CalcDeriv(pidInputDerivOld, pidInputDerivNew, pidInput->PIDGet(), currUpdateTime - prevUpdateTime);

			//is the speed/acceleration/whatever within the threshold to lower the PID derivative?
			for(unsigned int i = 0; i < pidInputDerivOld.size(); ++i)
			{
				if (OnnTarget_tunsafe(i))
				{
					//if the derivative level changes, then reset I and D settings
					m_currentSetpointIndex = i;
					m_totalError = 0.0f;
					m_prevError = 0.0f;
				}

				//finally, if none of the values are close enough, resort to the n order derivative
				if(i == pidInputDerivOld.size() - 1)
				{
					//if the current setpoint is not the last order setpoint, then reset these values
					if(m_currentSetpointIndex != i)
					{
						m_totalError = 0.0f;
						m_prevError = 0.0f;
					}

					//if the current setpoint index is highest order derivative, then do NOT reset the error values
					m_currentSetpointIndex = i;
				}
			}

			//get the current order PID input
			float input = 0.0f;
			if(m_currentSetpointIndex == 0)
				input = pidInput->PIDGet();
			else
				input = pidInputDerivOld[m_currentSetpointIndex];

			float P, I, D, F;
			P = m_PIDF[m_currentSetpointIndex].p;
			I = m_PIDF[m_currentSetpointIndex].i;
			D = m_PIDF[m_currentSetpointIndex].d;
			F = m_PIDF[m_currentSetpointIndex].f;


			//for the setpoint, change the sign depending on which side of the 0 order derivative it is
			float setpoint = 0.0f;
			if(setpoint == 0)
				setpoint = m_setpoint[0];
			else
				setpoint = m_setpoint[m_currentSetpointIndex] * GetnError(0) > 0 ? 1 : -1;
			float result;
			PIDOutput *pidOutput;

			m_error = setpoint - input;
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

			if(I != 0)
			{
				double potentialIGain = (m_totalError + m_error) * I;
				if (potentialIGain < m_maximumOutput)
				{
					if (potentialIGain > m_minimumOutput)
						m_totalError += m_error;
					else
						m_totalError = m_minimumOutput / I;
				}
				else
				{
					m_totalError = m_maximumOutput / I;
				}
			}

			m_result = P * m_error + I * m_totalError + D * (m_error - m_prevError) + setpoint * F;
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
 *
 */
void OzPIDController::SetPIDn(float p, float i, float d, float n)
{
	CRITICAL_REGION(m_semaphore)
	{
		OzPID::ModifyOzPIDDerivLevel(m_PIDF, p, i, d, 0.0f, n);
	}
	END_REGION
}

/**
 *
 */
void OzPIDController::SetPIDn(float p, float i, float d, float f, float n)
{
	CRITICAL_REGION(m_semaphore)
	{
		OzPID::ModifyOzPIDDerivLevel(m_PIDF, p, i, d, f, n);
	}
	END_REGION
}

/**
 *
 */
void OzPIDController::SetPID(OzPIDDerivLevelVector derivLevelVector)
{
	CRITICAL_REGION(m_semaphore)
	{
		m_PIDF = derivLevelVector;
	}
	END_REGION
}

/**
 *
 */
OzPIDDerivLevelVector OzPIDController::GetPID()
{
	OzPIDDerivLevelVector ret;
	CRITICAL_REGION(m_semaphore)
	{
		ret = m_PIDF;
	}
	END_REGION

	return ret;
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

	//make sure the setpoint chain does not have any positives or negatives in it (except for 0 deriv)
	VALIDATE_SETPOINT_CHAIN(setpointChain);

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
 *
 */
float OzPIDController::GetnPosition(unsigned char n)
{
	float temp;

	CRITICAL_REGION(m_semaphore)
	{
		if(n == 0)
			temp = m_pidInput->PIDGet();
		if(n >= m_pidInputCalc.size())
			temp =  0.0f;
		else
			temp = m_pidInputCalc[n];
	}
	END_REGION

	return temp;
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
 * Returns the setpoint of n derivative of the current input
 *
 */
float OzPIDController::GetnSetpoint(unsigned char n)
{
	//if the n derivative does not exist, return 0
	if(m_setpoint.size() <= n)
		return 0.0f;

	float setpoint;
	CRITICAL_REGION(m_semaphore)
	{
		setpoint = m_setpoint[n];
	}
	END_REGION
	return setpoint;
}

/**
 *
 */
void OzPIDController::SetnDeriv(unsigned char n)
{
	CRITICAL_REGION(m_semaphore)
	{
		m_pidInputCalc.resize(n);
	}
	END_REGION
}

/**
 *
 */
unsigned char OzPIDController::GetnDeriv()
{
	unsigned char n;
	CRITICAL_REGION(m_semaphore)
	{
		n = m_pidInputCalc.size();
	}
	END_REGION
	return n;
}

/**
 * Returns the current PID input derivative (i.e. position velocity acceleration) depending on current derivative
 */
float OzPIDController::GetCurrentPIDInput()
{
	float temp = 0.0f;
	CRITICAL_REGION(m_semaphore)
	{
		if(m_currentSetpointIndex == 0)
			temp = m_pidInput->PIDGet();
		else
			temp = m_pidInputCalc[m_currentSetpointIndex];
	}
	END_REGION

	return temp;
}

/**
 * Retruns the current difference of the input from the setpoint
 * @return the current error
 */
float OzPIDController::GetError()
{
	return GetnError(m_currentSetpointIndex);
}

/**
 *
 */
float OzPIDController::GetnError(unsigned char n)
{
	float error;
	double pidInput;
	CRITICAL_REGION(m_semaphore)
	{
		//to avoid the staircase effect on at least 0 derivative
		if(n == 0)
			pidInput = m_pidInput->PIDGet();
		else
			pidInput = m_pidInputCalc[n];
	}
	END_REGION;
	error =	this->GetnSetpoint(n) - pidInput;
	return error;
}

/*
 * Set the percentage error which is considered tolerable for use with
 * OnTarget.
 * @param percentage error which is tolerable
 */
void OzPIDController::SetnTolerance(float percent, unsigned char n)
{
	CRITICAL_REGION(m_semaphore)
	{
		if(n > m_tolerances.size())
		{
			m_tolerances.resize(n + 1);
		}

		m_tolerances[n] = OzPIDTolerance(percent, kPercentTolerance);
	}
	END_REGION;
}

/*
 * Set the percentage error which is considered tolerable for use with
 * OnTarget.
 * @param percentage error which is tolerable
 */
void OzPIDController::SetPercentnTolerance(float percent, unsigned char n)
{
	CRITICAL_REGION(m_semaphore)
	{
		if(n > m_tolerances.size())
		{
			m_tolerances.resize(n + 1);
		}

		m_tolerances[n] = OzPIDTolerance(percent, kPercentTolerance);
	}
	END_REGION;
}

/*
 * Set the absolute error which is considered tolerable for use with
 * OnTarget.
 * @param percentage error which is tolerable
 */
void OzPIDController::SetAbsolutenTolerance(float absTolerance, unsigned char n)
{
	CRITICAL_REGION(m_semaphore)
	{
		if(n > m_tolerances.size())
		{
			m_tolerances.resize(n + 1);
		}

		m_tolerances[n] = OzPIDTolerance(absTolerance, kAbsoluteTolerance);
	}
	END_REGION;
}

/*
 * Return true if the error is within the percentage of the total input range,
 * determined by SetTolerance. This assumes that the maximum and minimum input
 * were set using SetInput.
 * Currently this just reports on target as the actual value passes through the setpoint.
 * Ideally it should be based on being within the tolerance for some period of time.
 */
bool OzPIDController::OnTarget()
{
	return OnnTarget(m_currentSetpointIndex);
}

/**
 *
 */
bool OzPIDController::OnnTarget(unsigned char n)
{
	bool temp;
	double error = GetnError(n);
	CRITICAL_REGION(m_semaphore)
	{
		OzPIDTolerance tolerance = m_tolerances[n];
		switch (tolerance.second)
		{
		case kPercentTolerance:
			temp = fabs(error) < (tolerance.first / 100 * (m_maximumInput - m_minimumInput));
			break;
		case kAbsoluteTolerance:
			temp = fabs(error) < tolerance.first;
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
 *
 *
 */
bool OzPIDController::OnnTarget_tunsafe(unsigned char n)
{
	double error = GetnError(n);

	OzPIDTolerance tolerance = m_tolerances[n];
	switch (tolerance.second)
	{
	case kPercentTolerance:
		return fabs(error) < (tolerance.first / 100 * (m_maximumInput - m_minimumInput));
		break;
	case kAbsoluteTolerance:
		return fabs(error) < tolerance.first;
		break;
	//TODO: this case needs an error
	case kNoTolerance:
		return false;

	default://THIS CONTROL PATH SHOULD NEVER BE HIT
		return false;
	}
}

/**
 * Begin running the OzPIDController
 */
void OzPIDController::Enable()
{
	CRITICAL_REGION(m_semaphore)
	{
		m_enabled = true;
		m_prevUpdateClock = clock();//update this when calling enable to make sure the position delta isn't calculated from the old time
	}
	END_REGION;

	if (m_table != NULL)
	{
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

	if (m_table != NULL)
	{
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

std::string OzPIDController::GetSmartDashboardType()
{
	return "OzPIDController";
}

void OzPIDController::InitTable(ITable* table)
{
	if(m_table!=NULL)
		m_table->RemoveTableListener(this);
	m_table = table;
	if(m_table!=NULL)
	{
		std::string i_s = "";
		OzPIDDerivLevelVector pidVec;

		CRITICAL_REGION(m_semaphore)
		{
			pidVec = m_PIDF;
		}
		END_REGION

		for(unsigned int i = 0; i < GetnDeriv(); ++i)
		{
			i_s = std::to_string(i);

			m_table->PutNumber(kSetpoint + i_s, GetnSetpoint(i));

			m_table->PutNumber(kP + i_s, pidVec[i].p);
			m_table->PutNumber(kI + i_s, pidVec[i].i);
			m_table->PutNumber(kD + i_s, pidVec[i].d);
			m_table->PutNumber(kF + i_s, pidVec[i].f);
		}
		m_table->PutBoolean(kEnabled, IsEnabled());
		m_table->AddTableListener(this, false);
	}
}

void OzPIDController::ValidateSetpointChain(OzPIDSetpointChain &chain)
{
	for(unsigned int i = 1; i < chain.size(); ++i)
	{
		chain[i] = fabsf(chain[i]);
	}
}

ITable* OzPIDController::GetTable(){
	return m_table;
}

void OzPIDController::ValueChanged(ITable* source, const std::string& key, EntryValue value, bool isNew)
{
	std::string keyNumber_s = "";
	keyNumber_s += (key[key.size() - 1]);



	unsigned char keyNumber = std::stoi(keyNumber_s);//minus one to get the last value

	if (key==kP + keyNumber_s || key==kI + keyNumber_s || key==kD + keyNumber_s || key==kF + keyNumber_s)
	{
		OzPIDDerivLevelVector pidfValues;
		CRITICAL_REGION(m_semaphore)
		{
			pidfValues = m_PIDF;
		}
		END_REGION

		if (pidfValues[keyNumber].p != m_table->GetNumber(kP + keyNumber_s) ||
			pidfValues[keyNumber].i != m_table->GetNumber(kI + keyNumber_s) ||
			pidfValues[keyNumber].d != m_table->GetNumber(kD + keyNumber_s) ||
			pidfValues[keyNumber].f != m_table->GetNumber(kF + keyNumber_s)  )
		{
			OzPID::ModifyOzPIDDerivLevel(pidfValues,
					m_table->GetNumber(kP + keyNumber_s, 0.0),
					m_table->GetNumber(kI + keyNumber_s, 0.0),
					m_table->GetNumber(kD + keyNumber_s, 0.0),
					m_table->GetNumber(kF + keyNumber_s, 0.0), keyNumber);
		}

		CRITICAL_REGION(m_semaphore)
		{
			m_PIDF = pidfValues;
		}
		END_REGION
	}
	else if (key==kSetpoint + keyNumber_s && m_setpoint[keyNumber] != value.f)
	{

		SetnSetpoint(value.f, keyNumber);

	}
	else if (key==kEnabled && m_enabled != value.b)
	{
		if (value.b)
		{
			Enable();
		}
		else
		{
			Disable();
		}
	}
}

void OzPIDController::UpdateTable()
{

}

void OzPIDController::StartLiveWindowMode()
{
	Disable();
}

void OzPIDController::StopLiveWindowMode()
{

}

void OzPIDController::SetnSetpoint(float setpoint, unsigned char n)
{
	setpoint = fabsf(setpoint);

	CRITICAL_REGION(m_semaphore)
	{
		m_setpoint[n] = setpoint;
	}
	END_REGION
}

void OzPIDController::CalcDeriv(std::vector<float> oldDerivatives, std::vector<float> &newDerivatives,
		float curr0DerivReading, float deltaTime_s)
{
	unsigned char size = oldDerivatives.size();

	//get position as a baseline value
	newDerivatives.resize(size);
	newDerivatives[0] = curr0DerivReading;

	for(unsigned char i = 1; i < size; ++i)
	{
		//calculate each derivative as final minus initial all over time.
		newDerivatives[i] = (newDerivatives[i-1] - oldDerivatives[i-1])/ deltaTime_s;
	}
}

