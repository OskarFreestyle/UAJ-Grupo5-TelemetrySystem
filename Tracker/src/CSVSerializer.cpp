#include "CSVSerializer.h"
#include "TrackerEvent.h"

std::string CSVSerializer::Serialize(TrackerEvent* event) {
	return event->toCSV();
}

std::string CSVSerializer::getPrefix(EventType eventType)
{
	return CSVPrefixes[(int)eventType];
}

std::string CSVSerializer::getInterfix(EventType eventType)
{
	return interfix;
}

std::string CSVSerializer::getSufix(EventType eventType)
{
	return sufix;
}
