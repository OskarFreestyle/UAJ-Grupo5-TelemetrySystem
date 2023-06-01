#include "JsonSerializer.h"
#include "Events/TrackerEvent.h"

JsonSerializer::JsonSerializer() {
	prefix = "{\n\t\"events\": [\n";
	interfix = ",\n";
	sufix = "\n\t]\n}";

	for (auto type : eventTypes)
	{
		firstEventPerType[type] = true;
	}
}

std::string JsonSerializer::Serialize(TrackerEvent* event) {

	std::string stringEvent = event->toJson();

	// Añadimos identacion a cada linea de stringEvent
	std::string indentString = "\t\t";
	size_t pos = 0;
	while (pos != std::string::npos) {
		pos = stringEvent.find('\n', pos + 1);  // Find the next newline character
		if (pos != std::string::npos) {
			stringEvent.insert(pos + 1, indentString);  // Insert the indentation after the newline
			pos += indentString.length() + 1;  // Move the position to skip the inserted indentation
		}
	}

	stringEvent.insert(0, indentString);

	return stringEvent;
}

std::string JsonSerializer::getPrefix(EventType eventType)
{
	return prefix;
}

std::string JsonSerializer::getInterfix(EventType eventType)
{
	if (firstEventPerType[eventTypes[(int) eventType]]) {
		firstEventPerType[eventTypes[(int)eventType]] = false;
		return "";
	}
	else {
		return interfix;
	}
}

std::string JsonSerializer::getSufix(EventType eventType)
{
	return sufix;
}