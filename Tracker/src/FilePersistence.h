#pragma once

#include "IPersistence.h"

class FilePersistence : public IPersistence {

public: 

	FilePersistence(int MaxElementsInQueue, const std::string& sessionId, std::list<std::string> serializersToUse);

	~FilePersistence();

	virtual void Flush(bool finalFlush);

private:
	void createFilePerEventType(ISerializer* s);
	void addSufixToEveryFile(ISerializer* s);
	
	std::string eventsLogPath;
	bool firstFlush;

	std::unordered_map<std::string, bool> firstEventPerType;
};

