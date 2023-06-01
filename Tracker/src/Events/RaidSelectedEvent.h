#pragma once

#include "TrackerEvent.h"

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