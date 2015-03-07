#ifndef DriveTrain_H
#define DriveTrain_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class DriveTrain: public Subsystem
{
private:

	SpeedController* m_pFrontLeft;
	//SpeedController* m_pRearLeft;
	SpeedController* m_pFrontRight;
	//SpeedController* m_pRearRight;

	Encoder* m_pLeftEncoder;
	Encoder* m_pRightEncoder;

	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	DriveTrain();
	~DriveTrain();
	void InitDefaultCommand();

	/*
	 * Motor Accessors
	 */
	void StopMotors();
	float getLeft(){return m_pFrontLeft->Get();}
	float getRight(){return m_pFrontRight->Get();}

	/*
	 * Driving Commands
	 */
	void ArcadeDrivePeriodic(Joystick* stick);
	void RaceDrivePeriodic(Joystick* stick);
	void TankDrivePeriodic(Joystick* stick1, Joystick* stick2);
	void DriveStraight(float motorVal);

	/*
	 * Motor Controls
	 */
	void setLeft(float val);
	void setRight(float val);

	/*
	 * Encoder Control Functions
	 */
	void resetEncoderLeft(){m_pLeftEncoder->Reset();}
	void resetEncoderRight(){m_pRightEncoder->Reset();}

	/*
	 * Encoder Accessor Functions
	 */

	//NOTE: to get the rotations, use getEncDistance, or getEncRate

	double	getEncCountLeft()		{return double(m_pLeftEncoder->Get());			}
	int		getEncRawCountLeft()	{return m_pLeftEncoder->GetRaw();				}
	double 	getEncDistanceLeft()	{return m_pLeftEncoder->GetDistance();			}
	double 	getEncRateLeft()		{return m_pLeftEncoder->GetRate();				}
	bool 	getEncDirectionLeft()	{return m_pLeftEncoder->GetDirection();			}
	bool 	getEncStoppedLeft()		{return m_pLeftEncoder->GetStopped();			}

	double	getEncCountRight()		{return double(m_pRightEncoder->Get());			}
	int		getEncRawCountRight()	{return m_pRightEncoder->GetRaw();				}
	double 	getEncDistanceRight()	{return m_pRightEncoder->GetDistance();			}
	double 	getEncRateRight()		{return m_pRightEncoder->GetRate();				}
	bool 	getEncDirectionRight()	{return m_pRightEncoder->GetDirection();		}
	bool 	getEncStoppedRight()	{return m_pRightEncoder->GetStopped();			}
};

#endif
