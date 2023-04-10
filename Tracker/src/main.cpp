#include <iostream>
#include "Tracker.h"

int main() {

	Tracker::Instance();

	std::cin.get();

	Tracker::End();

	return 0;

}