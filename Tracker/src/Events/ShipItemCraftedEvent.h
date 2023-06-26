#pragma once

#include "TrackerEvent.h"

// Evento crafteo de item de nave
class ShipItemCraftedEvent : public TrackerEvent {
private:
	int nCrafted;
	int nCraftables;
	int day;
public:
	ShipItemCraftedEvent(int timestamp, const std::string& id);

	ShipItemCraftedEvent* setCrafted(int crafted);
	ShipItemCraftedEvent* setCraftables(int craftables);
	ShipItemCraftedEvent* setDay(int day);

	virtual const std::string toJson();
	virtual const void toCSV(std::unordered_map<CSVFields, std::string>& eventCSV);
};