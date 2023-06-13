#pragma once
#include <list>
#include <ctime>
#include <string>

class Timer {

private:

	Timer() {};
	~Timer() {};

	static Timer* instance;

public:
	static Timer* Instance();
	static void End();

	time_t getTimeNow();
};

