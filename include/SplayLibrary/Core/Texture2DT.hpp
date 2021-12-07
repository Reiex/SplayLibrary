#pragma once

#include <SplayLibrary/Core/Texture2D.hpp>

namespace spl
{
	template<typename PixelType>
	Texture2D::Texture2D(const djv::Img<PixelType>& image, TextureInternalFormat internalFormat) : Texture2D()
	{
		createNew(image, internalFormat);
	}

	template<typename PixelType>
	void Texture2D::createNew(const djv::Img<PixelType>& image, TextureInternalFormat internalFormat)
	{
		// TODO: Create appropriate buffer

		const uvec2 size(image.width(), image.height());
		const uint8_t components = RawTexture::internalFormatComponents(internalFormat);
		uint8_t* data = new uint8_t[size.x * size.y * std::bitset<8>(components).count()];

		uint64_t k = -1;
		for (uint64_t j = size.y - 1; j != UINT64_MAX; --j)
		{
			for (uint64_t i = 0; i < size.x; ++i)
			{
				float r, g, b, a;
				image[i][j].getRGBA(r, g, b, a);

				switch (components)
				{
					case 1:
					case 16:
					case 32:
					{
						data[++k] = static_cast<uint8_t>(r * 255.99999f);
						break;
					}
					case 3:
					case 48:
					{
						data[++k] = static_cast<uint8_t>(r * 255.99999f);
						data[++k] = static_cast<uint8_t>(g * 255.99999f);
						break;
					}
					case 7:
					{
						data[++k] = static_cast<uint8_t>(r * 255.99999f);
						data[++k] = static_cast<uint8_t>(g * 255.99999f);
						data[++k] = static_cast<uint8_t>(b * 255.99999f);
						break;
					}
					case 15:
					{
						data[++k] = static_cast<uint8_t>(r * 255.99999f);
						data[++k] = static_cast<uint8_t>(g * 255.99999f);
						data[++k] = static_cast<uint8_t>(b * 255.99999f);
						data[++k] = static_cast<uint8_t>(a * 255.99999f);
						break;
					}
					default:
					{
						assert(false);
						break;
					}
				}
			}
		}

		createNew(size, data, internalFormat);
	}

	template<typename PixelType>
	void Texture2D::update(const djv::Img<PixelType>& image, const uvec2& offset)
	{
		// TODO: Create appropriate buffer

		const uvec2 size(image.width(), image.height());
		const uint8_t components = RawTexture::internalFormatComponents(getCreationParams().internalFormat);
		uint8_t* data = new uint8_t[size.x * size.y * std::bitset<8>(components).count()];

		uint64_t k = -1;
		for (uint64_t j = size.y - 1; j != UINT64_MAX; --j)
		{
			for (uint64_t i = 0; i < size.x; ++i)
			{
				float r, g, b, a;
				image[i][j].getRGBA(r, g, b, a);

				switch (components)
				{
				case 1:
				case 16:
				case 32:
				{
					data[++k] = static_cast<uint8_t>(r * 255.99999f);
					break;
				}
				case 3:
				case 48:
				{
					data[++k] = static_cast<uint8_t>(r * 255.99999f);
					data[++k] = static_cast<uint8_t>(g * 255.99999f);
					break;
				}
				case 7:
				{
					data[++k] = static_cast<uint8_t>(r * 255.99999f);
					data[++k] = static_cast<uint8_t>(g * 255.99999f);
					data[++k] = static_cast<uint8_t>(b * 255.99999f);
					break;
				}
				case 15:
				{
					data[++k] = static_cast<uint8_t>(r * 255.99999f);
					data[++k] = static_cast<uint8_t>(g * 255.99999f);
					data[++k] = static_cast<uint8_t>(b * 255.99999f);
					data[++k] = static_cast<uint8_t>(a * 255.99999f);
					break;
				}
				default:
				{
					assert(false);
					break;
				}
				}
			}
		}

		update(size, data, offset);
	}

}