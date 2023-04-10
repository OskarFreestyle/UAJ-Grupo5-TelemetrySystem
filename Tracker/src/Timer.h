#pragma once
#include <list>
#include <ctime>

class Timer {

private:
	static Timer* instance;
	time_t startTime;

	Timer();
	~Timer();
public:
	static Timer* Instance();
	static void Release();

	float getTimeSinceStart();
	time_t getTimeNow();
};

