#pragma once
#include <string>

// Tipos de Eventos que recoge el tracker

enum EventType { 
	START_SESSION,
	END_SESSION,
	RETURN_BASE,		// Información al llegar a la base
	BASE_SLEEP_OPTION,  // Opcion de sueño elegida
	CRAFTED_SHIP_ITEMS, // Partes la nave crafteadas cada dia
	BASE_ACTIONS_USED,  // Acciones usadas en el refugio
	SELECTING_RAID,     // Opcion de raid elegidas
	USING_ITEM
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

protected:
	float timestamp_;
	std::string id_;
	EventType eventType_;

public:
	TrackerEvent(double timestamp, std::string id, EventType eventType);

	virtual const std::string toJson();

	const EventType getType();

	virtual TrackerEvent* clone() = 0;
};


// Eventos de inicio y fin de sesion
class SessionStartEvent : public TrackerEvent {
public:
	SessionStartEvent(float timeDone_, std::string id_);
	virtual TrackerEvent* clone();
};

class SessionEndEvent : public TrackerEvent {
public:
	SessionEndEvent(float timeDone_, std::string id_);
	virtual TrackerEvent* clone();
};


// Clase intermedia Eventos diarios
class DailyEvents : public TrackerEvent {
protected:
	int day;
	DailyEvents(float timeDone_, std::string id_, EventType eventName_);
public:
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
	ReturnBaseEvent(float timeDone_, std::string id_);

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