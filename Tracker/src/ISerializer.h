#pragma once

#include <string>

class TrackerEvent;

class ISerializer {

public:

	/// <summary>
	/// Returns the event serialized in an especific format
	/// </summary>
	virtual std::string Serialize(TrackerEvent* event) = 0;

	/// <summary>
	/// Returns format name to be added to the file name
	/// </summary>
	virtual std::string Format() = 0;

};
