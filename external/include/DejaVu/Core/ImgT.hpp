#pragma once

#include <DejaVu/DejaVu.hpp>

namespace djv
{
	template<uint64_t N>
	PixelBase<N>::PixelBase(float x)
	{
		std::fill<float*, float>(_components, _components + N, x);
	}

	template<uint64_t N>
	PixelBase<N>::PixelBase(float r, float g, float b, float a)
	{
		if constexpr (N >= 1)
		{
			_components[0] = r;
		}
		if constexpr (N >= 2)
		{
			_components[1] = g;
		}
		if constexpr (N >= 3)
		{
			_components[2] = b;
		}
		if constexpr (N >= 4)
		{
			_components[3] = a;
		}
		if constexpr (N >= 5)
		{
			std::fill<float*, float>(_components + 4, _components + N, 0.f);
		}
	}

	template<uint64_t N>
	float& PixelBase<N>::operator[](uint64_t i)
	{
		assert(i < N);
		return _components[i];
	}

	template<uint64_t N>
	const float& PixelBase<N>::operator[](uint64_t i) const
	{
		assert(i < N);
		return _components[i];
	}

	template<uint64_t N>
	PixelBase<N>& PixelBase<N>::operator+=(const PixelBase<N>& pixel)
	{
		for (uint64_t i = 0; i < N; i++)
		{
			_components[i] += pixel._components[i];
		}

		return *this;
	}

	template<uint64_t N>
	PixelBase<N>& PixelBase<N>::operator-=(const PixelBase<N>& pixel)
	{
		for (uint64_t i = 0; i < N; i++)
		{
			_components[i] -= pixel._components[i];
		}

		return *this;
	}

	template<uint64_t N>
	PixelBase<N>& PixelBase<N>::operator*=(const PixelBase<N>& pixel)
	{
		for (uint64_t i = 0; i < N; i++)
		{
			_components[i] *= pixel._components[i];
		}

		return *this;
	}

	template<uint64_t N>
	PixelBase<N>& PixelBase<N>::operator/=(const PixelBase<N>& pixel)
	{
		for (uint64_t i = 0; i < N; i++)
		{
			_components[i] /= pixel._components[i];
		}

		return *this;
	}

	template<uint64_t N>
	PixelBase<N>& PixelBase<N>::operator%=(const PixelBase<N>& pixel)
	{
		for (uint64_t i = 0; i < N; i++)
		{
			_components[i] %= pixel._components[i];
		}

		return *this;
	}

	template<uint64_t N>
	PixelBase<N>& PixelBase<N>::operator+=(float x)
	{
		for (uint64_t i = 0; i < N; i++)
		{
			_components[i] += x;
		}

		return *this;
	}

	template<uint64_t N>
	PixelBase<N>& PixelBase<N>::operator-=(float x)
	{
		for (uint64_t i = 0; i < N; i++)
		{
			_components[i] -= x;
		}

		return *this;
	}

	template<uint64_t N>
	PixelBase<N>& PixelBase<N>::operator*=(float x)
	{
		for (uint64_t i = 0; i < N; i++)
		{
			_components[i] *= x;
		}

		return *this;
	}

	template<uint64_t N>
	PixelBase<N>& PixelBase<N>::operator/=(float x)
	{
		for (uint64_t i = 0; i < N; i++)
		{
			_components[i] /= x;
		}

		return *this;
	}

	template<uint64_t N>
	PixelBase<N>& PixelBase<N>::operator%=(float x)
	{
		for (uint64_t i = 0; i < N; i++)
		{
			_components[i] %= x;
		}

		return *this;
	}

	template<uint64_t N>
	void PixelBase<N>::getRGBA(float& red, float& green, float& blue, float& alpha) const
	{
		if constexpr (N >= 1)
		{
			red = _components[0];
		}
		else
		{
			red = 0.f;
		}

		if constexpr (N >= 2)
		{
			green = _components[1];
		}
		else
		{
			green = red;
		}

		if constexpr (N >= 3)
		{
			blue = _components[2];
		}
		else
		{
			blue = green;
		}

		if constexpr (N >= 4)
		{
			alpha = _components[3];
		}
		else
		{
			alpha = 1.f;
		}
	}

	template<uint64_t N>
	PixelBase<N> operator+(const PixelBase<N>& pixelA, const PixelBase<N>& pixelB)
	{
		PixelBase<N> pixelC(pixelA);
		pixelC += pixelB;

		return pixelC;
	}

	template<uint64_t N>
	PixelBase<N>&& operator+(PixelBase<N>&& pixelA, const PixelBase<N>& pixelB)
	{
		pixelA += pixelB;
		return std::move(pixelA);
	}

	template<uint64_t N>
	PixelBase<N>&& operator+(const PixelBase<N>& pixelA, PixelBase<N>&& pixelB)
	{
		pixelB += pixelA;
		return std::move(pixelB);
	}

	template<uint64_t N>
	PixelBase<N>&& operator+(PixelBase<N>&& pixelA, PixelBase<N>&& pixelB)
	{
		pixelA += pixelB;
		return std::move(pixelA);
	}

	template<uint64_t N>
	PixelBase<N> operator-(const PixelBase<N>& pixelA, const PixelBase<N>& pixelB)
	{
		PixelBase<N> pixelC(pixelA);
		pixelC -= pixelB;

		return pixelC;
	}

	template<uint64_t N>
	PixelBase<N>&& operator-(PixelBase<N>&& pixelA, const PixelBase<N>& pixelB)
	{
		pixelA -= pixelB;
		return std::move(pixelA);
	}

	template<uint64_t N>
	PixelBase<N> operator*(const PixelBase<N>& pixelA, const PixelBase<N>& pixelB)
	{
		PixelBase<N> pixelC(pixelA);
		pixelC *= pixelB;

		return pixelC;
	}

	template<uint64_t N>
	PixelBase<N>&& operator*(PixelBase<N>&& pixelA, const PixelBase<N>& pixelB)
	{
		pixelA *= pixelB;
		return std::move(pixelA);
	}

	template<uint64_t N>
	PixelBase<N>&& operator*(const PixelBase<N>& pixelA, PixelBase<N>&& pixelB)
	{
		pixelB *= pixelA;
		return std::move(pixelB);
	}

	template<uint64_t N>
	PixelBase<N>&& operator*(PixelBase<N>&& pixelA, PixelBase<N>&& pixelB)
	{
		pixelA *= pixelB;
		return std::move(pixelA);
	}

	template<uint64_t N>
	PixelBase<N> operator/(const PixelBase<N>& pixelA, const PixelBase<N>& pixelB)
	{
		PixelBase<N> pixelC(pixelA);
		pixelC /= pixelB;

		return pixelC;
	}

	template<uint64_t N>
	PixelBase<N>&& operator/(PixelBase<N>&& pixelA, const PixelBase<N>& pixelB)
	{
		pixelA /= pixelB;
		return std::move(pixelA);
	}

	template<uint64_t N>
	PixelBase<N> operator%(const PixelBase<N>& pixelA, const PixelBase<N>& pixelB)
	{
		PixelBase<N> pixelC(pixelA);
		pixelC %= pixelB;

		return pixelC;
	}

	template<uint64_t N>
	PixelBase<N>&& operator%(PixelBase<N>&& pixelA, const PixelBase<N>& pixelB)
	{
		pixelA %= pixelB;
		return std::move(pixelA);
	}

	template<uint64_t N>
	PixelBase<N> operator+(const PixelBase<N>& pixel, float x)
	{
		PixelBase<N> result(pixel);
		result += x;

		return result;
	}

	template<uint64_t N>
	PixelBase<N>&& operator+(PixelBase<N>&& pixel, float x)
	{
		pixel += x;
		return std::move(pixel);
	}

	template<uint64_t N>
	PixelBase<N> operator+(float x, const PixelBase<N>& pixel)
	{
		PixelBase<N> result(pixel);
		result += x;

		return result;
	}

	template<uint64_t N>
	PixelBase<N>&& operator+(float x, PixelBase<N>&& pixel)
	{
		pixel += x;
		return std::move(pixel);
	}

	template<uint64_t N>
	PixelBase<N> operator-(const PixelBase<N>& pixel, float x)
	{
		PixelBase<N> result(pixel);
		result -= x;

		return result;
	}

	template<uint64_t N>
	PixelBase<N>&& operator-(PixelBase<N>&& pixel, float x)
	{
		pixel -= x;
		return std::move(pixel);
	}

	template<uint64_t N>
	PixelBase<N> operator*(const PixelBase<N>& pixel, float x)
	{
		PixelBase<N> result(pixel);
		result *= x;

		return result;
	}

	template<uint64_t N>
	PixelBase<N>&& operator*(PixelBase<N>&& pixel, float x)
	{
		pixel *= x;
		return std::move(pixel);
	}

	template<uint64_t N>
	PixelBase<N> operator*(float x, const PixelBase<N>& pixel)
	{
		PixelBase<N> result(pixel);
		result *= x;

		return result;
	}

	template<uint64_t N>
	PixelBase<N>&& operator*(float x, PixelBase<N>&& pixel)
	{
		pixel *= x;
		return std::move(pixel);
	}

	template<uint64_t N>
	PixelBase<N> operator/(const PixelBase<N>& pixel, float x)
	{
		PixelBase<N> result(pixel);
		result /= x;

		return result;
	}

	template<uint64_t N>
	PixelBase<N>&& operator/(PixelBase<N>&& pixel, float x)
	{
		pixel /= x;
		return std::move(pixel);
	}

	template<uint64_t N>
	PixelBase<N> operator%(const PixelBase<N>& pixel, float x)
	{
		PixelBase<N> result(pixel);
		result %= x;

		return result;
	}

	template<uint64_t N>
	PixelBase<N>&& operator%(PixelBase<N>&& pixel, float x)
	{
		pixel %= x;
		return std::move(pixel);
	}
}

namespace std
{
	template<uint64_t N>
	float norm(const djv::PixelBase<N>& pixel)
	{
		float s = 0.f;
		for (uint64_t i = 0; i < N; ++i)
		{
			s += pixel[i] * pixel[i];
		}

		return s;
	}

	template<uint64_t N>
	float abs(const djv::PixelBase<N>& pixel)
	{
		return sqrt(norm(pixel));
	}
}

namespace djv
{
	template<typename PixelType>
	Img<PixelType>::Img() :
		_data(nullptr)
	{
	}

	template<typename PixelType>
	Img<PixelType>::Img(uint64_t width, uint64_t height, PixelType pixelInit) :
		_data(std::make_unique<scp::Mat<PixelType>>(width, height, pixelInit))
	{
	}

	template<typename PixelType>
	Img<PixelType>::Img(const std::string& filename, bool transpose, bool flipHorizontally, bool flipVertically) : Img<PixelType>()
	{
		int w, h;
		uint8_t* image = stbi_load(filename.c_str(), &w, &h, nullptr, STBI_rgb_alpha);
		if (image == nullptr)
		{
			throw std::runtime_error("Couldn't open '" + filename + "'.");
		}

		uint64_t imageWidth = w, imageHeight = h;
		if (transpose)
		{
			std::swap(w, h);
		}

		_data = std::make_unique<scp::Mat<PixelType>>(imageWidth, imageHeight);

		for (uint64_t i = 0; i < w; ++i)
		{
			for (uint64_t j = 0; j < h; ++j)
			{
				uint64_t x = flipHorizontally && !transpose || flipVertically && transpose ? w - i - 1 : i;
				uint64_t y = flipVertically && !transpose || flipHorizontally && transpose ? h - j - 1 : j;
				uint8_t* it = image + 4 * (x + w * y);

				float r = *it / 255.f;
				float g = *(++it) / 255.f;
				float b = *(++it) / 255.f;
				float a = *(++it) / 255.f;

				if (transpose)
				{
					(*_data)[j][i] = PixelType(r, g, b, a);
				}
				else
				{
					(*_data)[i][j] = PixelType(r, g, b, a);
				}
			}
		}

		stbi_image_free(image);
	}

	template<typename PixelType>
	Img<PixelType>::Img(const scp::Mat<PixelType>& mat) :
		_data(std::make_unique<scp::Mat<PixelType>>(mat))
	{
	}

	template<typename PixelType>
	Img<PixelType>::Img(scp::Mat<PixelType>&& mat) :
		_data(std::make_unique<scp::Mat<PixelType>>(std::move(mat)))
	{
	}

	template<typename PixelType>
	Img<PixelType>::Img(const Img<PixelType>& image) :
		_data(std::make_unique<scp::Mat<PixelType>>(*image._data))
	{
	}

	template<typename PixelType>
	Img<PixelType>& Img<PixelType>::operator=(const Img<PixelType>& image)
	{
		_data = std::make_unique<scp::Mat<PixelType>>(*image._data);
	}

	template<typename PixelType>
	scp::Vec<PixelType>& Img<PixelType>::operator[](uint64_t i)
	{
		return (*_data)[i];
	}

	template<typename PixelType>
	const scp::Vec<PixelType>& Img<PixelType>::operator[](uint64_t i) const
	{
		return (*_data)[i];
	}

	template<typename PixelType>
	scp::Mat<float> Img<PixelType>::getComponent(uint64_t i) const
	{
		scp::Mat<float> r(_data->shape(0), _data->shape(1));

		for (uint64_t i = 0; i < r.shape(0); ++i)
		{
			for (uint64_t j = 0; j < r.shape(1); ++j)
			{
				r[i][j] = (*_data)[i][j][i];
			}
		}

		return r;
	}

	template<typename PixelType>
	void Img<PixelType>::setComponent(uint64_t i, const scp::Mat<float>& comp)
	{
		assert(comp.shape(0) == _data->shape(0) && comp.shape(1) == _data->shape(1));
		assert(i < PixelType::componentCount);

		for (uint64_t x = 0; x < comp.shape(0); ++x)
		{
			for (uint64_t y = 0; y < comp.shape(1); ++y)
			{
				(*_data)[x][y][i] = comp[x][y];
			}
		}
	}

	template<typename PixelType>
	void Img<PixelType>::normalize(PixelType min, PixelType max)
	{
		PixelType currentMin = (*_data)[0][0], currentMax = (*_data)[0][0];
		for (uint64_t i = 0; i < _data->shape(0); ++i)
		{
			for (uint64_t j = 0; j < _data->shape(1); ++j)
			{
				for (uint64_t k = 0; k < PixelType::componentCount; ++k)
				{
					if ((*_data)[i][j][k] > currentMax[k])
					{
						currentMax[k] = (*_data)[i][j][k];
					}
					if ((*_data)[i][j][k] < currentMin[k])
					{
						currentMin[k] = (*_data)[i][j][k];
					}
				}
			}
		}

		for (uint64_t k = 0; k < PixelType::componentCount; ++k)
		{
			for (uint64_t i = 0; i < _data->shape(0); ++i)
			{
				for (uint64_t j = 0; j < _data->shape(1); ++j)
				{
					if (currentMin[k] == currentMax[k])
					{
						(*_data)[i][j][k] = currentMin[k] < min[k] ? min[k] : max[k];
					}
					else
					{
						(*_data)[i][j][k] = min[k] + (max[k] - min[k])*((*_data)[i][j][k] - currentMin[k])/(currentMax[k] - currentMin[k]);
					}
				}
			}
		}
	}

	template<typename PixelType>
	template<typename T>
	Img<T> Img<PixelType>::castToPixelType() const
	{
		scp::Mat<T> mat(_data->shape(0), _data->shape(1));
		for (uint64_t i = 0; i < _data->shape(0); ++i)
		{
			for (uint64_t j = 0; j < _data->shape(1); ++j)
			{
				float r, g, b, a;
				(*_data)[i][j].getRGBA(r, g, b, a);

				mat[i][j] = T(r, g, b, a);
			}
		}

		return Img<T>(mat);
	}

	template<typename PixelType>
	void Img<PixelType>::saveToFile(const std::string& filename) const
	{
		assert(filename.size() > 4);

		uint64_t w = _data->shape(0), h = _data->shape(1);
		std::vector<uint8_t> image(4 * _data->globalLength());
		std::vector<uint8_t>::iterator it = image.begin();

		for (uint64_t j(0); j < h; ++j)
		{
			for (uint64_t i(0); i < w; ++i)
			{
				float r, g, b, a;
				(*_data)[i][j].getRGBA(r, g, b, a);
				*it = 255 * std::max(std::min(r, 1.f), 0.f);
				*(++it) = 255 * std::max(std::min(g, 1.f), 0.f);
				*(++it) = 255 * std::max(std::min(b, 1.f), 0.f);
				*(++it) = 255 * std::max(std::min(a, 1.f), 0.f);
				++it;
			}
		}

		if (filename.substr(filename.size() - 4, 4) == ".bmp")
		{
			stbi_write_bmp(filename.c_str(), w, h, 4, image.data());
			return;
		}
		else if (filename.substr(filename.size() - 4, 4) == ".jpg")
		{
			stbi_write_jpg(filename.c_str(), w, h, 4, image.data(), 95);
			return;
		}
		else if (filename.substr(filename.size() - 4, 4) == ".png")
		{
			stbi_write_png(filename.c_str(), w, h, 4, image.data(), 4 * w);
			return;
		}
		else if (filename.substr(filename.size() - 4, 4) == ".tga")
		{
			stbi_write_tga(filename.c_str(), w, h, 4, image.data());
			return;
		}

		assert(filename.size() > 5);

		if (filename.substr(filename.size() - 5, 5) == ".jpeg")
		{
			stbi_write_jpg(filename.c_str(), w, h, 4, image.data(), 95);
			return;
		}
		else
		{
			throw std::runtime_error("File extension '" + filename + "' unrecognized.");
		}
	}

	template<typename PixelType>
	void Img<PixelType>::resize(uint64_t width, uint64_t height)
	{
		uint64_t w = _data->shape(0);
		uint64_t h = _data->shape(1);

		std::unique_ptr<scp::Mat<PixelType>> oldData = std::move(_data);
		_data = std::make_unique<scp::Mat<PixelType>>(width, height);

		for (uint64_t i = 0; i < width; ++i)
		{
			for (uint64_t j = 0; j < height; ++j)
			{
				uint64_t x = static_cast<float>(i) / width * w;
				uint64_t y = static_cast<float>(j) / height * h;
				(*_data)[i][j] = (*oldData)[x][y];
			}
		}
	}

	template<typename PixelType>
	void Img<PixelType>::scale(float factor)
	{
		uint64_t w = _data->shape(0) * factor;
		uint64_t h = _data->shape(1) * factor;
		assert(w != 0 && h != 0);
		resize(w, h);
	}

	template<typename PixelType>
	void Img<PixelType>::scale(float xFactor, float yFactor)
	{
		uint64_t w = _data->shape(0) * xFactor;
		uint64_t h = _data->shape(1) * yFactor;
		assert(w != 0 && h != 0);
		resize(w, h);
	}

	template<typename PixelType>
	void Img<PixelType>::upsample(uint64_t count)
	{
		assert(count > 1);

		std::unique_ptr<scp::Mat<PixelType>> oldData = std::move(_data);
		_data = std::make_unique<scp::Mat<PixelType>>(oldData->shape(0) * count, oldData->shape(1) * count);

		for (uint64_t i = 0; i < oldData->shape(0); ++i)
		{
			for (uint64_t j = 0; j < oldData->shape(1); ++j)
			{
				uint64_t x = i * count;
				uint64_t y = j * count;
				for (uint64_t p = 0; p < count; ++p)
				{
					for (uint64_t q = 0; q < count; ++q)
					{
						(*_data)[x + p][y + q] = (*oldData)[i][j];
					}
				}
			}
		}
	}

	template<typename PixelType>
	void Img<PixelType>::downsample(uint64_t count)
	{
		assert(count > 1);

		std::unique_ptr<scp::Mat<PixelType>> oldData = std::move(_data);
		_data = std::make_unique<scp::Mat<PixelType>>(oldData->shape(0) / count, oldData->shape(1) / count);

		for (uint64_t i = 0, p = 0; i < _data->shape(0); ++i, p += count)
		{
			for (uint64_t j = 0, q = 0; j < _data->shape(1); ++j, q += count)
			{
				(*_data)[i][j] = (*oldData)[p][q];
			}
		}
	}

	template<typename PixelType>
	void Img<PixelType>::rotate(float angle, PixelType pixelInit)
	{
		float w = _data->shape(0);
		float h = _data->shape(1);
		float ca = std::cos(angle);
		float sa = -std::sin(angle);
		float ar = -angle + std::atan(h / w);
		float car = std::cos(ar);
		float sar = std::sin(ar);
		float r = std::sqrt(w * w + h * h);
		float mx = std::min({ 0.f, -h * sa, w * ca, r * car });
		float my = std::min({ 0.f, h * ca, w * sa, r * sar });
		float Mx = std::max({ 0.f, -h * sa, w * ca, r * car });
		float My = std::max({ 0.f, h * ca, w * sa, r * sar });

		uint64_t wNew = Mx - mx + 1;
		uint64_t hNew = My - my + 1;

		std::unique_ptr<scp::Mat<PixelType>> oldData = std::move(_data);
		_data = std::make_unique<scp::Mat<PixelType>>(wNew, hNew, pixelInit);

		for (uint64_t i = 0; i < wNew; ++i)
		{
			for (uint64_t j = 0; j < hNew; ++j)
			{
				int64_t x = (i + mx) * ca + (j + my) * sa - 1;
				int64_t y = (j + my) * ca - (i + mx) * sa - 1;

				if (x >= 0 && x < oldData->shape(0) && y >= 0 && y < oldData->shape(1))
				{
					(*_data)[i][j] = (*oldData)[x][y];
				}
			}
		}
	}

	template<typename PixelType>
	void Img<PixelType>::flipHorizontally()
	{
		uint64_t h = _data->shape(1) / 2;

		for (uint64_t i = 0; i < _data->shape(0); ++i)
		{
			for (uint64_t j = 0; j < h; ++j)
			{
				std::swap((*_data)[i][j], (*_data)[i][_data->shape(1) - j - 1]);
			}
		}
	}

	template<typename PixelType>
	void Img<PixelType>::flipVertically()
	{
		uint64_t w = _data->shape(0) / 2;

		for (uint64_t i = 0; i < w; ++i)
		{
			for (uint64_t j = 0; j < _data->shape(1); ++j)
			{
				std::swap((*_data)[i][j], (*_data)[_data->shape(0) - i - 1][j]);
			}
		}
	}

	template<typename PixelType>
	void Img<PixelType>::transpose()
	{
		for (uint64_t i = 0; i < _data->shape(0); ++i)
		{
			for (uint64_t j = i + 1; j < _data->shape(1); ++j)
			{
				std::swap((*_data)[i][j], (*_data)[j][i]);
			}
		}
	}

	template<typename PixelType>
	Img<PixelType> Img<PixelType>::subImage(uint64_t x, uint64_t y, uint64_t w, uint64_t h) const
	{
		assert(w > 0 && x + w <= _data->shape(0));
		assert(h > 0 && y + h <= _data->shape(1));

		scp::Mat<PixelType> result(w, h);
		for (uint64_t i = 0, p = x; i < w; ++i, ++p)
		{
			for (uint64_t j = 0, q = y; j < h; ++j, ++q)
			{
				result[i][j] = (*_data)[p][q];
			}
		}

		return result;
	}

	template<typename PixelType>
	Img<PixelType> Img<PixelType>::subImage(const Shape& shape, const PixelType& pixelInit) const
	{
		std::unique_ptr<Shape::PixelIterator> it = shape.getPixelIterator();

		uint64_t w = _data->shape(0), h = _data->shape(1);
		int64_t xMin = w - 1, xMax = 0, yMin = h - 1, yMax = 0;
		int64_t x, y;
		while (it->getPixel(x, y))
		{
			if (x < xMin && x >= 0)
			{
				xMin = x;
			}
			if (x > xMax && x < w)
			{
				xMax = x;
			}
			if (y < yMin && y >= 0)
			{
				yMin = y;
			}
			if (y > yMax && y < h)
			{
				yMax = y;
			}
		}

		scp::Mat<PixelType> result(xMax - xMin + 1, yMax - yMin + 1, pixelInit);
		it = shape.getPixelIterator();
		while (it->getPixel(x, y))
		{
			if (x >= 0 && y >= 0 && x < w && y < h)
			{
				result[x - xMin][y - yMin] = (*_data)[x][y];
			}
		}

		return result;
	}

	template<typename PixelType>
	void Img<PixelType>::draw(const Shape& shape, const PixelType& color)
	{
		std::unique_ptr<Shape::PixelIterator> it = shape.getPixelIterator();

		uint64_t w = _data->shape(0), h = _data->shape(1);
		int64_t x, y;
		while (it->getPixel(x, y))
		{
			if (x >= 0 && y >= 0 && x < w && y < h)
			{
				(*_data)[x][y] = color;
			}
		}
	}

	template<typename PixelType>
	void Img<PixelType>::draw(const Shape& shape, const Img<PixelType>& src)
	{
		std::unique_ptr<Shape::PixelIterator> it = shape.getPixelIterator();

		uint64_t w = _data->shape(0), h = _data->shape(1);
		int64_t x, y;
		while (it->getPixel(x, y))
		{
			if (x >= 0 && y >= 0 && x < w && y < h)
			{
				(*_data)[x][y] = src[x][y];
			}
		}
	}

	template<typename PixelType>
	uint64_t Img<PixelType>::width() const
	{
		return _data->shape(0);
	}

	template<typename PixelType>
	uint64_t Img<PixelType>::height() const
	{
		return _data->shape(1);
	}

	template<typename PixelType>
	const scp::Mat<PixelType>& Img<PixelType>::getData() const
	{
		return *_data;
	}
}
