#include "TrackerEvent.h"
#include "nlohmann/json.hpp"
#include "checkML.h"
#include "Tracker.h"
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

	return j.dump(2);
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

SessionEndEvent* SessionEndEvent::clone() {
	return new SessionEndEvent(timestamp_, id_);
}





// ------------------- ReturnBaseEvent -----------------------

LeaveBaseEvent::LeaveBaseEvent(float timestamp, std::string id) : TrackerEvent(timestamp, id, EventType::LEAVE_BASE) {
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

	std::string parentJson = TrackerEvent::toJson();

	json j;
	j["Fatigue"] = fatigue;
	j["Sleep Option"] = sleepOption;
	j["Day"] = day;

	return parentJson + j.dump(2);

}

const std::string LeaveBaseEvent::toCSV() {
	std::string parentCSV = TrackerEvent::toCSV();

	std::stringstream ss;
	ss << parentCSV << ",Fatigue:" << fatigue << ",Sleep Option:" << sleepOption << ",Day:" << day;

	return ss.str();
}

LeaveBaseEvent* LeaveBaseEvent::clone() {
	LeaveBaseEvent* e = new LeaveBaseEvent(timestamp_, id_);

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
	j["Can Craft Food Items"] = craft;
	j["Day"] = day;

	return parentJson + j.dump(2);
}

const std::string FoodItemCraftedEvent::toCSV() {
	std::string parentCSV = TrackerEvent::toCSV();

	std::stringstream ss;
	ss << parentCSV << ",Hunger:" << hunger << ",Can Craft Food Items:" << craft << ",Day:" << day;

	return ss.str();
}

FoodItemCraftedEvent* FoodItemCraftedEvent::clone() {
	FoodItemCraftedEvent* e = new FoodItemCraftedEvent(timestamp_, id_);

	e->setHunger(hunger)->setCraft(craft)->setDay(day);

	return e;
}




// -------------------------- CraftShipEvent ------------------------------

ShipItemCraftedEvent::ShipItemCraftedEvent(float timestamp, std::string id) : TrackerEvent(timestamp, id, EventType::SHIP_ITEM_CRAFTED) {
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
	std::string parentJson = TrackerEvent::toJson();

	json j;
	j["Ship Items Crafted"] = nCrafted;
	j["Craftable Ship Items"] = nCraftables;
	j["Day"] = day;

	return parentJson + j.dump(2);
}

const std::string ShipItemCraftedEvent::toCSV() {
	std::string parentCSV = TrackerEvent::toCSV();

	std::stringstream ss;
	ss << parentCSV << ",Ship Items Crafted:" << nCrafted << ",Craftable Ship Items:" << nCraftables << ",Day:" << day;

	return ss.str();
}

ShipItemCraftedEvent* ShipItemCraftedEvent::clone() {
	ShipItemCraftedEvent* e = new ShipItemCraftedEvent(timestamp_, id_);

	e->setCrafted(nCrafted)->setCraftables(nCraftables)->setDay(day);

	return e;

}


// ---------------------------- ActionUsedEvent ---------------------------------

ActionUsedEvent::ActionUsedEvent(float timestamp, std::string id) : TrackerEvent(timestamp, id, EventType::ACTION_USED) {
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
	std::string parentJson = TrackerEvent::toJson();

	json j;
	j["Actions Used"] = nActions;
	j["Day"] = day;

	return parentJson + j.dump(2);
}

const std::string ActionUsedEvent::toCSV() {
	std::string parentCSV = TrackerEvent::toCSV();

	std::stringstream ss;
	ss << parentCSV << ",Actions Used:" << nActions << ",Day:" << day;

	return ss.str();
}

ActionUsedEvent* ActionUsedEvent::clone() {
	ActionUsedEvent* e = new ActionUsedEvent(timestamp_, id_);

	e->setActions(nActions)->setDay(day);

	return e;
}



// ------------------------ EnterRaidMenuEvent ------------------------------

EnterRaidMenuEvent::EnterRaidMenuEvent(float timestamp, std::string id) : TrackerEvent(timestamp, id, EventType::ENTER_RAID_MENU) {
	day = 0;
}

EnterRaidMenuEvent* EnterRaidMenuEvent::setDay(int day) {
	this->day = day;

	return this;
}

const std::string EnterRaidMenuEvent::toJson() {
	std::string parentJson = TrackerEvent::toJson();

	json j;
	j["Day"] = day;

	return parentJson + j.dump(2);
}

const std::string EnterRaidMenuEvent::toCSV() {
	std::string parentCSV = TrackerEvent::toCSV();

	std::stringstream ss;
	ss << parentCSV << ",Day:" << day;

	return ss.str();
}

EnterRaidMenuEvent* EnterRaidMenuEvent::clone() {
	EnterRaidMenuEvent* e = new EnterRaidMenuEvent(timestamp_, id_);

	e->setDay(day);

	return e;
}




// ------------------- RaidSelectedEvent -----------------------

RaidSelectedEvent::RaidSelectedEvent(float timestamp, std::string id) : TrackerEvent(timestamp, id, EventType::RAID_SELECTED) {
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
	std::string parentJson = TrackerEvent::toJson();

	json j;
	j["Day"] = day;

	return parentJson + j.dump(2);
}

const std::string RaidSelectedEvent::toCSV() {
	std::string parentCSV = TrackerEvent::toCSV();

	std::stringstream ss;
	ss << parentCSV << ",Day:" << day;

	return ss.str();
}

RaidSelectedEvent* RaidSelectedEvent::clone() {
	RaidSelectedEvent* e = new RaidSelectedEvent(timestamp_, id_);

	e->setDay(day);

	return e;
}



// ------------------- UsingItemEvent -----------------------

ItemConsumedEvent::ItemConsumedEvent(float timestamp, std::string id) : TrackerEvent(timestamp, id, EventType::ITEM_CONSUMED) {
	day = 0;
}

ItemConsumedEvent* ItemConsumedEvent::setDay(int day) {
	this->day = day;

	return this;
}


const std::string ItemConsumedEvent::toJson() {
	std::string parentJson = TrackerEvent::toJson();

	json j;
	j["Day"] = day;

	return parentJson + j.dump(2);
}

const std::string ItemConsumedEvent::toCSV() {
	std::string parentCSV = TrackerEvent::toCSV();

	std::stringstream ss;
	ss << parentCSV << ",Day:" << day;

	return ss.str();
}

ItemConsumedEvent* ItemConsumedEvent::clone() {
	ItemConsumedEvent* e = new ItemConsumedEvent(timestamp_, id_);

	e->setDay(day);

	return e;
}

RecurringEvent::RecurringEvent(float interval, std::function<TrackerEvent* ()> func) {

	timer = 0;
	creator = func;
	this->interval = interval;
}

void RecurringEvent::Update(float dt)
{
	timer += dt;

	if (timer > interval) {

		Tracker::Instance()->trackEvent(creator());

		timer = 0;
	}
}

PositionEvent::PositionEvent(float timestamp, std::string id): TrackerEvent(timestamp, id, EventType::POSITION)
{
	x = y = 0;
}
PositionEvent* PositionEvent::setPosition(float x, float y)
{
	this->x = x;
	this->y = y;

	return this;
}

PositionEvent* PositionEvent::setEntity(std::string name)
{
	entity = name;
	return this;
}
const std::string PositionEvent::toJson()
{
	json j = nlohmann::json::parse(TrackerEvent::toJson());

	j["x"] = x;
	j["y"] = x;
	j["entity"] = entity;

	return j.dump(2);
}

const std::string PositionEvent::toCSV()
{
	std::string parentCSV = TrackerEvent::toCSV();

	std::stringstream ss;
	ss << parentCSV << ",x:" << x << ",y:" << y << ",entity:" << entity;

	return ss.str();
}

PositionEvent* PositionEvent::clone()
{
	PositionEvent* e = new PositionEvent(timestamp_, id_);

	e->setPosition(x, y);
	e->setEntity(entity);

	return e;
}
