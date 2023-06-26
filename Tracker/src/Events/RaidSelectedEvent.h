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
	RaidSelectedEvent(int timestamp, const std::string& id);

	RaidSelectedEvent* setItems(const std::list<int>& l);
	RaidSelectedEvent* setLocation(int location);
	RaidSelectedEvent* setHunger(int hunger);
	RaidSelectedEvent* setDay(int day);

	virtual const std::string toJson();
	virtual const void toCSV(std::unordered_map<CSVFields, std::string>& eventCSV);
};