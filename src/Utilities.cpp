#include "Utilities.h"
#include "RobotMap.h"
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

float  motorConstSpeed(float rpmDesired, float rpmCurrent, float &rpmCompounded,
		float gearingRatio, float maxMotorRPM)
{
	//convert the rpm of the component to the rpm of the motor
	float desiredSpeedRPM = rpmDesired * gearingRatio;
	float currSpeedRPM = rpmCurrent * gearingRatio;

	//take the RPM we need to give the motor to increase the speed to what we want
	float requiredRPM = desiredSpeedRPM - currSpeedRPM;
	float neededPercentageOfDesired = requiredRPM / desiredSpeedRPM;

	//make sure this percentage is not bigger than 1.5 percent, so it doesn't make drastic changes that cause jerking
	//  or damage equipment; HOPEFULLY this fixes the problem of stopping too quickly, or putting to much torque on the motor
	neededPercentageOfDesired = Utilities::clamp<float>(neededPercentageOfDesired, -RobotMap::maxRPMDelta, RobotMap::maxRPMDelta);

	//the rpm to feed into the normalized value is calculated by adding the neededRPM to the compounded rpm
	rpmCompounded += neededPercentageOfDesired * desiredSpeedRPM;

	//divide by the rpm to get a value between -1 and 1;
	float normalizedValue = rpmCompounded / RobotMap::Shovel::shovelMotorRPM;

	return normalizedValue;
}


}
