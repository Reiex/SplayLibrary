#include "main.hpp"

// TODO: add "_" in front of private methods
// TODO: Make constexpr what should be constexpr

int main()
{
	std::thread basicPhongThread(&basicPhongMain);
	std::thread advancedLightingThread(&advancedLightingMain);

	basicPhongThread.join();
	advancedLightingThread.join();

	return 0;
}
