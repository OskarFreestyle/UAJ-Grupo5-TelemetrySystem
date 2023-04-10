#include "TrackerEvent.h"
#include "nlohmann/json.hpp"
#include "checkML.h"
#include <sstream>

using json = nlohmann::json;

// -------------------------- Clase padre -----------------------

TrackerEvent::TrackerEvent(double timestamp, std::string id, ::EventType eventType) {

	timestamp_ = timestamp;
	id_ = id;
	eventType_ = eventType;
	maskBits_ = std::pow(2, (int) eventType_);

}

const std::string TrackerEvent::toJson() {
	json j;

	j["SessionId"] = id_;
	j["TimeSinceStart"] = timestamp_;
	j["EventType"] = eventTypes[(int) eventType_];

	return j.dump();
}

const std::string TrackerEvent::toCSV() {

	std::string time = std::to_string(timestamp_);

	return "id: " + id_ + ",time:" + time + ",eventType:" + eventTypes[(int)eventType_];
}

const EventType TrackerEvent::getType() {
	return eventType_;
}

bool TrackerEvent::isTrackable(uint16_t eventsMaskBits) {
	return (maskBits_ & eventsMaskBits) != 0;
}

void TrackerEvent::DestroyEvent(TrackerEvent* event) {
	delete event; event = nullptr;
}




// ------------------- SessionStartEvent -----------------------

SessionStartEvent::SessionStartEvent(float timestamp, std::string id) : TrackerEvent(timestamp, id, EventType::SESSION_STARTED) {}

TrackerEvent* SessionStartEvent::clone() {
	return new SessionStartEvent(timestamp_, id_);
}




// ------------------- SessionEndEvent -----------------------

SessionEndEvent::SessionEndEvent(float timestamp, std::string id) : TrackerEvent(timestamp, id, EventType::SESSION_ENDED) {}

TrackerEvent* SessionEndEvent::clone() {
	return new SessionEndEvent(timestamp_, id_);
}





// ------------------- ReturnBaseEvent -----------------------

ReturnToBaseEvent::ReturnToBaseEvent(float timestamp, std::string id) : TrackerEvent(timestamp, id, EventType::RETURNED_TO_BASE) {
	fatigue = sleepOption = day = 0;
}

ReturnToBaseEvent* ReturnToBaseEvent::setFatigue(int fatigue) {
	this->fatigue = fatigue;

	return this;
}

ReturnToBaseEvent* ReturnToBaseEvent::setSleepOption(int sleepOption) {
	this->sleepOption = sleepOption;

	return this;
}

ReturnToBaseEvent* ReturnToBaseEvent::setDay(int day) {
	this->day = day;

	return this;
}

const std::string ReturnToBaseEvent::toJson() {

	std::string parentJson = TrackerEvent::toJson();

	json j;
	j["Fatigue"] = fatigue;
	j["SleepOption"] = sleepOption;
	j["Day"] = day;

	return parentJson + j.dump();

}

const std::string ReturnToBaseEvent::toCSV() {
	std::string parentCSV = TrackerEvent::toCSV();

	std::stringstream ss;
	ss << parentCSV + ",Fatigue:" << fatigue << ",SleepOption:" << sleepOption << ",Day:" << day;

	return ss.str();
}

TrackerEvent* ReturnToBaseEvent::clone() {
	ReturnToBaseEvent* e = new ReturnToBaseEvent(timestamp_, id_);

	e->setFatigue(fatigue)->setSleepOption(sleepOption)->setDay(day);

	return e;
}




// -------------------- FoodItemCraftedEvent --------------------------------

FoodItemCraftedEvent::FoodItemCraftedEvent(float timestamp, std::string id) : TrackerEvent(timestamp, id, EventType::FOOD_ITEM_CRAFTED) {
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
	std::string parentJson = TrackerEvent::toJson();

	json j;
	j["Hunger"] = hunger;
	j["CanCraftFoodItems"] = craft;
	j["Day"] = day;

	return parentJson + j.dump();
}

const std::string FoodItemCraftedEvent::toCSV() {
	std::string parentCSV = TrackerEvent::toCSV();

	std::stringstream ss;
	ss << parentCSV + ",Hunger:" << hunger << ",CanCraftFoodItems:" << craft << ",Day:" << day;

	return ss.str();
}

TrackerEvent* FoodItemCraftedEvent::clone() {
	FoodItemCraftedEvent* e = new FoodItemCraftedEvent(timestamp_, id_);

	e->setHunger(hunger)->setCraft(craft)->setDay(day);

	return e;
}





// ------------------- BaseSleepEvent -----------------------

BaseSleepEvent::BaseSleepEvent(float timeDone_, std::string id_) : TrackerEvent(timeDone_, id_, EventType::ACTION_USED) {

}

void BaseSleepEvent::setParameters(int sleepOption_, int nFood_, int nMedicine_, int nCraftingItems_, int nAmmo_, int nShipPieces_, int day_) {
	sleepOption = sleepOption_;
	nFood = nFood_;
	nMedicine = nMedicine_;
	nCraftingItems = nCraftingItems_;
	nAmmo = nAmmo_;
	nShipPieces = nShipPieces_;
	day = day_;

}

const std::string BaseSleepEvent::toJson() {
	// TODO
	return "";
}

const std::string BaseSleepEvent::toCSV() {
	// TODO
	return "";
}

TrackerEvent* BaseSleepEvent::clone() {
	BaseSleepEvent* aux = new BaseSleepEvent(timestamp_, id_);
	aux->setParameters(sleepOption, nFood, nMedicine, nCraftingItems, nAmmo, nShipPieces, day);

	return aux;
}



// ------------------- CraftShipEvent -----------------------

CraftShipEvent::CraftShipEvent(float timeDone_, std::string id_) : TrackerEvent(timeDone_, id_, EventType::SHIP_ITEM_CRAFTED) {
}

void CraftShipEvent::setParameters(int nCrafted_, int day_) {
	nCrafted = nCrafted_;
	day = day_;

}

const std::string CraftShipEvent::toJson() {
	// TODO
	return "";
}

const std::string CraftShipEvent::toCSV() {
	// TODO
	return "";
}

TrackerEvent* CraftShipEvent::clone() {
	CraftShipEvent* aux = new CraftShipEvent(timestamp_, id_);
	aux->setParameters(nCrafted, day);

	return aux;

}


// ------------------- BaseActionsEvent -----------------------

BaseActionsEvent::BaseActionsEvent(float timeDone_, std::string id_) : TrackerEvent(timeDone_, id_, EventType::ACTION_USED) {
}

void BaseActionsEvent::setParameters(int nActions_, int day_) {
	nActions = nActions_;
	day = day_;

}

const std::string BaseActionsEvent::toJson() {
	// TODO
	return "";
}

const std::string BaseActionsEvent::toCSV() {
	// TODO
	return "";
}

TrackerEvent* BaseActionsEvent::clone() {
	BaseActionsEvent* aux = new BaseActionsEvent(timestamp_, id_);
	aux->setParameters(nActions, day);

	return aux;
}



// ------------------- SelectingRaidEvent -----------------------

SelectingRaidEvent::SelectingRaidEvent(float timeDone_, std::string id_) : TrackerEvent(timeDone_, id_, EventType::RAID_SELECTED) {
}

void SelectingRaidEvent::setParameters(Locations location_, Action accion_, int day_) {
	location = location_;
	accion = accion_;
	day = day_;

}

const std::string SelectingRaidEvent::toJson() {
	// TODO
	return "";
}

const std::string SelectingRaidEvent::toCSV() {
	// TODO
	return "";
}

TrackerEvent* SelectingRaidEvent::clone() {
	SelectingRaidEvent* aux = new SelectingRaidEvent(timestamp_, id_);
	aux->setParameters(location, accion, day);

	return aux;
}



// ------------------- UsingItemEvent -----------------------

UsingItemEvent::UsingItemEvent(float timeDone_, std::string id_) : TrackerEvent(timeDone_, id_, EventType::ITEM_CONSUMED) {
}

void UsingItemEvent::setParameters(int nItems_, int day_) {
	nItems = nItems_;
	day = day_;

}

const std::string UsingItemEvent::toJson() {
	// TODO
	return "";
}

const std::string UsingItemEvent::toCSV() {
	// TODO
	return "";
}

TrackerEvent* UsingItemEvent::clone() {
	UsingItemEvent* aux = new UsingItemEvent(timestamp_, id_);
	aux->setParameters(nItems, day);

	return aux;
}
