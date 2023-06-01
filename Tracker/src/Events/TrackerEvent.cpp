#include "TrackerEvent.h"
#include "../checkML.h"
#include "../Tracker.h"
#include <sstream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

// -------------------------- Clase padre -----------------------

TrackerEvent::TrackerEvent(const std::string& timestamp, const std::string& id, ::EventType eventType) {

	timestamp_ = timestamp;
	id_ = id;
	eventType_ = eventType;
	maskBits_ = std::pow(2, (int) eventType_);

}

const std::string TrackerEvent::toJson() {
	json j;

	j["SessionId"] = id_;
	j["TimeNow"] = timestamp_;

	return j.dump(2);
}

const std::string TrackerEvent::toCSV() {

	return id_ + "," + timestamp_ + "," + eventTypes[(int)eventType_];
}

const EventType TrackerEvent::getType() {
	return eventType_;
}

bool TrackerEvent::isTrackable(uint16_t eventsMaskBits) {
	return (maskBits_ & eventsMaskBits) != 0;
}

void TrackerEvent::DestroyEvent(TrackerEvent* event) {
	delete event; event = nullptr;
}