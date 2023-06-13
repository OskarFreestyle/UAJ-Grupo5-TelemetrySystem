#pragma once

#include "TrackerEvent.h"

// Evento de fin de sesion
class SessionEndEvent : public TrackerEvent {

public:
	SessionEndEvent(double timestamp, const std::string& id);
};