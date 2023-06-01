#pragma once

#include "TrackerEvent.h"

// Evento de inicio de sesion
class SessionStartEvent : public TrackerEvent {

public:
	SessionStartEvent(const std::string& timestamp, const std::string& id);

};