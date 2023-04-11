#include "FilePersistence.h"
#include "TrackerEvent.h"
#include "Tracker.h"

#include <iostream>
#include <fstream>
#include <direct.h>
#include <cassert>
#include <io.h>

FilePersistence::FilePersistence(int maxElementsInQueue, const std::string& sessionId) : IPersistence(maxElementsInQueue) {

	eventsLogPath = "\events_log\\";

	int result = _access(eventsLogPath.c_str(), 0);

	if (result != 0) {
		int err = _mkdir(eventsLogPath.c_str());

		if (err != 0)
			std::cout << "La creacion del directorio ha fallado!";
	}

	eventsLogPath.append("\\" + sessionId + ".");
}

FilePersistence::~FilePersistence() {}

#include <iostream>

void FilePersistence::Flush() {

	std::ofstream file;

	auto s = Tracker::GetSerializer();
	std::string path;
	path.append(eventsLogPath + s->Format());
	file.open(path, std::ios::out | std::ios::app);

	file << s->prefix;

	while (!events.empty()) {

		TrackerEvent* event = events.front();
		events.pop();

		std::string stringEvent = s->Serialize(event);

		file << stringEvent << '\n';

		TrackerEvent::DestroyEvent(event);
	}

	file << s->sufix;

	file.close();

}


