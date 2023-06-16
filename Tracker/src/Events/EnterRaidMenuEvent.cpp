#include "EnterRaidMenuEvent.h"
#include "../Tracker.h"
#include <sstream>
#include "nlohmann/json.hpp"
#include "../CSVSerializer.h"

// ------------------------ EnterRaidMenuEvent ------------------------------

EnterRaidMenuEvent::EnterRaidMenuEvent(double timestamp, const std::string& id) : TrackerEvent(timestamp, id, EventType::ENTER_RAID_MENU) {
	day = 0;
}

EnterRaidMenuEvent* EnterRaidMenuEvent::setDay(int day) {
	this->day = day;

	return this;
}

const std::string EnterRaidMenuEvent::toJson() {
	nlohmann::ordered_json j = nlohmann::ordered_json::parse(TrackerEvent::toJson());

	j["Day"] = day;

	return j.dump(2);
}

const void EnterRaidMenuEvent::toCSV(std::unordered_map<CSVFields, std::string>& eventCSV) {
	TrackerEvent::toCSV(eventCSV);

	eventCSV[CSVFields::Day] = std::to_string(day);
}
