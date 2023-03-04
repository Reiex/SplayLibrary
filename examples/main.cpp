#include "main.hpp"

// TODO: Search all "uint32_t" for sizes/offset... if it's GLintptr or GLsizeiptr, replace with uintptr_t
// TODO: make accessors inline ?
// TODO: Create all "texture" classes (and put them with TextureBase and Texture2D in a sub-file)

// TODO: Finish scp::Quat

int main()
{
	// std::thread basicPhongThread(&basicPhongMain);
	// std::thread advancedLightingThread(&advancedLightingMain);
	// 
	// basicPhongThread.join();
	// advancedLightingThread.join();
	// 
	// return 0;

	return basicPhongMain();
}
