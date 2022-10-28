///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2019-2022
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <DejaVu/Core/Image.hpp>

namespace djv
{
	template<typename TComponent, uint8_t ComponentCount>
	constexpr Pixel<TComponent, ComponentCount>::Pixel(const TComponent& value)
	{
		std::fill_n(_components, ComponentCount, value);
	}

	template<typename TComponent, uint8_t ComponentCount>
	constexpr Pixel<TComponent, ComponentCount>::Pixel(const std::initializer_list<TComponent>& components)
	{
		assert(components.size() == ComponentCount);
		std::copy_n(components.begin(), ComponentCount, _components);
	}
	
	template<typename TComponent, uint8_t ComponentCount>
	constexpr TComponent& Pixel<TComponent, ComponentCount>::operator[](uint8_t i)
	{
		assert(i < ComponentCount);
		return _components[i];
	}
	
	template<typename TComponent, uint8_t ComponentCount>
	constexpr const TComponent& Pixel<TComponent, ComponentCount>::operator[](uint8_t i) const
	{
		assert(i < ComponentCount);
		return _components[i];
	}

	template<typename TComponent, uint8_t ComponentCount>
	constexpr Pixel<TComponent, ComponentCount>& Pixel<TComponent, ComponentCount>::operator+=(const Pixel<TComponent, ComponentCount>& pixel)
	{
		std::transform(_components, _components + ComponentCount, pixel._components, _components, std::plus<TComponent>());
		return *this;
	}

	template<typename TComponent, uint8_t ComponentCount>
	constexpr Pixel<TComponent, ComponentCount>& Pixel<TComponent, ComponentCount>::operator-=(const Pixel<TComponent, ComponentCount>& pixel)
	{
		std::transform(_components, _components + ComponentCount, pixel._components, _components, std::minus<TComponent>());
		return *this;
	}

	template<typename TComponent, uint8_t ComponentCount>
	constexpr Pixel<TComponent, ComponentCount>& Pixel<TComponent, ComponentCount>::operator*=(float value)
	{
		std::transform(_components, _components + ComponentCount, _components, [&](const TComponent& x) { return x * value; });
		return *this;
	}

	template<typename TComponent, uint8_t ComponentCount>
	constexpr Pixel<TComponent, ComponentCount>& Pixel<TComponent, ComponentCount>::operator/=(float value)
	{
		std::transform(_components, _components + ComponentCount, _components, [&](const TComponent& x) { return x / value; });
		return *this;
	}

	template<typename TComponent, uint8_t ComponentCount>
	constexpr bool Pixel<TComponent, ComponentCount>::operator==(const Pixel<TComponent, ComponentCount>& pixel)
	{
		return std::equal(_components, _components + ComponentCount, pixel._components);
	}
	
	template<typename TComponent, uint8_t ComponentCount>
	constexpr bool Pixel<TComponent, ComponentCount>::operator!=(const Pixel<TComponent, ComponentCount>& pixel)
	{
		return !(*this == pixel);
	}

	template<typename TComponent, uint8_t ComponentCount>
	template<typename T>
	constexpr void Pixel<TComponent, ComponentCount>::set(uint8_t i, const T& value)
	{
		assert(i < ComponentCount);
		dsk::convertNum<T, TComponent>(&value, &_components[i]);
	}

	template<typename TComponent, uint8_t ComponentCount>
	template<typename T>
	constexpr void Pixel<TComponent, ComponentCount>::get(uint8_t i, T& value) const
	{
		assert(i < ComponentCount);
		dsk::convertNum<TComponent, T>(&_components[i], &value);
	}


	template<typename TComponent, uint8_t ComponentCount>
	constexpr Pixel<TComponent, ComponentCount> operator+(const Pixel<TComponent, ComponentCount>& a, const Pixel<TComponent, ComponentCount>& b)
	{
		Pixel<TComponent, ComponentCount> c(a);
		c += b;
		return c;
	}

	template<typename TComponent, uint8_t ComponentCount>
	constexpr Pixel<TComponent, ComponentCount>&& operator+(Pixel<TComponent, ComponentCount>&& a, const Pixel<TComponent, ComponentCount>& b)
	{
		a += b;
		return std::forward<Pixel<TComponent, ComponentCount>>(a);
	}

	template<typename TComponent, uint8_t ComponentCount>
	constexpr Pixel<TComponent, ComponentCount>&& operator+(const Pixel<TComponent, ComponentCount>& a, Pixel<TComponent, ComponentCount>&& b)
	{
		b += a;
		return std::forward<Pixel<TComponent, ComponentCount>>(b);
	}

	template<typename TComponent, uint8_t ComponentCount>
	constexpr Pixel<TComponent, ComponentCount>&& operator+(Pixel<TComponent, ComponentCount>&& a, Pixel<TComponent, ComponentCount>&& b)
	{
		a += b;
		return std::forward<Pixel<TComponent, ComponentCount>>(a);
	}

	template<typename TComponent, uint8_t ComponentCount>
	constexpr Pixel<TComponent, ComponentCount> operator-(const Pixel<TComponent, ComponentCount>& a, const Pixel<TComponent, ComponentCount>& b)
	{
		Pixel<TComponent, ComponentCount> c(a);
		c -= b;
		return c;
	}

	template<typename TComponent, uint8_t ComponentCount>
	constexpr Pixel<TComponent, ComponentCount>&& operator-(Pixel<TComponent, ComponentCount>&& a, const Pixel<TComponent, ComponentCount>& b)
	{
		a -= b;
		return std::forward<Pixel<TComponent, ComponentCount>>(a);
	}

	template<typename TComponent, uint8_t ComponentCount>
	constexpr Pixel<TComponent, ComponentCount> operator*(const Pixel<TComponent, ComponentCount>& a, float x)
	{
		Pixel<TComponent, ComponentCount> b(a);
		b *= x;
		return b;
	}

	template<typename TComponent, uint8_t ComponentCount>
	constexpr Pixel<TComponent, ComponentCount>&& operator*(Pixel<TComponent, ComponentCount>&& a, float x)
	{
		a *= x;
		return std::forward<Pixel<TComponent, ComponentCount>>(a);
	}

	template<typename TComponent, uint8_t ComponentCount>
	constexpr Pixel<TComponent, ComponentCount> operator*(float x, const Pixel<TComponent, ComponentCount>& a)
	{
		Pixel<TComponent, ComponentCount> b(a);
		b *= x;
		return b;
	}

	template<typename TComponent, uint8_t ComponentCount>
	constexpr Pixel<TComponent, ComponentCount>&& operator*(float x, Pixel<TComponent, ComponentCount>&& a)
	{
		a *= x;
		return std::forward<Pixel<TComponent, ComponentCount>>(a);
	}

	template<typename TComponent, uint8_t ComponentCount>
	constexpr Pixel<TComponent, ComponentCount> operator/(const Pixel<TComponent, ComponentCount>& a, float x)
	{
		Pixel<TComponent, ComponentCount> b(a);
		b /= x;
		return b;
	}

	template<typename TComponent, uint8_t ComponentCount>
	constexpr Pixel<TComponent, ComponentCount>&& operator/(Pixel<TComponent, ComponentCount>&& a, float x)
	{
		a /= x;
		return std::forward<Pixel<TComponent, ComponentCount>>(a);
	}


	namespace _djv
	{
		template<uint8_t ComponentCount>
		constexpr void defaultLoadSwizzling(uint8_t* swizzling)
		{
			constexpr uint8_t n = std::min<uint8_t>(ComponentCount, 4);
			for (uint8_t i = 0; i < n; ++i)
			{
				swizzling[i] = i;
			}

			if constexpr (ComponentCount > 4)
			{
				std::fill_n(swizzling + 4, ComponentCount - 4, UINT8_MAX);
			}
		}

		template<uint8_t ComponentCount>
		constexpr void defaultSaveSwizzling(uint8_t* swizzling)
		{
			constexpr uint8_t n = std::min<uint8_t>(ComponentCount, 4);
			for (uint8_t i = 0; i < n; ++i)
			{
				swizzling[i] = i;
			}

			if constexpr (ComponentCount < 4)
			{
				std::fill_n(swizzling + ComponentCount, 4 - ComponentCount, UINT8_MAX);
			}
		}
	
		template<PixelConcept TPixelFrom, PixelConcept TPixelTo>
		constexpr void defaultConversionFunction(const TPixelFrom& from, TPixelTo& to)
		{
			constexpr uint8_t n = std::min(TPixelFrom::componentCount, TPixelTo::componentCount);
			for (uint8_t i = 0; i < n; ++i)
			{
				to.set(i, from[i]);
			}
		}
	}

	template<PixelConcept TPixel>
	constexpr Image<TPixel>::Image() :
		_width(0),
		_height(0),
		_pixels(nullptr),
		_owner(true)
	{
	}

	template<PixelConcept TPixel>
	constexpr Image<TPixel>::Image(uint64_t width, uint64_t height) : Image<TPixel>()
	{
		_create(width, height);
	}

	template<PixelConcept TPixel>
	constexpr Image<TPixel>::Image(uint64_t width, uint64_t height, const TPixel& value) : Image<TPixel>(width, height)
	{
		std::fill_n(_pixels, _width * _height, value);
	}

	template<PixelConcept TPixel>
	constexpr Image<TPixel>::Image(uint64_t width, uint64_t height, const TPixel* values) : Image<TPixel>(width, height)
	{
		std::copy_n(values, _width * _height, _pixels);
	}

	template<PixelConcept TPixel>
	constexpr Image<TPixel>::Image(const std::filesystem::path& path) : Image<TPixel>()
	{
		loadFromFile(path);
	}

	template<PixelConcept TPixel>
	constexpr Image<TPixel>::Image(const std::filesystem::path& path, const uint8_t* swizzling) : Image<TPixel>()
	{
		loadFromFile(path, swizzling);
	}

	template<PixelConcept TPixel>
	constexpr Image<TPixel>::Image(const std::filesystem::path& path, const std::initializer_list<uint8_t>& swizzling) : Image<TPixel>()
	{
		loadFromFile(path, swizzling);
	}

	template<PixelConcept TPixel>
	constexpr Image<TPixel>::Image(const std::istream& stream, ImageFormat format) : Image<TPixel>()
	{
		loadFromStream(stream, format);
	}

	template<PixelConcept TPixel>
	constexpr Image<TPixel>::Image(const std::istream& stream, ImageFormat format, const uint8_t* swizzling) : Image<TPixel>()
	{
		loadFromStream(stream, format, swizzling);
	}

	template<PixelConcept TPixel>
	constexpr Image<TPixel>::Image(const std::istream& stream, ImageFormat format, const std::initializer_list<uint8_t>& swizzling) : Image<TPixel>()
	{
		loadFromStream(stream, format, swizzling);
	}

	template<PixelConcept TPixel>
	template<ImageConcept TImage>
	constexpr Image<TPixel>::Image(const TImage& image) : Image<TPixel>()
	{
		convertFrom(image);
	}

	template<PixelConcept TPixel>
	template<ImageConcept TImage>
	constexpr Image<TPixel>::Image(const TImage& image, const PixelConversionFunction<typename TImage::PixelType, TPixel>& conversionFunc) : Image<TPixel>()
	{
		convertFrom(image, conversionFunc);
	}

	template<PixelConcept TPixel>
	constexpr Image<TPixel>::Image(const Image<TPixel>& image) : Image<TPixel>()
	{
		_copyFrom(image);
	}

	template<PixelConcept TPixel>
	constexpr Image<TPixel>::Image(Image<TPixel>&& image) : Image<TPixel>()
	{
		_moveFrom(std::forward<Image<TPixel>>(image));
	}

	template<PixelConcept TPixel>
	constexpr Image<TPixel>* Image<TPixel>::constructAroundMemory(uint64_t width, uint64_t height, TPixel* memory)
	{
		assert(width != 0);
		assert(height != 0);

		Image<TPixel>* image = new Image<TPixel>();

		image._width = width;
		image._height = height;
		image._pixels = memory;
		image._owner = false;

		return image;
	}

	template<PixelConcept TPixel>
	constexpr Image<TPixel>& Image<TPixel>::operator=(const Image<TPixel>& image)
	{
		_copyFrom(image);
		return *this;
	}

	template<PixelConcept TPixel>
	constexpr Image<TPixel>& Image<TPixel>::operator=(Image<TPixel>&& image)
	{
		_moveFrom(std::forward<Image<TPixel>>(image));
		return *this;
	}

	template<PixelConcept TPixel>
	constexpr void Image<TPixel>::loadFromFile(const std::filesystem::path& path)
	{
		uint8_t swizzling[TPixel::componentCount];
		_djv::defaultLoadSwizzling<TPixel::componentCount>(swizzling);
		_loadFromFile(path, swizzling);
	}

	template<PixelConcept TPixel>
	constexpr void Image<TPixel>::loadFromFile(const std::filesystem::path& path, const uint8_t* swizzling)
	{
		_loadFromFile(path, swizzling);
	}

	template<PixelConcept TPixel>
	constexpr void Image<TPixel>::loadFromFile(const std::filesystem::path& path, const std::initializer_list<uint8_t>& swizzling)
	{
		assert(swizzling.size() == TPixel::componentCount);
		_loadFromFile(path, swizzling.begin());
	}

	template<PixelConcept TPixel>
	constexpr void Image<TPixel>::loadFromStream(const std::istream& stream, ImageFormat format)
	{
		uint8_t swizzling[TPixel::componentCount];
		_djv::defaultLoadSwizzling<TPixel::componentCount>(swizzling);
		_loadFromStream(stream, format, swizzling);
	}

	template<PixelConcept TPixel>
	constexpr void Image<TPixel>::loadFromStream(const std::istream& stream, ImageFormat format, const uint8_t* swizzling)
	{
		_loadFromStream(stream, format, swizzling);
	}

	template<PixelConcept TPixel>
	constexpr void Image<TPixel>::loadFromStream(const std::istream& stream, ImageFormat format, const std::initializer_list<uint8_t>& swizzling)
	{
		assert(swizzling.size() == TPixel::componentCount);
		_loadFromStream(stream, format, swizzling.begin());
	}

	template<PixelConcept TPixel>
	template<ImageConcept TImage>
	constexpr void Image<TPixel>::convertFrom(const TImage& image)
	{
		convertFrom(image, _djv::defaultConversionFunction<typename TImage::PixelType, TPixel>);
	}

	template<PixelConcept TPixel>
	template<ImageConcept TImage>
	constexpr void Image<TPixel>::convertFrom(const TImage& image, const PixelConversionFunction<typename TImage::PixelType, TPixel>& conversionFunc)
	{
		if (_width != image._width || _height != image._height)
		{
			_destroy();
			_create(image._width, image._height);
		}

		TPixel* it = _pixels;
		const TPixel* const itEnd = it + _width * _height;
		const typename TImage::PixelType* itFrom = image._pixels;

		for (; it != itEnd; ++it, ++itFrom)
		{
			conversionFunc(*itFrom, *it);
		}
	}

	template<PixelConcept TPixel>
	template<scp::InterpolationMethod IMethod>
	constexpr void Image<TPixel>::resize(const Image<TPixel>& image)
	{
		// Simple copy

		if (image._width == _width && image._height == _height)
		{
			*this = image;
		}

		// Downsample

		else if (image._width >= _width && image._width % _width == 0 && image._height >= _height && image._height % _height == 0)
		{
			const uint64_t xStep = image._width / _width;
			const uint64_t yStep = image._height / _height - 1;

			TPixel* it = _pixels;
			const TPixel* itImage = image._pixels;

			for (uint64_t i = 0; i < _height; ++i)
			{
				for (uint64_t j = 0; j < _width; ++j, ++it, itImage += xStep)
				{
					*it = *itImage;
				}

				itImage += yStep * image._width;
			}
		}

		else
		{
			if constexpr (IMethod == scp::InterpolationMethod::Nearest)
			{
				// Upsample

				if (_width > image._width && _width % image._width == 0 && _height > image._height && _height % image._height == 0)
				{
					const uint64_t xRepeat = _width / image._width;
					const uint64_t yRepeat = _height / image._height - 1;

					TPixel* it = _pixels;
					const TPixel* itImage = image._pixels;

					for (uint64_t i = 0; i < image._height; ++i)
					{
						for (uint64_t j = 0; j < image._width; ++j, ++itImage, it += xRepeat)
						{
							std::fill_n(it, xRepeat, *itImage);
						}

						for (uint64_t k = 0; k < yRepeat; ++k, it += _width)
						{
							std::copy(it - _width, it, it);
						}
					}

					return;
				}

				// X-Downsample & Y-Upsample

				else if (image._width > _width && image._width % _width == 0 && _height > image._height && _height % image._height == 0)
				{
					const uint64_t xStep = image._width / _width;
					const uint64_t yRepeat = _height / image._height - 1;

					TPixel* it = _pixels;
					const TPixel* itImage = image._pixels;

					for (uint64_t i = 0; i < image._height; ++i)
					{
						for (uint64_t j = 0; j < _width; ++j, ++it, itImage += xStep)
						{
							*it = *itImage;
						}

						for (uint64_t k = 0; k < yRepeat; ++k, it += _width)
						{
							std::copy(it - _width, it, it);
						}
					}

					return;
				}

				// X-Upsample & Y-Downsample

				else if (_width > image._width && _width % image._width == 0 && image._height > _height && image._height % _height == 0)
				{
					const uint64_t xRepeat = _width / image._width;
					const uint64_t yStep = image._height / _height - 1;

					TPixel* it = _pixels;
					const TPixel* itImage = image._pixels;

					for (uint64_t i = 0; i < _height; ++i)
					{
						for (uint64_t j = 0; j < image._width; ++j, ++itImage, it += xRepeat)
						{
							std::fill_n(it, xRepeat, *itImage);
						}

						itImage += yStep * image._width;
					}

					return;
				}
			}

			// Pure resize (with interpolation...)

			scp::Tensor<TPixel>* imageTensor = scp::Tensor<TPixel>::createAroundMemory({ image._height, image._width }, const_cast<TPixel*>(image._pixels));
			scp::Tensor<TPixel>* tensor = scp::Tensor<TPixel>::createAroundMemory({ _height, _width }, _pixels);

			tensor->interpolation<float, IMethod>(*imageTensor);

			delete imageTensor;
			delete tensor;
		}
	}

	template<PixelConcept TPixel>
	constexpr void Image<TPixel>::crop(const Image<TPixel>& image, uint64_t x, uint64_t y)
	{
		assert(x + _width <= image._width);
		assert(y + _height <= image._height);

		const TPixel* itImage = image._pixels + y * image._width + x;
		TPixel* it = _pixels;

		for (uint64_t j = 0; j < _height; ++j, it += _width, itImage += image._width)
		{
			std::copy_n(itImage, _width, it);
		}
	}

	template<PixelConcept TPixel>
	constexpr Image<TPixel>& Image<TPixel>::transpose()
	{
		scp::Matrix<TPixel>* matrix = scp::Matrix<TPixel>::createAroundMemory(_height, _width, _pixels);
		matrix->transpose();
		delete matrix;

		std::swap(_width, _height);

		return *this;
	}

	template<PixelConcept TPixel>
	template<scp::InterpolationMethod IMethod>
	constexpr Image<TPixel>& Image<TPixel>::rotate(float angle, const TPixel& backgroundColor)
	{
		if (std::abs(angle - 0.f) < 1e-3)
		{
			// Nothing.
		}
		else if (std::abs(angle - 0.5f * std::numbers::pi) < 1e-3)
		{
			transpose();
			flip(true, false);
		}
		else if (std::abs(angle - std::numbers::pi) < 1e-3)
		{
			flip(true, true);
		}
		else if (std::abs(angle - 1.5f * std::numbers::pi) < 1e-3)
		{
			flip(true, false);
			transpose();
		}
		else
		{
			const float w = static_cast<float>(_width);
			const float h = static_cast<float>(_height);
			const float ca = std::cos(angle);
			const float sa = -std::sin(angle);
			const float ar = -angle + std::atan(h / w);
			const float car = std::cos(ar);
			const float sar = std::sin(ar);
			const float r = std::sqrt(w * w + h * h);
			const float mx = std::min({ 0.f, -h * sa, w * ca, r * car });
			const float my = std::min({ 0.f, h * ca, w * sa, r * sar });
			const float Mx = std::max({ 0.f, -h * sa, w * ca, r * car });
			const float My = std::max({ 0.f, h * ca, w * sa, r * sar });

			scp::Tensor<TPixel>* tensor = scp::Tensor<TPixel>::createAroundMemory({ _height, _width }, _pixels);

			_width = Mx - mx + 1;
			_height = My - my + 1;

			TPixel* pixels = new TPixel[_width * _height];
			TPixel* it = pixels;

			float indices[2];
			for (uint64_t j = 0; j < _height; ++j)
			{
				for (uint64_t i = 0; i < _width; ++i, ++it)
				{
					indices[0] = (j + my) * ca - (i + mx) * sa;
					indices[1] = (i + mx) * ca + (j + my) * sa;

					if (indices[0] >= 0 && indices[0] < h && indices[1] >= 0 && indices[1] < w)
					{
						*it = tensor->getInterpolated<float, IMethod>(indices);
					}
					else
					{
						*it = backgroundColor;
					}
				}
			}

			delete tensor;
			if (_owner)
			{
				delete[] _pixels;
			}
			_pixels = pixels;
		}

		return *this;
	}

	template<PixelConcept TPixel>
	constexpr Image<TPixel>& Image<TPixel>::flip(bool vertically, bool horizontally)
	{
		uint64_t index;
		uint64_t revIndex;

		if (vertically && horizontally)
		{
			index = 0;
			revIndex = _width * _height - 1;
			for (; index < revIndex; ++index, --revIndex)
			{
				std::swap(_pixels[index], _pixels[revIndex]);
			}
		}
		else if (vertically && !horizontally)
		{
			const uint64_t halfHeight = _height / 2;

			index = 0;
			for (uint64_t j = 0; j < halfHeight; ++j)
			{
				revIndex = (_height - j - 1) * _width;
				for (uint64_t i = 0; i < _width; ++i, ++index, ++revIndex)
				{
					std::swap(_pixels[index], _pixels[revIndex]);
				}
			}
		}
		else if (!vertically && horizontally)
		{
			for (uint64_t j = 0; j < _height; ++j)
			{
				index = j * _width;
				revIndex = (j + 1) * _width - 1;
				for (; index < revIndex; ++index, --revIndex)
				{
					std::swap(_pixels[index], _pixels[revIndex]);
				}
			}
		}

		return *this;
	}

	template<PixelConcept TPixel>
	constexpr Image<TPixel>& Image<TPixel>::draw(const Shape& shape, const TPixel& color)
	{
		auto it = shape.getPixelIterator();

		int64_t x, y;
		while (it->getPixel(x, y))
		{
			if (x >= 0 && y >= 0 && x < _width && y < _height)
			{
				_pixels[x * _height + y] = color;
			}
		}

		return *this;
	}

	template<PixelConcept TPixel>
	constexpr Image<TPixel>& Image<TPixel>::draw(const Shape& shape, const Image<TPixel>& image)
	{
		auto it = shape.getPixelIterator();

		int64_t x, y;
		while (it->getPixel(x, y))
		{
			if (x >= 0 && y >= 0 && x < _width && y < _height && x < image._width && y < image._height)
			{
				_pixels[x * _height + y] = image._pixels[x * _height + y];
			}
		}

		return *this;
	}

	template<PixelConcept TPixel>
	constexpr void Image<TPixel>::saveToFile(const std::filesystem::path& path) const
	{
		uint8_t swizzling[4];
		_djv::defaultSaveSwizzling<TPixel::componentCount>(swizzling);
		_saveToFile(path, swizzling);
	}

	template<PixelConcept TPixel>
	constexpr void Image<TPixel>::saveToFile(const std::filesystem::path& path, const uint8_t* swizzling) const
	{
		_saveToFile(path, swizzling);
	}

	template<PixelConcept TPixel>
	constexpr void Image<TPixel>::saveToFile(const std::filesystem::path& path, const std::initializer_list<uint8_t>& swizzling) const
	{
		assert(swizzling.size() == 4);
		_saveToFile(path, swizzling.begin());
	}

	template<PixelConcept TPixel>
	constexpr void Image<TPixel>::saveToStream(const std::istream& stream, ImageFormat format)
	{
		uint8_t swizzling[4];
		_djv::defaultSaveSwizzling<TPixel::componentCount>(swizzling);
		_saveToStream(stream, format, swizzling);
	}

	template<PixelConcept TPixel>
	constexpr void Image<TPixel>::saveToStream(const std::istream& stream, ImageFormat format, const uint8_t* swizzling)
	{
		_saveToStream(stream, format, swizzling);
	}

	template<PixelConcept TPixel>
	constexpr void Image<TPixel>::saveToStream(const std::istream& stream, ImageFormat format, const std::initializer_list<uint8_t>& swizzling)
	{
		assert(swizzling.size() == 4);
		_saveToStream(stream, format, swizzling);
	}

	template<PixelConcept TPixel>
	constexpr TPixel& Image<TPixel>::operator[](const std::initializer_list<uint64_t>& indices)
	{
		assert(indices.size() == 2);
		assert(indices.begin()[0] < _width && indices.begin()[1] < _height);

		return _pixels[indices.begin()[1] * _width + indices.begin()[0]];
	}

	template<PixelConcept TPixel>
	constexpr const TPixel& Image<TPixel>::operator[](const std::initializer_list<uint64_t>& indices) const
	{
		assert(indices.size() == 2);
		assert(indices.begin()[0] < _width && indices.begin()[1] < _height);

		return _pixels[indices.begin()[1] * _width + indices.begin()[0]];
	}

	template<PixelConcept TPixel>
	constexpr TPixel* Image<TPixel>::begin()
	{
		return _pixels;
	}

	template<PixelConcept TPixel>
	constexpr TPixel* Image<TPixel>::end()
	{
		return _pixels + _width * _height;
	}

	template<PixelConcept TPixel>
	constexpr const TPixel* Image<TPixel>::begin() const
	{
		return _pixels;
	}

	template<PixelConcept TPixel>
	constexpr const TPixel* Image<TPixel>::end() const
	{
		return _pixels + _width * _height;
	}

	template<PixelConcept TPixel>
	constexpr const TPixel* Image<TPixel>::cbegin() const
	{
		return _pixels;
	}

	template<PixelConcept TPixel>
	constexpr const TPixel* Image<TPixel>::cend() const
	{
		return _pixels + _width * _height;
	}

	template<PixelConcept TPixel>
	constexpr TPixel* Image<TPixel>::getData()
	{
		return _pixels;
	}

	template<PixelConcept TPixel>
	constexpr const TPixel* Image<TPixel>::getData() const
	{
		return _pixels;
	}

	template<PixelConcept TPixel>
	constexpr const uint64_t& Image<TPixel>::getWidth() const
	{
		return _width;
	}

	template<PixelConcept TPixel>
	constexpr const uint64_t& Image<TPixel>::getHeight() const
	{
		return _height;
	}

	template<PixelConcept TPixel>
	constexpr bool Image<TPixel>::isValid() const
	{
		return _pixels;
	}

	template<PixelConcept TPixel>
	constexpr Image<TPixel>::~Image()
	{
		_destroy();
	}

	template<PixelConcept TPixel>
	constexpr void Image<TPixel>::_create(uint64_t width, uint64_t height)
	{
		assert(width != 0);
		assert(height != 0);

		_width = width;
		_height = height;
		_pixels = new TPixel[_width * _height];
		_owner = true;
	}

	template<PixelConcept TPixel>
	constexpr void Image<TPixel>::_copyFrom(const Image<TPixel>& image)
	{
		if (_width != image._width || _height != image._height)
		{
			_destroy();
			_create(image._width, image._height);
		}

		std::copy_n(image._pixels, _width * _height, _pixels);
	}

	template<PixelConcept TPixel>
	constexpr void Image<TPixel>::_moveFrom(Image<TPixel>&& image)
	{
		if (!_owner || !image._owner)
		{
			_copyFrom(image);
			return;
		}

		_destroy();

		_width = image._width;
		_height = image._height;
		_pixels = image._pixels;
	}

	template<PixelConcept TPixel>
	constexpr void Image<TPixel>::_destroy()
	{
		if (_pixels && _owner)
		{
			delete[] _pixels;
		}

		_width = 0;
		_height = 0;
		_pixels = nullptr;
		_owner = true;
	}

	template<PixelConcept TPixel>
	constexpr bool Image<TPixel>::_extensionToImageFormat(const std::filesystem::path& extension, ImageFormat& imageFormat)
	{
		static const std::unordered_map<std::filesystem::path, ImageFormat> extensionToImageFormat = {
			{ ".png", ImageFormat::Png },
			{ ".pbm", ImageFormat::Pbm },
			{ ".pgm", ImageFormat::Pgm },
			{ ".ppm", ImageFormat::Ppm },
			{ ".pnm", ImageFormat::Pnm }
		};

		auto it = extensionToImageFormat.find(extension);

		if (it == extensionToImageFormat.end())
		{
			return false;
		}
		else
		{
			imageFormat = it->second;
			return true;
		}
	}

	template<PixelConcept TPixel>
	constexpr void Image<TPixel>::_loadFromFile(const std::filesystem::path& path, const uint8_t* swizzling)
	{
		if (!std::filesystem::exists(path))
		{
			return;
		}

		std::ifstream stream(path, std::ios::in | std::ios::binary);
		if (!stream)
		{
			return;
		}

		ImageFormat imageFormat;
		if (_extensionToImageFormat(path.extension(), imageFormat))
		{
			_loadFromStream(stream, imageFormat, swizzling);
		}
	}

	template<PixelConcept TPixel>
	constexpr void Image<TPixel>::_loadFromStream(std::istream& stream, ImageFormat format, const uint8_t* swizzling)
	{
		assert(stream);

		for (uint8_t i = 0; i < TPixel::componentCount; ++i)
		{
			assert(swizzling[i] < 4 || swizzling[i] == UINT8_MAX);
		}

		(this->*(_imageFormatToLoadFunc[static_cast<size_t>(format)]))(stream, swizzling);
	}

	template<PixelConcept TPixel>
	constexpr void Image<TPixel>::_loadFromPng(std::istream& stream, const uint8_t* swizzling)
	{
		dsk::fmt::PngIStream pngIStream;
		pngIStream.setSource(stream);

		// TODO: Repair PNG in Diskon and replace this by the commented block below (stream read instead of buffered read)
		// TODO: Do the same for _saveToPng

		dsk::fmt::png::File<TComponent> pngFile;
		pngIStream.readFile(pngFile);

		if (_width != pngFile.header.imageStructure.width || _height != pngFile.header.imageStructure.height)
		{
			_destroy();
			_create(pngFile.header.imageStructure.width, pngFile.header.imageStructure.height);
		}

		const uint64_t n = _width * _height;
		TComponent* buffer = pngFile.pixels.data();

		for (uint64_t i = 0; i < n; ++i, buffer += 4)
		{
			for (uint8_t j = 0; j < TPixel::componentCount; ++j)
			{
				if (swizzling[j] == UINT8_MAX)
				{
					_pixels[i][j] = colors::black<TComponent, TPixel::componentCount>[j];
				}
				else
				{
					_pixels[i][j] = buffer[swizzling[j]];
				}
			}
		}

		// dsk::fmt::png::Header pngHeader;
		// pngIStream.readHeader(pngHeader);
		// 
		// _create(pngHeader.imageStructure.width, pngHeader.imageStructure.height);
		// 
		// const uint64_t n = _width * _height;
		// TComponent buffer[4];
		// 
		// // TODO: Check if something must be done with metadatas...
		// // TODO: Deinterlacing
		// 
		// for (uint64_t i = 0; i < n; ++i)
		// {
		// 	pngIStream.readPixels(buffer, 1);
		// 
		// 	for (uint8_t j = 0; j < TPixel::componentCount; ++j)
		// 	{
		// 		if (swizzling[j] == UINT8_MAX)
		// 		{
		// 			_pixels[i][j] = colors::black<TComponent, TPixel::componentCount>[j];
		// 		}
		// 		else
		// 		{
		// 			_pixels[i][j] = buffer[swizzling[j]];
		// 		}
		// 	}
		// }
		// 
		// dsk::fmt::png::Ending pngEnding;
		// pngIStream.readEnding(pngEnding);
	}

	template<PixelConcept TPixel>
	template<ImageFormat Format>
	constexpr void Image<TPixel>::_loadFromPnm(std::istream& stream, const uint8_t* swizzling)
	{
		dsk::fmt::PnmIStream pnmIStream;
		pnmIStream.setSource(stream);

		dsk::fmt::pnm::Header pnmHeader;
		pnmIStream.readHeader(pnmHeader);

		switch (Format)
		{
			case ImageFormat::Pbm:
			{
				if (pnmHeader.format != dsk::fmt::pnm::Format::PlainPBM && pnmHeader.format != dsk::fmt::pnm::Format::RawPBM)
				{
					return;
				}

				break;
			}
			case ImageFormat::Pgm:
			{
				if (pnmHeader.format != dsk::fmt::pnm::Format::PlainPGM && pnmHeader.format != dsk::fmt::pnm::Format::RawPGM)
				{
					return;
				}

				break;
			}
			case ImageFormat::Ppm:
			{
				if (pnmHeader.format != dsk::fmt::pnm::Format::PlainPPM && pnmHeader.format != dsk::fmt::pnm::Format::RawPPM)
				{
					return;
				}

				break;
			}
		}

		if (_width != pnmHeader.width || _height != pnmHeader.height)
		{
			_destroy();
			_create(pnmHeader.width, pnmHeader.height);
		}

		const float ratio = 2.f / pnmHeader.maxSampleVal.value();
		const uint64_t n = _width * _height;
		uint16_t buffer[3];

		for (uint64_t i = 0; i < n; ++i)
		{
			pnmIStream.readPixels(buffer, 1);

			for (uint64_t j = 0; j < TPixel::componentCount; ++j)
			{
				if (swizzling[j] == UINT8_MAX)
				{
					_pixels[i][j] = colors::black<TComponent, TPixel::componentCount>[j];
				}
				else if (swizzling[j] == 3)
				{
					_pixels[i][j] = colors::white<TComponent, TPixel::componentCount>[j];
				}
				else
				{
					switch (pnmHeader.format)
					{
						case dsk::fmt::pnm::Format::PlainPBM:
						case dsk::fmt::pnm::Format::RawPBM:
						{
							_pixels[i][j] = buffer[0] ? colors::white<TComponent, TPixel::componentCount>[j] : colors::black<TComponent, TPixel::componentCount>[j];
							break;
						}
						case dsk::fmt::pnm::Format::PlainPGM:
						case dsk::fmt::pnm::Format::RawPGM:
						{
							_pixels[i].set<float>(j, buffer[0] * ratio - 1.f);
							break;
						}
						case dsk::fmt::pnm::Format::PlainPPM:
						case dsk::fmt::pnm::Format::RawPPM:
						{
							_pixels[i].set<float>(j, buffer[swizzling[j]] * ratio - 1.f);
							break;
						}
					}
				}
			}
		}
	}

	template<PixelConcept TPixel>
	constexpr void Image<TPixel>::_saveToFile(const std::filesystem::path& path, const uint8_t* swizzling) const
	{
		std::ofstream stream(path, std::ios::out | std::ios::binary);
		if (!stream)
		{
			return;
		}

		ImageFormat imageFormat;
		if (_extensionToImageFormat(path.extension(), imageFormat))
		{
			_saveToStream(stream, imageFormat, swizzling);
		}
	}

	template<PixelConcept TPixel>
	constexpr void Image<TPixel>::_saveToStream(std::ostream& stream, ImageFormat format, const uint8_t* swizzling) const
	{
		assert(stream);
		assert(swizzling[0] < TPixel::componentCount || swizzling[0] == UINT8_MAX);
		assert(swizzling[1] < TPixel::componentCount || swizzling[1] == UINT8_MAX);
		assert(swizzling[2] < TPixel::componentCount || swizzling[2] == UINT8_MAX);
		assert(swizzling[3] < TPixel::componentCount || swizzling[3] == UINT8_MAX);

		(this->*(_imageFormatToSaveFunc[static_cast<size_t>(format)]))(stream, swizzling);
	}

	template<PixelConcept TPixel>
	constexpr void Image<TPixel>::_saveToPng(std::ostream& stream, const uint8_t* swizzling) const
	{
		// TODO (see _loadFromPng)

		dsk::fmt::PngOStream pngOStream;
		pngOStream.setDestination(stream);

		dsk::fmt::png::File<TComponent> pngFile;
		pngFile.header.imageStructure.width = _width;
		pngFile.header.imageStructure.height = _height;
		pngFile.header.imageStructure.bitDepth = 8;
		pngFile.header.imageStructure.colorType = dsk::fmt::png::ColorType::TrueColorAlpha;
		pngFile.header.imageStructure.compressionMethod = dsk::fmt::png::CompressionMethod::Deflate;
		pngFile.header.imageStructure.filterMethod = dsk::fmt::png::FilterMethod::Default;
		pngFile.header.imageStructure.interlaceMethod = dsk::fmt::png::InterlaceMethod::NoInterlace;

		const uint64_t n = _width * _height;
		pngFile.pixels.resize(4 * n);
		TComponent* buffer = pngFile.pixels.data();

		for (uint64_t i = 0; i < n; ++i, buffer += 4)
		{
			buffer[0] = swizzling[0] == UINT8_MAX ? colors::black<TComponent, TPixel::componentCount>[0] : _pixels[i][swizzling[0]];
			buffer[1] = swizzling[1] == UINT8_MAX ? colors::black<TComponent, TPixel::componentCount>[1] : _pixels[i][swizzling[1]];
			buffer[2] = swizzling[2] == UINT8_MAX ? colors::black<TComponent, TPixel::componentCount>[2] : _pixels[i][swizzling[2]];
			buffer[3] = swizzling[3] == UINT8_MAX ? colors::white<TComponent, TPixel::componentCount>[3] : _pixels[i][swizzling[3]];
		}

		pngOStream.writeFile(pngFile);
	}

	template<PixelConcept TPixel>
	template<ImageFormat Format>
	constexpr void Image<TPixel>::_saveToPnm(std::ostream& stream, const uint8_t* swizzling) const
	{
		dsk::fmt::PnmOStream pnmOStream;
		pnmOStream.setDestination(stream);

		const uint64_t n = _width * _height;

		dsk::fmt::pnm::Header pnmHeader;
		pnmHeader.width = _width;
		pnmHeader.height = _height;
		pnmHeader.maxSampleVal.emplace(65535);

		switch (Format)
		{
			case ImageFormat::Pbm:
			{
				pnmHeader.format = dsk::fmt::pnm::Format::PlainPBM;
				break;
			}
			case ImageFormat::Pgm:
			{
				pnmHeader.format = dsk::fmt::pnm::Format::PlainPGM;
				break;
			}
			case ImageFormat::Ppm:
			{
				pnmHeader.format = dsk::fmt::pnm::Format::PlainPPM;
				break;
			}
			case ImageFormat::Pnm:
			{
				pnmHeader.format = dsk::fmt::pnm::Format::PlainPPM;
				break;
			}
		}

		pnmOStream.writeHeader(pnmHeader);

		uint16_t buffer[3];
		for (uint64_t i = 0; i < n; ++i)
		{
			switch (pnmHeader.format)
			{
				case dsk::fmt::pnm::Format::PlainPBM:
				case dsk::fmt::pnm::Format::PlainPGM:
				{
					if (swizzling[0] == UINT8_MAX)
					{
						buffer[0] = 0;
					}
					else
					{
						_pixels[i].get(swizzling[0], buffer[0]);
					}

					break;
				}
				case dsk::fmt::pnm::Format::PlainPPM:
				{
					for (uint8_t j = 0; j < 3; ++j)
					{
						if (swizzling[j] == UINT8_MAX)
						{
							buffer[j] = 0;
						}
						else
						{
							_pixels[i].get(swizzling[j], buffer[j]);
						}
					}

					break;
				}
			}

			pnmOStream.writePixels(buffer, 1);
		}
	}
}
