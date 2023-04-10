#pragma once

#include "IPersistence.h"

class FilePersistence : public IPersistence {

public: 

	FilePersistence(const std::list<ISerializer*>& serializers, const std::string& sessionId);

	~FilePersistence();

	virtual void Flush();

private:
	
	std::string eventsLogPath;

};

