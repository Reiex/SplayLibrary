///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2019-2022
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <DejaVu/Core/types.hpp>

namespace djv
{
	#pragma pack(push, 1)
	template<typename TComponent, uint8_t ComponentCount>
	class Pixel
	{
		static_assert(ComponentCount != 0);

		public:

			using ComponentType = TComponent;
			static constexpr uint8_t componentCount = ComponentCount;

			constexpr Pixel() = default;
			constexpr Pixel(const TComponent& value);
			constexpr Pixel(const std::initializer_list<TComponent>& components);
			constexpr Pixel(const Pixel<TComponent, ComponentCount>& pixel) = default;
			constexpr Pixel(Pixel<TComponent, ComponentCount>&& pixel) = default;
	
			constexpr Pixel<TComponent, ComponentCount>& operator=(const Pixel<TComponent, ComponentCount>& pixel) = default;
			constexpr Pixel<TComponent, ComponentCount>& operator=(Pixel<TComponent, ComponentCount>&& pixel) = default;
	
			constexpr TComponent& operator[](uint8_t i);
			constexpr const TComponent& operator[](uint8_t i) const;

			constexpr Pixel<TComponent, ComponentCount>& operator+=(const Pixel<TComponent, ComponentCount>& pixel);
			constexpr Pixel<TComponent, ComponentCount>& operator-=(const Pixel<TComponent, ComponentCount>& pixel);
			constexpr Pixel<TComponent, ComponentCount>& operator*=(float value);
			constexpr Pixel<TComponent, ComponentCount>& operator/=(float value);
	
			constexpr bool operator==(const Pixel<TComponent, ComponentCount>& pixel);
			constexpr bool operator!=(const Pixel<TComponent, ComponentCount>& pixel);
	
			template<typename T> constexpr void set(uint8_t i, const T& value);
			template<typename T> constexpr void get(uint8_t i, T& value) const;
	
			constexpr ~Pixel() = default;
	
		private:
	
			TComponent _components[ComponentCount];
	};
	#pragma pack(pop)


	template<typename TComponent, uint8_t ComponentCount>
	constexpr Pixel<TComponent, ComponentCount> operator+(const Pixel<TComponent, ComponentCount>& a, const Pixel<TComponent, ComponentCount>& b);
	template<typename TComponent, uint8_t ComponentCount>
	constexpr Pixel<TComponent, ComponentCount>&& operator+(Pixel<TComponent, ComponentCount>&& a, const Pixel<TComponent, ComponentCount>& b);
	template<typename TComponent, uint8_t ComponentCount>
	constexpr Pixel<TComponent, ComponentCount>&& operator+(const Pixel<TComponent, ComponentCount>& a, Pixel<TComponent, ComponentCount>&& b);
	template<typename TComponent, uint8_t ComponentCount>
	constexpr Pixel<TComponent, ComponentCount>&& operator+(Pixel<TComponent, ComponentCount>&& a, Pixel<TComponent, ComponentCount>&& b);

	template<typename TComponent, uint8_t ComponentCount>
	constexpr Pixel<TComponent, ComponentCount> operator-(const Pixel<TComponent, ComponentCount>& a, const Pixel<TComponent, ComponentCount>& b);
	template<typename TComponent, uint8_t ComponentCount>
	constexpr Pixel<TComponent, ComponentCount>&& operator-(Pixel<TComponent, ComponentCount>&& a, const Pixel<TComponent, ComponentCount>& b);

	template<typename TComponent, uint8_t ComponentCount>
	constexpr Pixel<TComponent, ComponentCount> operator*(const Pixel<TComponent, ComponentCount>& a, float x);
	template<typename TComponent, uint8_t ComponentCount>
	constexpr Pixel<TComponent, ComponentCount>&& operator*(Pixel<TComponent, ComponentCount>&& a, float x);
	template<typename TComponent, uint8_t ComponentCount>
	constexpr Pixel<TComponent, ComponentCount> operator*(float x, const Pixel<TComponent, ComponentCount>& a);
	template<typename TComponent, uint8_t ComponentCount>
	constexpr Pixel<TComponent, ComponentCount>&& operator*(float x, Pixel<TComponent, ComponentCount>&& a);

	template<typename TComponent, uint8_t ComponentCount>
	constexpr Pixel<TComponent, ComponentCount> operator/(const Pixel<TComponent, ComponentCount>& a, float x);
	template<typename TComponent, uint8_t ComponentCount>
	constexpr Pixel<TComponent, ComponentCount>&& operator/(Pixel<TComponent, ComponentCount>&& a, float x);


	namespace colors
	{
		template<typename TComponent, uint8_t ComponentCount>
		static constexpr Pixel<TComponent, ComponentCount> black = std::integral<TComponent> ? std::numeric_limits<TComponent>::min() : -1.0;

		template<typename TComponent, uint8_t ComponentCount>
		static constexpr Pixel<TComponent, ComponentCount> white = std::integral<TComponent> ? std::numeric_limits<TComponent>::max() : 1.0;
	}


	enum class ImageFormat
	{
		Png,

		Pbm,
		Pgm,
		Ppm,
		Pnm
	};


	template<PixelConcept TPixelFrom, PixelConcept TPixelTo>
	using PixelConversionFunction = std::function<void(const TPixelFrom&, TPixelTo&)>;


	template<PixelConcept TPixel>
	class Image
	{
		public:
			
			using PixelType = TPixel;

			constexpr Image(uint64_t width, uint64_t height);
			constexpr Image(uint64_t width, uint64_t height, const TPixel& value);
			constexpr Image(uint64_t width, uint64_t height, const TPixel* values);
			constexpr Image(const std::filesystem::path& path);
			constexpr Image(const std::filesystem::path& path, const uint8_t* swizzling);
			constexpr Image(const std::filesystem::path& path, const std::initializer_list<uint8_t>& swizzling);
			constexpr Image(const std::istream& stream, ImageFormat format);
			constexpr Image(const std::istream& stream, ImageFormat format, const uint8_t* swizzling);
			constexpr Image(const std::istream& stream, ImageFormat format, const std::initializer_list<uint8_t>& swizzling);
			template<ImageConcept TImage> constexpr Image(const TImage& image);
			template<ImageConcept TImage> constexpr Image(const TImage& image, const PixelConversionFunction<typename TImage::PixelType, TPixel>& conversionFunc);
			constexpr Image(const Image<TPixel>& image);
			constexpr Image(Image<TPixel>&& image);

			static constexpr Image<TPixel>* constructAroundMemory(uint64_t width, uint64_t height, TPixel* memory);

			constexpr Image<TPixel>& operator=(const Image<TPixel>& image);
			constexpr Image<TPixel>& operator=(Image<TPixel>&& image);


			constexpr void loadFromFile(const std::filesystem::path& path);
			constexpr void loadFromFile(const std::filesystem::path& path, const uint8_t* swizzling); // {0, 3, -1} means first component is red, second is alpha and third is set to 0
			constexpr void loadFromFile(const std::filesystem::path& path, const std::initializer_list<uint8_t>& swizzling);
			constexpr void loadFromStream(const std::istream& stream, ImageFormat format);
			constexpr void loadFromStream(const std::istream& stream, ImageFormat format, const uint8_t* swizzling);
			constexpr void loadFromStream(const std::istream& stream, ImageFormat format, const std::initializer_list<uint8_t>& swizzling);

			template<ImageConcept TImage> constexpr void convertFrom(const TImage& image);
			template<ImageConcept TImage> constexpr void convertFrom(const TImage& image, const PixelConversionFunction<typename TImage::PixelType, TPixel>& conversionFunc);

			template<scp::InterpolationMethod IMethod> constexpr void resize(const Image<TPixel>& image);
			constexpr void crop(const Image<TPixel>& image, uint64_t x, uint64_t y);

			constexpr Image<TPixel>& transpose();
			template<scp::InterpolationMethod IMethod> constexpr Image<TPixel>& rotate(float angle, const TPixel& backgroundColor);	// TODO: BorderBehaviour (FixedColor, repeat, continuous...)

			constexpr Image<TPixel>& flip(bool vertically, bool horizontally);
			constexpr Image<TPixel>& draw(const Shape& shape, const TPixel& color);
			constexpr Image<TPixel>& draw(const Shape& shape, const Image<TPixel>& image);

			constexpr void saveToFile(const std::filesystem::path& path) const;
			constexpr void saveToFile(const std::filesystem::path& path, const uint8_t* swizzling) const;	// {0, 3, -1, -1} means red is first component, green is fourth component, blue is set to 0 and alpha is 255
			constexpr void saveToFile(const std::filesystem::path& path, const std::initializer_list<uint8_t>& swizzling) const;
			constexpr void saveToStream(const std::istream& stream, ImageFormat format);
			constexpr void saveToStream(const std::istream& stream, ImageFormat format, const uint8_t* swizzling);
			constexpr void saveToStream(const std::istream& stream, ImageFormat format, const std::initializer_list<uint8_t>& swizzling);


			constexpr TPixel& operator[](const std::initializer_list<uint64_t>& indices);
			constexpr const TPixel& operator[](const std::initializer_list<uint64_t>& indices) const;

			constexpr TPixel* begin();
			constexpr TPixel* end();
			constexpr const TPixel* begin() const;
			constexpr const TPixel* end() const;
			constexpr const TPixel* cbegin() const;
			constexpr const TPixel* cend() const;

			constexpr TPixel* getData();
			constexpr const TPixel* getData() const;
			constexpr const uint64_t& getWidth() const;
			constexpr const uint64_t& getHeight() const;
			constexpr bool isValid() const;

			constexpr ~Image();

		private:

			using TComponent = typename TPixel::ComponentType;

			constexpr Image();

			constexpr void _create(uint64_t width, uint64_t height);
			constexpr void _copyFrom(const Image<TPixel>& image);
			constexpr void _moveFrom(Image<TPixel>&& image);
			constexpr void _destroy();

			constexpr void _loadFromFile(const std::filesystem::path& path, const uint8_t* swizzling);
			constexpr void _loadFromStream(std::istream& stream, ImageFormat format, const uint8_t* swizzling);
			
			constexpr void _loadFromPng(std::istream& stream, const uint8_t* swizzling);
			template<ImageFormat Format> constexpr void _loadFromPnm(std::istream& stream, const uint8_t* swizzling);

			constexpr void _saveToFile(const std::filesystem::path& path, const uint8_t* swizzling) const;
			constexpr void _saveToStream(std::ostream& stream, ImageFormat format, const uint8_t* swizzling) const;

			constexpr void _saveToPng(std::ostream& stream, const uint8_t* swizzling) const;
			template<ImageFormat Format> constexpr void _saveToPnm(std::ostream& stream, const uint8_t* swizzling) const;

			static constexpr void (Image<TPixel>::* _imageFormatToLoadFunc[])(std::istream&, const uint8_t*) = {
				&Image<TPixel>::_loadFromPng,
				&Image<TPixel>::_loadFromPnm<ImageFormat::Pbm>,
				&Image<TPixel>::_loadFromPnm<ImageFormat::Pgm>,
				&Image<TPixel>::_loadFromPnm<ImageFormat::Ppm>,
				&Image<TPixel>::_loadFromPnm<ImageFormat::Pnm>,
			};
			static constexpr void (Image<TPixel>::* _imageFormatToSaveFunc[])(std::ostream&, const uint8_t*) const = {
				&Image<TPixel>::_saveToPng,
				&Image<TPixel>::_saveToPnm<ImageFormat::Pbm>,
				&Image<TPixel>::_saveToPnm<ImageFormat::Pgm>,
				&Image<TPixel>::_saveToPnm<ImageFormat::Ppm>,
				&Image<TPixel>::_saveToPnm<ImageFormat::Pnm>,
			};
			static constexpr bool _extensionToImageFormat(const std::filesystem::path& extension, ImageFormat& imageFormat);


			uint64_t _width;
			uint64_t _height;

			TPixel* _pixels;

			bool _owner;

		template<PixelConcept T> friend class Image;
	};
}

#include <DejaVu/Core/templates/Image.hpp>
