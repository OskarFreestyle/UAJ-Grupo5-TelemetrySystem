#include "CSVSerializer.h"
#include "Events/TrackerEvent.h"


CSVSerializer::CSVSerializer()
{
	interfix = "\n";

	for (auto type : eventTypes)
	{
		firstEventPerType[type] = true;
	}
}

std::string CSVSerializer::Serialize(TrackerEvent* event) {
	return event->toCSV();
}

std::string CSVSerializer::getPrefix(EventType eventType)
{
	return CSVPrefixes[(int)eventType];
}

std::string CSVSerializer::getInterfix(EventType eventType)
{
	if (firstEventPerType[eventTypes[(int)eventType]]) {
		firstEventPerType[eventTypes[(int)eventType]] = false;
		return "";
	}
	else {
		return interfix;
	}
}

std::string CSVSerializer::getSufix(EventType eventType)
{
	return sufix;
}
