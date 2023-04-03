#pragma once
#include <string>

//Tipos de Eventos que recoge el tracker
enum EventType { 
	START_SESSION,
	END_SESSION,
	RETURN_BASE_SLEEP, //Noche en el juego y sueño antes de dormir
	BASE_SLEEP_OPTION, //Opcion de sueño elegida
	RETURN_BASE_FOOD, //Porcentaje de comida que tiene
	RETURN_BASE_CRAFTABLE_FOOD //Comida que podria haber crafteado una noche
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

//EVENTO SUEÑO AL LLEGAR AL REFUGIO
class ReturnBaseEvent : public TrackerEvents {
private:
	int sleepValue;
	int day;
public:
	ReturnBaseEvent(float timeDone_, std::string id_);

	void setParameters(int sleepValue_, int day_);

	virtual const std::string toJson();

	virtual TrackerEvents* clone();
};

//EVENTO ELECCION DE SUEÑO
class BaseSleepEvent : public TrackerEvents {
private:
	int sleepOption;
	int day;
public:
	BaseSleepEvent(float timeDone_, std::string id_);

	void setParameters(int sleepOption_, int day_);

	virtual const std::string toJson();

	virtual TrackerEvents* clone();
};

// VALOR DEL HAMBRE
class ReturnBaseFoodEvent : public TrackerEvents {
private:
	int hungerValue;
	int day;
public:
	ReturnBaseFoodEvent(float timeDone_, std::string id_);

	void setParameters(int hungerValue_, int day_);

	virtual const std::string toJson();

	virtual TrackerEvents* clone();
};

// NCOMIDA CRAFTEABLE
class CraftableFoodEvent : public TrackerEvents {
private:
	int nFood;
	int day;
public:
	CraftableFoodEvent(float timeDone_, std::string id_);

	void setParameters(int numberFood, int day_);

	virtual const std::string toJson();

	virtual TrackerEvents* clone();
};