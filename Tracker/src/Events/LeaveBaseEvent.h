#pragma once

#include "TrackerEvent.h"

// Evento sueño al llegar al refugio
class LeaveBaseEvent : public TrackerEvent {
private:

	int fatigue;	    // Sueño al llegar al refugio
	int sleepOption;	// Opcion de sueño elegida
	int day;			// Dia del ciclo

public:

	LeaveBaseEvent(int timestamp, const std::string& id);

	LeaveBaseEvent* setFatigue(int fatigue);
	LeaveBaseEvent* setSleepOption(int sleepOption);
	LeaveBaseEvent* setDay(int day);

	virtual const std::string toJson();
	virtual const void toCSV(std::unordered_map<CSVFields, std::string>& eventCSV);

};