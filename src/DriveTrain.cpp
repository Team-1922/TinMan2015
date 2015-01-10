#include "DriveTrain.h"

DriveTrain::DriveTrain()
{
    frontLeft  = std::shared_ptr<SpeedController>(new Talon(0));
    rearLeft   = std::shared_ptr<SpeedController>(new Talon(1));
    frontRight = std::shared_ptr<SpeedController>(new Talon(2));
    rearRight  = std::shared_ptr<SpeedController>(new Talon(3));
}

DriveTrain::~DriveTrain()
{
    //no explicit deconstructors with smart pointers
}

void DriveTrain :: ozDrive(Joystick* stick)
{
    //put the stick values in a couple floats
    float xVal = stick->GetX();
    float yVal = stick->GetY();

    //arcade drive
    float leftMotor  = yVal + xVal;
    float rightMotor = yVal - xVal;

    frontLeft->Set(leftMotor);
    rearLeft->Set(leftMotor);

    frontRight->Set(rightMotor);
    rearRight->Set(rightMotor);

}
