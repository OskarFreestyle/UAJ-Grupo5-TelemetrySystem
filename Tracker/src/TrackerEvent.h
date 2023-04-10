#pragma once
#include <string>

// Tipos de Eventos que recoge el tracker

enum class EventType { 
	SESSION_STARTED,	// Comienzo de la sesion
	SESSION_ENDED,		// Fin de la sesion
	RETURNED_TO_BASE,	// Vuelta de una raid al refugio
	FOOD_ITEM_CRAFTED,	// Crafteo de items de comida
	SHIP_ITEM_CRAFTED,  // Crafteo de item de nave
	ACTION_USED,		// Uso de una accion
	RAID_SELECTED,      // Opcion de raid elegidas
	ITEM_CONSUMED,		// Consumo de un item
};	

enum Locations {
	Hospital,
	Nuclear_Station,
	Coms,
	Supermarket,
	Shop
};

enum Action {
	Enter,
	Leave,
	Click
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
	virtual TrackerEvent* clone();
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
	virtual TrackerEvent* clone();
};


// Evento crafteo de un item de comida
class FoodItemCraftedEvent : public TrackerEvent {
private:

	int hunger;		    // Sueño al llegar al refugio
	bool craft;		// Indica si puede craftear el jugador items de comida
	int day;			// Dia del ciclo

public:

	FoodItemCraftedEvent(float timestamp, std::string id);

	FoodItemCraftedEvent* setHunger(int hunger);
	FoodItemCraftedEvent* setCraft(bool craft);
	FoodItemCraftedEvent* setDay(int day);

	virtual const std::string toJson();
	virtual const std::string toCSV();
	virtual TrackerEvent* clone();
};







// Evento elección de sueño
class BaseSleepEvent : public TrackerEvent {
private:
	int sleepOption;

	int nFood;
	int nMedicine;
	int nCraftingItems;
	int nAmmo;
	int nShipPieces;
	int day;

public:
	BaseSleepEvent(float timeDone_, std::string id_);

	void setParameters(int sleepOption_, int nFood_, int nMedicine_, int nCraftingItems_, int nAmmo_, int nShipPieces_, int day_);

	virtual const std::string toJson();

	virtual const std::string toCSV();

	virtual TrackerEvent* clone();
};


// Evento crafteo nave
class CraftShipEvent : public TrackerEvent {
private:
	int nCrafted;
	int day;
public:
	CraftShipEvent(float timeDone_, std::string id_);

	void setParameters(int nCrafted_, int day_);

	virtual const std::string toJson();

	virtual const std::string toCSV();

	virtual TrackerEvent* clone();
};


// Evento crafteo nave
class BaseActionsEvent : public TrackerEvent {
private:
	int nActions;
	int day;
public:
	BaseActionsEvent(float timeDone_, std::string id_);

	void setParameters(int nActions_, int day_);

	virtual const std::string toJson();

	virtual const std::string toCSV();

	virtual TrackerEvent* clone();
};


// Evento seleccion de raid
class SelectingRaidEvent : public TrackerEvent {
private:
	Locations location;
	Action accion;
	int day;
public:
	SelectingRaidEvent(float timeDone_, std::string id_);

	void setParameters(Locations location_, Action accion, int day_);

	virtual const std::string toJson();

	virtual const std::string toCSV();

	virtual TrackerEvent* clone();
};


// Evento uso de item
class UsingItemEvent : public TrackerEvent {
private:
	int nItems;
	int day;
public:
	UsingItemEvent(float timeDone_, std::string id_);

	void setParameters(int nItems, int day_);

	virtual const std::string toJson();

	virtual const std::string toCSV();

	virtual TrackerEvent* clone();
};