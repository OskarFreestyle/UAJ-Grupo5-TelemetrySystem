#include "FoodItemCraftedEvent.h"
#include "../Tracker.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

// -------------------- FoodItemCraftedEvent --------------------------------

FoodItemCraftedEvent::FoodItemCraftedEvent(const std::string& timestamp, const std::string& id) : TrackerEvent(timestamp, id, EventType::FOOD_ITEM_CRAFTED) {
	hunger = day = craft = 0;
}

FoodItemCraftedEvent* FoodItemCraftedEvent::setHunger(int hunger) {
	this->hunger = hunger;

	return this;
}

FoodItemCraftedEvent* FoodItemCraftedEvent::setCraft(bool craft) {
	this->craft = craft;

	return this;
}

FoodItemCraftedEvent* FoodItemCraftedEvent::setDay(int day) {
	this->day = day;

	return this;
}

const std::string FoodItemCraftedEvent::toJson() {
	json j = nlohmann::json::parse(TrackerEvent::toJson());

	j["Hunger"] = hunger;
	j["Can Craft Food Items"] = craft;
	j["Day"] = day;

	return j.dump(2);
}

const std::string FoodItemCraftedEvent::toCSV() {
	std::string parentCSV = TrackerEvent::toCSV();

	std::stringstream ss;
	ss << parentCSV << "," << hunger << "," << craft << "," << day;

	return ss.str();
}