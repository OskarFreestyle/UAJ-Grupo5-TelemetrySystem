#pragma once

#include "TrackerEvent.h"

// Evento crafteo de item de nave
class ShipItemCraftedEvent : public TrackerEvent {
private:
	int nCrafted;
	int nCraftables;
	int day;
public:
	ShipItemCraftedEvent(double timestamp, const std::string& id);

	ShipItemCraftedEvent* setCrafted(int crafted);
	ShipItemCraftedEvent* setCraftables(int craftables);
	ShipItemCraftedEvent* setDay(int day);

	virtual const std::string toJson();
	virtual const std::string toCSV();
};