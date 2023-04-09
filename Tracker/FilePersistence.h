#pragma once

class TrackerEvent;
class FilePersistence //: hereda de IPersistence --> Incluir
{
public: 

	FilePersistence();

	virtual ~FilePersistence();

	virtual void Flush();

	virtual void Send(TrackerEvent* tEvent);
};

