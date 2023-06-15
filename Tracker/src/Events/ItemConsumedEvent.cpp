#include "ItemConsumedEvent.h"
#include "../Tracker.h"
#include <sstream>
#include "nlohmann/json.hpp"


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

const std::string ItemConsumedEvent::toCSV() {
	std::string parentCSV = TrackerEvent::toCSV();

	std::stringstream ss;
	ss << parentCSV << "," << day;

	return ss.str();
}
