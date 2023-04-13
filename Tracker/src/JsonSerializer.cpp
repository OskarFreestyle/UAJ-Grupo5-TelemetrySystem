#include "JsonSerializer.h"
#include "TrackerEvent.h"

JsonSerializer::JsonSerializer()
{
	prefix = "{\n\t\"events\": [\n";
	interfix = ',';
	sufix = "\t]\n}";
}

std::string JsonSerializer::Serialize(TrackerEvent* event) {
	return event->toJson();
}
