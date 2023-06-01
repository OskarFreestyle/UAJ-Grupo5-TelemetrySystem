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
