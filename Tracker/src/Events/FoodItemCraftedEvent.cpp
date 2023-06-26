#include "FoodItemCraftedEvent.h"
#include "../Tracker.h"
#include <sstream>
#include "nlohmann/json.hpp"
#include "../CSVSerializer.h"

// -------------------- FoodItemCraftedEvent --------------------------------

FoodItemCraftedEvent::FoodItemCraftedEvent(int timestamp, const std::string& id) : TrackerEvent(timestamp, id, EventType::FOOD_ITEM_CRAFTED) {
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
	nlohmann::ordered_json j = nlohmann::ordered_json::parse(TrackerEvent::toJson());

	j["Hunger"] = hunger;
	j["Can Craft Food Items"] = craft;
	j["Day"] = day;

	return j.dump(2);
}

const void FoodItemCraftedEvent::toCSV(std::unordered_map<CSVFields, std::string>& eventCSV) {
	TrackerEvent::toCSV(eventCSV);

	eventCSV[CSVFields::Hunger] = std::to_string(hunger);
	eventCSV[CSVFields::CanCraftFoodItems] = craft ? "true" : "false";
	eventCSV[CSVFields::Day] = std::to_string(day);
}

