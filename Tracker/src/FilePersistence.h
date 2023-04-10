#pragma once

#include "IPersistence.h"

class TrackerEvent;
class FilePersistence : public IPersistence {

public: 

	FilePersistence();

	virtual ~FilePersistence();

	virtual void Flush();

	virtual void Send(TrackerEvent* tEvent);
};

