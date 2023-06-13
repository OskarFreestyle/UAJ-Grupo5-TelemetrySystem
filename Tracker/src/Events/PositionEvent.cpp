#include "PositionEvent.h"
#include "../Tracker.h"
#include <sstream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;


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

	json j = nlohmann::json::parse(TrackerEvent::toJson());

	j["x"] = x;
	j["y"] = x;
	j["entity"] = entity;

	return j.dump(2);
}

const std::string PositionEvent::toCSV() {

	std::string parentCSV = TrackerEvent::toCSV();

	std::stringstream ss;
	ss << parentCSV << "," << x << "," << y << "," << entity;

	return ss.str();
}
