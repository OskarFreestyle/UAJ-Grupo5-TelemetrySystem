#include "RaidVisualizedEvent.h"
#include "../Tracker.h"
#include <sstream>
#include "nlohmann/json.hpp"
#include "../CSVSerializer.h"

// ------------------- RaidSelectedEvent -----------------------

RaidVisualizedEvent::RaidVisualizedEvent(int timestamp, const std::string& id) : TrackerEvent(timestamp, id, EventType::RAID_VISUALIZED) {
	location = 0;
}

RaidVisualizedEvent* RaidVisualizedEvent::setLocation(int location) {
	this->location = location;

	return this;
}

const std::string RaidVisualizedEvent::toJson() {
	nlohmann::ordered_json j = nlohmann::ordered_json::parse(TrackerEvent::toJson());

	j["Location"] = location;

	return j.dump(2);
}

const void RaidVisualizedEvent::toCSV(std::unordered_map<CSVFields, std::string>& eventCSV) {
	TrackerEvent::toCSV(eventCSV);

	eventCSV[CSVFields::Location] = std::to_string(location);
}


