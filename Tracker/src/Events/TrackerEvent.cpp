#include "TrackerEvent.h"
#include "nlohmann/json.hpp"
#include "..\checkML.h"
#include "..\Tracker.h"
#include <sstream>
#include "..\CSVSerializer.h"

// ordered_json utiliza FIFO para escribir los elementos agregados mientras json los escribe alfabeticamente
using ordered_json = nlohmann::ordered_json;

// -------------------------- Clase padre -----------------------

TrackerEvent::TrackerEvent(double timestamp, const std::string& id, ::EventType eventType) {

	timestamp_ = timestamp;
	id_ = id;
	eventType_ = eventType;
	maskBits_ = std::pow(2, (int) eventType_);

}

const std::string TrackerEvent::toJson() {
	ordered_json j;

	j["EventType"] = eventTypes[(int)eventType_];
	//j["EventType"] = eventType_;
	j["SessionId"] = id_;
	j["TimeStamp"] = timestamp_;

	return j.dump(2);
}

const void TrackerEvent::toCSV(std::unordered_map<CSVFields, std::string>& eventCSV) {

	eventCSV[CSVFields::Id] = id_;
	eventCSV[CSVFields::Time] = std::to_string(timestamp_);
	eventCSV[CSVFields::EventType] = eventTypes[(int)eventType_];

}

const EventType TrackerEvent::getType() {
	return eventType_;
}

bool TrackerEvent::isTrackable(uint16_t eventsMaskBits) {
	return (maskBits_ & eventsMaskBits) != 0;
}

void TrackerEvent::DestroyEvent(TrackerEvent* event) {
	delete event; 
	event = nullptr;
}