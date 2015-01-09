#include "DriveTrain.h"

DriveTrain :: DriveTrain() : frontLeft(0),
							 rearLeft(1),
							 frontRight(2),
							 rearRight(3)
{

}

DriveTrain :: ~DriveTrain(){
	delete frontLeft;
	delete rearLeft;
	delete frontRight;
	delete rearRight

}

void DriveTrain :: ozDrive(Joystick* stick){
//put the stick values in a couple floats
float xVal =stick->GetX();
float yVal= stick->GetY();

//arcade drive
float leftMotor = yVal + xVal;
float rightMotor = yVal - xVal;

frontLeft->Set(leftMotor);
rearLeft->Set(leftMotor);

frontRight->Set(rightMotor);
rearRight->Set(rightMotor);

}

