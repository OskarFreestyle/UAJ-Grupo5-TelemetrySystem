#include "EnterRaidMenuEvent.h"
#include "../Tracker.h"
#include <sstream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

// ------------------------ EnterRaidMenuEvent ------------------------------

EnterRaidMenuEvent::EnterRaidMenuEvent(double timestamp, const std::string& id) : TrackerEvent(timestamp, id, EventType::ENTER_RAID_MENU) {
	day = 0;
}

EnterRaidMenuEvent* EnterRaidMenuEvent::setDay(int day) {
	this->day = day;

	return this;
}

const std::string EnterRaidMenuEvent::toJson() {
	json j = nlohmann::json::parse(TrackerEvent::toJson());

	j["Day"] = day;

	return j.dump(2);
}

const std::string EnterRaidMenuEvent::toCSV() {
	std::string parentCSV = TrackerEvent::toCSV();

	std::stringstream ss;
	ss << parentCSV << "," << day;

	return ss.str();
}
