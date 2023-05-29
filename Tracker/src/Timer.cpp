#include "Timer.h"
#include <ctime>

Timer* Timer::instance = nullptr;

Timer* Timer::Instance() {

	if (instance == nullptr)
		instance = new Timer();

	return instance;
}

void Timer::End() {

	if (instance != nullptr) {
		delete instance; 
		instance = nullptr;
	}
}

time_t Timer::getTimeNow() {
	return std::time(NULL);
}
