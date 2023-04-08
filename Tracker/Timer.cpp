#include "Timer.h"

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
	startTime = time(NULL);
}

Timer::~Timer() {}

float Timer::getTimeSinceStart()
{
	return difftime(time(NULL), startTime);
}