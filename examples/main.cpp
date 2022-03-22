#include "main.hpp"

#include <thread>

int main()
{
	std::thread basicPhongThread(&basicPhongMain);
	std::thread advancedLightingThread(&advancedLightingMain);

	basicPhongThread.join();
	advancedLightingThread.join();

	return 0;
}
