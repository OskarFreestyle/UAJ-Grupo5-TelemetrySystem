#include "SessionEndEvent.h"
#include "../Tracker.h"

// ------------------- SessionEndEvent -----------------------

SessionEndEvent::SessionEndEvent(const std::string& timestamp, const std::string& id) : TrackerEvent(timestamp, id, EventType::SESSION_ENDED) {}

