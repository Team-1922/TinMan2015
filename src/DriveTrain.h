#ifndef DRIVE_TRAIN_H
#define DRIVE_TRAIN_H

#include "WPILib.h"

class DriveTrain
{
    public:
        DriveTrain();
        ~DriveTrain();
        void ozDrive(Joystick *stick);

    private:
        SpeedController *frontLeft;
        SpeedController *rearLeft;
        SpeedController *frontRight;
        SpeedController *rearRight;
};

#endif
