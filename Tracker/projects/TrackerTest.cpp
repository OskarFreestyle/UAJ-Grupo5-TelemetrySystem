

#include <iostream>
#include <memory>
#include "../src/Tracker.h"

int main() {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	std::cout << "Tracker test" << std::endl;


	Tracker::Instance();


	Tracker::Instance()->trackEvent(Tracker::createActionUsedEvent()->setDay(2));
	Tracker::Instance()->trackEvent(Tracker::createRaidSelectedEvent());


	Tracker::End();
	return 0;
}