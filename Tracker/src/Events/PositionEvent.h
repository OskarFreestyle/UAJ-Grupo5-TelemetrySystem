#pragma once

#include "TrackerEvent.h"

// Evento posicion actual de una entidad de juego
class PositionEvent : public TrackerEvent {

private:
	float x;
	float y;

	std::string entity;

public:
	PositionEvent(double timestamp, const std::string& id);

	PositionEvent* setPosition(float x, float y);
	PositionEvent* setEntity(std::string name);

	virtual const std::string toJson();
	virtual const std::string toCSV();
};