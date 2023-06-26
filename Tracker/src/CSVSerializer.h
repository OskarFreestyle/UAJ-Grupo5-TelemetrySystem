#pragma once

#include "ISerializer.h"
#include <unordered_map>

class TrackerEvent;

const std::string CSVPrefixes[] = {
	"Id",
	"Time",
	"Event type",
	"Fatigue",
	"Sleep option",
	"Hunger",
	"Can craft food items",
	"Ship items crafted",
	"Craftable ship items",
	"Actions used",
	"X",
	"Y",
	"Entity",
	"Day",
	"Location",
	"Items"
};

enum class CSVFields {
	Id,
	Time,
	EventType,
	Fatigue,
	SleepOption,
	Hunger,
	CanCraftFoodItems,
	ShipItemsCrafted,
	CraftableShipItems,
	ActionsUsed,
	X,
	Y,
	Entity,
	Day,
	Location,
	Items,
	COUNT
};


class CSVSerializer : public ISerializer {

public:

	CSVSerializer();
	~CSVSerializer();

	/// <summary>
	/// Devuelve el evento serializado en formato CSV
	/// </summary>
	std::string Serialize(TrackerEvent* event);

	/// <summary>
	/// Devuelve el formato para identificar los ficheros
	/// </summary>
	inline std::string Format() { return "csv"; };

	virtual	std::string getPrefix();
	virtual	std::string getInterfix();
	virtual	std::string getSufix();

	void clearEventCSV();

	std::string separator;

	std::unordered_map<CSVFields, std::string> eventCSV;
};

