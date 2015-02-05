#include "Utilities.h"
#include <cmath>
#include <time.h>

namespace Utilities
{

//if val is within a given epsilon of test (threshold)
bool isEqual(float test, float val, float epsilon)
{
	if (fabs(val - test) > epsilon)
		return false;
	else
		return true;
}


float weightAverage(std::vector<float> numbers, std::vector<float> weights)
{
	if(weights.size() != numbers.size())
		return 0.0f;

	float ret = 0.0f;//weighted sum
	float wSum = 0.0f;//sum of the weights

	auto wIt = weights.begin();
	for(auto it : numbers)
	{
		ret += it * *wIt;
		wSum += *wIt;

		++wIt;
	}

	ret /= wSum;

	return ret;
}


//global values
time_t g_Timer;


void startTimer()
{
	//get the time at when the application started
	time(&g_Timer);
}
float getTime()
{
	//get the current time
	time_t timer;
	time(&timer);

	//return the difference
	return difftime(timer, g_Timer);
}

}
