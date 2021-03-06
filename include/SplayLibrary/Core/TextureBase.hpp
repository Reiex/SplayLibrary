#pragma once

#include <SplayLibrary/Core/types.hpp>

#include <SplayLibrary/Core/RawTexture.hpp>

namespace spl
{
	// TODO: Template class that take an internal format and whose "::Type" is a corresponding PixelType
	// template<TextureInternalFormat InternalFormat> struct InternalFormatPixelType { using PixelType = djv::RGBAPixel; }
	// The goal is to load only necessary precision and necessary components

	class TextureBase
	{
		public:

			TextureBase(const TextureBase& texture) = delete;
			TextureBase(TextureBase&& texture) = delete;

			TextureBase& operator=(const TextureBase& texture) = delete;
			TextureBase& operator=(TextureBase&& texture) = delete;

			static TextureFormat getUsualTextureFormatOf(TextureInternalFormat internalFormat);
			static TextureDataType getUsualTextureDataTypeOf(TextureInternalFormat internalFormat);

			const RawTexture& getRawTexture() const;
			RawTexture& getRawTexture();
			bool isValid() const;

			~TextureBase() = default;

		protected:

			TextureBase() = default;

			template<typename PixelType> static void createDejaVuImgBuffer(const djv::Img<PixelType>& image, TextureInternalFormat internalFormat, void*& buffer, TextureFormat& format, TextureDataType& dataType);

			RawTexture _texture;
	};
}

#include <SplayLibrary/Core/template/TextureBase.hpp>
