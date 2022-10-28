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
	// namespace edgeDetectors
	// {
	// 	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 	/// \ingroup ImageProcessing
	// 	/// \defgroup edgeDetectors
	// 	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	// 	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 	/// \ingroup edgeDetectors
	// 	/// \brief Returns the result of the Marr-Hildreth edge detection algorithm.
	// 	/// 
	// 	/// The Marr-Hildreth edge detection algorithm is a simple evaluation of whether the laplacian changes sign or
	// 	/// not at proximity of a pixel. If the sign changes, then the pixel is part of an edge, and its strength is
	// 	/// the square of the magnitude of the gradient at that pixel.
	// 	/// 
	// 	/// The gradient computation method used is djv::operators::simpleGradient.
	// 	/// The laplacian computation method used is djv::operators::simpleLaplacian.
	// 	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 	template<typename PixelType>
	// 	Img<PixelType> marrHildreth(const Img<PixelType>& img);
	// 	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 	/// \ingroup edgeDetectors
	// 	/// \brief Returns the result of the Canny edge detection algorithm.
	// 	/// 
	// 	/// The Canny edge detection algorithm is a simple evaluation of whether the magnitude of the gradient is at a
	// 	/// local maximum in the direction of the gradient or not at a pixel. If it is, then the pixel is part of an
	// 	/// edge, and its strength is the square of the magnitude of the gradient at that pixel.
	// 	/// 
	// 	/// The gradient computation method used is djv::operators::simpleGradient.
	// 	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 	template<typename PixelType>
	// 	Img<PixelType> canny(const Img<PixelType>& img);
	// }
	// 
	// namespace cornerDetectors
	// {
	// 	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 	/// \ingroup ImageProcessing
	// 	/// \defgroup cornerDetectors
	// 	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	// 	namespace harrisResponses
	// 	{
	// 		///////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 		/// \ingroup cornerDetectors
	// 		/// \defgroup harrisResponses
	// 		///////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 		
	// 		///////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 		/// \ingroup harrisResponses
	// 		/// \brief Compute the response as \f$R(M) = det(M) - 0.05 \cdot tr(M)^2\f$.
	// 		///////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 		template<typename PixelType>
	// 		PixelType defaultResponse(const PixelType& Ixx, const PixelType& Ixy, const PixelType& Iyy);
	// 	}
	// 
	// 	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 	/// \ingroup cornerDetectors
	// 	/// \brief Returns the result of the Harris corner detection algorithm.
	// 	/// 
	// 	/// The Harris corner detection algorithm is an evaluation of whether the Harris response computed from the
	// 	/// eigenvalues of the auto-correlation matrix of the gradient on a window around a pixel is at a local maximum
	// 	/// or not at the pixel. If it is, then the pixel is part of a corner, and its strength is the Harris response.
	// 	/// 
	// 	/// The gradient computation method used is djv::operators::simpleGradient.
	// 	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 	template<typename PixelType>
	// 	Img<PixelType> harris(const Img<PixelType>& img, const scp::Mat<float>& window = { 3, 3, 1.f }, const std::function<PixelType(const PixelType&, const PixelType&, const PixelType&)>& response = harrisResponses::defaultResponse<PixelType>);
	// }
}

#include <DejaVu/ImageProcessing/templates/FeatureDetection.hpp>
