#include "CSVSerializer.h"
#include "Events/TrackerEvent.h"
#include "checkML.h"

CSVSerializer::CSVSerializer()
{
	interfix = "\n";
	
	separator = "\t";

	prefix = "";

	for (int i = 0; i < (int) CSVFields::COUNT; i++) {
		if (i < (int)CSVFields::COUNT - 1) {
			prefix += CSVPrefixes[i] + separator;
		}
		else {
			prefix += CSVPrefixes[i];
		}

		eventCSV[(CSVFields) i] = "";
	}

	prefix += interfix;

}

CSVSerializer::~CSVSerializer()
{
	clearEventCSV();
}

std::string CSVSerializer::Serialize(TrackerEvent* event) {
	clearEventCSV();
	event->toCSV(eventCSV);

	std::string csvString = "";

	for (int i = 0; i < (int)CSVFields::COUNT; i++) {
		if (i < (int)CSVFields::COUNT - 1) {
			csvString += eventCSV[(CSVFields)i] + separator;
		}
		else {
			csvString += eventCSV[(CSVFields)i];
		}
	}

	return csvString;
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

void CSVSerializer::clearEventCSV()
{
	for (int i = 0; i < (int)CSVFields::COUNT; i++) {
		eventCSV[(CSVFields)i] = "";
	}
	eventCSV.clear();
}
