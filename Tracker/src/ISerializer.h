#pragma once

#include <string>

class TrackerEvent;
enum class EventType;

class ISerializer {

public:

	/// <summary>
	/// Método abstracto a redefinir por los objetos serializadores
	/// </summary>
	virtual std::string Serialize(TrackerEvent* event) = 0;

	virtual std::string Format() = 0;

	virtual	std::string getPrefix(EventType eventType) = 0;
	virtual	std::string getInterfix(EventType eventType) = 0;
	virtual	std::string getSufix(EventType eventType) = 0;

protected:

	std::string prefix = "";
	std::string interfix = "";
	std::string sufix = "";
};
