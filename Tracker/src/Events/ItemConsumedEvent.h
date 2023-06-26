#pragma once

#include "TrackerEvent.h"

// Evento uso de item
class ItemConsumedEvent : public TrackerEvent {

private:
	int day;

public:
	ItemConsumedEvent(int timestamp, const std::string& id);

	ItemConsumedEvent* setDay(int day);

	virtual const std::string toJson();
	virtual const void toCSV(std::unordered_map<CSVFields, std::string>& eventCSV);

};

