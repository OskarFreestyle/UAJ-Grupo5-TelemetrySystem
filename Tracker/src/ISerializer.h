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

	virtual	std::string getPrefix(EventType eventType) = 0;
	virtual	std::string getInterfix(EventType eventType) = 0;
	virtual	std::string getSufix(EventType eventType) = 0;

protected:

	std::string prefix = "";
	std::string interfix = "";
	std::string sufix = "";

	bool ignoreFirstInterfix = false; // TODO quitar?

	// Queremos ignorar el primer interifijo por cada tipo de evento, ya que arriba solo estará el prefijo
	std::unordered_map<std::string, bool> firstEventPerType;
};
