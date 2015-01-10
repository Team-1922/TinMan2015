#ifndef DRIVE_TRAIN_H
#define DRIVE_TRAIN_H

#include "WPILib.h"
#include <memory>

class DriveTrain : public MotorSafety, public ErrorBase
{
    public:
        DriveTrain(uint32_t _frontLeft, uint32_t _rearLeft, uint32_t _frontRight, uint32_t _rearRight);
        ~DriveTrain();
        void ArcadeDrive(Joystick& stick); //reference to avoid nullptr possibility

        void Drive(float magnitude);
        void Drive(float leftMag, float rightMag);
        void InvertDrive(bool newVal = false);

        void TurnInPlace(float rotSpeed);

        //inherited functions

        //Motor Safety
        virtual void SetExpiration(float timeout = DEFAULT_SAFETY_EXPIRATION);
        virtual float GetExpiration()               { return expiration; }
        virtual bool IsAlive();
        virtual void StopMotor();
        virtual void SetSafetyEnabled(bool enabled) { safetyEnabled = enabled; }
        virtual bool IsSafetyEnabled()              { return safetyEnabled; }
        virtual void GetDescription(char *desc)     { memcpy(desc, name, sizeof(name)); }

    private:
        std::shared_ptr<SpeedController> frontLeft;
        std::shared_ptr<SpeedController> rearLeft;
        std::shared_ptr<SpeedController> frontRight;
        std::shared_ptr<SpeedController> rearRight;
        
        //true = positive, false = negative
        bool motorSign; 

        //Motor Safety
        float expiration;
        bool safetyEnabled;
        const char* name = "Team 1922 Drive Train";
};

#endif
