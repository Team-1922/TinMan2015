#ifndef DRIVE_TRAIN_H
#define DRIVE_TRAIN_H

#include "WPILib.h"
#include <memory>

enum MotorLocation
{
    FRONT_LEFT = 0,
    REAR_LEFT = 1,
    FRONT_RIGHT = 2,
    REAR_RIGHT = 3
};

class DriveTrain : public MotorSafety, public ErrorBase
{
    public:
        DriveTrain(uint32_t _frontLeft, uint32_t _rearLeft, uint32_t _frontRight, uint32_t _rearRight);
        ~DriveTrain();

        //Same as RobotDrive in WPILib Doc.
        void ArcadeDrive(Joystick& stick); //reference to avoid nullptr possibility
        void TankDrive(Joystick& leftStick, Joystick& rightStick);

        //set forward speed
        void Drive(float magnitude);

        //set forward speed separately left and right
        void Drive(float leftMag, float rightMag);

        //invert the x and y axis controls for inerted motors
        void InvertDrive(bool newVal = false);
        bool IsInverted();

        //rotate in place
        void TurnInPlace(float rotSpeed);

        //inherited functions
        //Motor Safety
        virtual void SetExpiration(float timeout = DEFAULT_SAFETY_EXPIRATION);
        virtual float GetExpiration();
        virtual bool IsAlive();
        virtual void StopMotor();
        virtual void SetSafetyEnabled(bool enabled);
        virtual bool IsSafetyEnabled();
        virtual void GetDescription(char *desc);

    private:

        void SetMotor(MotorLocation loc, float value);

        std::shared_ptr<SpeedController> frontLeft;
        std::shared_ptr<SpeedController> rearLeft;
        std::shared_ptr<SpeedController> frontRight;
        std::shared_ptr<SpeedController> rearRight;
        
        //true = positive, false = negative
        bool motorSign; 

        //Motor Safety
        float expiration;
        bool safetyEnabled;
        bool motorStopped;
        const char* name = "Team 1922 2015 Drive Train";
};

#endif
