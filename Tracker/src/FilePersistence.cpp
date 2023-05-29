#include "FilePersistence.h"
#include "TrackerEvent.h"
#include "Tracker.h"

#include <iostream>
#include <fstream>
#include <direct.h>
#include <cassert>
#include <io.h>
#include "checkML.h"

FilePersistence::FilePersistence(int maxElementsInQueue, const std::string& sessionId, std::list<std::string> serializersToUse) : IPersistence(maxElementsInQueue, serializersToUse) {

	eventsLogPath = "\events_log\\";

	int result = _access(eventsLogPath.c_str(), 0);

	if (result != 0) {
		int err = _mkdir(eventsLogPath.c_str());

		if (err != 0)
			std::cout << "La creacion del directorio ha fallado!";
	}

	eventsLogPath.append("\\" + sessionId + ".");

	firstFlush = true;

}

FilePersistence::~FilePersistence() {}

void FilePersistence::Flush(bool finalFlush) {

	std::ofstream file;

	//pillar lista
	for (const auto& serializerPair : serializers_) {
		ISerializer* s = serializerPair.second;

		std::string path;
		path.append(eventsLogPath + s->Format());
		file.open(path, std::ios::out | std::ios::app);

		// Si es la primera vez que se flushea se escribe la parte inicial del archivo
		if (firstFlush) {
			file << s->prefix;
			firstFlush = false;
		}

		while (!events.empty()) {

			TrackerEvent* event = events.front();
			events.pop();

			std::string stringEvent = s->Serialize(event);

			file << stringEvent;

			if (!(finalFlush && events.size() == 0))
				file << s->interfix;

			file << '\n';

			TrackerEvent::DestroyEvent(event);
		}

		if (finalFlush)
			file << s->sufix;

		file.close();
	}
}


