///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2019-2022
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <SplayLibrary/Core/TextureBase.hpp>

namespace spl
{
	template<djv::CPixel TPixel>
	void TextureBase::createDejaVuImgBuffer(const djv::Image<TPixel>& image, TextureInternalFormat internalFormat, void*& buffer, TextureFormat& format, TextureDataType& dataType)
	{
		format = getUsualTextureFormatOf(internalFormat);
		dataType = getUsualTextureDataTypeOf(internalFormat);

		const uint64_t width = image.getWidth();
		const uint64_t height = image.getHeight();
		const uint64_t elementCount = width * height;

		switch (internalFormat)
		{
			case TextureInternalFormat::R:
				buffer = new uint8_t[elementCount];
				break;
			case TextureInternalFormat::RG:
				buffer = new uint8_t[elementCount * 2];
				break;
			case TextureInternalFormat::RGB:
				buffer = new uint8_t[elementCount * 3];
				break;
			case TextureInternalFormat::RGBA:
				buffer = new uint8_t[elementCount * 4];
				break;
			case TextureInternalFormat::DepthComponent:
				buffer = new float[elementCount];
				break;
			case TextureInternalFormat::StencilIndex:
				buffer = new uint8_t[elementCount];
				break;
			case TextureInternalFormat::DepthStencil:
				buffer = new float[elementCount * 2];
				break;
			case TextureInternalFormat::R8:
				buffer = new uint8_t[elementCount];
				break;
			case TextureInternalFormat::R8_SNORM:
				buffer = new int8_t[elementCount];
				break;
			case TextureInternalFormat::R8I:
				buffer = new int8_t[elementCount];
				break;
			case TextureInternalFormat::R8UI:
				buffer = new uint8_t[elementCount];
				break;
			case TextureInternalFormat::R16:
				buffer = new uint16_t[elementCount];
				break;
			case TextureInternalFormat::R16_SNORM:
				buffer = new int16_t[elementCount];
				break;
			case TextureInternalFormat::R16I:
				buffer = new int16_t[elementCount];
				break;
			case TextureInternalFormat::R16UI:
				buffer = new uint16_t[elementCount];
				break;
			case TextureInternalFormat::R16F:
				buffer = new float[elementCount];
				break;
			case TextureInternalFormat::R32I:
				buffer = new int32_t[elementCount];
				break;
			case TextureInternalFormat::R32UI:
				buffer = new uint32_t[elementCount];
				break;
			case TextureInternalFormat::R32F:
				buffer = new float[elementCount];
				break;
			case TextureInternalFormat::RG8:
				buffer = new uint8_t[elementCount * 2];
				break;
			case TextureInternalFormat::RG8_SNORM:
				buffer = new int8_t[elementCount * 2];
				break;
			case TextureInternalFormat::RG8I:
				buffer = new int8_t[elementCount * 2];
				break;
			case TextureInternalFormat::RG8UI:
				buffer = new uint8_t[elementCount * 2];
				break;
			case TextureInternalFormat::RG16:
				buffer = new uint16_t[elementCount * 2];
				break;
			case TextureInternalFormat::RG16_SNORM:
				buffer = new int16_t[elementCount * 2];
				break;
			case TextureInternalFormat::RG16I:
				buffer = new int16_t[elementCount * 2];
				break;
			case TextureInternalFormat::RG16UI:
				buffer = new uint16_t[elementCount * 2];
				break;
			case TextureInternalFormat::RG16F:
				buffer = new float[elementCount * 2];
				break;
			case TextureInternalFormat::RG32I:
				buffer = new int32_t[elementCount * 2];
				break;
			case TextureInternalFormat::RG32UI:
				buffer = new uint32_t[elementCount * 2];
				break;
			case TextureInternalFormat::RG32F:
				buffer = new float[elementCount * 2];
				break;
			case TextureInternalFormat::R3_G3_B2:
				buffer = new uint8_t[elementCount];
				break;
			case TextureInternalFormat::RGB4:
				buffer = new uint8_t[elementCount * 3];
				break;
			case TextureInternalFormat::RGB5:
				buffer = new uint8_t[elementCount * 3];
				break;
			case TextureInternalFormat::R5_G6_B5:
				buffer = new uint16_t[elementCount];
				break;
			case TextureInternalFormat::RGB8:
				buffer = new uint8_t[elementCount * 3];
				break;
			case TextureInternalFormat::RGB8_SNORM:
				buffer = new int8_t[elementCount * 3];
				break;
			case TextureInternalFormat::RGB8I:
				buffer = new int8_t[elementCount * 3];
				break;
			case TextureInternalFormat::RGB8UI:
				buffer = new uint8_t[elementCount * 3];
				break;
			case TextureInternalFormat::RGB9_E5:
				buffer = new uint16_t[elementCount * 3];
				break;
			case TextureInternalFormat::RGB10:
				buffer = new uint16_t[elementCount * 3];
				break;
			case TextureInternalFormat::R11F_G11F_B10F:
				buffer = new uint16_t[elementCount * 3];
				break;
			case TextureInternalFormat::RGB12:
				buffer = new uint16_t[elementCount * 3];
				break;
			case TextureInternalFormat::RGB16:
				buffer = new uint16_t[elementCount * 3];
				break;
			case TextureInternalFormat::RGB16_SNORM:
				buffer = new int16_t[elementCount * 3];
				break;
			case TextureInternalFormat::RGB16I:
				buffer = new int16_t[elementCount * 3];
				break;
			case TextureInternalFormat::RGB16UI:
				buffer = new uint16_t[elementCount * 3];
				break;
			case TextureInternalFormat::RGB16F:
				buffer = new float[elementCount * 3];
				break;
			case TextureInternalFormat::RGB32I:
				buffer = new int32_t[elementCount * 3];
				break;
			case TextureInternalFormat::RGB32UI:
				buffer = new uint32_t[elementCount * 3];
				break;
			case TextureInternalFormat::RGB32F:
				buffer = new float[elementCount * 3];
				break;
			case TextureInternalFormat::RGBA2:
				buffer = new uint8_t[elementCount * 4];
				break;
			case TextureInternalFormat::RGBA4:
				buffer = new uint16_t[elementCount];
				break;
			case TextureInternalFormat::RGB5_A1:
				buffer = new uint16_t[elementCount];
				break;
			case TextureInternalFormat::RGBA8:
				buffer = new uint8_t[elementCount * 4];
				break;
			case TextureInternalFormat::RGBA8_SNORM:
				buffer = new int8_t[elementCount * 4];
				break;
			case TextureInternalFormat::RGBA8I:
				buffer = new int8_t[elementCount * 4];
				break;
			case TextureInternalFormat::RGBA8UI:
				buffer = new uint8_t[elementCount * 4];
				break;
			case TextureInternalFormat::RGB10_A2:
				buffer = new uint32_t[elementCount];
				break;
			case TextureInternalFormat::RGB10UI_A2UI:
				buffer = new uint32_t[elementCount];
				break;
			case TextureInternalFormat::RGBA12:
				buffer = new uint16_t[elementCount * 4];
				break;
			case TextureInternalFormat::RGBA16:
				buffer = new uint16_t[elementCount * 4];
				break;
			case TextureInternalFormat::RGBA16_SNORM:
				buffer = new int16_t[elementCount * 4];
				break;
			case TextureInternalFormat::RGBA16I:
				buffer = new int16_t[elementCount * 4];
				break;
			case TextureInternalFormat::RGBA16UI:
				buffer = new uint16_t[elementCount * 4];
				break;
			case TextureInternalFormat::RGBA16F:
				buffer = new float[elementCount * 4];
				break;
			case TextureInternalFormat::RGBA32I:
				buffer = new int32_t[elementCount * 4];
				break;
			case TextureInternalFormat::RGBA32UI:
				buffer = new uint32_t[elementCount * 4];
				break;
			case TextureInternalFormat::RGBA32F:
				buffer = new float[elementCount * 4];
				break;
			case TextureInternalFormat::SRGB8:
				buffer = new uint8_t[elementCount * 3];
				break;
			case TextureInternalFormat::SRGBA8:
				buffer = new uint8_t[elementCount * 4];
				break;
			case TextureInternalFormat::DepthComponent16:
				buffer = new uint16_t[elementCount];
				break;
			case TextureInternalFormat::DepthComponent24:
				buffer = new uint32_t[elementCount];
				break;
			case TextureInternalFormat::DepthComponent32:
				buffer = new uint32_t[elementCount];
				break;
			case TextureInternalFormat::DepthComponent32F:
				buffer = new float[elementCount];
				break;
			case TextureInternalFormat::StencilIndex1:
				buffer = new uint8_t[elementCount];
				break;
			case TextureInternalFormat::StencilIndex4:
				buffer = new uint8_t[elementCount];
				break;
			case TextureInternalFormat::StencilIndex8:
				buffer = new uint8_t[elementCount];
				break;
			case TextureInternalFormat::StencilIndex16:
				buffer = new uint16_t[elementCount];
				break;
			case TextureInternalFormat::Depth24_Stencil8:
				buffer = new uint32_t[elementCount];
				break;
			case TextureInternalFormat::Depth32F_Stencil8:
				buffer = new float[elementCount * 2];
				break;
			default:
				assert(false);
				return;
		}
		
		const TPixel* it = image.getData();
		uint64_t k = -1;
		for (uint64_t i = 0; i < elementCount; ++i, ++it)
		{
			switch (dataType)
			{
				case TextureDataType::UnsignedByte:
				{
					uint8_t* data = reinterpret_cast<uint8_t*>(buffer);
					switch (format)
					{
						case TextureFormat::R:
						case TextureFormat::iR:
						case TextureFormat::DepthComponent:
						case TextureFormat::StencilIndex:
						{
							it->get(0, data[++k]);
							break;
						}
						case TextureFormat::RG:
						case TextureFormat::iRG:
						case TextureFormat::DepthStencil:
						{
							it->get(0, data[++k]);
							it->get(1, data[++k]);
							break;
						}
						case TextureFormat::RGB:
						case TextureFormat::iRGB:
						{
							it->get(0, data[++k]);
							it->get(1, data[++k]);
							it->get(2, data[++k]);
							break;
						}
						case TextureFormat::RGBA:
						case TextureFormat::iRGBA:
						{
							it->get(0, data[++k]);
							it->get(1, data[++k]);
							it->get(2, data[++k]);
							it->get(3, data[++k]);
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
					int8_t* data = reinterpret_cast<int8_t*>(buffer);
					switch (format)
					{
						case TextureFormat::R:
						case TextureFormat::iR:
						case TextureFormat::DepthComponent:
						case TextureFormat::StencilIndex:
						{
							it->get(0, data[++k]);
							break;
						}
						case TextureFormat::RG:
						case TextureFormat::iRG:
						case TextureFormat::DepthStencil:
						{
							it->get(0, data[++k]);
							it->get(1, data[++k]);
							break;
						}
						case TextureFormat::RGB:
						case TextureFormat::iRGB:
						{
							it->get(0, data[++k]);
							it->get(1, data[++k]);
							it->get(2, data[++k]);
							break;
						}
						case TextureFormat::RGBA:
						case TextureFormat::iRGBA:
						{
							it->get(0, data[++k]);
							it->get(1, data[++k]);
							it->get(2, data[++k]);
							it->get(3, data[++k]);
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
					uint16_t* data = reinterpret_cast<uint16_t*>(buffer);
					switch (format)
					{
						case TextureFormat::R:
						case TextureFormat::iR:
						case TextureFormat::DepthComponent:
						case TextureFormat::StencilIndex:
						{
							it->get(0, data[++k]);
							break;
						}
						case TextureFormat::RG:
						case TextureFormat::iRG:
						case TextureFormat::DepthStencil:
						{
							it->get(0, data[++k]);
							it->get(1, data[++k]);
							break;
						}
						case TextureFormat::RGB:
						case TextureFormat::iRGB:
						{
							it->get(0, data[++k]);
							it->get(1, data[++k]);
							it->get(2, data[++k]);
							break;
						}
						case TextureFormat::RGBA:
						case TextureFormat::iRGBA:
						{
							it->get(0, data[++k]);
							it->get(1, data[++k]);
							it->get(2, data[++k]);
							it->get(3, data[++k]);
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
					int16_t* data = reinterpret_cast<int16_t*>(buffer);
					switch (format)
					{
						case TextureFormat::R:
						case TextureFormat::iR:
						case TextureFormat::DepthComponent:
						case TextureFormat::StencilIndex:
						{
							it->get(0, data[++k]);
							break;
						}
						case TextureFormat::RG:
						case TextureFormat::iRG:
						case TextureFormat::DepthStencil:
						{
							it->get(0, data[++k]);
							it->get(1, data[++k]);
							break;
						}
						case TextureFormat::RGB:
						case TextureFormat::iRGB:
						{
							it->get(0, data[++k]);
							it->get(1, data[++k]);
							it->get(2, data[++k]);
							break;
						}
						case TextureFormat::RGBA:
						case TextureFormat::iRGBA:
						{
							it->get(0, data[++k]);
							it->get(1, data[++k]);
							it->get(2, data[++k]);
							it->get(3, data[++k]);
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
					uint32_t* data = reinterpret_cast<uint32_t*>(buffer);
					switch (format)
					{
						case TextureFormat::R:
						case TextureFormat::iR:
						case TextureFormat::DepthComponent:
						case TextureFormat::StencilIndex:
						{
							it->get(0, data[++k]);
							break;
						}
						case TextureFormat::RG:
						case TextureFormat::iRG:
						case TextureFormat::DepthStencil:
						{
							it->get(0, data[++k]);
							it->get(1, data[++k]);
							break;
						}
						case TextureFormat::RGB:
						case TextureFormat::iRGB:
						{
							it->get(0, data[++k]);
							it->get(1, data[++k]);
							it->get(2, data[++k]);
							break;
						}
						case TextureFormat::RGBA:
						case TextureFormat::iRGBA:
						{
							it->get(0, data[++k]);
							it->get(1, data[++k]);
							it->get(2, data[++k]);
							it->get(3, data[++k]);
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
					int32_t* data = reinterpret_cast<int32_t*>(buffer);
					switch (format)
					{
						case TextureFormat::R:
						case TextureFormat::iR:
						case TextureFormat::DepthComponent:
						case TextureFormat::StencilIndex:
						{
							it->get(0, data[++k]);
							break;
						}
						case TextureFormat::RG:
						case TextureFormat::iRG:
						case TextureFormat::DepthStencil:
						{
							it->get(0, data[++k]);
							it->get(1, data[++k]);
							break;
						}
						case TextureFormat::RGB:
						case TextureFormat::iRGB:
						{
							it->get(0, data[++k]);
							it->get(1, data[++k]);
							it->get(2, data[++k]);
							break;
						}
						case TextureFormat::RGBA:
						case TextureFormat::iRGBA:
						{
							it->get(0, data[++k]);
							it->get(1, data[++k]);
							it->get(2, data[++k]);
							it->get(3, data[++k]);
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
					float* data = reinterpret_cast<float*>(buffer);
					switch (format)
					{
						case TextureFormat::R:
						case TextureFormat::iR:
						case TextureFormat::DepthComponent:
						case TextureFormat::StencilIndex:
						{
							it->get(0, data[++k]);
							break;
						}
						case TextureFormat::RG:
						case TextureFormat::iRG:
						case TextureFormat::DepthStencil:
						{
							it->get(0, data[++k]);
							it->get(1, data[++k]);
							break;
						}
						case TextureFormat::RGB:
						case TextureFormat::iRGB:
						{
							it->get(0, data[++k]);
							it->get(1, data[++k]);
							it->get(2, data[++k]);
							break;
						}
						case TextureFormat::RGBA:
						case TextureFormat::iRGBA:
						{
							it->get(0, data[++k]);
							it->get(1, data[++k]);
							it->get(2, data[++k]);
							it->get(3, data[++k]);
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
					uint8_t r, g, b;
					it->get(0, r);
					it->get(1, g);
					it->get(2, b);

					uint8_t* data = reinterpret_cast<uint8_t*>(buffer);
					data[++k] = (r & 0xE0) & ((g & 0xE0) >> 3) & ((b & 0xC0) >> 6);
					break;
				}
				case TextureDataType::UnsignedShort_5_6_5:
				{
					uint16_t r, g;
					uint8_t b;
					it->get(0, r);
					it->get(1, g);
					it->get(2, b);

					uint16_t* data = reinterpret_cast<uint16_t*>(buffer);
					data[++k] = (r & 0xF800) & ((g & 0xFC00) >> 5) & ((b & 0xF8) >> 3);
					break;
				}
				case TextureDataType::UnsignedShort_4_4_4_4:
				{
					uint16_t r, g;
					uint8_t b, a;
					it->get(0, r);
					it->get(1, g);
					it->get(2, b);
					it->get(3, a);

					uint16_t* data = reinterpret_cast<uint16_t*>(buffer);
					data[++k] = (r & 0xF000) & ((g & 0xF000) >> 4) & (b & 0xF0) & ((a & 0xF0) >> 4);
					break;
				}
				case TextureDataType::UnsignedShort_5_5_5_1:
				{
					uint16_t r, g;
					uint8_t b, a;
					it->get(0, r);
					it->get(1, g);
					it->get(2, b);
					it->get(3, a);

					uint16_t* data = reinterpret_cast<uint16_t*>(buffer);
					data[++k] = (r & 0xF800) & ((g & 0xF800) >> 5) & ((b & 0xF8) >> 2) & ((a & 0x80) >> 7);
					break;
				}
				case TextureDataType::UnsignedInt_10_10_10_2:
				{
					uint32_t r, g;
					uint16_t b;
					uint8_t a;
					it->get(0, r);
					it->get(1, g);
					it->get(2, b);
					it->get(3, a);

					uint32_t* data = reinterpret_cast<uint32_t*>(buffer);
					data[++k] = (r & 0xFFC00000) & ((g & 0xFFC00000) >> 10) & ((b & 0xFFC0) >> 4) & ((a & 0xC0) >> 6);
					break;
				}
				case TextureDataType::UnsignedInt_24_8:
				{
					uint32_t r;
					uint8_t g;
					it->get(0, r);
					it->get(1, g);

					uint32_t* data = reinterpret_cast<uint32_t*>(buffer);
					data[++k] = (r & 0xFFFFFF00) & g;
					break;
				}
				case TextureDataType::Float32_UnsignedInt_24_8_Rev:
				{
					float* dataFloat = reinterpret_cast<float*>(buffer);
					it->get(0, dataFloat[++k]);
					uint32_t* dataInt = reinterpret_cast<uint32_t*>(buffer);
					it->get(1, dataInt[++k]);
					dataInt[++k] >>= 24;
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
