#include "DriveTrain.h"

DriveTrain::DriveTrain(uint32_t _frontLeft, uint32_t _rearLeft, uint32_t _frontRight, uint32_t _rearRight)
{
    frontLeft  = std::shared_ptr<SpeedController>(new Talon(_frontLeft));
    rearLeft   = std::shared_ptr<SpeedController>(new Talon(_rearLeft));
    frontRight = std::shared_ptr<SpeedController>(new Talon(_frontRight));
    rearRight  = std::shared_ptr<SpeedController>(new Talon(_rearRight));
}

DriveTrain::~DriveTrain()
{
    //no explicit deconstructors with smart pointers
}

void DriveTrain::ArcadeDrive(Joystick& stick)
{
    //put the stick values in a couple floats
    float xVal = stick.GetX();
    float yVal = stick.GetY();

    //arcade drive
    float leftMotor  = yVal + xVal;
    float rightMotor = yVal - xVal;

    Drive(leftMotor, rightMotor);

    
    //Twist to turn in place?
    /*if (xVal == 0 && yVal == 0)
    {
        //assume positive twist is clockwise
        float tVal = stick.GetTwist();

        TurnInPlace(tVal);
    }*/
}

void DriveTrain::Drive(float magnitude)
{
    Drive(magnitude, magnitude);
}

void DriveTrain::Drive(float leftMag, float rightMag)
{
    frontLeft->Set(leftMag);
    rearLeft->Set(leftMag);

    frontRight->Set(rightMag);
    rearRight->Set(rightMag);
}

void DriveTrain::TurnInPlace(float rotSpeed)
{
    Drive(rotSpeed, -rotSpeed);
}