#include "TrackerEvent.h"
#include <iostream>


TrackerEvent::TrackerEvent(double timestamp, std::string id, EventType eventType) : timestamp_(timestamp), id_(id_), eventType_(eventType) {}

const std::string TrackerEvent::toJson() {
	// TODO
	return "";
}

const EventType TrackerEvent::getType() {
	return eventType_;
}



// ------------------- DailyEvents -----------------------

DailyEvents::DailyEvents(float timeDone_, std::string id_, EventType eventName_) : TrackerEvent(timeDone_, id_, eventName_) {

}

const std::string DailyEvents::toJson() {
	// TODO
	return "";
}



// ------------------- SessionStartEvent -----------------------

SessionStartEvent::SessionStartEvent(float timeDone_, std::string id_) : TrackerEvent(timeDone_, id_, START_SESSION) {
	std::cout << "Empezo la sesion" << std::endl;
}

TrackerEvent* SessionStartEvent::clone() {
	return new SessionStartEvent(timestamp_, id_);
}



// ------------------- SessionEndEvent -----------------------

SessionEndEvent::SessionEndEvent(float timeDone_, std::string id_) : TrackerEvent(timeDone_, id_, END_SESSION) {
	std::cout << "Empezo la sesion" << std::endl;
}

TrackerEvent* SessionEndEvent::clone() {
	return new SessionStartEvent(timestamp_, id_);
}



// ------------------- ReturnBaseEvent -----------------------

ReturnBaseEvent::ReturnBaseEvent(float timeDone_, std::string id_) : DailyEvents(timeDone_, id_, RETURN_BASE) {
	std::cout << "Ha vuelto a la base" << std::endl;
}

void ReturnBaseEvent::setParameters(int sleepValue_, int hungerValue_, int nFood_, int nShipsPieces_, int day_) {
	sleepValue = sleepValue_;
	hungerValue = hungerValue_;
	nFood = nFood_;
	nShipsPieces = nShipsPieces_;
	day = day_;
}

const std::string ReturnBaseEvent::toJson() {
	// TODO
	return "";
}

TrackerEvent* ReturnBaseEvent::clone() {
	ReturnBaseEvent* aux = new ReturnBaseEvent(timestamp_, id_);
	aux->setParameters(sleepValue, hungerValue, nFood, nShipsPieces,day);

	return aux;
}


// ------------------- BaseSleepEvent -----------------------

BaseSleepEvent::BaseSleepEvent(float timeDone_, std::string id_) : DailyEvents(timeDone_, id_, BASE_SLEEP_OPTION) {
	std::cout << "Ha ido a dormir" << std::endl;
}

void BaseSleepEvent::setParameters(int sleepOption_, int nFood_, int nMedicine_, int nCraftingItems_, int nAmmo_, int nShipPieces_, int day_) {
	sleepOption = sleepOption_;
	nFood = nFood_;
	nMedicine = nMedicine_;
	nCraftingItems = nCraftingItems_;
	nAmmo = nAmmo_;
	nShipPieces = nShipPieces_;
	day = day_;

	std::cout << "El dia " << day << " ha elegido la opcion de dormir " << sleepOption << std::endl;
}

const std::string BaseSleepEvent::toJson() {
	// TODO
	return "";
}

TrackerEvent* BaseSleepEvent::clone() {
	BaseSleepEvent* aux = new BaseSleepEvent(timestamp_, id_);
	aux->setParameters(sleepOption, nFood, nMedicine, nCraftingItems, nAmmo, nShipPieces, day);

	return aux;
}



// ------------------- CraftShipEvent -----------------------

CraftShipEvent::CraftShipEvent(float timeDone_, std::string id_) : DailyEvents(timeDone_, id_, CRAFTED_SHIP_ITEMS) {
	std::cout << "Crafteo de nave" << std::endl;
}

void CraftShipEvent::setParameters(int nCrafted_, int day_) {
	nCrafted = nCrafted_;
	day = day_;

	std::cout << "El dia " << day << " he crafteado de nave estas piezas " << nCrafted << std::endl;
}

const std::string CraftShipEvent::toJson() {
	// TODO
	return "";
}

TrackerEvent* CraftShipEvent::clone() {
	CraftShipEvent* aux = new CraftShipEvent(timestamp_, id_);
	aux->setParameters(nCrafted, day);

	return aux;

}


// ------------------- BaseActionsEvent -----------------------

BaseActionsEvent::BaseActionsEvent(float timeDone_, std::string id_) : DailyEvents(timeDone_, id_, BASE_ACTIONS_USED) {
	std::cout << "Crafteo de nave" << std::endl;
}

void BaseActionsEvent::setParameters(int nActions_, int day_) {
	nActions = nActions_;
	day = day_;

	std::cout << "El dia " << day << " he usado estas acciones " << nActions << std::endl;
}

const std::string BaseActionsEvent::toJson() {
	// TODO
	return "";
}

TrackerEvent* BaseActionsEvent::clone() {
	BaseActionsEvent* aux = new BaseActionsEvent(timestamp_, id_);
	aux->setParameters(nActions, day);

	return aux;
}



// ------------------- SelectingRaidEvent -----------------------

SelectingRaidEvent::SelectingRaidEvent(float timeDone_, std::string id_) : DailyEvents(timeDone_, id_, SELECTING_RAID) {
	std::cout << "Crafteo de nave" << std::endl;
}

void SelectingRaidEvent::setParameters(Locations location_, Action accion_, int day_) {
	location = location_;
	accion = accion_;
	day = day_;

	std::cout << "El dia " << day << " esta sobre " << location_ << std::endl;
}

const std::string SelectingRaidEvent::toJson() {
	// TODO
	return "";
}

TrackerEvent* SelectingRaidEvent::clone() {
	SelectingRaidEvent* aux = new SelectingRaidEvent(timestamp_, id_);
	aux->setParameters(location, accion, day);

	return aux;
}



// ------------------- UsingItemEvent -----------------------

UsingItemEvent::UsingItemEvent(float timeDone_, std::string id_) : DailyEvents(timeDone_, id_, USING_ITEM) {
	std::cout << "Crafteo de nave" << std::endl;
}

void UsingItemEvent::setParameters(int nItems_, int day_) {
	nItems = nItems_;
	day = day_;

	std::cout << "El dia " << day << " ha usado estos items " << nItems << std::endl;
}

const std::string UsingItemEvent::toJson() {
	// TODO
	return "";
}

TrackerEvent* UsingItemEvent::clone() {
	UsingItemEvent* aux = new UsingItemEvent(timestamp_, id_);
	aux->setParameters(nItems, day);

	return aux;
}