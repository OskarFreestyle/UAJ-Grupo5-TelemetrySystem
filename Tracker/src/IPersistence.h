#pragma once
#include "TrackerEvent.h"
#include "ISerializer.h"
#include <string>
#include <list>
#include <queue>

class IPersistence {

public:

	IPersistence() {};
	virtual ~IPersistence() {};

	inline void sendEvent(TrackerEvent* trackerEvent) {
		TrackerEvent* clone = trackerEvent->clone();
		events.push(clone);

		if (events.size() >= MAX_EVENTS_IN_QUEUE) Flush();
	}

	virtual void Flush() = 0;

protected:

	std::list<ISerializer*> serializers;

	std::queue<TrackerEvent*> events;

	const int MAX_EVENTS_IN_QUEUE = 1;
};
