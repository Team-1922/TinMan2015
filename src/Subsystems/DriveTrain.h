#ifndef DriveTrain_H
#define DriveTrain_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class DriveTrain: public Subsystem
{
private:

	SpeedController* m_pFrontLeft;
	SpeedController* m_pRearLeft;
	SpeedController* m_pFrontRight;
	SpeedController* m_pRearRight;

	Encoder* m_pLeftEncoder;
	Encoder* m_pRightEncoder;

	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	DriveTrain();
	~DriveTrain();
	void InitDefaultCommand();

	void StopMotors();
	void ArcadeDrivePeriodic(Joystick* stick);
	void RaceDrivePeriodic(Joystick* stick);
	void TankDrivePeriodic(Joystick* stick1, Joystick* stick2);
	void DriveStraight(float motorVal);

	/*
	 * Encoder Control Functions
	 */
	void resetEncoderLeft(){m_pLeftEncoder->Reset();}
	void resetEncoderRight(){m_pRightEncoder->Reset();}

	/*
	 * Encoder Accessor Functions
	 */

	double	getEncCountLeft()		{return double(m_pLeftEncoder->Get()) / 500.0;  }
	int		getEncRawCountLeft()	{return m_pLeftEncoder->GetRaw();				}
	double 	getEncDistanceLeft()	{return m_pLeftEncoder->GetDistance();			}
	double 	getEncRateLeft()		{return m_pLeftEncoder->GetRate()/500.0;		}
	bool 	getEncDirectionLeft()	{return m_pLeftEncoder->GetDirection();			}
	bool 	getEncStoppedLeft()		{return m_pLeftEncoder->GetStopped();			}

	double	getEncCountRight()		{return double(m_pRightEncoder->Get()) / 500.0; }
	int		getEncRawCountRight()	{return m_pRightEncoder->GetRaw();				}
	double 	getEncDistanceRight()	{return m_pRightEncoder->GetDistance();			}
	double 	getEncRateRight()		{return m_pRightEncoder->GetRate()/500.0;		}
	bool 	getEncDirectionRight()	{return m_pRightEncoder->GetDirection();		}
	bool 	getEncStoppedRight()	{return m_pRightEncoder->GetStopped();			}
};

#endif
