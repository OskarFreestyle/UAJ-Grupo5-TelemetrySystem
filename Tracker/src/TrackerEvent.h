#pragma once

#include <string>
#include <list>


// Tipos de Eventos que recoge el tracker

enum class EventType { 
	SESSION_STARTED,	// Comienzo de la sesion
	SESSION_ENDED,		// Fin de la sesion
	RETURNED_TO_BASE,	// Vuelta de una raid al refugio
	FOOD_ITEM_CRAFTED,	// Crafteo de items de comida
	SHIP_ITEM_CRAFTED,  // Crafteo de item de nave
	ACTION_USED,		// Uso de una accion
	ENTER_RAID_MENU,	// Entrada al menu de raid
	RAID_SELECTED,      // Opcion de raid elegidas
	ITEM_CONSUMED,		// Consumo de un item
};	


// Enum -> String (Comodidad)
const std::string eventTypes[] = {
	"SESSION_STARTED",
	"SESSION_ENDED",
	"RETURNED_TO_BASE",
	"FOOD_ITEM_CRAFTED",
	"SHIP_ITEM_CRAFTED",
	"ACTION_USED",
	"RAID_SELECTED",
	"ITEM_CONSUMED"
};



class TrackerEvent {

public:

	TrackerEvent(double timestamp, std::string id, EventType eventType);

	virtual TrackerEvent* clone() = 0;
	virtual const std::string toJson();
	virtual const std::string toCSV();

	const EventType getType();

	bool isTrackable(uint16_t eventsMaskBits);

	static void DestroyEvent(TrackerEvent* event);

protected:

	float timestamp_;
	std::string id_;
	EventType eventType_;
	uint16_t maskBits_;

};


// Evento de inicio de sesion
class SessionStartEvent : public TrackerEvent {

public:
	SessionStartEvent(float timestamp, std::string id);
	virtual TrackerEvent* clone();

};


// Evento de fin de sesion
class SessionEndEvent : public TrackerEvent {

public:
	SessionEndEvent(float timestamp, std::string id);
	virtual SessionEndEvent* clone();
};


// Evento sueño al llegar al refugio
class ReturnToBaseEvent : public TrackerEvent {
private:

	int fatigue;	    // Sueño al llegar al refugio
	int sleepOption;	// Opcion de sueño elegida
	int day;			// Dia del ciclo

public:

	ReturnToBaseEvent(float timestamp, std::string id);

	ReturnToBaseEvent* setFatigue(int fatigue);
	ReturnToBaseEvent* setSleepOption(int sleepOption);
	ReturnToBaseEvent* setDay(int day);

	virtual const std::string toJson();
	virtual const std::string toCSV();
	virtual ReturnToBaseEvent* clone();
};


// Evento crafteo de un item de comida
class FoodItemCraftedEvent : public TrackerEvent {
private:

	int hunger;		// Sueño al llegar al refugio
	bool craft;		// Indica si puede craftear el jugador items de comida
	int day;		// Dia del ciclo

public:

	FoodItemCraftedEvent(float timestamp, std::string id);

	FoodItemCraftedEvent* setHunger(int hunger);
	FoodItemCraftedEvent* setCraft(bool craft);
	FoodItemCraftedEvent* setDay(int day);

	virtual const std::string toJson();
	virtual const std::string toCSV();
	virtual FoodItemCraftedEvent* clone();
};



// Evento crafteo de item de nave
class ShipItemCraftedEvent : public TrackerEvent {
private:
	int nCrafted;
	int nCraftables;
	int day;
public:
	ShipItemCraftedEvent(float timestamp, std::string id);

	ShipItemCraftedEvent* setCrafted(int crafted);
	ShipItemCraftedEvent* setCraftables(int craftables);
	ShipItemCraftedEvent* setDay(int day);

	virtual const std::string toJson();
	virtual const std::string toCSV();
	virtual ShipItemCraftedEvent* clone();
};




// Evento uso de accion
class ActionUsedEvent : public TrackerEvent {
private:
	int nActions;
	int day;
public:

	ActionUsedEvent(float timestamp, std::string id);

	ActionUsedEvent* setActions(int actions);
	ActionUsedEvent* setDay(int day);

	virtual const std::string toJson();
	virtual const std::string toCSV();
	virtual ActionUsedEvent* clone();
};



// Evento entrada al menu de raid
class EnterRaidMenuEvent : public TrackerEvent {
private:

	int day;

public:

	EnterRaidMenuEvent(float timestamp, std::string id);

	EnterRaidMenuEvent* setDay(int day);

	virtual const std::string toJson();
	virtual const std::string toCSV();
	virtual EnterRaidMenuEvent* clone();
};



// Evento seleccion de raid
class RaidSelectedEvent : public TrackerEvent {
private:

	std::list<int> items;
	int location;
	int hunger;
	int day;

public:
	RaidSelectedEvent(float timestamp, std::string id);

	RaidSelectedEvent* setItems(const std::list<int>& l);
	RaidSelectedEvent* setLocation(int location);
	RaidSelectedEvent* setHunger(int hunger);
	RaidSelectedEvent* setDay(int day);

	virtual const std::string toJson();
	virtual const std::string toCSV();
	virtual RaidSelectedEvent* clone();
};



// Evento uso de item
class ItemConsumedEvent : public TrackerEvent {

private:
	int day;

public:
	ItemConsumedEvent(float timestamp, std::string id);

	ItemConsumedEvent* setDay(int day);

	virtual const std::string toJson();
	virtual const std::string toCSV();
	virtual ItemConsumedEvent* clone();
};