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
	namespace clustering
	{
		struct Clustering
		{
			constexpr Clustering() = delete;
			constexpr Clustering(uint64_t w, uint64_t h);
			constexpr Clustering(const Clustering& clustering) = default;
			constexpr Clustering(Clustering&& clustering) = default;

			constexpr Clustering& operator=(const Clustering& clustering) = default;
			constexpr Clustering& operator=(Clustering&& clustering) = default;

			template<PixelConcept TPixel> constexpr void applyTo(Image<TPixel>& image) const;	// TODO: 'ColorSelectionMethod' (not just picking

			constexpr ~Clustering() = default;

			scp::Matrix<uint64_t> clusterMap;	// size = {w, h}
		};

		// template<PixelConcept TPixel>
		// Clustering kMeans(const Image<TPixel>& image, uint64_t k, float epsilon = 1e-2f);
		// template<PixelConcept TPixel>
		// Clustering slic(const Image<TPixel>& image, uint64_t k, float relativePosWeight = 40.f, float epsilon = 1e-2f);
	}
}

#include <DejaVu/ImageProcessing/templates/Clustering.hpp>
