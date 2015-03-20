/*
 * OzPIDController.h
 *
 *  Created on: Mar 16, 2015
 *      Author: Kevin
 */

#ifndef OZPIDCONTROLLER_H_
#define OZPIDCONTROLLER_H_

#include "Base.h"
#include "Controller.h"
#include "LiveWindow/LiveWindow.h"
#include "HAL/Semaphore.hpp"
#include <ctime>
#include <cmath>

class PIDOutput;
class PIDSource;
class Notifier;

#ifndef SAFE_DELETE
#define SAFE_DELETE(__x__) {if(nullptr != __x__){delete __x__; __x__ = nullptr;}}
#define SAFE_DELETE_ARRAY(__x__){if(nullptr != __x__){delete[] __x__; __x__ = nullptr;}}
#endif

//where OzPIDSetpointChain[n] = (d^nx)/(dt^n) * PIDInput; NOTE: if PIDInput is position, then velocity is PIDInput units per second
typedef std::vector<float> OzPIDSetpointChain;

struct OzPIDStruct
{
public:
	float p;
	float i;
	float d;
	float f;

	OzPIDStruct()
	{
		p = 0.0f;
		i = 0.0f;
		d = 0.0f;
		f = 0.0f;
	}

	OzPIDStruct(const float* pidf)
	{
		if(sizeof(pidf) != sizeof(this))
		{
			p = 0.0f;
			i = 0.0f;
			d = 0.0f;
			f = 0.0f;
		}
		else
		{
			p = pidf[0];
			i = pidf[1];
			d = pidf[2];
			f = pidf[3];
		}
	}

	OzPIDStruct(const float& kP, const float& kI, const float& kD, const float& kF)
	{
		p = kP;
		i = kI;
		d = kD;
		f = kF;
	}
};

class OzPIDDerivLevelVector : public std::vector<OzPIDStruct>
{
public:

	//for easy construction of the vector
	/*OzPIDDerivLevelVector& operator =(const OzPIDStruct* rParam)
	{
		clear();
		for(unsigned int i = 0; i < sizeof(rParam) / sizeof(OzPIDStruct); ++i)
		{
			push_back(rParam[i]);
		}

		return *this;
	}*/

	OzPIDDerivLevelVector()
	{
		clear();
	}

	OzPIDDerivLevelVector(const OzPIDStruct* rParam)
	{
		clear();
		for(unsigned int i = 0; i < sizeof(rParam) / sizeof(OzPIDStruct); ++i)
		{
			push_back(rParam[i]);
		}
	}

	OzPIDDerivLevelVector& operator =(const OzPIDStruct rParam[])
	{
		clear();
		for(unsigned int i = 0; i < sizeof(rParam) / sizeof(OzPIDStruct); ++i)
		{
			push_back(rParam[i]);
		}

		return *this;
	}
};

//macro to help make this OzPIDDerivLevelVector; NOTE: ONLY DEFINE THIS IN SOURCES FILES; IT CREATES JIBBERISH NAMESPACES
#define DECLARE_OZ_PID_DERIV_LEVEL_VECTOR(__NAME__, __DATA__) const OzPIDStruct __NAME__##__RAW__DATA__[] = __DATA__;OzPIDDerivLevelVector __NAME__ = __NAME__##__RAW__DATA__;
#define MACRO_ARRAY(...) __VA_ARGS__
//EXAMPLE:
/*
 *
 * DECLARE_OZ_PID_DERIV_LEVEL_VECTOR(TestData,
		MACRO_ARRAY({OzPIDStruct(0.0f, 0.0f, 0.0f, 0.0f), OzPIDStruct(0.0f, 0.0f, 0.0f, 0.0f), OzPIDStruct(0.0f, 0.0f, 0.0f, 0.0f)}));
 *
 */

namespace OzPID
{
//helper functions for working with the OzPIDDerivLevelVector

//creates a vector with identical p, i, d, and f values of n components
void FillOzPIDDerivLevel(OzPIDDerivLevelVector& vec, float p, float i, float d, float f, float n);

//this takes a vector and modifies the 'n'th component's p, i, d, and f values
void ModifyOzPIDDerivLevel(OzPIDDerivLevelVector& vec, float p, float i, float d, float f, float n);

//this takes a vector and modifies the 'n'th components p value
void ModifyOzPIDDerivLevelP(OzPIDDerivLevelVector& vec, float p, float n);

//this takes a vector and modifies the 'n'th components i value
void ModifyOzPIDDerivLevelI(OzPIDDerivLevelVector& vec, float i, float n);

//this takes a vector and modifies the 'n'th components d value
void ModifyOzPIDDerivLevelD(OzPIDDerivLevelVector& vec, float d, float n);

//this takes a vector and modifies the 'n'th components f value
void ModifyOzPIDDerivLevelF(OzPIDDerivLevelVector& vec, float f, float n);

}

//used to determine if the setpoint chain is valid
#define ASSERT_SETPOINT_CHAIN(__chain__) (__chain__.size() != 0)

#define VALIDATE_SETPOINT_CHAIN(__chain__) {OzPIDController::ValidateSetpointChain(__chain__);}

#define INFINITE_INPUT (float)0xFFFFFFFF

/**
 * Class implements a PID Control Loop.
 *
 * Creates a separate thread which reads the given PIDSource and takes
 * care of the integral calculations, as well as writing the given
 * PIDOutput
 *
 * n or nDeriv is the derivative calculated, so if the OzPIDController
 * takes nDeriv of 2 as parameters, it will go up to and calculate
 * second derivative
 *
 * NOTE: all links in the setpoint chain higher than 0 derivative
 * will be a SCALAR QUANTITY. i.e. always positive.  This means
 * the side of the 0th target the current PIDInput is on
 * determines direction
 */
class OzPIDController : public LiveWindowSendable, public Controller, public ITableListener
{
public:
	OzPIDController(OzPIDDerivLevelVector pidf, PIDSource *source, PIDOutput *output, float period =
			0.05, unsigned char nDeriv = 2);
	virtual ~OzPIDController();
	virtual float Get();
	virtual void SetContinuous(bool continuous = true);
	virtual void SetInputRange(float minimumInput, float maximumInput);
	virtual void SetOutputRange(float minimumOutput, float maximumOutput);
	virtual void SetPIDn(float p, float i, float d, float n);
	virtual void SetPIDn(float p, float i, float d, float f, float n);
	virtual void SetPID(OzPIDDerivLevelVector pidf);

	virtual OzPIDDerivLevelVector GetPID();

	virtual void SetSetpointChain(OzPIDSetpointChain setpointChain);
	virtual OzPIDSetpointChain GetSetpointChain();

	virtual float GetnPosition(unsigned char n);//returns the n derivative of the input

	virtual float GetCurrentSetpoint();
	virtual float GetnSetpoint(unsigned char n);

	virtual void  SetnDeriv(unsigned char n); //n is the maximum derivative of the input that will be calculated
	virtual unsigned char GetnDeriv();

	virtual float GetCurrentPIDInput();

	virtual float GetError();
	virtual float GetnError(unsigned char n);

	virtual void SetnTolerance(float percent, unsigned char n);
	virtual void SetAbsolutenTolerance(float absValue, unsigned char n);
	virtual void SetPercentnTolerance(float percentValue, unsigned char n);
	virtual bool OnTarget();
	virtual bool OnnTarget(unsigned char n);

	virtual void Enable();
	virtual void Disable();
	virtual bool IsEnabled();

	virtual void Reset();

	virtual void InitTable(ITable* table);

	//NOTE: you never need to call this; it is handled internally
	static void ValidateSetpointChain(OzPIDSetpointChain &chain);

private:
	//float m_P;			// factor for "proportional" control
	//float m_I;			// factor for "integral" control
	//float m_D;			// factor for "derivative" control
	//float m_F;			// factor for "feed forward" control
	OzPIDDerivLevelVector m_PIDF;

	float m_maximumOutput;	// |maximum output|
	float m_minimumOutput;	// |minimum output|
	float m_maximumInput;		// maximum input - limit setpoint to this
	float m_minimumInput;		// minimum input - limit setpoint to this
	bool m_continuous;	// do the endpoints wrap around? eg. Absolute encoder
	bool m_enabled; 			//is the pid controller enabled
	bool m_destruct; // should the calculate thread stop running
	float m_prevError;	// the prior sensor input (used to compute velocity)
	double m_totalError; //the sum of the errors for use in the integral calc
	unsigned char m_currentSetpointIndex; //the index of the setpoint vector that is currently in use
	enum __TOLERANCE_TYPE__
	{
		kAbsoluteTolerance,
		kPercentTolerance,
		kNoTolerance
	};

	typedef std::pair<float, __TOLERANCE_TYPE__> OzPIDTolerance;

	std::vector<OzPIDTolerance> m_tolerances;	//the percetage or absolute error that is considered on target
	OzPIDSetpointChain m_setpoint;
	float m_error;
	float m_result;
	float m_period;

	clock_t m_prevUpdateClock;

	std::vector<float> m_pidInputCalc; //the calculated input derivatives, where 0 is 0th derivative of the input

	MUTEX_ID m_semaphore;

	PIDSource *m_pidInput;
	PIDOutput *m_pidOutput;

	Notifier* m_controlLoop;

	void Initialize(OzPIDDerivLevelVector pidf, PIDSource *source, PIDOutput *output,
			float period = 0.05, unsigned char n = 2);
	static void CallCalculate(void *controller);

	virtual ITable* GetTable();
	virtual std::string GetSmartDashboardType();
	virtual void ValueChanged(ITable* source, const std::string& key, EntryValue value, bool isNew);
	virtual void UpdateTable();
	virtual void StartLiveWindowMode();
	virtual void StopLiveWindowMode();

	//this is private, because NO ONE EXCEPT FOR THE LIVE WINDOW CALLBACK SHOULD USE THIS
	virtual void SetnSetpoint(float setpoint, unsigned char n);

	//NEVER CALL THESE EXCEPT WITHIN A CRITICAL REGION BLOCK
	virtual bool OnnTarget_tunsafe(unsigned char n);

	static void CalcDeriv(std::vector<float> oldDerivatives, std::vector<float> &newDerivatives,
			float curr0DerivReading, float deltaTime_s);
protected:
	ITable* m_table;
	void Calculate();

	DISALLOW_COPY_AND_ASSIGN(OzPIDController);
};



#endif /* OZPIDCONTROLLER_H_ */
