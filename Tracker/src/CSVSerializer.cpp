#include "CSVSerializer.h"
#include "Events/TrackerEvent.h"


CSVSerializer::CSVSerializer()
{
	interfix = "\n";
}

std::string CSVSerializer::Serialize(TrackerEvent* event) {
	return event->toCSV();
}

std::string CSVSerializer::getPrefix()
{
	return prefix;
}

std::string CSVSerializer::getInterfix()
{
	return interfix;
}

std::string CSVSerializer::getSufix()
{
	return sufix;
}
