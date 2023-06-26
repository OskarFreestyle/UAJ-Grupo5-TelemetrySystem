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
	RAID_VISUALIZED,	// Visualizar una raid
	ITEM_CONSUMED,		// Consumo de un item
	POSITION,	        // Posicion del jugador u otro npc
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
	"RAID_VISUALIZED",	//8
	"ITEM_CONSUMED",	//9
	"POSITION"			//10,
};

enum class CSVFields;

// Clase padre para representar un evento con la informacion base
class TrackerEvent {

public:
	TrackerEvent(int timestamp, const std::string& id, EventType eventType);
	virtual ~TrackerEvent() {};
	virtual const std::string toJson();
	virtual const void toCSV(std::unordered_map<CSVFields, std::string>& eventCSV);

	const EventType getType();

	bool isTrackable(uint16_t eventsMaskBits);

	static void DestroyEvent(TrackerEvent* event);

protected:

	int timestamp_;
	std::string id_;
	EventType eventType_;
	uint16_t maskBits_;
};
