#pragma once

#include "TrackerEvent.h"

// Evento crafteo de un item de comida
class FoodItemCraftedEvent : public TrackerEvent {
private:

	int hunger;		// Sueño al llegar al refugio
	bool craft;		// Indica si puede craftear el jugador items de comida
	int day;		// Dia del ciclo

public:

	FoodItemCraftedEvent(double timestamp, const std::string& id);

	FoodItemCraftedEvent* setHunger(int hunger);
	FoodItemCraftedEvent* setCraft(bool craft);
	FoodItemCraftedEvent* setDay(int day);

	virtual const std::string toJson();
	virtual const void toCSV(std::unordered_map<CSVFields, std::string>& eventCSV);

};
