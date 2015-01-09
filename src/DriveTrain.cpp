#include "DriveTrain.h"

DriveTrain::DriveTrain()
{
    frontLeft  = new Talon(0);
    rearLeft   = new Talon(1);
    frontRight = new Talon(2);
    rearRight  = new Talon(3);
}

DriveTrain::~DriveTrain()
{
    delete frontLeft;
    delete rearLeft;
    delete frontRight;
    delete rearRight;
}

void DriveTrain :: ozDrive(Joystick* stick){
//put the stick values in a couple floats
float xVal =stick->GetX();
float yVal= stick->GetY();

//arcade drive
float leftMotor = yVal + xVal;
float rightMotor = yVal - xVal;

frontLeft->Set(leftMotor);
rearLeft->Set(leftMotor);

frontRight->Set(rightMotor);
rearRight->Set(rightMotor);

}
