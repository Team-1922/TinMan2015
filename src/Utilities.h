/*
 * Utilities.h
 *
 *  Created on: Jan 13, 2015
 *      Author: Kevin
 */

#ifndef SRC_UTILITIES_H_
#define SRC_UTILITIES_H_

#define SAFE_DELETE(x) {if(NULL != x){delete x; x = NULL;}}

//Global utilities for use around robot code

namespace Utilities
{

//if val is within a given epsilon of test (threshold)
bool isEqual(float test, float val, float epsilon);

}

#endif /* SRC_UTILITIES_H_ */
