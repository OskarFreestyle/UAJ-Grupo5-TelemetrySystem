#include "Timer.h"
#include <ctime>

Timer* Timer::instance = nullptr;

Timer* Timer::Instance()
{
	if (instance == nullptr)
		instance = new Timer();

	return instance;
}

void Timer::Release()
{
	if (instance != nullptr) 
	{
		delete instance; 
		instance = nullptr;
	}
}

Timer::Timer() {
	startTime = std::time(NULL);
}

Timer::~Timer() {}

float Timer::getTimeSinceStart() {
	return std::difftime(getTimeNow(), startTime);
}

time_t Timer::getTimeNow() {
	return std::time(NULL);
}
