#include "SessionStartEvent.h"
#include "../Tracker.h"

// ------------------- SessionStartEvent -----------------------

SessionStartEvent::SessionStartEvent(const std::string& timestamp, const std::string& id) : TrackerEvent(timestamp, id, EventType::SESSION_STARTED) {}

