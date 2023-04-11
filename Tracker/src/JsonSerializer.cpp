#include "JsonSerializer.h"
#include "TrackerEvent.h"

JsonSerializer::JsonSerializer()
{
	prefix = "[\n";
	sufix = "\n]";
}

std::string JsonSerializer::Serialize(TrackerEvent* event) {
	return event->toJson();
}
