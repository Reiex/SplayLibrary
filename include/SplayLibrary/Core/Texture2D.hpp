#pragma once

#include <SplayLibrary/Core/types.hpp>

#include <SplayLibrary/Core/Glsl.hpp>
#include <SplayLibrary/Core/RawTexture.hpp>

namespace spl
{
	class Texture2D : public RawTexture
	{
		public:

			// TODO: Ne pas faire hériter, faire une classe a part qui hérite de "TextureBase" et qui contient un RawTexture

			Texture2D();
			Texture2D(const uvec2& size, TextureInternalFormat internalFormat = TextureInternalFormat::RGB8);
			Texture2D(const uvec2& size, const uint8_t* data, TextureInternalFormat internalFormat = TextureInternalFormat::RGB8);
			Texture2D(const uvec2& size, const uint16_t* data, TextureInternalFormat internalFormat = TextureInternalFormat::RGB8);
			Texture2D(const uvec2& size, const uint32_t* data, TextureInternalFormat internalFormat = TextureInternalFormat::RGB8);
			Texture2D(const std::filesystem::path& path, TextureInternalFormat internalFormat = TextureInternalFormat::RGB8);
			template<typename PixelType> Texture2D(const djv::Img<PixelType>& image, TextureInternalFormat internalFormat = TextureInternalFormat::RGB8);
			Texture2D(const Texture2D& texture) = delete;
			Texture2D(Texture2D&& texture) = delete;

			Texture2D& operator=(const Texture2D& texture) = delete;
			Texture2D& operator=(Texture2D&& texture) = delete;

			void createNew(const uvec2& size, TextureInternalFormat internalFormat = TextureInternalFormat::RGB8);
			void createNew(const uvec2& size, const uint8_t* data, TextureInternalFormat internalFormat = TextureInternalFormat::RGB8);
			void createNew(const uvec2& size, const uint16_t* data, TextureInternalFormat internalFormat = TextureInternalFormat::RGB8);
			void createNew(const uvec2& size, const uint32_t* data, TextureInternalFormat internalFormat = TextureInternalFormat::RGB8);
			void createNew(const std::filesystem::path& path, TextureInternalFormat internalFormat = TextureInternalFormat::RGB8);
			template<typename PixelType> void createNew(const djv::Img<PixelType>& image, TextureInternalFormat internalFormat = TextureInternalFormat::RGB8);
			void update(const uvec2& size, const uint8_t* data, const uvec2& offset = { 0, 0 });
			void update(const uvec2& size, const uint16_t* data, const uvec2& offset = { 0, 0 });
			void update(const uvec2& size, const uint32_t* data, const uvec2& offset = { 0, 0 });
			void update(const std::filesystem::path& path, const uvec2& offset = { 0, 0 });
			template<typename PixelType> void update(const djv::Img<PixelType>& image, const uvec2& offset = { 0, 0 });
			void destroy();

			const uvec2& getSize() const;

			~Texture2D();

		private:

			using RawTexture::createNew;
			using RawTexture::update;
			using RawTexture::destroy;

			uvec2 _size;
	};
}

#include <SplayLibrary/Core/Texture2DT.hpp>
