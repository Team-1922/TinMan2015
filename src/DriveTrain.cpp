#include "DriveTrain.h"

DriveTrain::DriveTrain(uint32_t _frontLeft, uint32_t _rearLeft, uint32_t _frontRight, uint32_t _rearRight)
{
    expiration = DEFAULT_SAFETY_EXPIRATION;
    safetyEnabled = true;
    motorStopped = false;

    frontLeft  = std::shared_ptr<SpeedController>(new Talon(_frontLeft));
    rearLeft   = std::shared_ptr<SpeedController>(new Talon(_rearLeft));
    frontRight = std::shared_ptr<SpeedController>(new Talon(_frontRight));
    rearRight  = std::shared_ptr<SpeedController>(new Talon(_rearRight));
}

DriveTrain::~DriveTrain()
{
    //no explicit deconstructors with smart pointers
}

void DriveTrain::ArcadeDrive(Joystick& stick)
{
    //put the stick values in a couple floats
    float xVal = stick.GetX();
    float yVal = stick.GetY();

    //arcade drive
    float leftMotor  = yVal + xVal;
    float rightMotor = yVal - xVal;

    Drive(leftMotor, rightMotor);
}

void DriveTrain::TankDrive(Joystick& leftStick, Joystick& rightStick)
{
    //a thin wrapper
    Drive(leftStick.GetY(), rightStick.GetY());
}

void DriveTrain::InvertDrive(bool newVal)
{
    motorSign = newVal;
}

bool DriveTrain::IsInverted()
{
    return motorSign;
}

void DriveTrain::Drive(float magnitude)
{
    Drive(magnitude, magnitude);
}

void DriveTrain::Drive(float leftMag, float rightMag)
{
    SetMotor(FRONT_LEFT, leftMag);
    SetMotor(REAR_LEFT, leftMag);

    SetMotor(FRONT_RIGHT, rightMag);
    SetMotor(REAR_RIGHT, rightMag);
}

void DriveTrain::TurnInPlace(float rotSpeed)
{
    Drive(rotSpeed, -rotSpeed);
}

void DriveTrain::SetMotor(MotorLocation loc, float value)
{
    if (motorStopped)
        return;

    //invert the value
    value = motorSign ? value : -value;

    switch (loc)
    {
    case FRONT_LEFT:
        frontLeft->Set(value);
        break;
    case REAR_LEFT:
        rearLeft->Set(value);
        break;
    case FRONT_RIGHT:
        frontRight->Set(value);
        break;
    case REAR_RIGHT:
        rearRight->Set(value);
        break;
    }
}

//motor safety functions
void DriveTrain::SetExpiration(float timeout)
{
    expiration = timeout;
}

float DriveTrain::GetExpiration()
{
    return expiration;
}

bool DriveTrain::IsAlive()
{
    //if any of the motors are getting power
    return (frontLeft->Get()  || 
            rearLeft->Get()   || 
            frontRight->Get() || 
            rearRight->Get()  ||
            !motorStopped);
}

void DriveTrain::StopMotor()
{
    frontLeft->Set(0);
    rearLeft->Set(0);
    frontRight->Set(0);
    rearRight->Set(0);

    motorStopped = true;
}

void DriveTrain::SetSafetyEnabled(bool enabled)
{
    safetyEnabled = enabled;
}

bool DriveTrain::IsSafetyEnabled()
{
    return safetyEnabled;
}

void DriveTrain::GetDescription(char* desc)
{
    memcpy(desc, name, sizeof(name));
}