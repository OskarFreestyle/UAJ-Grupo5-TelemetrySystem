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

ReturnBaseEvent::ReturnBaseEvent(float timeDone_, std::string id_) : TrackerEvents(timeDone_, id_, RETURN_BASE_SLEEP)
{
	std::cout << "Ha vuelto a la base" << std::endl;
}

void ReturnBaseEvent::setParameters(int sleepValue_, int day_)
{
	sleepValue = sleepValue_;
	day = day_;

	std::cout << "El dia "<< day<< " con sueño " << sleepValue << std::endl;
}

const std::string ReturnBaseEvent::toJson()
{
	return "";
}

TrackerEvents* ReturnBaseEvent::clone()
{
	ReturnBaseEvent* aux = new ReturnBaseEvent(timeDone, id);
	aux->setParameters(sleepValue, day);

	return aux;
}

//CLASE BaseSleepEvent

BaseSleepEvent::BaseSleepEvent(float timeDone_, std::string id_) : TrackerEvents(timeDone_, id_, BASE_SLEEP_OPTION)
{
	std::cout << "Ha ido a dormir" << std::endl;
}

void BaseSleepEvent::setParameters(int sleepOption_, int day_)
{
	sleepOption = sleepOption_;
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
	aux->setParameters(sleepOption, day);

	return aux;
}

//CLASE ReturnBaseFoodEvent

ReturnBaseFoodEvent::ReturnBaseFoodEvent(float timeDone_, std::string id_) : TrackerEvents(timeDone_, id_, BASE_SLEEP_OPTION)
{
	std::cout << "Ha ido a base" << std::endl;
}

void ReturnBaseFoodEvent::setParameters(int hungerValue_, int day_)
{
	hungerValue = hungerValue_;
	day = day_;

	std::cout << "El dia " << day << " tiene de hambre " << hungerValue << std::endl;
}

const std::string ReturnBaseFoodEvent::toJson()
{
	return "";
}

TrackerEvents* ReturnBaseFoodEvent::clone()
{
	ReturnBaseFoodEvent* aux = new ReturnBaseFoodEvent(timeDone, id);
	aux->setParameters(hungerValue, day);

	return aux;
}

//CLASE CraftableFoodEvent

CraftableFoodEvent::CraftableFoodEvent(float timeDone_, std::string id_) : TrackerEvents(timeDone_, id_, BASE_SLEEP_OPTION)
{
	std::cout << "Ha ido a base" << std::endl;
}

void CraftableFoodEvent::setParameters(int numberFood, int day_)
{
	nFood = numberFood;
	day = day_;

	std::cout << "El dia " << day << " ha  podido craftear comida " << numberFood << "veces." << std::endl;
}

const std::string CraftableFoodEvent::toJson()
{
	return "";
}

TrackerEvents* CraftableFoodEvent::clone()
{
	CraftableFoodEvent* aux = new CraftableFoodEvent(timeDone, id);
	aux->setParameters(nFood, day);

	return aux;
}