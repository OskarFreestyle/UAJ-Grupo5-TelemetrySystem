#include "SessionStartEvent.h"
#include "../Tracker.h"

// ------------------- SessionStartEvent -----------------------

SessionStartEvent::SessionStartEvent(double timestamp, const std::string& id) : TrackerEvent(timestamp, id, EventType::SESSION_STARTED) {}

