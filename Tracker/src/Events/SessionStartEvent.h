#pragma once

#include "TrackerEvent.h"

// Evento de inicio de sesion
class SessionStartEvent : public TrackerEvent {

public:
	SessionStartEvent(int timestamp, const std::string& id);

};