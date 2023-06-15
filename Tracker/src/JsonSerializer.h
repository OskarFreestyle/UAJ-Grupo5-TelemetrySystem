#pragma once

#include "ISerializer.h"

#include <iostream>

class TrackerEvent;

class JsonSerializer : public ISerializer {

public:

	JsonSerializer();
	~JsonSerializer() {};

	/// <summary>
	/// Devuelve el evento serializado en formato JSON
	/// </summary>
	std::string Serialize(TrackerEvent* event);

	/// <summary>
	/// Devuelve el formato para identificar los ficheros
	/// </summary>
	inline std::string Format() { return "json"; };

	virtual	std::string getPrefix();
	virtual	std::string getInterfix();
	virtual	std::string getSufix();

};

