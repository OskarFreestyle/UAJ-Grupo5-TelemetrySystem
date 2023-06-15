#pragma once

#include <string>
#include <list>
#include <unordered_map>
#include <queue>

class TrackerEvent;
enum class EventType;

class ISerializer {

public:

	/// <summary>
	/// Método abstracto a redefinir por los objetos serializadores
	/// </summary>
	virtual std::string Serialize(TrackerEvent* event) = 0;

	virtual std::string Format() = 0;

	virtual	std::string getPrefix() = 0;
	virtual	std::string getInterfix() = 0;
	virtual	std::string getSufix() = 0;

protected:

	std::string prefix = "";
	std::string interfix = "";
	std::string sufix = "";
};
