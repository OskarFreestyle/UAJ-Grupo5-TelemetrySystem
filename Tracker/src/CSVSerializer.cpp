#include "CSVSerializer.h"
#include "TrackerEvent.h"

std::string CSVSerializer::Serialize(TrackerEvent* event) {
	return event->toCSV();
}
