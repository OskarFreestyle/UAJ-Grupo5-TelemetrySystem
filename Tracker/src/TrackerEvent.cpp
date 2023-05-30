#include "TrackerEvent.h"
#include "nlohmann/json.hpp"
#include "checkML.h"
#include "Tracker.h"
#include <sstream>

using json = nlohmann::json;

// -------------------------- Clase padre -----------------------

TrackerEvent::TrackerEvent(const std::string& timestamp, const std::string& id, ::EventType eventType) {

	timestamp_ = timestamp;
	id_ = id;
	eventType_ = eventType;
	maskBits_ = std::pow(2, (int) eventType_);

}

const std::string TrackerEvent::toJson() {
	json j;

	j["SessionId"] = id_;
	j["TimeSinceStart"] = timestamp_;

	return j.dump(2);
}

const std::string TrackerEvent::toCSV() {

	std::string time = std::to_string(timestamp_);

	return id_ + "," + time + "," + eventTypes[(int)eventType_];
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



// --------------------- Eventos periodicos ------------------------

RecurringEvent::RecurringEvent(std::function<TrackerEvent* ()> func, float interval) {

	timer = 0;
	creator = func;
	this->interval = interval;
}

void RecurringEvent::Update(float dt) {

	timer += dt;

	if (timer > interval) {

		Tracker::Instance()->trackEvent(creator());

		timer = 0;
	}
}




// ------------------- SessionStartEvent -----------------------

SessionStartEvent::SessionStartEvent(const std::string& timestamp, const std::string& id) : TrackerEvent(timestamp, id, EventType::SESSION_STARTED) {}




// ------------------- SessionEndEvent -----------------------

SessionEndEvent::SessionEndEvent(const std::string& timestamp, const std::string& id) : TrackerEvent(timestamp, id, EventType::SESSION_ENDED) {}





// ------------------- ReturnBaseEvent -----------------------

LeaveBaseEvent::LeaveBaseEvent(const std::string& timestamp, const std::string& id) : TrackerEvent(timestamp, id, EventType::LEAVE_BASE) {
	fatigue = sleepOption = day = 0;
}

LeaveBaseEvent* LeaveBaseEvent::setFatigue(int fatigue) {
	this->fatigue = fatigue;

	return this;
}

LeaveBaseEvent* LeaveBaseEvent::setSleepOption(int sleepOption) {
	this->sleepOption = sleepOption;

	return this;
}

LeaveBaseEvent* LeaveBaseEvent::setDay(int day) {
	this->day = day;

	return this;
}

const std::string LeaveBaseEvent::toJson() {

	json j = nlohmann::json::parse(TrackerEvent::toJson());

	j["Fatigue"] = fatigue;
	j["Sleep Option"] = sleepOption;
	j["Day"] = day;

	return j.dump(2);

}

const std::string LeaveBaseEvent::toCSV() {
	std::string parentCSV = TrackerEvent::toCSV();

	std::stringstream ss;
	ss << parentCSV << "," << fatigue << "," << sleepOption << "," << day;

	return ss.str();
}




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


// ---------------------------- ActionUsedEvent ---------------------------------

ActionUsedEvent::ActionUsedEvent(const std::string& timestamp, const std::string& id) : TrackerEvent(timestamp, id, EventType::ACTION_USED) {
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
	json j = nlohmann::json::parse(TrackerEvent::toJson());

	j["Actions Used"] = nActions;
	j["Day"] = day;

	return j.dump(2);
}

const std::string ActionUsedEvent::toCSV() {
	std::string parentCSV = TrackerEvent::toCSV();

	std::stringstream ss;
	ss << parentCSV << "," << nActions << "," << day;

	return ss.str();
}



// ------------------------ EnterRaidMenuEvent ------------------------------

EnterRaidMenuEvent::EnterRaidMenuEvent(const std::string& timestamp, const std::string& id) : TrackerEvent(timestamp, id, EventType::ENTER_RAID_MENU) {
	day = 0;
}

EnterRaidMenuEvent* EnterRaidMenuEvent::setDay(int day) {
	this->day = day;

	return this;
}

const std::string EnterRaidMenuEvent::toJson() {
	json j = nlohmann::json::parse(TrackerEvent::toJson());

	j["Day"] = day;

	return j.dump(2);
}

const std::string EnterRaidMenuEvent::toCSV() {
	std::string parentCSV = TrackerEvent::toCSV();

	std::stringstream ss;
	ss << parentCSV << "," << day;

	return ss.str();
}




// ------------------- RaidSelectedEvent -----------------------

RaidSelectedEvent::RaidSelectedEvent(const std::string& timestamp, const std::string& id) : TrackerEvent(timestamp, id, EventType::RAID_SELECTED) {
	day = hunger = location = 0;
}

RaidSelectedEvent* RaidSelectedEvent::setItems(const std::list<int>& l) {
	items = l;

	return this;
}

RaidSelectedEvent* RaidSelectedEvent::setLocation(int location) {
	this->location = location;

	return this;
}

RaidSelectedEvent* RaidSelectedEvent::setHunger(int hunger) {
	this->hunger = hunger;

	return this;
}

RaidSelectedEvent* RaidSelectedEvent::setDay(int day) {
	this->day = day;

	return this;
}

const std::string RaidSelectedEvent::toJson() {
	json j = nlohmann::json::parse(TrackerEvent::toJson());

	j["Day"] = day;

	return j.dump(2);
}

const std::string RaidSelectedEvent::toCSV() {
	std::string parentCSV = TrackerEvent::toCSV();

	std::stringstream ss;
	ss << parentCSV << "," << day;

	return ss.str();
}



// ------------------- UsingItemEvent -----------------------

ItemConsumedEvent::ItemConsumedEvent(const std::string& timestamp, const std::string& id) : TrackerEvent(timestamp, id, EventType::ITEM_CONSUMED) {
	day = 0;
}

ItemConsumedEvent* ItemConsumedEvent::setDay(int day) {
	this->day = day;

	return this;
}


const std::string ItemConsumedEvent::toJson() {
	json j = nlohmann::json::parse(TrackerEvent::toJson());

	j["Day"] = day;

	return j.dump(2);
}

const std::string ItemConsumedEvent::toCSV() {
	std::string parentCSV = TrackerEvent::toCSV();

	std::stringstream ss;
	ss << parentCSV << "," << day;

	return ss.str();
}


// -------------------- Position Event -----------------------

PositionEvent::PositionEvent(const std::string& timestamp, const std::string& id): TrackerEvent(timestamp, id, EventType::POSITION) {
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
