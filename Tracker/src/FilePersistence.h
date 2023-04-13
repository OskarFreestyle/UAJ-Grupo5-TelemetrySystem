#pragma once

#include "IPersistence.h"

class FilePersistence : public IPersistence {

public: 

	FilePersistence(int MaxElementsInQueue, const std::string& sessionId);

	~FilePersistence();

	virtual void Flush(bool finalFlush);

private:
	
	std::string eventsLogPath;
	bool firstFlush;

};

