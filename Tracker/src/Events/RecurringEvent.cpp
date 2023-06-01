#include "RecurringEvent.h"
#include "../Tracker.h"

// --------------------- Eventos periodicos ------------------------

RecurringEvent::RecurringEvent(std::function<TrackerEvent* ()> func, float interval) {

	timer = 0;
	creator = func;
	this->interval = interval;
}

void RecurringEvent::Update(float dt) {

	timer += dt;

	if (timer > interval) {

		Tracker::Instance()->trackEvent(creator());

		timer = 0;
	}
}