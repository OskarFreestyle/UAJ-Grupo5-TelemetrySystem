#pragma once

#include "TrackerEvent.h"

// Evento seleccion de raid
class RaidVisualizedEvent : public TrackerEvent {
private:

	int location;

public:
	RaidVisualizedEvent(int timestamp, const std::string& id);

	RaidVisualizedEvent* setLocation(int location);

	virtual const std::string toJson();
	virtual const void toCSV(std::unordered_map<CSVFields, std::string>& eventCSV);
};