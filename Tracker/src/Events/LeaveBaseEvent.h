#pragma once

#include "TrackerEvent.h"

// Evento sue�o al llegar al refugio
class LeaveBaseEvent : public TrackerEvent {
private:

	int fatigue;	    // Sue�o al llegar al refugio
	int sleepOption;	// Opcion de sue�o elegida
	int day;			// Dia del ciclo

public:

	LeaveBaseEvent(const std::string& timestamp, const std::string& id);

	LeaveBaseEvent* setFatigue(int fatigue);
	LeaveBaseEvent* setSleepOption(int sleepOption);
	LeaveBaseEvent* setDay(int day);

	virtual const std::string toJson();
	virtual const std::string toCSV();
};