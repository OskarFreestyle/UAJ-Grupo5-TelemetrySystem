#pragma once

#include "TrackerEvent.h"

// Evento uso de accion
class ActionUsedEvent : public TrackerEvent {
private:
	int nActions;
	int day;
public:

	ActionUsedEvent(int timestamp, const std::string& id);

	ActionUsedEvent* setActions(int actions);
	ActionUsedEvent* setDay(int day);

	virtual const std::string toJson();
	virtual const void toCSV(std::unordered_map<CSVFields, std::string>& eventCSV);

};
