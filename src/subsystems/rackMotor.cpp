#include "Subsystems/rackMotor.h"

rackMotor::rackMotor() : Subsystem("rackMotor"){
	motor = new Jaguar(1);
	potentiometer = new AnalogPotentiometer(1,270.0,135.0);
}

void rackMotor::setMotor(float level) {
	motor->Set(level);
}

float rackMotor::getPotentiometer(){
  float potVal = potentiometer->Get();

return (potVal);
}
