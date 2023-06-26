#include "ShipItemCraftedEvent.h"
#include "../Tracker.h"
#include <sstream>
#include "nlohmann/json.hpp"
#include "../CSVSerializer.h"

// -------------------------- CraftShipEvent ------------------------------

ShipItemCraftedEvent::ShipItemCraftedEvent(int timestamp, const std::string& id) : TrackerEvent(timestamp, id, EventType::SHIP_ITEM_CRAFTED) {
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
	nlohmann::ordered_json j = nlohmann::ordered_json::parse(TrackerEvent::toJson());

	j["Ship Items Crafted"] = nCrafted;
	j["Craftable Ship Items"] = nCraftables;
	j["Day"] = day;

	return j.dump(2);
}

const void ShipItemCraftedEvent::toCSV(std::unordered_map<CSVFields, std::string>& eventCSV) {
	TrackerEvent::toCSV(eventCSV);

	eventCSV[CSVFields::ShipItemsCrafted] = std::to_string(nCrafted);
	eventCSV[CSVFields::CraftableShipItems] = std::to_string(nCraftables);
	eventCSV[CSVFields::Day] = std::to_string(day);
}

