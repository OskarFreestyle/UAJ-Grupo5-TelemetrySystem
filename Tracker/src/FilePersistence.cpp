#include "FilePersistence.h"
#include "TrackerEvent.h"
#include "Tracker.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <direct.h>
#include <cassert>
#include <io.h>
#include "checkML.h"

FilePersistence::FilePersistence(int maxElementsInQueue, const std::string& sessionId, std::list<std::string> serializersToUse) : IPersistence(maxElementsInQueue, serializersToUse) {

	eventsLogPath = "\events_log\\";

	// Intenta acceder a la carpeta events_log
	int result = _access(eventsLogPath.c_str(), 0);

	// Si no consigue acceder, la crea
	if (result != 0) {
		int err = _mkdir(eventsLogPath.c_str());

		if (err != 0)
			std::cout << "La creacion del directorio events_log ha fallado!";
	}

	// Anade a la ruta el id de la sesion
	eventsLogPath.append(sessionId + "\\");

	// Crea una carpeta con la sesion actual
	int err = _mkdir(eventsLogPath.c_str());
	if (err != 0) std::cout << "La creacion del directorio de la sesion actual ha fallado!";

	//eventsLogPath.append("\\" + sessionId + ".");

	firstFlush = true;
}

FilePersistence::~FilePersistence() {}

void FilePersistence::createFilePerEventType(ISerializer* s)
{
	std::ofstream file;
	int i = 0;
	for (auto eventType : eventTypes)
	{
		std::string path;
		path.append(eventsLogPath + "\\" + /*std::to_string(i) + "_" +*/ eventTypes[i] + "." + s->Format());

		std::cout << "Create: " << eventTypes[i] << std::endl;

		// Crea el archivo
		file.open(path, std::ios::out | std::ios::app);

		// Se escribe la parte inicial del archivo
		file << s->getPrefix((EventType) i);

		file.close();
		i++;
	}
}

void FilePersistence::addSufixToEveryFile(ISerializer* s)
{
	std::ofstream file;

	int i = 0;
	for (auto eventType : eventTypes)
	{
		// Solo anade sufijo a los archivos que existen
		if (!firstEventPerType[eventTypes[i]]) {
			std::string path;
			path.append(eventsLogPath + "\\" + eventTypes[i] + "." + s->Format());

			std::cout << "Sufixed: " << eventTypes[i] << std::endl;

			// Crea el archivo
			file.open(path, std::ios::out | std::ios::app);

			// Se escribe la parte inicial del archivo
			file << s->getSufix((EventType)i);

			file.close();
		}
		i++;
	}
}

void FilePersistence::Flush(bool finalFlush) {

	// Mientras queden eventos en la cola
	while (!events_.isEmpty()) {

		// Se coje el primer evento
		TrackerEvent* event = events_.frontElement();
		events_.pop();

		for (const auto& serializerPair : serializers_) {
			ISerializer* s = serializerPair.second;
			int eventType = (int)event->getType();

			std::ofstream file;
			std::string path;

			// Se abre el archivo para las persistencias de ese evento en concreto
			path.append(eventsLogPath + "\\" + eventTypes[eventType] + "." + s->Format());
			file.open(path, std::ios::out | std::ios::app);

			file << s->getInterfix(event->getType());

			// Se serializa
			std::string stringEvent = s->Serialize(event);
			file << stringEvent;
		}

		TrackerEvent::DestroyEvent(event);
	}

	if (finalFlush) {
		for (const auto& serializerPair : serializers_) {
			ISerializer* s = serializerPair.second;
			addSufixToEveryFile(s);
		}
	}
}
