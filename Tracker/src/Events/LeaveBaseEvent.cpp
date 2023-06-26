#include "LeaveBaseEvent.h"
#include "../Tracker.h"
#include <sstream>
#include "nlohmann/json.hpp"
#include "../CSVSerializer.h"

// ------------------- ReturnBaseEvent -----------------------

LeaveBaseEvent::LeaveBaseEvent(int timestamp, const std::string& id) : TrackerEvent(timestamp, id, EventType::LEAVE_BASE) {
	fatigue = sleepOption = day = 0;
}

LeaveBaseEvent* LeaveBaseEvent::setFatigue(int fatigue) {
	this->fatigue = fatigue;

	return this;
}

LeaveBaseEvent* LeaveBaseEvent::setSleepOption(int sleepOption) {
	this->sleepOption = sleepOption;

	return this;
}

LeaveBaseEvent* LeaveBaseEvent::setDay(int day) {
	this->day = day;

	return this;
}

const std::string LeaveBaseEvent::toJson() {

	nlohmann::ordered_json j = nlohmann::ordered_json::parse(TrackerEvent::toJson());

	j["Fatigue"] = fatigue;
	j["Sleep Option"] = sleepOption;
	j["Day"] = day;

	return j.dump(2);
}

const void LeaveBaseEvent::toCSV(std::unordered_map<CSVFields, std::string>& eventCSV) {
	TrackerEvent::toCSV(eventCSV);

	eventCSV[CSVFields::Fatigue] = std::to_string(fatigue);
	eventCSV[CSVFields::SleepOption] = std::to_string(sleepOption);
	eventCSV[CSVFields::Day] = std::to_string(day);
}
