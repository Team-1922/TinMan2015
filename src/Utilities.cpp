#include "Utilities.h"
#include "RobotMap.h"
#include <cmath>
#include <chrono>
#include <sys/time.h>

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


//global values in seconds
std::chrono::high_resolution_clock::time_point g_StartTime;

void startTimer()
{
	//get the time at when the application started
	g_StartTime = std::chrono::high_resolution_clock::now();
}

float getTime()
{
	//get the current time
	auto timeNow = std::chrono::high_resolution_clock::now();

	//difference from the beginning of the application
	auto timeDiff = std::chrono::duration_cast<std::chrono::duration<float>>(timeNow - g_StartTime);

	return timeDiff.count();
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
	float normalizedValue = rpmCompounded / maxMotorRPM;

	return normalizedValue;
}


float getShovelSetpointFromRackVoltage(float rackVoltage)
{
	//this uses a linear function that I got using point slope form; the slope WILL be NEGATIVE one, because the poteontiometers have the same
	// "gearing"  The negative one comes from the fact the as the rack voltage increases, the shovel voltage decreases
#ifdef COMP_BOT
	return -rackVoltage + RobotMap::Rack::voltageVertical + RobotMap::Shovel::voltageVertical;
#else
	return 0.0f;
#endif
	//simplified form of this point slope equation:
	//			retVal - RobotMap::Shovel::voltageVertical = -1(rackVoltage - RobotMap::Rack::voltageVertical)
}


}
