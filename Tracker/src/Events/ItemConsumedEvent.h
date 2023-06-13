#pragma once

#include "TrackerEvent.h"

// Evento uso de item
class ItemConsumedEvent : public TrackerEvent {

private:
	int day;

public:
	ItemConsumedEvent(double timestamp, const std::string& id);

	ItemConsumedEvent* setDay(int day);

	virtual const std::string toJson();
	virtual const std::string toCSV();
};

