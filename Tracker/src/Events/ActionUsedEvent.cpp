#include "ActionUsedEvent.h"
#include "../Tracker.h"
#include <sstream>
#include "nlohmann/json.hpp"
#include "../CSVSerializer.h"

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

const void ActionUsedEvent::toCSV(std::unordered_map<CSVFields, std::string>& eventCSV) {
	TrackerEvent::toCSV(eventCSV);

	eventCSV[CSVFields::ActionsUsed] = std::to_string(nActions);
	eventCSV[CSVFields::Day] = std::to_string(day);
}
