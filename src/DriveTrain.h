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
        //void Drive(float leftMag, float rightMag);
        void InvertDrive(bool newVal = false);

        void TurnInPlace(float rotSpeed);


    private:
        //std::shared_ptr<SpeedController> frontLeft;
        //std::shared_ptr<SpeedController> rearLeft;
        //std::shared_ptr<SpeedController> frontRight;
        //std::shared_ptr<SpeedController> rearRight;
        
        //true = positive, false = negative
        bool motorSign; 

        RobotDrive drive;
};

#endif
