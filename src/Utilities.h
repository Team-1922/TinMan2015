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

//takes a list of numbers, and a list of weights to apply to each of these numbers in a weighted average
//UNTESTED
float weightAverage(std::vector<float> numbers, std::vector<float> weights);

//call this ONCE in the begging of the application
void startTimer();

//this gets the time in seconds since the begging of the application running; this IS multithreaded
float getTime();

}

#endif /* SRC_UTILITIES_H_ */
