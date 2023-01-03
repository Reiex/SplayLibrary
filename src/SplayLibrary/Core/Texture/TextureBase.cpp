///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2021-2023
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SplayLibrary/Core/Core.hpp>
#include <SplayLibrary/Private/PrivateNotIncluded.hpp>

namespace spl
{
	TextureFormat TextureBase::getUsualTextureFormatOf(TextureInternalFormat internalFormat)
	{
		switch (internalFormat)
		{
			case TextureInternalFormat::R:
			case TextureInternalFormat::R8:
			case TextureInternalFormat::R8_SNORM:
			case TextureInternalFormat::R16:
			case TextureInternalFormat::R16_SNORM:
			case TextureInternalFormat::R16F:
				return TextureFormat::R;

			case TextureInternalFormat::R8I:
			case TextureInternalFormat::R8UI:
			case TextureInternalFormat::R16I:
			case TextureInternalFormat::R16UI:
			case TextureInternalFormat::R32I:
			case TextureInternalFormat::R32UI:
			case TextureInternalFormat::R32F:
				return TextureFormat::iR;

			case TextureInternalFormat::RG:
			case TextureInternalFormat::RG8:
			case TextureInternalFormat::RG8_SNORM:
			case TextureInternalFormat::RG16:
			case TextureInternalFormat::RG16_SNORM:
			case TextureInternalFormat::RG16F:
			case TextureInternalFormat::RG32F:
				return TextureFormat::RG;

			case TextureInternalFormat::RG8I:
			case TextureInternalFormat::RG8UI:
			case TextureInternalFormat::RG16I:
			case TextureInternalFormat::RG16UI:
			case TextureInternalFormat::RG32I:
			case TextureInternalFormat::RG32UI:
				return TextureFormat::iRG;

			case TextureInternalFormat::RGB:
			case TextureInternalFormat::R3_G3_B2:
			case TextureInternalFormat::RGB4:
			case TextureInternalFormat::RGB5:
			case TextureInternalFormat::R5_G6_B5:
			case TextureInternalFormat::RGB8:
			case TextureInternalFormat::RGB8_SNORM:
			case TextureInternalFormat::RGB9_E5:
			case TextureInternalFormat::RGB10:
			case TextureInternalFormat::R11F_G11F_B10F:
			case TextureInternalFormat::RGB12:
			case TextureInternalFormat::RGB16:
			case TextureInternalFormat::RGB16_SNORM:
			case TextureInternalFormat::RGB16F:
			case TextureInternalFormat::RGB32F:
			case TextureInternalFormat::SRGB8:
				return TextureFormat::RGB;

			case TextureInternalFormat::RGB8I:
			case TextureInternalFormat::RGB8UI:
			case TextureInternalFormat::RGB16I:
			case TextureInternalFormat::RGB16UI:
			case TextureInternalFormat::RGB32I:
			case TextureInternalFormat::RGB32UI:
				return TextureFormat::iRGB;

			case TextureInternalFormat::RGBA:
			case TextureInternalFormat::RGBA2:
			case TextureInternalFormat::RGBA4:
			case TextureInternalFormat::RGB5_A1:
			case TextureInternalFormat::RGBA8:
			case TextureInternalFormat::RGBA8_SNORM:
			case TextureInternalFormat::RGB10_A2:
			case TextureInternalFormat::RGBA12:
			case TextureInternalFormat::RGBA16:
			case TextureInternalFormat::RGBA16_SNORM:
			case TextureInternalFormat::RGBA16F:
			case TextureInternalFormat::RGBA32F:
			case TextureInternalFormat::SRGBA8:
				return TextureFormat::RGBA;

			case TextureInternalFormat::RGBA8I:
			case TextureInternalFormat::RGBA8UI:
			case TextureInternalFormat::RGB10UI_A2UI:
			case TextureInternalFormat::RGBA16I:
			case TextureInternalFormat::RGBA16UI:
			case TextureInternalFormat::RGBA32I:
			case TextureInternalFormat::RGBA32UI:
				return TextureFormat::iRGBA;

			case TextureInternalFormat::DepthComponent:
			case TextureInternalFormat::DepthComponent16:
			case TextureInternalFormat::DepthComponent24:
			case TextureInternalFormat::DepthComponent32:
			case TextureInternalFormat::DepthComponent32F:
				return TextureFormat::DepthComponent;

			case TextureInternalFormat::StencilIndex:
			case TextureInternalFormat::StencilIndex1:
			case TextureInternalFormat::StencilIndex4:
			case TextureInternalFormat::StencilIndex8:
			case TextureInternalFormat::StencilIndex16:
				return TextureFormat::StencilIndex;

			case TextureInternalFormat::DepthStencil:
			case TextureInternalFormat::Depth24_Stencil8:
			case TextureInternalFormat::Depth32F_Stencil8:
				return TextureFormat::DepthStencil;

			default:
				assert(false);
				return TextureFormat::Undefined;
		}
	}

	TextureDataType TextureBase::getUsualTextureDataTypeOf(TextureInternalFormat internalFormat)
	{
		switch (internalFormat)
		{
			case TextureInternalFormat::R:
			case TextureInternalFormat::RG:
			case TextureInternalFormat::RGB:
			case TextureInternalFormat::RGBA:
			case TextureInternalFormat::StencilIndex:
			case TextureInternalFormat::R8:
			case TextureInternalFormat::R8UI:
			case TextureInternalFormat::RG8:
			case TextureInternalFormat::RG8UI:
			case TextureInternalFormat::RGB4:
			case TextureInternalFormat::RGB5:
			case TextureInternalFormat::RGB8:
			case TextureInternalFormat::RGB8UI:
			case TextureInternalFormat::RGBA2:
			case TextureInternalFormat::RGBA8:
			case TextureInternalFormat::RGBA8UI:
			case TextureInternalFormat::SRGB8:
			case TextureInternalFormat::SRGBA8:
			case TextureInternalFormat::StencilIndex1:
			case TextureInternalFormat::StencilIndex4:
			case TextureInternalFormat::StencilIndex8:
				return TextureDataType::UnsignedByte;

			case TextureInternalFormat::R8_SNORM:
			case TextureInternalFormat::R8I:
			case TextureInternalFormat::RG8_SNORM:
			case TextureInternalFormat::RG8I:
			case TextureInternalFormat::RGB8_SNORM:
			case TextureInternalFormat::RGB8I:
			case TextureInternalFormat::RGBA8_SNORM:
			case TextureInternalFormat::RGBA8I:
				return TextureDataType::Byte;

			case TextureInternalFormat::R16:
			case TextureInternalFormat::R16UI:
			case TextureInternalFormat::RG16:
			case TextureInternalFormat::RG16UI:
			case TextureInternalFormat::RGB9_E5:
			case TextureInternalFormat::RGB10:
			case TextureInternalFormat::R11F_G11F_B10F:
			case TextureInternalFormat::RGB12:
			case TextureInternalFormat::RGB16:
			case TextureInternalFormat::RGB16UI:
			case TextureInternalFormat::RGBA12:
			case TextureInternalFormat::RGBA16:
			case TextureInternalFormat::RGBA16UI:
			case TextureInternalFormat::DepthComponent16:
			case TextureInternalFormat::StencilIndex16:
				return TextureDataType::UnsignedShort;

			case TextureInternalFormat::R16_SNORM:
			case TextureInternalFormat::R16I:
			case TextureInternalFormat::RG16_SNORM:
			case TextureInternalFormat::RG16I:
			case TextureInternalFormat::RGB16_SNORM:
			case TextureInternalFormat::RGB16I:
			case TextureInternalFormat::RGBA16_SNORM:
			case TextureInternalFormat::RGBA16I:
				return TextureDataType::Short;

			case TextureInternalFormat::DepthStencil:
			case TextureInternalFormat::R32UI:
			case TextureInternalFormat::RG32UI:
			case TextureInternalFormat::RGB32UI:
			case TextureInternalFormat::RGBA32UI:
			case TextureInternalFormat::DepthComponent24:
			case TextureInternalFormat::DepthComponent32:
				return TextureDataType::UnsignedInt;

			case TextureInternalFormat::R32I:
			case TextureInternalFormat::RG32I:
			case TextureInternalFormat::RGB32I:
			case TextureInternalFormat::RGBA32I:
				return TextureDataType::Int;

			case TextureInternalFormat::DepthComponent:
			case TextureInternalFormat::R16F:
			case TextureInternalFormat::R32F:
			case TextureInternalFormat::RG16F:
			case TextureInternalFormat::RG32F:
			case TextureInternalFormat::RGB16F:
			case TextureInternalFormat::RGB32F:
			case TextureInternalFormat::RGBA16F:
			case TextureInternalFormat::RGBA32F:
			case TextureInternalFormat::DepthComponent32F:
				return TextureDataType::Float;

			case TextureInternalFormat::R3_G3_B2:
				return TextureDataType::UnsignedByte_3_3_2;

			case TextureInternalFormat::R5_G6_B5:
				return TextureDataType::UnsignedShort_5_6_5;

			case TextureInternalFormat::RGBA4:
				return TextureDataType::UnsignedShort_4_4_4_4;

			case TextureInternalFormat::RGB5_A1:
				return TextureDataType::UnsignedShort_5_5_5_1;

			case TextureInternalFormat::RGB10_A2:
			case TextureInternalFormat::RGB10UI_A2UI:
				return TextureDataType::UnsignedInt_10_10_10_2;

			case TextureInternalFormat::Depth24_Stencil8:
				return TextureDataType::UnsignedInt_24_8;

			case TextureInternalFormat::Depth32F_Stencil8:
				return TextureDataType::Float32_UnsignedInt_24_8_Rev;

			default:
				assert(false);
				return TextureDataType::Undefined;
		}
	}

	const RawTexture& TextureBase::getRawTexture() const
	{
		return _texture;
	}

	RawTexture& TextureBase::getRawTexture()
	{
		return _texture;
	}

	bool TextureBase::isValid() const
	{
		return _texture.isValid();
	}
}
