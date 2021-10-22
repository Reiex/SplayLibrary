#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Functions and classes for image manipulations.
/// \author Reiex
/// 
/// For a more detailed description, see class Img.
/// 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <DejaVu/Core/types.hpp>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \addtogroup Core
/// \{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace djv
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \brief Class for pixel manipulation. Any PixelType used in Img template class must be derived from this class.
	/// 
	/// PixelBase implement a pixel as an array of N components with each operator overloaded component wise.
	/// The components are expected to be in range [0, 1].
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<uint64_t N>
	class PixelBase
	{
		public:

			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \brief Default constructor. Initialize each component of the pixel with x.
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			PixelBase(float x = 0.f);
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \brief Initialize the four first components of the pixel with r, g, b and a.
			///
			/// The other components are initialized with 0.f.
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			PixelBase(float r, float g, float b, float a);
			PixelBase(const PixelBase<N>& pixel) = default;
			PixelBase(PixelBase<N>&& pixel) = default;

			PixelBase<N>& operator=(const PixelBase<N>& pixel) = default;
			PixelBase<N>& operator=(PixelBase<N>&& pixel) = default;

			float& operator[](uint64_t i);
			const float& operator[](uint64_t i) const;

			PixelBase<N>& operator+=(const PixelBase<N>& pixel);
			PixelBase<N>& operator-=(const PixelBase<N>& pixel);
			PixelBase<N>& operator*=(const PixelBase<N>& pixel);
			PixelBase<N>& operator/=(const PixelBase<N>& pixel);
			PixelBase<N>& operator%=(const PixelBase<N>& pixel);
			PixelBase<N>& operator+=(float x);
			PixelBase<N>& operator-=(float x);
			PixelBase<N>& operator*=(float x);
			PixelBase<N>& operator/=(float x);
			PixelBase<N>& operator%=(float x);

			static const uint64_t componentCount = N;
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \brief Returns the classical RGBA components associated to a pixel.
			///
			/// The only restriction of PixelBase is the color to be representable by N components with each component
			/// in range [0, 1].
			/// However, each pixel should still represent a color or something convertible to/from a color. Thus the
			/// constructor from r, g, b, a and this function are used for this conversion.
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			void getRGBA(float& red, float& green, float& blue, float& alpha) const;

		protected:

			float _components[N];
	};

	template<uint64_t N>
	PixelBase<N> operator+(const PixelBase<N>& pixelA, const PixelBase<N>& pixelB);
	template<uint64_t N>
	PixelBase<N>&& operator+(PixelBase<N>&& pixelA, const PixelBase<N>& pixelB);
	template<uint64_t N>
	PixelBase<N>&& operator+(const PixelBase<N>& pixelA, PixelBase<N>&& pixelB);
	template<uint64_t N>
	PixelBase<N>&& operator+(PixelBase<N>&& pixelA, PixelBase<N>&& pixelB);

	template<uint64_t N>
	PixelBase<N> operator-(const PixelBase<N>& pixelA, const PixelBase<N>& pixelB);
	template<uint64_t N>
	PixelBase<N>&& operator-(PixelBase<N>&& pixelA, const PixelBase<N>& pixelB);

	template<uint64_t N>
	PixelBase<N> operator*(const PixelBase<N>& pixelA, const PixelBase<N>& pixelB);
	template<uint64_t N>
	PixelBase<N>&& operator*(PixelBase<N>&& pixelA, const PixelBase<N>& pixelB);
	template<uint64_t N>
	PixelBase<N>&& operator*(const PixelBase<N>& pixelA, PixelBase<N>&& pixelB);
	template<uint64_t N>
	PixelBase<N>&& operator*(PixelBase<N>&& pixelA, PixelBase<N>&& pixelB);

	template<uint64_t N>
	PixelBase<N> operator/(const PixelBase<N>& pixelA, const PixelBase<N>& pixelB);
	template<uint64_t N>
	PixelBase<N>&& operator/(PixelBase<N>&& pixelA, const PixelBase<N>& pixelB);

	template<uint64_t N>
	PixelBase<N> operator%(const PixelBase<N>& pixelA, const PixelBase<N>& pixelB);
	template<uint64_t N>
	PixelBase<N>&& operator%(PixelBase<N>&& pixelA, const PixelBase<N>& pixelB);

	template<uint64_t N>
	PixelBase<N> operator+(const PixelBase<N>& pixel, float x);
	template<uint64_t N>
	PixelBase<N>&& operator+(PixelBase<N>&& pixel, float x);
	template<uint64_t N>
	PixelBase<N> operator+(float x, const PixelBase<N>& pixel);
	template<uint64_t N>
	PixelBase<N>&& operator+(float x, PixelBase<N>&& pixel);

	template<uint64_t N>
	PixelBase<N> operator-(const PixelBase<N>& pixel, float x);
	template<uint64_t N>
	PixelBase<N>&& operator-(PixelBase<N>&& pixel, float x);

	template<uint64_t N>
	PixelBase<N> operator*(const PixelBase<N>& pixel, float x);
	template<uint64_t N>
	PixelBase<N>&& operator*(PixelBase<N>&& pixel, float x);
	template<uint64_t N>
	PixelBase<N> operator*(float x, const PixelBase<N>& pixel);
	template<uint64_t N>
	PixelBase<N>&& operator*(float x, PixelBase<N>&& pixel);

	template<uint64_t N>
	PixelBase<N> operator/(const PixelBase<N>& pixel, float x);
	template<uint64_t N>
	PixelBase<N>&& operator/(PixelBase<N>&& pixel, float x);

	template<uint64_t N>
	PixelBase<N> operator%(const PixelBase<N>& pixel, float x);
	template<uint64_t N>
	PixelBase<N>&& operator%(PixelBase<N>&& pixel, float x);
}

namespace std
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \relates djv::PixelBase
	/// \brief Returns the square of the euclidian norm of the pixel, ie. the sum of the square of the components.
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<uint64_t N>
	float norm(const djv::PixelBase<N>& pixel);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \relates djv::PixelBase
	/// \brief Returns the euclidian norm of the pixel, ie. the square root of the sum of the square of the components.
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<uint64_t N>
	float abs(const djv::PixelBase<N>& pixel);
}

namespace djv
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \brief Class for image manipulation. `PixelType` must be derived from `PixelBase` template class.
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename PixelType>
	class Img
	{
		public:

			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \brief Initialize an image of `width*size` with all pixels at `pixelInit`.
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			Img(uint64_t width, uint64_t height, PixelType pixelInit = 0.f);
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \brief Initialize an image from a file on disk, recognizing the format according to the extension.
			///
			/// Extensions recognized are: .bmp, .jpg, .jpeg, .png, .tga
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			Img(const std::string& filename, bool transpose = false, bool flipHorizontally = false, bool flipVertically = false);
			Img(const scp::Mat<PixelType>& mat);
			Img(scp::Mat<PixelType>&& mat);
			Img(const Img<PixelType>& image);
			Img(Img<PixelType>&& image) = default;

			Img<PixelType>& operator=(const Img<PixelType>& image);
			Img<PixelType>& operator=(Img<PixelType>&& image) = default;

			scp::Vec<PixelType>& operator[](uint64_t i);
			const scp::Vec<PixelType>& operator[](uint64_t i) const;
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \brief Project each pixel i-th component in a matrix and returns this matrix.
			///
			/// Try use this method the less possible because a new matrix must be constructed at each call.
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			scp::Mat<float> getComponent(uint64_t i) const;
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \brief Set each pixels i-th component of the image according to the matrix `comp`.
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			void setComponent(uint64_t i, const scp::Mat<float>& comp);

			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \brief Linearly scale each pixel to have each component between `min` and `max` same component.
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			void normalize(PixelType min = 0.f, PixelType max = 1.f);
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \brief Casts the image to an image with another `PixelType`.
			///
			/// The conversion is done using `T` constructor with r, g, b and a obtained with `PixelType::getRGBA`.
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			template<typename T> Img<T> castToPixelType() const;
			void saveToFile(const std::string& filename) const;

			void resize(uint64_t width, uint64_t height);			///< Resizes the image to desired width and height.
			void scale(float factor);								///< Multiplies the width and height of the image by `factor`.
			void scale(float xFactor, float yFactor);				///< Multiplies the width of the image by `xFactor` and the height of the image by `yFactor`.
			void upsample(uint64_t count = 2);						///< Multiplies the width and height of the image by repeating each pixel `count` times.
			void downsample(uint64_t count = 2);					///< Divides the width and height of the image by selecting one pixel every `count` pixels.
			void rotate(float angle, PixelType pixelInit = 0.f);	///< Rotate the image according to angle (in radians). The "empty" pixels are set to `pixelInit`.
			void flipHorizontally();								///< Flips the image horizontally.
			void flipVertically();									///< Flips the image vertically.
			void transpose();										///< Transpose the image - flip it according to its diagonal.

			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \brief Returns a new image containing the region specified by the rectangle area given in parameters.
			/// 
			/// The `x` and `y` parameters design the top-left corner of the rectangle and `w` and `h` design the
			/// width and height of the rectangle.
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			Img<PixelType> subImage(uint64_t x, uint64_t y, uint64_t w, uint64_t h) const;
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \brief Returns a new image containing the region specified by the shape given in parameters.
			/// 
			/// Each pixel obtained while iterating over the shape is part of the region.
			/// "Empty" pixels are set to `pixelInit`.
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			Img<PixelType> subImage(const Shape& shape, const PixelType& pixelInit = 0.f) const;

			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \brief Draws the shape with a solid `color`.
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			void draw(const Shape& shape, const PixelType& color);
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \brief Draws the shape using pixels from `src`.
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			void draw(const Shape& shape, const Img<PixelType>& src);

			uint64_t width() const;						///< Returns the width of the image.
			uint64_t height() const;					///< Returns the height of the image.
			const scp::Mat<PixelType>& getData() const;	///< Returns a constant reference to the matrix of pixels of the image.

			~Img() = default;

		protected:

			Img();

			std::unique_ptr<scp::Mat<PixelType>> _data;	///< Pixels of the image. A row of the matrix is a column of the image.
	};
}

namespace djv
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \brief Pixel class associated to GrayScaleImg.
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	struct GrayScalePixel : public PixelBase<1>
	{
		using PixelBase<1>::PixelBase;

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Init a gray pixel (a simple float) from a color pixel.
		///
		/// The intensity is computed as: `I = r*0.299f + g*0.587f + b*0.114f`.
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		GrayScalePixel(float r, float g, float b, float a);
		GrayScalePixel(const PixelBase<1>& pixel);
		GrayScalePixel(PixelBase<1>&& pixel);
		GrayScalePixel(const GrayScalePixel& pixel) = default;
		GrayScalePixel(GrayScalePixel&& pixel) = default;

		GrayScalePixel& operator=(const GrayScalePixel& pixel) = default;
		GrayScalePixel& operator=(GrayScalePixel&& pixel) = default;
	};
}

namespace djv
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \brief Class for manipulating gray scale images.
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class GrayScaleImg : public Img<GrayScalePixel>
	{
		public:

			using Img<GrayScalePixel>::Img;

			GrayScaleImg() = delete;
			GrayScaleImg(const RGBAImg& image, float redWeight = 0.299f, float greenWeight = 0.587f, float blueWeight = 0.114f);
			GrayScaleImg(const scp::Mat<float>& image);
			GrayScaleImg(const Img<GrayScalePixel>& image);
			GrayScaleImg(Img<GrayScalePixel>&& image);
			GrayScaleImg(const GrayScaleImg& image);
			GrayScaleImg(GrayScaleImg&& image) = default;

			GrayScaleImg& operator=(const GrayScaleImg& image);
			GrayScaleImg& operator=(GrayScaleImg&& image) = default;

			~GrayScaleImg() = default;
	};
}

namespace djv
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \brief Pixel class associated to RGBAImg.
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	struct RGBAPixel : public PixelBase<4>
	{
		using PixelBase<4>::PixelBase;

		RGBAPixel(const PixelBase<4>& pixel);
		RGBAPixel(PixelBase<4>&& pixel);
		RGBAPixel(const RGBAPixel& pixel) = default;
		RGBAPixel(RGBAPixel&& pixel) = default;

		RGBAPixel& operator=(const RGBAPixel& pixel) = default;
		RGBAPixel& operator=(RGBAPixel&& pixel) = default;
	};
}

namespace djv
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \brief Class for manipulating RGBA (Red, Green, Blue, Alpha) images.
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class RGBAImg : public Img<RGBAPixel>
	{
		public:

			using Img<RGBAPixel>::Img;

			RGBAImg() = delete;
			RGBAImg(const scp::Mat<float>& red, const scp::Mat<float>& green, const scp::Mat<float>& blue, const scp::Mat<float>& alpha);
			RGBAImg(const GrayScaleImg& image);
			RGBAImg(const Img<RGBAPixel>& image);
			RGBAImg(Img<RGBAPixel>&& image);
			RGBAImg(const RGBAImg& image);
			RGBAImg(RGBAImg&& image) = default;

			RGBAImg& operator=(const RGBAImg& image);
			RGBAImg& operator=(RGBAImg&& image) = default;

			~RGBAImg() = default;
	};
}

namespace djv
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \brief Pixel class associated to HSVImg.
	///
	/// The saturation, value AND HUE are in range [0, 1] !
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	struct HSVPixel : public PixelBase<3>
	{
		using PixelBase<3>::PixelBase;

		HSVPixel(float r, float g, float b, float a);
		HSVPixel(const PixelBase<3>& pixel);
		HSVPixel(PixelBase<3>&& pixel);
		HSVPixel(const HSVPixel& pixel) = default;
		HSVPixel(HSVPixel&& pixel) = default;

		HSVPixel& operator=(const HSVPixel& pixel) = default;
		HSVPixel& operator=(HSVPixel&& pixel) = default;

		void getRGBA(float& red, float& green, float& blue, float& alpha) const;
	};
}

namespace djv
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \brief Class for manipulating RGBA (Hue, Saturation, Value) images.
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class HSVImg : public Img<HSVPixel>
	{
		public:

			using Img<HSVPixel>::Img;

			HSVImg() = delete;
			HSVImg(const Img<HSVPixel>& image);
			HSVImg(Img<HSVPixel>&& image);
			HSVImg(const HSVImg& image);
			HSVImg(HSVImg&& image) = default;

			HSVImg& operator=(const HSVImg& image);
			HSVImg& operator=(HSVImg&& image) = default;

			~HSVImg() = default;
	};
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <DejaVu/Core/ImgT.hpp>
