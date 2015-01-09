#ifndef DRIVE_TRAIN_H
#define DRIVE_TRAIN_H

#include "WPILib.h"

class DriveTrain
{
    public:
        DriveTrain();
        ~DriveTrain();

    private:
        RobotDrive ozDrive(Joystick *stick);
        SpeedController *frontLeft;
        SpeedController *rearLeft;
        SpeedController *frontRight;
        SpeedController *rearRight;
};

#endif
