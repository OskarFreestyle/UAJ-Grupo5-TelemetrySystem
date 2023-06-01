#pragma once

#include "TrackerEvent.h"
#include <functional>

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