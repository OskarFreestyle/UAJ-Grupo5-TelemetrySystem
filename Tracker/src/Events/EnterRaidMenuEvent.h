#pragma once

#include "TrackerEvent.h"

// Evento entrada al menu de raid
class EnterRaidMenuEvent : public TrackerEvent {
private:

	int day;

public:

	EnterRaidMenuEvent(const std::string& timestamp, const std::string& id);

	EnterRaidMenuEvent* setDay(int day);

	virtual const std::string toJson();
	virtual const std::string toCSV();
};

