#ifndef DRIVE_TRAIN_H
#define DRIVE_TRAIN_H

#include "WPILib.h"
#include <memory>

class DriveTrain
{
    public:
        DriveTrain(uint32_t _frontLeft, uint32_t _rearLeft, uint32_t _frontRight, uint32_t _rearRight);
        ~DriveTrain();
        void ArcadeDrive(Joystick& stick); //reference to avoid nullptr possibility

        void Drive(float magnitude, float curve);

        void SetExpiration(float val){ drive.SetExpiration(val); }

    private:

        RobotDrive drive;
};

#endif
