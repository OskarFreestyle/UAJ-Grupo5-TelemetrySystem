#pragma once

#include "IPersistence.h"

class FilePersistence : public IPersistence {

public: 

	FilePersistence(int MaxElementsInQueue, const std::string& sessionId, std::list<std::string> serializersToUse);

	~FilePersistence();

	virtual void Flush();

private:

	/// <summary>
	/// Abre los archivos que se hayan añadido al vector de _serializers
	/// </summary>
	void openPersistenceFiles();

	/// <summary>
	/// Cierra los archivos que se hayan añadido al vector de _serializers
	/// </summary>
	void closePersistenceFiles();

	// Punteros del ofstream de cada archivo abierto
	std::vector<std::ofstream*> files;
	
	// Ruta de los archivos abiertos
	std::string eventsLogPath;

	// ID de la sesion
	std::string sessionID;

	// El primer evento que se serializa no tiene la "," que lo separa del anterior
	bool firstFlush = true;
};

