#include "SessionStartEvent.h"
#include "../Tracker.h"

// ------------------- SessionStartEvent -----------------------

SessionStartEvent::SessionStartEvent(int timestamp, const std::string& id) : TrackerEvent(timestamp, id, EventType::SESSION_STARTED) {}

