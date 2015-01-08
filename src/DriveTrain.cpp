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

