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
	ITEM_CONSUMED		// Consumo de un item
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
	Click	// Ubicacion seleccionada para raidear
};


class TrackerEvent {

public:
	TrackerEvent(double timestamp, std::string id, EventType eventType);

	virtual const std::string toJson() = 0;

	virtual TrackerEvent* clone() = 0;

	const EventType getType();

	bool isTrackable(uint16_t eventsMaskBits);

	static void DestroyEvent(TrackerEvent* event);

protected:

	float timestamp_;
	std::string id_;
	EventType eventType_;
	uint16_t maskBits_;

};

// Test
class TestEvent : public TrackerEvent {

public:
	TestEvent(float timestamp, std::string id, EventType eventType);

	virtual const std::string toJson();
	virtual TrackerEvent* clone();
};

// Clase intermedia para eventos diarios
class DailyEvents : public TrackerEvent {

public:
	virtual const std::string toJson();

protected:
	int day;
	DailyEvents(float timestamp, std::string id, EventType eventType);

};


// Eventos de inicio y fin de sesion
class SessionStartEvent : public TrackerEvent {

public:
	SessionStartEvent(float timestamp, std::string id);
	virtual TrackerEvent* clone();
	virtual const std::string toJson();

};

class SessionEndEvent : public TrackerEvent {

public:
	SessionEndEvent(float timestamp, std::string id);
	virtual TrackerEvent* clone();
	virtual const std::string toJson();
};


// Evento sueño al llegar al refugio
class ReturnBaseEvent : public DailyEvents {
private:
	int sleepValue;	    // Sueño al llegar al refugio
	int hungerValue;	// Hambre al llegar al refugio
	int nFood;			// Comida que se puede craftear con lo que tienes al llegar al refugio
	int nShipsPieces;	// Piezas que se pueden craftear con lo que tiene la nave
public:
	ReturnBaseEvent(float timestamp, std::string id);

	void setParameters(int sleepValue_,int hungerValue_, int nFood_, int nShipsPieces_, int day_);

	virtual const std::string toJson();

	virtual TrackerEvent* clone();
};

// Evento elección de sueño
class BaseSleepEvent : public DailyEvents {
private:
	int sleepOption;

	int nFood;
	int nMedicine;
	int nCraftingItems;
	int nAmmo;
	int nShipPieces;
public:
	BaseSleepEvent(float timeDone_, std::string id_);

	void setParameters(int sleepOption_, int nFood_, int nMedicine_, int nCraftingItems_, int nAmmo_, int nShipPieces_, int day_);

	virtual const std::string toJson();

	virtual TrackerEvent* clone();
};


// Evento crafteo nave
class CraftShipEvent : public DailyEvents {
private:
	int nCrafted;
public:
	CraftShipEvent(float timeDone_, std::string id_);

	void setParameters(int nCrafted_, int day_);

	virtual const std::string toJson();

	virtual TrackerEvent* clone();
};


// Evento crafteo nave
class BaseActionsEvent : public DailyEvents {
private:
	int nActions;
public:
	BaseActionsEvent(float timeDone_, std::string id_);

	void setParameters(int nActions_, int day_);

	virtual const std::string toJson();

	virtual TrackerEvent* clone();
};


// Evento seleccion de raid
class SelectingRaidEvent : public DailyEvents {
private:
	Locations location;
	Action accion;
public:
	SelectingRaidEvent(float timeDone_, std::string id_);

	void setParameters(Locations location_, Action accion, int day_);

	virtual const std::string toJson();

	virtual TrackerEvent* clone();
};


// Evento uso de item
class UsingItemEvent : public DailyEvents {
private:
	int nItems;
public:
	UsingItemEvent(float timeDone_, std::string id_);

	void setParameters(int nItems, int day_);

	virtual const std::string toJson();

	virtual TrackerEvent* clone();
};