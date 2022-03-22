#pragma once

#include <SplayLibrary/Core/TextureBase.hpp>

#define FLOAT_TO_UINT8(x) static_cast<uint8_t>(std::clamp<float>((x), 0.f, 1.f) * 255.9999847f)
#define FLOAT_TO_UINT16(x) static_cast<uint16_t>(std::clamp<float>((x), 0.f, 1.f) * 65535.98828f)
#define FLOAT_TO_UINT32(x) static_cast<uint32_t>(std::clamp<double>((x), 0.0, 1.1) * 4294967295.999999523)
#define FLOAT_TO_INT8(x) static_cast<int8_t>((std::clamp<float>((x), 0.f, 1.f) - 0.5f) * 255.9999847f)
#define FLOAT_TO_INT16(x) static_cast<uint16_t>((std::clamp<float>((x), 0.f, 1.f) - 0.5f) * 65535.98828f)
#define FLOAT_TO_INT32(x) static_cast<uint32_t>((std::clamp<double>((x), 0.0, 1.0) - 0.5) * 4294967295.999999523)

namespace spl
{
	template<typename PixelType>
	void TextureBase::createDejaVuImgBuffer(const djv::Img<PixelType>& image, TextureInternalFormat internalFormat, void*& buffer, TextureFormat& format, TextureDataType& dataType)
	{
		format = getUsualTextureFormatOf(internalFormat);
		dataType = getUsualTextureDataTypeOf(internalFormat);

		const uvec2 size(image.width(), image.height());

		switch (internalFormat)
		{
			case TextureInternalFormat::R:
				buffer = new uint8_t[size.x * size.y];
				break;
			case TextureInternalFormat::RG:
				buffer = new uint8_t[size.x * size.y * 2];
				break;
			case TextureInternalFormat::RGB:
				buffer = new uint8_t[size.x * size.y * 3];
				break;
			case TextureInternalFormat::RGBA:
				buffer = new uint8_t[size.x * size.y * 4];
				break;
			case TextureInternalFormat::DepthComponent:
				buffer = new float[size.x * size.y];
				break;
			case TextureInternalFormat::StencilIndex:
				buffer = new uint8_t[size.x * size.y];
				break;
			case TextureInternalFormat::DepthStencil:
				buffer = new float[size.x * size.y * 2];
				break;
			case TextureInternalFormat::R8:
				buffer = new uint8_t[size.x * size.y];
				break;
			case TextureInternalFormat::R8_SNORM:
				buffer = new int8_t[size.x * size.y];
				break;
			case TextureInternalFormat::R8I:
				buffer = new int8_t[size.x * size.y];
				break;
			case TextureInternalFormat::R8UI:
				buffer = new uint8_t[size.x * size.y];
				break;
			case TextureInternalFormat::R16:
				buffer = new uint16_t[size.x * size.y];
				break;
			case TextureInternalFormat::R16_SNORM:
				buffer = new int16_t[size.x * size.y];
				break;
			case TextureInternalFormat::R16I:
				buffer = new int16_t[size.x * size.y];
				break;
			case TextureInternalFormat::R16UI:
				buffer = new uint16_t[size.x * size.y];
				break;
			case TextureInternalFormat::R16F:
				buffer = new float[size.x * size.y];
				break;
			case TextureInternalFormat::R32I:
				buffer = new int32_t[size.x * size.y];
				break;
			case TextureInternalFormat::R32UI:
				buffer = new uint32_t[size.x * size.y];
				break;
			case TextureInternalFormat::R32F:
				buffer = new float[size.x * size.y];
				break;
			case TextureInternalFormat::RG8:
				buffer = new uint8_t[size.x * size.y * 2];
				break;
			case TextureInternalFormat::RG8_SNORM:
				buffer = new int8_t[size.x * size.y * 2];
				break;
			case TextureInternalFormat::RG8I:
				buffer = new int8_t[size.x * size.y * 2];
				break;
			case TextureInternalFormat::RG8UI:
				buffer = new uint8_t[size.x * size.y * 2];
				break;
			case TextureInternalFormat::RG16:
				buffer = new uint16_t[size.x * size.y * 2];
				break;
			case TextureInternalFormat::RG16_SNORM:
				buffer = new int16_t[size.x * size.y * 2];
				break;
			case TextureInternalFormat::RG16I:
				buffer = new int16_t[size.x * size.y * 2];
				break;
			case TextureInternalFormat::RG16UI:
				buffer = new uint16_t[size.x * size.y * 2];
				break;
			case TextureInternalFormat::RG16F:
				buffer = new float[size.x * size.y * 2];
				break;
			case TextureInternalFormat::RG32I:
				buffer = new int32_t[size.x * size.y * 2];
				break;
			case TextureInternalFormat::RG32UI:
				buffer = new uint32_t[size.x * size.y * 2];
				break;
			case TextureInternalFormat::RG32F:
				buffer = new float[size.x * size.y * 2];
				break;
			case TextureInternalFormat::R3_G3_B2:
				buffer = new uint8_t[size.x * size.y];
				break;
			case TextureInternalFormat::RGB4:
				buffer = new uint8_t[size.x * size.y * 3];
				break;
			case TextureInternalFormat::RGB5:
				buffer = new uint8_t[size.x * size.y * 3];
				break;
			case TextureInternalFormat::R5_G6_B5:
				buffer = new uint16_t[size.x * size.y];
				break;
			case TextureInternalFormat::RGB8:
				buffer = new uint8_t[size.x * size.y * 3];
				break;
			case TextureInternalFormat::RGB8_SNORM:
				buffer = new int8_t[size.x * size.y * 3];
				break;
			case TextureInternalFormat::RGB8I:
				buffer = new int8_t[size.x * size.y * 3];
				break;
			case TextureInternalFormat::RGB8UI:
				buffer = new uint8_t[size.x * size.y * 3];
				break;
			case TextureInternalFormat::RGB9_E5:
				buffer = new uint16_t[size.x * size.y * 3];
				break;
			case TextureInternalFormat::RGB10:
				buffer = new uint16_t[size.x * size.y * 3];
				break;
			case TextureInternalFormat::R11F_G11F_B10F:
				buffer = new uint16_t[size.x * size.y * 3];
				break;
			case TextureInternalFormat::RGB12:
				buffer = new uint16_t[size.x * size.y * 3];
				break;
			case TextureInternalFormat::RGB16:
				buffer = new uint16_t[size.x * size.y * 3];
				break;
			case TextureInternalFormat::RGB16_SNORM:
				buffer = new int16_t[size.x * size.y * 3];
				break;
			case TextureInternalFormat::RGB16I:
				buffer = new int16_t[size.x * size.y * 3];
				break;
			case TextureInternalFormat::RGB16UI:
				buffer = new uint16_t[size.x * size.y * 3];
				break;
			case TextureInternalFormat::RGB16F:
				buffer = new float[size.x * size.y * 3];
				break;
			case TextureInternalFormat::RGB32I:
				buffer = new int32_t[size.x * size.y * 3];
				break;
			case TextureInternalFormat::RGB32UI:
				buffer = new uint32_t[size.x * size.y * 3];
				break;
			case TextureInternalFormat::RGB32F:
				buffer = new float[size.x * size.y * 3];
				break;
			case TextureInternalFormat::RGBA2:
				buffer = new uint8_t[size.x * size.y * 4];
				break;
			case TextureInternalFormat::RGBA4:
				buffer = new uint16_t[size.x * size.y];
				break;
			case TextureInternalFormat::RGB5_A1:
				buffer = new uint16_t[size.x * size.y];
				break;
			case TextureInternalFormat::RGBA8:
				buffer = new uint8_t[size.x * size.y * 4];
				break;
			case TextureInternalFormat::RGBA8_SNORM:
				buffer = new int8_t[size.x * size.y * 4];
				break;
			case TextureInternalFormat::RGBA8I:
				buffer = new int8_t[size.x * size.y * 4];
				break;
			case TextureInternalFormat::RGBA8UI:
				buffer = new uint8_t[size.x * size.y * 4];
				break;
			case TextureInternalFormat::RGB10_A2:
				buffer = new uint32_t[size.x * size.y];
				break;
			case TextureInternalFormat::RGB10UI_A2UI:
				buffer = new uint32_t[size.x * size.y];
				break;
			case TextureInternalFormat::RGBA12:
				buffer = new uint16_t[size.x * size.y * 4];
				break;
			case TextureInternalFormat::RGBA16:
				buffer = new uint16_t[size.x * size.y * 4];
				break;
			case TextureInternalFormat::RGBA16_SNORM:
				buffer = new int16_t[size.x * size.y * 4];
				break;
			case TextureInternalFormat::RGBA16I:
				buffer = new int16_t[size.x * size.y * 4];
				break;
			case TextureInternalFormat::RGBA16UI:
				buffer = new uint16_t[size.x * size.y * 4];
				break;
			case TextureInternalFormat::RGBA16F:
				buffer = new float[size.x * size.y * 4];
				break;
			case TextureInternalFormat::RGBA32I:
				buffer = new int32_t[size.x * size.y * 4];
				break;
			case TextureInternalFormat::RGBA32UI:
				buffer = new uint32_t[size.x * size.y * 4];
				break;
			case TextureInternalFormat::RGBA32F:
				buffer = new float[size.x * size.y * 4];
				break;
			case TextureInternalFormat::SRGB8:
				buffer = new uint8_t[size.x * size.y * 3];
				break;
			case TextureInternalFormat::SRGBA8:
				buffer = new uint8_t[size.x * size.y * 4];
				break;
			case TextureInternalFormat::DepthComponent16:
				buffer = new uint16_t[size.x * size.y];
				break;
			case TextureInternalFormat::DepthComponent24:
				buffer = new uint32_t[size.x * size.y];
				break;
			case TextureInternalFormat::DepthComponent32:
				buffer = new uint32_t[size.x * size.y];
				break;
			case TextureInternalFormat::DepthComponent32F:
				buffer = new float[size.x * size.y];
				break;
			case TextureInternalFormat::StencilIndex1:
				buffer = new uint8_t[size.x * size.y];
				break;
			case TextureInternalFormat::StencilIndex4:
				buffer = new uint8_t[size.x * size.y];
				break;
			case TextureInternalFormat::StencilIndex8:
				buffer = new uint8_t[size.x * size.y];
				break;
			case TextureInternalFormat::StencilIndex16:
				buffer = new uint16_t[size.x * size.y];
				break;
			case TextureInternalFormat::Depth24_Stencil8:
				buffer = new uint32_t[size.x * size.y];
				break;
			case TextureInternalFormat::Depth32F_Stencil8:
				buffer = new float[size.x * size.y * 2];
				break;
			default:
				assert(false);
				return;
		}
		
		uint64_t k = -1;
		for (uint32_t j = size.y - 1; j != UINT64_MAX; --j)
		{
			for (uint32_t i = 0; i < size.x; ++i)
			{
				float r, g, b, a;
				image[i][j].getRGBA(r, g, b, a);

				switch (dataType)
				{
					case TextureDataType::UnsignedByte:
					{
						uint8_t* data = static_cast<uint8_t*>(buffer);
						switch (format)
						{
							case TextureFormat::R:
							case TextureFormat::iR:
							case TextureFormat::DepthComponent:
							case TextureFormat::StencilIndex:
							{
								data[++k] = FLOAT_TO_UINT8(r);
								break;
							}
							case TextureFormat::RG:
							case TextureFormat::iRG:
							case TextureFormat::DepthStencil:
							{
								data[++k] = FLOAT_TO_UINT8(r);
								data[++k] = FLOAT_TO_UINT8(g);
								break;
							}
							case TextureFormat::RGB:
							case TextureFormat::iRGB:
							{
								data[++k] = FLOAT_TO_UINT8(r);
								data[++k] = FLOAT_TO_UINT8(g);
								data[++k] = FLOAT_TO_UINT8(b);
								break;
							}
							case TextureFormat::RGBA:
							case TextureFormat::iRGBA:
							{
								data[++k] = FLOAT_TO_UINT8(r);
								data[++k] = FLOAT_TO_UINT8(g);
								data[++k] = FLOAT_TO_UINT8(b);
								data[++k] = FLOAT_TO_UINT8(a);
								break;
							}
							default:
							{
								assert(false);
								break;
							}
						}

						break;
					}
					case TextureDataType::Byte:
					{
						int8_t* data = static_cast<int8_t*>(buffer);
						switch (format)
						{
							case TextureFormat::R:
							case TextureFormat::iR:
							case TextureFormat::DepthComponent:
							case TextureFormat::StencilIndex:
							{
								data[++k] = FLOAT_TO_INT8(r);
								break;
							}
							case TextureFormat::RG:
							case TextureFormat::iRG:
							case TextureFormat::DepthStencil:
							{
								data[++k] = FLOAT_TO_INT8(r);
								data[++k] = FLOAT_TO_INT8(g);
								break;
							}
							case TextureFormat::RGB:
							case TextureFormat::iRGB:
							{
								data[++k] = FLOAT_TO_INT8(r);
								data[++k] = FLOAT_TO_INT8(g);
								data[++k] = FLOAT_TO_INT8(b);
								break;
							}
							case TextureFormat::RGBA:
							case TextureFormat::iRGBA:
							{
								data[++k] = FLOAT_TO_INT8(r);
								data[++k] = FLOAT_TO_INT8(g);
								data[++k] = FLOAT_TO_INT8(b);
								data[++k] = FLOAT_TO_INT8(a);
								break;
							}
							default:
							{
								assert(false);
								break;
							}
						}

						break;
					}
					case TextureDataType::UnsignedShort:
					{
						uint16_t* data = static_cast<uint16_t*>(buffer);
						switch (format)
						{
							case TextureFormat::R:
							case TextureFormat::iR:
							case TextureFormat::DepthComponent:
							case TextureFormat::StencilIndex:
							{
								data[++k] = FLOAT_TO_UINT16(r);
								break;
							}
							case TextureFormat::RG:
							case TextureFormat::iRG:
							case TextureFormat::DepthStencil:
							{
								data[++k] = FLOAT_TO_UINT16(r);
								data[++k] = FLOAT_TO_UINT16(g);
								break;
							}
							case TextureFormat::RGB:
							case TextureFormat::iRGB:
							{
								data[++k] = FLOAT_TO_UINT16(r);
								data[++k] = FLOAT_TO_UINT16(g);
								data[++k] = FLOAT_TO_UINT16(b);
								break;
							}
							case TextureFormat::RGBA:
							case TextureFormat::iRGBA:
							{
								data[++k] = FLOAT_TO_UINT16(r);
								data[++k] = FLOAT_TO_UINT16(g);
								data[++k] = FLOAT_TO_UINT16(b);
								data[++k] = FLOAT_TO_UINT16(a);
								break;
							}
							default:
							{
								assert(false);
								break;
							}
						}

						break;
					}
					case TextureDataType::Short:
					{
						int16_t* data = static_cast<int16_t*>(buffer);
						switch (format)
						{
							case TextureFormat::R:
							case TextureFormat::iR:
							case TextureFormat::DepthComponent:
							case TextureFormat::StencilIndex:
							{
								data[++k] = FLOAT_TO_INT16(r);
								break;
							}
							case TextureFormat::RG:
							case TextureFormat::iRG:
							case TextureFormat::DepthStencil:
							{
								data[++k] = FLOAT_TO_INT16(r);
								data[++k] = FLOAT_TO_INT16(g);
								break;
							}
							case TextureFormat::RGB:
							case TextureFormat::iRGB:
							{
								data[++k] = FLOAT_TO_INT16(r);
								data[++k] = FLOAT_TO_INT16(g);
								data[++k] = FLOAT_TO_INT16(b);
								break;
							}
							case TextureFormat::RGBA:
							case TextureFormat::iRGBA:
							{
								data[++k] = FLOAT_TO_INT16(r);
								data[++k] = FLOAT_TO_INT16(g);
								data[++k] = FLOAT_TO_INT16(b);
								data[++k] = FLOAT_TO_INT16(a);
								break;
							}
							default:
							{
								assert(false);
								break;
							}
						}

						break;
					}
					case TextureDataType::UnsignedInt:
					{
						uint32_t* data = static_cast<uint32_t*>(buffer);
						switch (format)
						{
							case TextureFormat::R:
							case TextureFormat::iR:
							case TextureFormat::DepthComponent:
							case TextureFormat::StencilIndex:
							{
								data[++k] = FLOAT_TO_UINT32(r);
								break;
							}
							case TextureFormat::RG:
							case TextureFormat::iRG:
							case TextureFormat::DepthStencil:
							{
								data[++k] = FLOAT_TO_UINT32(r);
								data[++k] = FLOAT_TO_UINT32(g);
								break;
							}
							case TextureFormat::RGB:
							case TextureFormat::iRGB:
							{
								data[++k] = FLOAT_TO_UINT32(r);
								data[++k] = FLOAT_TO_UINT32(g);
								data[++k] = FLOAT_TO_UINT32(b);
								break;
							}
							case TextureFormat::RGBA:
							case TextureFormat::iRGBA:
							{
								data[++k] = FLOAT_TO_UINT32(r);
								data[++k] = FLOAT_TO_UINT32(g);
								data[++k] = FLOAT_TO_UINT32(b);
								data[++k] = FLOAT_TO_UINT32(a);
								break;
							}
							default:
							{
								assert(false);
								break;
							}
						}

						break;
					}
					case TextureDataType::Int:
					{
						int32_t* data = static_cast<int32_t*>(buffer);
						switch (format)
						{
							case TextureFormat::R:
							case TextureFormat::iR:
							case TextureFormat::DepthComponent:
							case TextureFormat::StencilIndex:
							{
								data[++k] = FLOAT_TO_INT32(r);
								break;
							}
							case TextureFormat::RG:
							case TextureFormat::iRG:
							case TextureFormat::DepthStencil:
							{
								data[++k] = FLOAT_TO_INT32(r);
								data[++k] = FLOAT_TO_INT32(g);
								break;
							}
							case TextureFormat::RGB:
							case TextureFormat::iRGB:
							{
								data[++k] = FLOAT_TO_INT32(r);
								data[++k] = FLOAT_TO_INT32(g);
								data[++k] = FLOAT_TO_INT32(b);
								break;
							}
							case TextureFormat::RGBA:
							case TextureFormat::iRGBA:
							{
								data[++k] = FLOAT_TO_INT32(r);
								data[++k] = FLOAT_TO_INT32(g);
								data[++k] = FLOAT_TO_INT32(b);
								data[++k] = FLOAT_TO_INT32(a);
								break;
							}
							default:
							{
								assert(false);
								break;
							}
						}

						break;
					}
					case TextureDataType::Float:
					{
						float* data = static_cast<float*>(buffer);
						switch (format)
						{
							case TextureFormat::R:
							case TextureFormat::iR:
							case TextureFormat::DepthComponent:
							case TextureFormat::StencilIndex:
							{
								data[++k] = r;
								break;
							}
							case TextureFormat::RG:
							case TextureFormat::iRG:
							case TextureFormat::DepthStencil:
							{
								data[++k] = r;
								data[++k] = g;
								break;
							}
							case TextureFormat::RGB:
							case TextureFormat::iRGB:
							{
								data[++k] = r;
								data[++k] = g;
								data[++k] = b;
								break;
							}
							case TextureFormat::RGBA:
							case TextureFormat::iRGBA:
							{
								data[++k] = r;
								data[++k] = g;
								data[++k] = b;
								data[++k] = a;
								break;
							}
							default:
							{
								assert(false);
								break;
							}
						}

						break;
					}
					case TextureDataType::UnsignedByte_3_3_2:
					{
						uint8_t* data = static_cast<uint8_t*>(buffer);
						data[++k] = (FLOAT_TO_UINT8(r) & 0xE0) & ((FLOAT_TO_UINT8(g) & 0xE0) >> 3) & ((FLOAT_TO_UINT8(b) & 0xC0) >> 6);
						break;
					}
					case TextureDataType::UnsignedShort_5_6_5:
					{
						uint16_t* data = static_cast<uint16_t*>(buffer);
						data[++k] = (FLOAT_TO_UINT16(r) & 0xF800) & ((FLOAT_TO_UINT16(g) & 0xFC00) >> 5) & ((FLOAT_TO_UINT8(b) & 0xF8) >> 3);
						break;
					}
					case TextureDataType::UnsignedShort_4_4_4_4:
					{
						uint16_t* data = static_cast<uint16_t*>(buffer);
						data[++k] = (FLOAT_TO_UINT16(r) & 0xF000) & ((FLOAT_TO_UINT16(g) & 0xF000) >> 4) & (FLOAT_TO_UINT8(b) & 0xF0) & ((FLOAT_TO_UINT8(a) & 0xF0) >> 4);
						break;
					}
					case TextureDataType::UnsignedShort_5_5_5_1:
					{
						uint16_t* data = static_cast<uint16_t*>(buffer);
						data[++k] = (FLOAT_TO_UINT16(r) & 0xF800) & ((FLOAT_TO_UINT16(g) & 0xF800) >> 5) & ((FLOAT_TO_UINT8(b) & 0xF8) >> 2) & ((FLOAT_TO_UINT8(a) & 0x80) >> 7);
						break;
					}
					case TextureDataType::UnsignedInt_10_10_10_2:
					{
						uint32_t* data = static_cast<uint32_t*>(buffer);
						data[++k] = (FLOAT_TO_UINT32(r) & 0xFFC00000) & ((FLOAT_TO_UINT32(g) & 0xFFC00000) >> 10) & ((FLOAT_TO_UINT16(b) & 0xFFC0) >> 4) & ((FLOAT_TO_UINT8(a) & 0xC0) >> 6);
						break;
					}
					case TextureDataType::UnsignedInt_24_8:
					{
						uint32_t* data = static_cast<uint32_t*>(buffer);
						data[++k] = (FLOAT_TO_UINT32(r) & 0xFFFFFF00) & FLOAT_TO_UINT8(g);
						break;
					}
					case TextureDataType::Float32_UnsignedInt_24_8_Rev:
					{
						float* dataFloat = static_cast<float*>(buffer);
						dataFloat[++k] = r;
						uint32_t* dataInt = static_cast<uint32_t*>(buffer);
						dataInt[++k] = (FLOAT_TO_UINT32(g) & 0xFF000000) >> 24;
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
	}
}
