///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2019-2022
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <SplayLibrary/Core/types.hpp>

namespace spl
{
	enum class TextureTarget
	{
		Undefined,
		Texture1D,
		Texture2D,
		Texture3D,
		Array1D,
		Array2D,
		Rectangle,
		Buffer,
		CubeMap,
		CubeMapArray,
		Multisample2D,
		Multisample2DArray
	};

	enum class TextureFormat
	{
		Undefined,	///< TODO
		StencilIndex,
		DepthComponent,
		DepthStencil,
		R,
		G,
		B,
		RG,
		RGB,
		RGBA,
		BGR,
		BGRA,
		iR,
		iG,
		iB,
		iRG,
		iRGB,
		iRGBA,
		iBGR,
		iBGRA
	};

	enum class TextureDataType
	{
		Undefined,	///< TODO
		UnsignedByte,
		Byte,
		UnsignedShort,
		Short,
		UnsignedInt,
		Int,
		HalfFloat,
		Float,
		UnsignedByte_3_3_2,
		UnsignedByte_2_3_3_Rev,
		UnsignedShort_5_6_5,
		UnsignedShort_5_6_5_Rev,
		UnsignedShort_4_4_4_4,
		UnsignedShort_4_4_4_4_Rev,
		UnsignedShort_5_5_5_1,
		UnsignedShort_1_5_5_5_Rev,
		UnsignedInt_8_8_8_8,
		UnsignedInt_8_8_8_8_Rev,
		UnsignedInt_10_10_10_2,
		UnsignedInt_2_10_10_10_Rev,
		UnsignedInt_24_8,
		UnsignedInt_10F_11F_11F_Rev,
		UnsignedInt_5_9_9_9_Rev,
		Float32_UnsignedInt_24_8_Rev
	};

	enum class TextureInternalFormat
	{
		Undefined,

		R,
		RG,
		RGB,
		RGBA,
		DepthComponent,
		StencilIndex,
		DepthStencil,

		R8,
		R8_SNORM,
		R8I,
		R8UI,
		R16,
		R16_SNORM,
		R16I,
		R16UI,
		R16F,
		R32I,
		R32UI,
		R32F,

		RG8,
		RG8_SNORM,
		RG8I,
		RG8UI,
		RG16,
		RG16_SNORM,
		RG16I,
		RG16UI,
		RG16F,
		RG32I,
		RG32UI,
		RG32F,

		R3_G3_B2,
		RGB4,
		RGB5,
		R5_G6_B5,
		RGB8,
		RGB8_SNORM,
		RGB8I,
		RGB8UI,
		RGB9_E5,
		RGB10,
		R11F_G11F_B10F,
		RGB12,
		RGB16,
		RGB16_SNORM,
		RGB16I,
		RGB16UI,
		RGB16F,
		RGB32I,
		RGB32UI,
		RGB32F,

		RGBA2,
		RGBA4,
		RGB5_A1,
		RGBA8,
		RGBA8_SNORM,
		RGBA8I,
		RGBA8UI,
		RGB10_A2,
		RGB10UI_A2UI,
		RGBA12,
		RGBA16,
		RGBA16_SNORM,
		RGBA16I,
		RGBA16UI,
		RGBA16F,
		RGBA32I,
		RGBA32UI,
		RGBA32F,

		SRGB8,
		SRGBA8,

		DepthComponent16,
		DepthComponent24,
		DepthComponent32,
		DepthComponent32F,

		StencilIndex1,
		StencilIndex4,
		StencilIndex8,
		StencilIndex16,

		Depth24_Stencil8,
		Depth32F_Stencil8,
	};

	class RawTexture
	{
		public:

			struct CreationParams
			{
				TextureTarget target = TextureTarget::Undefined;
				TextureInternalFormat internalFormat = TextureInternalFormat::Undefined;

				const Buffer* buffer = nullptr;
				uint32_t bufferOffset = 0;
				uint32_t bufferSize = 0;

				uint32_t width = 0;
				uint32_t height = 0;
				uint32_t depth = 0;

				uint32_t levels = 1;

				uint32_t samples = 0;
				bool fixedSampleLocations = false;
			};

			struct UpdateParams
			{
				const Buffer* buffer = nullptr;
				uint32_t bufferOffset = 0;

				const void* data = nullptr;

				TextureFormat dataFormat = TextureFormat::Undefined;
				TextureDataType dataType = TextureDataType::Undefined;

				uint32_t offsetX = 0;
				uint32_t offsetY = 0;
				uint32_t offsetZ = 0;

				uint32_t width = 0;
				uint32_t height = 0;
				uint32_t depth = 0;

				uint32_t level = 0;
			};

			RawTexture();
			RawTexture(const RawTexture& texture) = delete;
			RawTexture(RawTexture&& texture) = delete;

			RawTexture& operator=(const RawTexture& texture) = delete;
			RawTexture& operator=(RawTexture&& texture) = delete;

			void createNew(const CreationParams& params);
			void update(const UpdateParams& params);
			void destroy();

			// TODO: Update from framebuffer

			uint32_t getHandle() const;
			const CreationParams& getCreationParams() const;
			bool isValid() const;

			static void bind(const RawTexture& texture, TextureTarget target, uint32_t textureUnit = 0);
			static void unbind(TextureTarget target, uint32_t textureUnit = 0);

			~RawTexture();

		private:

			uint32_t _texture;
			CreationParams _creationParams;
	};

	class RenderBuffer
	{
		public:

			RenderBuffer() = delete;
			RenderBuffer(TextureInternalFormat internalFormat, const scp::u32vec2& size, uint32_t samples = 0);
			RenderBuffer(const RenderBuffer& renderBuffer) = delete;
			RenderBuffer(RenderBuffer&& renderBuffer) = delete;

			RenderBuffer& operator=(const RenderBuffer& renderBuffer) = delete;
			RenderBuffer& operator=(RenderBuffer&& renderBuffer) = delete;

			uint32_t getHandle() const;
			TextureInternalFormat getInternalFormat() const;
			const scp::u32vec2& getSize() const;

			~RenderBuffer();

		private:

			uint32_t _renderBuffer;
			TextureInternalFormat _internalFormat;
			scp::u32vec2 _size;
	};
}
