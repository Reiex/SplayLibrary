///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2019-2022
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <SciPP/SciPP.hpp>
#include <Diskon/Diskon.hpp>

namespace djv
{
	template<typename TComponent, uint8_t ComponentCount> class Pixel;
	template<typename T> concept PixelConcept = requires { typename T::ComponentType; T::componentCount; } && std::derived_from<T, Pixel<typename T::ComponentType, T::componentCount>>;
	
	enum class ImageFormat;
	template<PixelConcept TPixel> class Image;
	template<typename T> concept ImageConcept = requires { typename T::PixelType; } && PixelConcept<typename T::PixelType> && std::derived_from<T, Image<typename T::PixelType>>;


	class Shape;
	namespace shape
	{
		class ThickRect;
		class FilledRect;
		class Rect;
		class Crown;
		class Disc;
		class Circle;
		class Line;
	}
}
