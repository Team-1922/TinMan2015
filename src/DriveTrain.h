#ifndef DRIVE_TRAIN_H
#define DRIVE_TRAIN_H

#include "WPILib.h"
#include <memory>

class DriveTrain
{
    public:
        DriveTrain();
        ~DriveTrain();
        void ozDrive(Joystick *stick);

    private:
        std::shared_ptr<SpeedController> frontLeft;
        std::shared_ptr<SpeedController> rearLeft;
        std::shared_ptr<SpeedController> frontRight;
        std::shared_ptr<SpeedController> rearRight;
};

#endif
