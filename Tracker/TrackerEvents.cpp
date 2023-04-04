#include "TrackerEvents.h"
#include <iostream>


TrackerEvents::TrackerEvents(double timeDone_, std::string id_, EventType eventName_) : timeDone(timeDone_), id(id_), eventName(eventName_) {}

const std::string TrackerEvents::toJson()
{
	//RELLENAR CUANDO SE TENGA EL FORMATO JSON
	return "";
}

const EventType TrackerEvents::getType()
{ 
	return eventName;
}

//Clase intermedia DailyEvents

DailyEvents::DailyEvents(float timeDone_, std::string id_, EventType eventName_) : TrackerEvents(timeDone_, id_, eventName_)
{

}

const std::string DailyEvents::toJson()
{
	return "";
}


//CLASE SessionStartEvent
SessionStartEvent::SessionStartEvent(float timeDone_, std::string id_) : TrackerEvents(timeDone_, id_, START_SESSION)
{ 
	std::cout << "Empezo la sesion" << std::endl; 
}

TrackerEvents* SessionStartEvent::clone()
{
	return new SessionStartEvent(timeDone, id);
}

//CLASE SessionEndEvent

SessionEndEvent::SessionEndEvent(float timeDone_, std::string id_) : TrackerEvents(timeDone_, id_, END_SESSION)
{
	std::cout << "Empezo la sesion" << std::endl;
}

TrackerEvents* SessionEndEvent::clone()
{
	return new SessionStartEvent(timeDone, id);
}

//CLASE ReturnBaseEvent

ReturnBaseEvent::ReturnBaseEvent(float timeDone_, std::string id_) : DailyEvents(timeDone_, id_, RETURN_BASE)
{
	std::cout << "Ha vuelto a la base" << std::endl;
}

void ReturnBaseEvent::setParameters(int sleepValue_, int hungerValue_, int nFood_, int nShipsPieces_, int day_)
{
	sleepValue = sleepValue_;
	hungerValue = hungerValue_;
	nFood = nFood_;
	nShipsPieces = nShipsPieces_;
	day = day_;
}

const std::string ReturnBaseEvent::toJson()
{
	return "";
}

TrackerEvents* ReturnBaseEvent::clone()
{
	ReturnBaseEvent* aux = new ReturnBaseEvent(timeDone, id);
	aux->setParameters(sleepValue, hungerValue, nFood, nShipsPieces,day);

	return aux;
}

//CLASE BaseSleepEvent

BaseSleepEvent::BaseSleepEvent(float timeDone_, std::string id_) : DailyEvents(timeDone_, id_, BASE_SLEEP_OPTION)
{
	std::cout << "Ha ido a dormir" << std::endl;
}

void BaseSleepEvent::setParameters(int sleepOption_, int nFood_, int nMedicine_, int nCraftingItems_, int nAmmo_, int nShipPieces_, int day_)
{
	sleepOption = sleepOption_;
	nFood = nFood_;
	nMedicine = nMedicine_;
	nCraftingItems = nCraftingItems_;
	nAmmo = nAmmo_;
	nShipPieces = nShipPieces_;
	day = day_;

	std::cout << "El dia " << day << " ha elegido la opcion de dormir " << sleepOption << std::endl;
}

const std::string BaseSleepEvent::toJson()
{
	return "";
}

TrackerEvents* BaseSleepEvent::clone()
{
	BaseSleepEvent* aux = new BaseSleepEvent(timeDone, id);
	aux->setParameters(sleepOption, nFood, nMedicine, nCraftingItems, nAmmo, nShipPieces, day);

	return aux;
}

//Clase CraftShipEvent

CraftShipEvent::CraftShipEvent(float timeDone_, std::string id_) : DailyEvents(timeDone_, id_, CRAFTED_SHIP_ITEMS)
{
	std::cout << "Crafteo de nave" << std::endl;
}

void CraftShipEvent::setParameters(int nCrafted_, int day_)
{
	nCrafted = nCrafted_;
	day = day_;

	std::cout << "El dia " << day << " he crafteado de nave estas piezas " << nCrafted << std::endl;
}

const std::string CraftShipEvent::toJson()
{
	return "";
}

TrackerEvents* CraftShipEvent::clone()
{
	CraftShipEvent* aux = new CraftShipEvent(timeDone, id);
	aux->setParameters(nCrafted, day);

	return aux;
}

//Clase CraftShipEvent

BaseActionsEvent::BaseActionsEvent(float timeDone_, std::string id_) : DailyEvents(timeDone_, id_, BASE_ACTIONS_USED)
{
	std::cout << "Crafteo de nave" << std::endl;
}

void BaseActionsEvent::setParameters(int nActions_, int day_)
{
	nActions = nActions_;
	day = day_;

	std::cout << "El dia " << day << " he usado estas acciones " << nActions << std::endl;
}

const std::string BaseActionsEvent::toJson()
{
	return "";
}

TrackerEvents* BaseActionsEvent::clone()
{
	BaseActionsEvent* aux = new BaseActionsEvent(timeDone, id);
	aux->setParameters(nActions, day);

	return aux;
}

//Clase SelectingRaidEvent

SelectingRaidEvent::SelectingRaidEvent(float timeDone_, std::string id_) : DailyEvents(timeDone_, id_, SELECTING_RAID)
{
	std::cout << "Crafteo de nave" << std::endl;
}

void SelectingRaidEvent::setParameters(Places location_, Action accion_, int day_)
{
	location = location_;
	accion = accion_;
	day = day_;

	std::cout << "El dia " << day << " esta sobre " << location_ << std::endl;
}

const std::string SelectingRaidEvent::toJson()
{
	return "";
}

TrackerEvents* SelectingRaidEvent::clone()
{
	SelectingRaidEvent* aux = new SelectingRaidEvent(timeDone, id);
	aux->setParameters(location, accion, day);

	return aux;
}

//Clase UsingItemEvent

UsingItemEvent::UsingItemEvent(float timeDone_, std::string id_) : DailyEvents(timeDone_, id_, USING_ITEM)
{
	std::cout << "Crafteo de nave" << std::endl;
}

void UsingItemEvent::setParameters(int nItems_, int day_)
{
	nItems = nItems_;
	day = day_;

	std::cout << "El dia " << day << " ha usado estos items " << nItems << std::endl;
}

const std::string UsingItemEvent::toJson()
{
	return "";
}

TrackerEvents* UsingItemEvent::clone()
{
	UsingItemEvent* aux = new UsingItemEvent(timeDone, id);
	aux->setParameters(nItems, day);

	return aux;
}