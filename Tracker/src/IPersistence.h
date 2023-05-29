#pragma once
#include "TrackerEvent.h"
#include "ISerializer.h"
#include <string>
#include <list>
#include <queue>
#include "JsonSerializer.h"
#include "CSVSerializer.h"

class IPersistence {

public:

	IPersistence(int maxEventsInQueue, std::list<std::string> serializersToUse) : MAX_EVENTS_IN_QUEUE(maxEventsInQueue) {
		createSerializers(serializersToUse);
	};
	virtual ~IPersistence() { };

	inline void sendEvent(TrackerEvent* trackerEvent) {
		TrackerEvent* clone = trackerEvent->clone();
		events.push(clone);

		if (events.size() >= MAX_EVENTS_IN_QUEUE) Flush(false);
	}

	virtual void Flush(bool finalFlush) = 0;

protected:

	std::unordered_map<std::string, ISerializer*> serializers_;
	std::queue<TrackerEvent*> events;

	int MAX_EVENTS_IN_QUEUE = 10;

private:
	void createSerializers(std::list<std::string> serializersToUse) {
		for(std::string serializer : serializersToUse) {
			if (serializer == "json") {			
				serializers_["json"] = new JsonSerializer();
			}
			else if (serializer == "csv") {
				serializers_["csv"] = new CSVSerializer();
			}
		}
	}
};
