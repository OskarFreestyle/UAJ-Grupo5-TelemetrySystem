#include "PositionEvent.h"
#include "../Tracker.h"
#include <sstream>
#include "nlohmann/json.hpp"
#include "../CSVSerializer.h"

// -------------------- Position Event -----------------------

PositionEvent::PositionEvent(double timestamp, const std::string& id) : TrackerEvent(timestamp, id, EventType::POSITION) {
	x = y = 0;
}

PositionEvent* PositionEvent::setPosition(float x, float y) {

	this->x = x;
	this->y = y;

	return this;
}

PositionEvent* PositionEvent::setEntity(std::string name) {

	entity = name;
	return this;
}

const std::string PositionEvent::toJson() {

	nlohmann::ordered_json j = nlohmann::ordered_json::parse(TrackerEvent::toJson());

	j["Entity"] = entity;
	j["x"] = x;
	j["y"] = x;

	return j.dump(2);
}

const void PositionEvent::toCSV(std::unordered_map<CSVFields, std::string>& eventCSV) {
	TrackerEvent::toCSV(eventCSV);

	eventCSV[CSVFields::X] = std::to_string((int)x);
	eventCSV[CSVFields::Y] = std::to_string((int)y);
	eventCSV[CSVFields::Entity] = entity;
}

