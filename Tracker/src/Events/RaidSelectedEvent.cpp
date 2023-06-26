#include "RaidSelectedEvent.h"
#include "../Tracker.h"
#include <sstream>
#include "nlohmann/json.hpp"
#include "../CSVSerializer.h"

// ------------------- RaidSelectedEvent -----------------------

RaidSelectedEvent::RaidSelectedEvent(double timestamp, const std::string& id) : TrackerEvent(timestamp, id, EventType::RAID_SELECTED) {
	day = hunger = location = 0;
}

RaidSelectedEvent* RaidSelectedEvent::setItems(const std::list<int>& l) {
	items = l;

	return this;
}

RaidSelectedEvent* RaidSelectedEvent::setLocation(int location) {
	this->location = location;

	return this;
}

RaidSelectedEvent* RaidSelectedEvent::setHunger(int hunger) {
	this->hunger = hunger;

	return this;
}

RaidSelectedEvent* RaidSelectedEvent::setDay(int day) {
	this->day = day;

	return this;
}

const std::string RaidSelectedEvent::toJson() {
	nlohmann::ordered_json j = nlohmann::ordered_json::parse(TrackerEvent::toJson());

	j["Day"] = day;
	j["Location"] = location;
	j["Hunger"] = hunger;

	return j.dump(2);
}

const void RaidSelectedEvent::toCSV(std::unordered_map<CSVFields, std::string>& eventCSV) {
	TrackerEvent::toCSV(eventCSV);

	eventCSV[CSVFields::Day] = std::to_string(day);
	eventCSV[CSVFields::Location] = std::to_string(location);
	eventCSV[CSVFields::Hunger] = std::to_string(hunger);
}


