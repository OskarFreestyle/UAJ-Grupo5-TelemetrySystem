#include "JsonSerializer.h"
#include "TrackerEvent.h"

std::string JsonSerializer::Serialize(TrackerEvent* event) {
	return event->toJson();
}
