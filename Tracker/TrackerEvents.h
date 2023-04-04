#pragma once
#include <string>

//Tipos de Eventos que recoge el tracker
enum EventType { 
	START_SESSION,
	END_SESSION,
	RETURN_BASE, //INFO AL LLEGAR A BASE
	BASE_SLEEP_OPTION, //Opcion de sueño elegida
	CRAFTED_SHIP_ITEMS, //Partes la nave crafteadas cada dia
	BASE_ACTIONS_USED, //acciones usadas en el refugio
	SELECTING_RAID, //Opcion de raid elegidas
	USING_ITEM
};	

enum Places {
	Hospital,
	Nuclear_Station,
	Coms,
	Supermarket,
	Shop
};

enum Action
{
	Enter,
	Leave,
	Click //Ubicacion seleccionada para raidear
};

class TrackerEvents
{
protected:
	float timeDone;
	std::string id;
	EventType eventName;

public:
	TrackerEvents(double timeDone_, std::string id_, EventType eventName_);

	virtual const std::string toJson();

	const EventType getType();

	virtual TrackerEvents* clone() = 0;
};

//EVENTOS DE INICIO Y FIN DE SESION
class SessionStartEvent : public TrackerEvents {
public:
	SessionStartEvent(float timeDone_, std::string id_);
	virtual TrackerEvents* clone();
};

class SessionEndEvent : public TrackerEvents {
public:
	SessionEndEvent(float timeDone_, std::string id_);
	virtual TrackerEvents* clone();
};

//Clase intermedia Eventos diarios
class DailyEvents : public TrackerEvents {
protected:
	int day;
	DailyEvents(float timeDone_, std::string id_, EventType eventName_);
public:
	virtual const std::string toJson();
};

//EVENTO SUEÑO AL LLEGAR AL REFUGIO
class ReturnBaseEvent : public DailyEvents {
private:
	int sleepValue; //sUEÑO AL LLEGAR AL REFUGIO
	int hungerValue; //HAMBRE AL LLEGAR AL REFUGIO
	int nFood;//cOMIDA QUE SE OUE SE PUEDE CRAFTEAR CON LO QUE TIENES AL LLEGAR AL REFUGIO
	int nShipsPieces;//PIEZAS QUE SE PUEDEN CRAFTEAR CON LO QUE TIENE DE LA NAVE
public:
	ReturnBaseEvent(float timeDone_, std::string id_);

	void setParameters(int sleepValue_,int hungerValue_, int nFood_, int nShipsPieces_, int day_);

	virtual const std::string toJson();

	virtual TrackerEvents* clone();
};

//EVENTO ELECCION DE SUEÑO
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

	virtual TrackerEvents* clone();
};

//EVENTO CFRATEO NAVE
class CraftShipEvent : public DailyEvents {
private:
	int nCrafted;
public:
	CraftShipEvent(float timeDone_, std::string id_);

	void setParameters(int nCrafted_, int day_);

	virtual const std::string toJson();

	virtual TrackerEvents* clone();
};

//EVENTO CFRATEO NAVE
class BaseActionsEvent : public DailyEvents {
private:
	int nActions;
public:
	BaseActionsEvent(float timeDone_, std::string id_);

	void setParameters(int nActions_, int day_);

	virtual const std::string toJson();

	virtual TrackerEvents* clone();
};

//EVENTO SelectingRaid
class SelectingRaidEvent : public DailyEvents {
private:
	Places location;
	Action accion;
public:
	SelectingRaidEvent(float timeDone_, std::string id_);

	void setParameters(Places location_, Action accion, int day_);

	virtual const std::string toJson();

	virtual TrackerEvents* clone();
};

//EVENTO Using Item
class UsingItemEvent : public DailyEvents {
private:
	int nItems;
public:
	UsingItemEvent(float timeDone_, std::string id_);

	void setParameters(int nItems, int day_);

	virtual const std::string toJson();

	virtual TrackerEvents* clone();
};