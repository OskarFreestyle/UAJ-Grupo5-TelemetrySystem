#pragma once

#include "TrackerEvent.h"

// Evento sue�o al llegar al refugio
class LeaveBaseEvent : public TrackerEvent {
private:

	int fatigue;	    // Sue�o al llegar al refugio
	int sleepOption;	// Opcion de sue�o elegida
	int day;			// Dia del ciclo

public:

	LeaveBaseEvent(int timestamp, const std::string& id);

	LeaveBaseEvent* setFatigue(int fatigue);
	LeaveBaseEvent* setSleepOption(int sleepOption);
	LeaveBaseEvent* setDay(int day);

	virtual const std::string toJson();
	virtual const void toCSV(std::unordered_map<CSVFields, std::string>& eventCSV);

};