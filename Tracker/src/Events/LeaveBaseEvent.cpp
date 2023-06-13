#include "LeaveBaseEvent.h"
#include "../Tracker.h"
#include <sstream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

// ------------------- ReturnBaseEvent -----------------------

LeaveBaseEvent::LeaveBaseEvent(double timestamp, const std::string& id) : TrackerEvent(timestamp, id, EventType::LEAVE_BASE) {
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

	json j = nlohmann::json::parse(TrackerEvent::toJson());

	j["Fatigue"] = fatigue;
	j["Sleep Option"] = sleepOption;
	j["Day"] = day;

	return j.dump(2);

}

const std::string LeaveBaseEvent::toCSV() {
	std::string parentCSV = TrackerEvent::toCSV();

	std::stringstream ss;
	ss << parentCSV << "," << fatigue << "," << sleepOption << "," << day;

	return ss.str();
}