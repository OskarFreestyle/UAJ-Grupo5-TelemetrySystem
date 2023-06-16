#include "ItemConsumedEvent.h"
#include "../Tracker.h"
#include <sstream>
#include "nlohmann/json.hpp"
#include "../CSVSerializer.h"

// ------------------- UsingItemEvent -----------------------

ItemConsumedEvent::ItemConsumedEvent(double timestamp, const std::string& id) : TrackerEvent(timestamp, id, EventType::ITEM_CONSUMED) {
	day = 0;
}

ItemConsumedEvent* ItemConsumedEvent::setDay(int day) {
	this->day = day;

	return this;
}


const std::string ItemConsumedEvent::toJson() {
	nlohmann::ordered_json j = nlohmann::ordered_json::parse(TrackerEvent::toJson());

	j["Day"] = day;

	return j.dump(2);
}


const void ItemConsumedEvent::toCSV(std::unordered_map<CSVFields, std::string>& eventCSV) {
	TrackerEvent::toCSV(eventCSV);

	eventCSV[CSVFields::Day] = std::to_string(day);
}
