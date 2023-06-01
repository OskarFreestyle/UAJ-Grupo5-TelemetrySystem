#include "ShipItemCraftedEvent.h"
#include "../Tracker.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;


// -------------------------- CraftShipEvent ------------------------------

ShipItemCraftedEvent::ShipItemCraftedEvent(const std::string& timestamp, const std::string& id) : TrackerEvent(timestamp, id, EventType::SHIP_ITEM_CRAFTED) {
	nCrafted = nCraftables = day = 0;
}

ShipItemCraftedEvent* ShipItemCraftedEvent::setCrafted(int crafted) {
	this->nCrafted = crafted;

	return this;
}

ShipItemCraftedEvent* ShipItemCraftedEvent::setCraftables(int craftables) {
	this->nCraftables = craftables;

	return this;
}

ShipItemCraftedEvent* ShipItemCraftedEvent::setDay(int day) {
	this->day = day;

	return this;
}


const std::string ShipItemCraftedEvent::toJson() {
	json j = nlohmann::json::parse(TrackerEvent::toJson());

	j["Ship Items Crafted"] = nCrafted;
	j["Craftable Ship Items"] = nCraftables;
	j["Day"] = day;

	return j.dump(2);
}

const std::string ShipItemCraftedEvent::toCSV() {
	std::string parentCSV = TrackerEvent::toCSV();

	std::stringstream ss;
	ss << parentCSV << "," << nCrafted << "," << nCraftables << "," << day;

	return ss.str();
}
