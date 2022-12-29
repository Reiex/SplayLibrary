#include "main.hpp"

// TODO: add "_" in front of private methods
// TODO: Finish buffers (mapping, clearing)
// TODO: Create all "texture" classes (and put them with TextureBase and Texture2D in a sub-file)
// TODO: Rewrite 'Drawable'
// TODO: Allow for better shader debugging ? Maybe... maybe not...

int main()
{
	std::thread basicPhongThread(&basicPhongMain);
	std::thread advancedLightingThread(&advancedLightingMain);

	basicPhongThread.join();
	advancedLightingThread.join();

	return 0;
}
