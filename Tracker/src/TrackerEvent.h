#pragma once

#include <string>
#include <list>
#include <functional>


// Tipos de Eventos que recoge el tracker

enum class EventType { 
	SESSION_STARTED,	// Comienzo de la sesion
	SESSION_ENDED,		// Fin de la sesion
	LEAVE_BASE,			// Vuelta de una raid al refugio
	FOOD_ITEM_CRAFTED,	// Crafteo de items de comida
	SHIP_ITEM_CRAFTED,  // Crafteo de item de nave
	ACTION_USED,		// Uso de una accion
	ENTER_RAID_MENU,	// Entrada al menu de raid
	RAID_SELECTED,      // Opcion de raid elegidas
	ITEM_CONSUMED,		// Consumo de un item
	POSITION,	        // Posicion del jugador u otro npc
};	

//Primera fila del CSV para cada eventType

const std::string CSVPrefixes[] = {
	"Id,Time\n",														//0
	"Id,Time\n",														//1
	"Id,Time,Fatigue,\"Sleepo ption\",Day\n",							//2
	"Id,Time,Hunger,\"Can craft food items\",Day\n",					//3
	"Id,Time,\"Ship items crafted\",\"Craftable ship items\",Day\n",	//4
	"Id,Time,\"Actions used\",Day\n",									//5
	"Id,Time,Day\n",													//6
	"Id,Time,Day\n",													//7
	"Id,Time,Day\n",													//8
	"Id,Time,X,Y,Entity\n"												//9,
};

// Enum -> String (Comodidad)
const std::string eventTypes[] = {
	"SESSION_STARTED",	//0
	"SESSION_ENDED",	//1
	"LEAVE_BASE",		//2
	"FOOD_ITEM_CRAFTED",//3
	"SHIP_ITEM_CRAFTED",//4
	"ACTION_USED",		//5
	"ENTER_RAID_MENU",	//6
	"RAID_SELECTED",	//7
	"ITEM_CONSUMED",	//8
	"POSITION"			//9,
};


// Clase padre para representar un evento con la informacion base
class TrackerEvent {

public:
	TrackerEvent(const std::string& timestamp, const std::string& id, EventType eventType);
	virtual ~TrackerEvent() {};
	virtual const std::string toJson();
	virtual const std::string toCSV();

	const EventType getType();

	bool isTrackable(uint16_t eventsMaskBits);

	static void DestroyEvent(TrackerEvent* event);

protected:

	std::string timestamp_;
	std::string id_;
	EventType eventType_;
	uint16_t maskBits_;
};

/*
* Clase para manejar eventos periodicos.
* 
* Recibe un evento como parametro para ser trackeado periodicamente.
* 
* Util para trackear posicion de entidades, vida del jugador... etc.
*/
class RecurringEvent {

public: 

	RecurringEvent(std::function<TrackerEvent* ()> func, float interval);

	void Update(float dt);

private:

	float interval;
	float timer;

	std::function<TrackerEvent* ()> creator;

};


// Evento de inicio de sesion
class SessionStartEvent : public TrackerEvent {

public:
	SessionStartEvent(const std::string& timestamp, const std::string& id);

};


// Evento de fin de sesion
class SessionEndEvent : public TrackerEvent {

public:
	SessionEndEvent(const std::string& timestamp, const std::string& id);
};


// Evento sueño al llegar al refugio
class LeaveBaseEvent : public TrackerEvent {
private:

	int fatigue;	    // Sueño al llegar al refugio
	int sleepOption;	// Opcion de sueño elegida
	int day;			// Dia del ciclo

public:

	LeaveBaseEvent(const std::string& timestamp, const std::string& id);

	LeaveBaseEvent* setFatigue(int fatigue);
	LeaveBaseEvent* setSleepOption(int sleepOption);
	LeaveBaseEvent* setDay(int day);

	virtual const std::string toJson();
	virtual const std::string toCSV();
};


// Evento crafteo de un item de comida
class FoodItemCraftedEvent : public TrackerEvent {
private:

	int hunger;		// Sueño al llegar al refugio
	bool craft;		// Indica si puede craftear el jugador items de comida
	int day;		// Dia del ciclo

public:

	FoodItemCraftedEvent(const std::string& timestamp, const std::string& id);

	FoodItemCraftedEvent* setHunger(int hunger);
	FoodItemCraftedEvent* setCraft(bool craft);
	FoodItemCraftedEvent* setDay(int day);

	virtual const std::string toJson();
	virtual const std::string toCSV();
};



// Evento crafteo de item de nave
class ShipItemCraftedEvent : public TrackerEvent {
private:
	int nCrafted;
	int nCraftables;
	int day;
public:
	ShipItemCraftedEvent(const std::string& timestamp, const std::string& id);

	ShipItemCraftedEvent* setCrafted(int crafted);
	ShipItemCraftedEvent* setCraftables(int craftables);
	ShipItemCraftedEvent* setDay(int day);

	virtual const std::string toJson();
	virtual const std::string toCSV();
};




// Evento uso de accion
class ActionUsedEvent : public TrackerEvent {
private:
	int nActions;
	int day;
public:

	ActionUsedEvent(const std::string& timestamp, const std::string& id);

	ActionUsedEvent* setActions(int actions);
	ActionUsedEvent* setDay(int day);

	virtual const std::string toJson();
	virtual const std::string toCSV();
};



// Evento entrada al menu de raid
class EnterRaidMenuEvent : public TrackerEvent {
private:

	int day;

public:

	EnterRaidMenuEvent(const std::string& timestamp, const std::string& id);

	EnterRaidMenuEvent* setDay(int day);

	virtual const std::string toJson();
	virtual const std::string toCSV();
};



// Evento seleccion de raid
class RaidSelectedEvent : public TrackerEvent {
private:

	std::list<int> items;
	int location;
	int hunger;
	int day;

public:
	RaidSelectedEvent(const std::string& timestamp, const std::string& id);

	RaidSelectedEvent* setItems(const std::list<int>& l);
	RaidSelectedEvent* setLocation(int location);
	RaidSelectedEvent* setHunger(int hunger);
	RaidSelectedEvent* setDay(int day);

	virtual const std::string toJson();
	virtual const std::string toCSV();
};



// Evento uso de item
class ItemConsumedEvent : public TrackerEvent {

private:
	int day;

public:
	ItemConsumedEvent(const std::string& timestamp, const std::string& id);

	ItemConsumedEvent* setDay(int day);

	virtual const std::string toJson();
	virtual const std::string toCSV();
};



// Evento posicion actual de una entidad de juego
class PositionEvent : public TrackerEvent {

private:
	float x;
	float y;

	std::string entity;

public:
	PositionEvent(const std::string& timestamp, const std::string& id);

	PositionEvent* setPosition(float x, float y);
	PositionEvent* setEntity(std::string name);

	virtual const std::string toJson();
	virtual const std::string toCSV();
};