#pragma once

#include "TrackerEvent.h"

// Evento de fin de sesion
class SessionEndEvent : public TrackerEvent {

public:
	SessionEndEvent(const std::string& timestamp, const std::string& id);
};