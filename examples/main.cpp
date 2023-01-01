#include "main.hpp"

// TODO: make gl conversion constexpr and move them to Private.hpp/cpp
// TODO: make accessors inline ?
// TODO: Finish buffers (mapping, clearing)
// TODO: Create all "texture" classes (and put them with TextureBase and Texture2D in a sub-file)
// TODO: Rewrite 'Drawable'
// TODO: Allow for better shader debugging ? Maybe... maybe not...

// TODO: Finish scp::Quat
// TODO: using f32quat, f64quat
// TODO: Move/Complete Transformable3D ?

int main()
{
	std::thread basicPhongThread(&basicPhongMain);
	std::thread advancedLightingThread(&advancedLightingMain);

	basicPhongThread.join();
	advancedLightingThread.join();

	return 0;
}
