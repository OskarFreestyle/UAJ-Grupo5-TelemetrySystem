#pragma once

#include "TrackerEvent.h"

// Evento de inicio de sesion
class SessionStartEvent : public TrackerEvent {

public:
	SessionStartEvent(double timestamp, const std::string& id);

};