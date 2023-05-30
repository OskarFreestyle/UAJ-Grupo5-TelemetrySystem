#pragma once
#include "TrackerEvent.h"
#include "ISerializer.h"
#include "CircularQueue.h"

class IPersistence {

public:

	IPersistence(int capacity) {
	
		events_ = CircularQueue<TrackerEvent*>(capacity);
	
	};

	virtual ~IPersistence() {};

	inline void sendEvent(TrackerEvent* trackerEvent) {
		TrackerEvent* e = events_.push(trackerEvent);

		if (e != nullptr)
			TrackerEvent::DestroyEvent(e);
	}

	virtual void Flush(bool finalFlush) = 0;

protected:

	CircularQueue<TrackerEvent*> events_;

};
