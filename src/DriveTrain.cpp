#include "DriveTrain.h"

DriveTrain::DriveTrain(uint32_t _frontLeft, uint32_t _rearLeft, uint32_t _frontRight, uint32_t _rearRight) : 
        drive(_frontLeft, _rearLeft, _frontRight, _rearRight)
{
}

DriveTrain::~DriveTrain()
{
}

void DriveTrain::ArcadeDrive(Joystick& stick)
{
    //put the stick values in a couple floats
    float xVal = stick.GetX();
    float yVal = stick.GetY();

    drive.ArcadeDrive(-yVal, -xVal);
}

void DriveTrain::Drive(float magnitude, float curve)
{
    drive.Drive(magnitude, curve);
}