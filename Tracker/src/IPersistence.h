#pragma once
#include "TrackerEvent.h"
#include "ISerializer.h"
#include <string>
#include <list>
#include <queue>

class IPersistence {

public:

	IPersistence(int maxEventsInQueue): MAX_EVENTS_IN_QUEUE(maxEventsInQueue) {};
	virtual ~IPersistence() { };

	inline void sendEvent(TrackerEvent* trackerEvent) {
		TrackerEvent* clone = trackerEvent->clone();
		events.push(clone);

		if (events.size() >= MAX_EVENTS_IN_QUEUE) Flush(false);
	}

	virtual void Flush(bool finalFlush) = 0;

protected:

	std::queue<TrackerEvent*> events;

	int MAX_EVENTS_IN_QUEUE = 10;
};
