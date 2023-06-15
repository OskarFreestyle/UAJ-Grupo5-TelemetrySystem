#include "ActionUsedEvent.h"
#include "../Tracker.h"
#include <sstream>
#include "nlohmann/json.hpp"

// ---------------------------- ActionUsedEvent ---------------------------------

ActionUsedEvent::ActionUsedEvent(double timestamp, const std::string& id) : TrackerEvent(timestamp, id, EventType::ACTION_USED) {
	nActions = day = 0;
}

ActionUsedEvent* ActionUsedEvent::setActions(int actions) {
	this->nActions = actions;

	return this;
}

ActionUsedEvent* ActionUsedEvent::setDay(int day) {
	this->day = day;

	return this;
}

const std::string ActionUsedEvent::toJson() {
	nlohmann::ordered_json j = nlohmann::ordered_json::parse(TrackerEvent::toJson());

	j["Actions Used"] = nActions;
	j["Day"] = day;

	return j.dump(2);
}

const std::string ActionUsedEvent::toCSV() {
	std::string parentCSV = TrackerEvent::toCSV();

	std::stringstream ss;
	ss << parentCSV << "," << nActions << "," << day;

	return ss.str();
}
