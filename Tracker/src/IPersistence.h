#pragma once
#include "Events/TrackerEvent.h"
#include "ISerializer.h"
#include "CircularQueue.h"
#include <string>
#include <list>
#include <queue>
#include "JsonSerializer.h"
#include "CSVSerializer.h"

class IPersistence {

public:

	IPersistence(int capacity, std::list<std::string> serializersToUse) {
		createSerializers(serializersToUse);

		events_ = CircularQueue<TrackerEvent*>(capacity);
	};
	
	virtual ~IPersistence() {
	
		for (auto s : serializers_) {
			delete s.second;
		}

		serializers_.clear();

	};

	inline void sendEvent(TrackerEvent* trackerEvent) {
		TrackerEvent* e = events_.push(trackerEvent);

		if (e != nullptr)
			TrackerEvent::DestroyEvent(e);
	}

	virtual void Flush(bool finalFlush) = 0;

protected:

	CircularQueue<TrackerEvent*> events_;

	std::unordered_map<std::string, ISerializer*> serializers_;

private:

	void createSerializers(std::list<std::string> serializersToUse) {

		for(std::string serializer : serializersToUse) {
			if (serializer == "json")		
				serializers_["json"] = new JsonSerializer();
			else if (serializer == "csv")
				serializers_["csv"] = new CSVSerializer();
		}

	}
};
