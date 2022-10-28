///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2019-2022
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <DejaVu/ImageProcessing/types.hpp>

namespace djv
{
	namespace proc
	{
		enum class DifferenceMethod
		{
			Naive,
			Leap,
			Prewitt,
			Sobel
		};

		template<DifferenceMethod DMethod, bool Normalized, scp::BorderBehaviour BBehaviour, ProcessiblePixel TPixel>
		constexpr void differenceX(const Image<TPixel>& image, Image<TPixel>& result);
		template<DifferenceMethod DMethod, bool Normalized, scp::BorderBehaviour BBehaviour, ProcessiblePixel TPixel>
		constexpr void differenceY(const Image<TPixel>& image, Image<TPixel>& result);

		template<DifferenceMethod DMethod, bool Normalized, scp::BorderBehaviour BBehaviour, ProcessiblePixel TPixel>
		constexpr void differenceXX(const Image<TPixel>& image, Image<TPixel>& result);
		template<DifferenceMethod DMethod, bool Normalized, scp::BorderBehaviour BBehaviour, ProcessiblePixel TPixel>
		constexpr void differenceXY(const Image<TPixel>& image, Image<TPixel>& result);
		template<DifferenceMethod DMethod, bool Normalized, scp::BorderBehaviour BBehaviour, ProcessiblePixel TPixel>
		constexpr void differenceYY(const Image<TPixel>& image, Image<TPixel>& result);

		enum class LaplacianMethod
		{
			Naive,
			Diagonals,
			DiagonalsCorrected
		};

		template<LaplacianMethod LMethod, bool Normalized, scp::BorderBehaviour BBehaviour, ProcessiblePixel TPixel>
		constexpr void laplacian(const Image<TPixel>& image, Image<TPixel>& result);


		template<scp::BorderBehaviour BBehaviour, PixelConcept TPixel>
		constexpr void blurGaussian(const Image<TPixel>& image, Image<TPixel>& result, float sigma);
		template<scp::BorderBehaviour BBehaviour, PixelConcept TPixel>
		constexpr void blurMedian(const Image<TPixel>& image, Image<TPixel>& result, uint64_t radius);
		template<scp::BorderBehaviour BBehaviour, PixelConcept TPixel>
		constexpr void blurMean(const Image<TPixel>& image, Image<TPixel>& result, uint64_t radius);

		template<scp::BorderBehaviour BBehaviour, PixelConcept TPixel>
		constexpr void blurGaussianBilateral(const Image<TPixel>& image, Image<TPixel>& result, float sigmaSpace, float sigmaColor);

		// Directionnal blur
		// Defocus aberration ?
	}
}

#include <DejaVu/ImageProcessing/templates/Misc.hpp>
