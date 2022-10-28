#pragma once

#include <SplayLibrary/Core/types.hpp>

#include <SplayLibrary/Core/Glsl.hpp>
#include <SplayLibrary/Core/TextureBase.hpp>

namespace spl
{
	class Texture2D : public TextureBase
	{
		public:

			Texture2D();
			Texture2D(const uvec2& size, TextureInternalFormat internalFormat = TextureInternalFormat::RGB8);
			Texture2D(const uvec2& size, const uint8_t* data, TextureInternalFormat internalFormat = TextureInternalFormat::RGB8);
			Texture2D(const uvec2& size, const uint16_t* data, TextureInternalFormat internalFormat = TextureInternalFormat::RGB8);
			Texture2D(const uvec2& size, const uint32_t* data, TextureInternalFormat internalFormat = TextureInternalFormat::RGB8);
			Texture2D(const uvec2& size, const float* data, TextureInternalFormat internalFormat = TextureInternalFormat::RGB8);
			Texture2D(const std::filesystem::path& path, TextureInternalFormat internalFormat = TextureInternalFormat::RGB8);
			template<djv::PixelConcept TPixel> Texture2D(const djv::Image<TPixel>& image, TextureInternalFormat internalFormat = TextureInternalFormat::RGB8);
			Texture2D(const Texture2D& texture) = delete;
			Texture2D(Texture2D&& texture) = delete;

			Texture2D& operator=(const Texture2D& texture) = delete;
			Texture2D& operator=(Texture2D&& texture) = delete;

			void createNew(const uvec2& size, TextureInternalFormat internalFormat = TextureInternalFormat::RGB8);
			void createNew(const uvec2& size, const uint8_t* data, TextureInternalFormat internalFormat = TextureInternalFormat::RGB8);
			void createNew(const uvec2& size, const uint16_t* data, TextureInternalFormat internalFormat = TextureInternalFormat::RGB8);
			void createNew(const uvec2& size, const uint32_t* data, TextureInternalFormat internalFormat = TextureInternalFormat::RGB8);
			void createNew(const uvec2& size, const float* data, TextureInternalFormat internalFormat = TextureInternalFormat::RGB8);
			void createNew(const std::filesystem::path& path, TextureInternalFormat internalFormat = TextureInternalFormat::RGB8);
			template<djv::PixelConcept TPixel> void createNew(const djv::Image<TPixel>& image, TextureInternalFormat internalFormat = TextureInternalFormat::RGB8);
			void update(const uvec2& size, const uint8_t* data, const uvec2& offset = { 0, 0 });
			void update(const uvec2& size, const uint16_t* data, const uvec2& offset = { 0, 0 });
			void update(const uvec2& size, const uint32_t* data, const uvec2& offset = { 0, 0 });
			void update(const uvec2& size, const float* data, const uvec2& offset = { 0, 0 });
			void update(const std::filesystem::path& path, const uvec2& offset = { 0, 0 });
			template<djv::PixelConcept TPixel> void update(const djv::Image<TPixel>& image, const uvec2& offset = { 0, 0 });
			void destroy();

			const uvec2& getSize() const;

			~Texture2D();

		private:

			uvec2 _size;
	};
}

#include <SplayLibrary/Core/template/Texture2D.hpp>
