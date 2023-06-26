#include "SessionEndEvent.h"
#include "../Tracker.h"

// ------------------- SessionEndEvent -----------------------

SessionEndEvent::SessionEndEvent(int timestamp, const std::string& id) : TrackerEvent(timestamp, id, EventType::SESSION_ENDED) {}

