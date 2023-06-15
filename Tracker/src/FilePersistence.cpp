#include "FilePersistence.h"
#include "Events/TrackerEvent.h"
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

	eventsLogPath = "events_log\\";

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

	sessionID = sessionId;

	// Abre los archivos en los que persistir
	openPersistenceFiles();
}

FilePersistence::~FilePersistence() {
	// Se cierran los archivos abiertos
	closePersistenceFiles();

	std::cout << "Persistencias cerradas\n";
}

void FilePersistence::Flush() {

	// Mientras queden eventos en la cola
	while (!events_.isEmpty()) {

		// Se coje el primer evento
		TrackerEvent* event = events_.frontElement();
		events_.pop();

		// Se serializa en cada archivo
		int aux = 0;
		for (const auto& serializerPair : serializers_) {
			ISerializer* s = serializerPair.second;

			(*files[aux]) << s->getInterfix(event->getType());

			// Se serializa
			std::string stringEvent = s->Serialize(event);
			(*files[aux]) << stringEvent;
			aux++;
		}

		// Se borra el evento ya serializado
		TrackerEvent::DestroyEvent(event);

	}
}

void FilePersistence::openPersistenceFiles()
{
	try {
		// Se abre el archivo a persistir (para todos los formatos)
		for (const auto& serializerPair : serializers_) {
			ISerializer* s = serializerPair.second;

			// Se abre el archivo para las persistencias de ese evento en concreto
			std::string path;
			path.append(eventsLogPath + "\\" + sessionID + "." + s->Format());
			std::ofstream* file = new ofstream();
			file->open(path, std::ios::out | std::ios::app);

			// Se anade el prefijo
			(*file) << s->getPrefix(EventType::SESSION_STARTED);

			// Se añade al mapa de files
			files.push_back(file);
		}
	}
	catch (exception& e) {
		std::cout << "Error opening persistence files\n";
		std::cout << "Error " << e.what() << "\n";
	}
}

void FilePersistence::closePersistenceFiles()
{
	// Cerramos los archivos
	try {
		int aux = 0;
		for (const auto& serializerPair : serializers_) {
			ISerializer* s = serializerPair.second;

			// Se anade el sufijo
			(*files[aux]) << s->getSufix(EventType::SESSION_ENDED);

			// Cierra el ofstream
			files[aux]->close();

			// Se elimina el puntero
			delete files[aux];

			aux++;
		}
	}
	catch (exception& e) {
		std::cout << "Error closing persistence files\n";
		std::cout << "Error " << e.what() << "\n";
	}
}
