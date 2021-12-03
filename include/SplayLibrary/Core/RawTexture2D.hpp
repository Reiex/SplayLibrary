#pragma once

#include <SplayLibrary/Core/types.hpp>

#include <SplayLibrary/Core/Glsl.hpp>
#include <SplayLibrary/Core/RawTexture.hpp>

namespace spl
{
	class RawTexture2D : private RawTexture
	{
		public:

			RawTexture2D(TextureInternalFormat internalFormat = TextureInternalFormat::RGB8);
			RawTexture2D(const uvec2& size, TextureInternalFormat internalFormat = TextureInternalFormat::RGB8);
			RawTexture2D(const std::filesystem::path& path, TextureInternalFormat internalFormat = TextureInternalFormat::RGB8);
			template<typename PixelType> RawTexture2D(const djv::Img<PixelType>& image, TextureInternalFormat internalFormat = TextureInternalFormat::RGB8);
			RawTexture2D(const uint8_t* data, TextureInternalFormat internalFormat = TextureInternalFormat::RGB8);
			RawTexture2D(const uint16_t* data, TextureInternalFormat internalFormat = TextureInternalFormat::RGB8);
			RawTexture2D(const uint32_t* data, TextureInternalFormat internalFormat = TextureInternalFormat::RGB8);

			const uvec2& getSize() const;

			using RawTexture::getHandle;
			using RawTexture::getCreationParams;
			using RawTexture::isValid;

			using RawTexture::bind;
			using RawTexture::unbind;

		private:

			uvec2 _size;
	};
}
