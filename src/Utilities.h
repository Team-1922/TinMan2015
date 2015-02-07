/*
 * Utilities.h
 *
 *  Created on: Jan 13, 2015
 *      Author: Kevin
 */

#ifndef SRC_UTILITIES_H_
#define SRC_UTILITIES_H_

#include <vector>

#define SAFE_DELETE(x) {if(NULL != x){delete x; x = NULL;}}

//Global utilities for use around robot code

namespace Utilities
{

//if val is within a given epsilon of test (threshold)
bool isEqual(float test, float val, float epsilon);


//true = positive
template<typename T>
inline bool getSign(T num)
{
	return (num >= 0.0f);
}

//takes a value, and makes sure it is between min and max; if it is above max, it returns max, same for min
template<typename T>
inline T clamp(T val, T min, T max)
{
	//for a better explanation, see: https://www.opengl.org/sdk/docs/man/html/clamp.xhtml
	//takes the large of the two numbers, the minimum value or the value, then takes the minimum of the returned value or the max value
	return std::min(std::max(val, min), max);
}

//takes a list of numbers, and a list of weights to apply to each of these numbers in a weighted average
//UNTESTED
float weightAverage(std::vector<float> numbers, std::vector<float> weights);

//call this ONCE in the begging of the application
void startTimer();

//this gets the time in seconds since the begging of the application running; this IS multithreaded
float getTime();

}

#endif /* SRC_UTILITIES_H_ */
