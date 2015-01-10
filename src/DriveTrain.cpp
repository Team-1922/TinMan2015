#include "DriveTrain.h"

DriveTrain::DriveTrain(uint32_t _frontLeft, uint32_t _rearLeft, uint32_t _frontRight, uint32_t _rearRight) : 
        drive(_frontLeft, _rearLeft, _frontRight, _rearRight)
{
    //frontLeft  = std::shared_ptr<SpeedController>(new Talon(_frontLeft));
    //rearLeft   = std::shared_ptr<SpeedController>(new Talon(_rearLeft));
    //frontRight = std::shared_ptr<SpeedController>(new Talon(_frontRight));
    //rearRight  = std::shared_ptr<SpeedController>(new Talon(_rearRight));
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
    /*float leftMotor  = yVal + xVal;
    float rightMotor = yVal - xVal;

    Drive(leftMotor, rightMotor);*/

    drive.ArcadeDrive(-yVal, xVal);
}

void DriveTrain::InvertDrive(bool newVal)
{
    motorSign = newVal;
}

void DriveTrain::Drive(float magnitude, float curve)
{
    drive.Drive(magnitude, curve);
}

/*void DriveTrain::Drive(float leftMag, float rightMag)
{
    
    //invert motor if necessary
    leftMag  = motorSign ? leftMag  : -leftMag;
    rightMag = motorSign ? rightMag : -rightMag;

    frontLeft->Set(leftMag);
    rearLeft->Set(leftMag);

    frontRight->Set(rightMag);
    rearRight->Set(rightMag);
}*/

void DriveTrain::TurnInPlace(float rotSpeed)
{
    Drive(rotSpeed, -rotSpeed);
}