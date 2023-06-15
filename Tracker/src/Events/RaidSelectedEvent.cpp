#include "RaidSelectedEvent.h"
#include "../Tracker.h"
#include <sstream>
#include "nlohmann/json.hpp"

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

	return j.dump(2);
}

const std::string RaidSelectedEvent::toCSV() {
	std::string parentCSV = TrackerEvent::toCSV();

	std::stringstream ss;
	ss << parentCSV << "," << day;

	return ss.str();
}

