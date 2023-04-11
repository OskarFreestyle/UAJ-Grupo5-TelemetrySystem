#include "FilePersistence.h"
#include "TrackerEvent.h"
#include "Tracker.h"

#include <iostream>
#include <fstream>
#include <direct.h>
#include <cassert>

FilePersistence::FilePersistence(const std::list<ISerializer*>& serializers, const std::string& sessionId) {

	eventsLogPath = "\events_log\\";
	int err = _mkdir(eventsLogPath.c_str());

	assert(err == 0, "La creación del directorio con nombre " + eventsLogPath.c_str() + " ha fallado!");

	eventsLogPath.append("\\" + sessionId + ".");

	this->serializers = std::list<ISerializer*>(serializers);
}

FilePersistence::~FilePersistence() {}

void FilePersistence::Flush() {

	while (!events.empty()) {

		TrackerEvent* event = events.front();
		events.pop();

		std::ofstream file;

		for (auto s : serializers) {
			std::string path;
			path.append(eventsLogPath + s->Format());
			file.open(path, std::ios::out | std::ios::app);

			std::string stringEvent = s->Serialize(event);
			file << stringEvent << '\n';

			file.close();
		}

		TrackerEvent::DestroyEvent(event);
	}

}


