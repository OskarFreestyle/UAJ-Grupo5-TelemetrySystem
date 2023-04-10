#include "FilePersistence.h"
#include "TrackerEvent.h"
#include "Tracker.h"

#include <iostream>
#include <fstream>
#include <Windows.h>
#include <stdlib.h>
#include <direct.h>
#include <cstdlib>

FilePersistence::FilePersistence(const std::list<ISerializer*>& serializers, const std::string& sessionId) {

	eventsLogPath = "\events_log\\";
	int err = _mkdir(eventsLogPath.c_str());

	eventsLogPath.append("\\" + sessionId + ".");

	this->serializers = std::list<ISerializer*>(serializers);
}

FilePersistence::~FilePersistence() {}

void FilePersistence::Flush() {

	while (!events.empty()) {

		TrackerEvent* event = events.front();
		events.pop();

		std::ofstream file;

		for (std::list<ISerializer*>::iterator it = serializers.begin(); it != serializers.end(); ++it) {

			std::string path;
			path.append(eventsLogPath + (*it)->Format());
			file.open(path, std::ios::out | std::ios::app);

			std::string stringEvent = (*it)->Serialize(event);
			file << stringEvent << '\n';

			file.close();
		}

		TrackerEvent::DestroyEvent(event);
	}

}


