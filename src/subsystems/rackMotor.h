#ifndef RACK_MOTOR_H
#define RACK_MOTOR_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

class rackMotor: public Subsystem {

private:
SpeedController* motor;
AnalogPotentiometer* potentiometer;

public:
rackMotor();
void InitDefaultCommand() {}

void setMotor(float level);
float getPotentiometer();


}

#endif
