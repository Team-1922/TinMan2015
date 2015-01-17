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
}

namespace Rack
{
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
}



#endif /* ROBOTMAP_H_ */
