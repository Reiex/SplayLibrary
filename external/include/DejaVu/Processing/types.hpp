///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2019-2022
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <DejaVu/Core/Core.hpp>

namespace djv
{
	namespace proc
	{
		template<typename T> concept CPrPixel = CPixel<T> && std::floating_point<typename T::ComponentType>;

		template<CPrPixel TPixel> class PrImage;
		template<typename T> concept CPrImage = requires { typename T::PixelType; } && CPrPixel<typename T::PixelType> && std::derived_from<T, PrImage<typename T::PixelType>>;
	}
}
