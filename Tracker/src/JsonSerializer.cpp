#include "JsonSerializer.h"
#include "TrackerEvent.h"

JsonSerializer::JsonSerializer() {
	prefix = "{\n\t\"events\": [\n";
	interfix = ',';
	sufix = "\t]\n}";
}

std::string JsonSerializer::Serialize(TrackerEvent* event) {
	return event->toJson();
}

std::string JsonSerializer::getPrefix(EventType eventType)
{
	return prefix;
}

std::string JsonSerializer::getInterfix(EventType eventType)
{
	return interfix;
}

std::string JsonSerializer::getSufix(EventType eventType)
{
	return sufix;
}