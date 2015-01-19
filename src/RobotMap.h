/*
 * RobotMap.h
 *
 *  Created on: Jan 14, 2015
 *      Author: Kevin
 */

#ifndef ROBOTMAP_H_
#define ROBOTMAP_H_

namespace RobotMap
{

namespace Controls
{
//The control for rasing, extending, and "flatting" the rack
extern const int raiseRack;
extern const int extendRack;
extern const int flatRack;

//the controls for the three shovel positions
extern const int groundShovel;
extern const int humanShovel;
extern const int dumpShovel;
}

namespace Rack
{
//the angles of each of the positions in degrees
extern const float extendAngle;
extern const float raiseAngle;
extern const float flatAngle;

//the number of turns
extern const float potentiometerTurnCount;

//the minimum bound of potentiometer
extern const float potentiometerMinVal;

//the maximum bound of potentiometer
extern const float potentiometerMaxVal;

//the range of the two above values
extern const float potentiometerRange;

//the location of the rack motor
extern const int motorLoc;

extern const int potentiometerLoc;
}

//the drive train constants
namespace DriveTrain
{

//the locations of the motors
extern const int frontLeft;
extern const int rearLeft;
extern const int frontRight;
extern const int rearRight;

}

namespace Shovel
{
//the angles of each of the positions in degrees
extern const float dumpAngle;
extern const float groundAngle;
extern const float humanAngle;
extern const float liftAngle;
extern const float storeAngle;


//the motor location for the shovel
extern const int motorLoc;

//the number of turns
extern const float potentiometerTurnCount;

//the minimum bound of potentiometer
extern const float potentiometerMinVal;

//the maximum bound of potentiometer
extern const float potentiometerMaxVal;

//the range of the two above values
extern const float potentiometerRange;

extern const int potentiometerLoc;
}
}



#endif /* ROBOTMAP_H_ */
