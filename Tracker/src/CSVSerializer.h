#pragma once

#include "ISerializer.h"

class CSVSerializer : public ISerializer {

public:

	CSVSerializer() {};
	~CSVSerializer() {};

	/// <summary>
	/// Devuelve el evento serializado en formato CSV
	/// </summary>
	std::string Serialize(TrackerEvent* event);

	/// <summary>
	/// Devuelve el formato para identificar los ficheros
	/// </summary>
	inline std::string Format() { return "csv"; };

};

