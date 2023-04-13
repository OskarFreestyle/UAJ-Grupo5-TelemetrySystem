#pragma once

#include <string>

class TrackerEvent;

class ISerializer {

public:

	/// <summary>
	/// Método abstracto a redefinir por los objetos serializadores
	/// </summary>
	virtual std::string Serialize(TrackerEvent* event) = 0;

	virtual std::string Format() = 0;

	std::string prefix = "";
	std::string interfix = "";
	std::string sufix = "";
};
