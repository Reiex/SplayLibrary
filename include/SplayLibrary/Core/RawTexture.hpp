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

	enum class TextureCubeMapTarget
	{
		Undefined,
		PositiveX,
		NegativeX,
		PositiveY,
		NegativeY,
		PositiveZ,
		NegativeZ
	};

	enum class TextureFormat
	{
		Undefined,
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
		Undefined,
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
		R8,
		R8_SNORM,
		R16,
		R16_SNORM,
		RG8,
		RG8_SNORM,
		R3_G3_B2,
		RGB4,
		RGB5,
		RGB565,
		RGB8,
		RGB8_SNORM,
		RGB10,
		RGB12,
		RGB16,
		RGB16_SNORM,
		SRGB8,
		SRGB8_ALPHA8,
		R16F,
		RG16F,
		RGB16F,
		RGBA16F,
		R32F,
		RG32F,
		RGB32F,
		RGBA32F,
		R11F_G11F_B10F,
		RGB9_E5,
		R8I,
		R8UI,
		R16I,
		R16UI,
		R32I,
		R32UI,
		RG8I,
		RG8UI,
		RG16I,
		RG16UI,
		RG32I,
		RG32UI,
		RGB8I,
		RGB8UI,
		RGB16I,
		RGB16UI,
		RGB32I,
		RGB32UI,
		RGBA8I,
		RGBA8UI,
		RGBA16I,
		RGBA16UI,
		RGBA32I,
		RGBA32UI,
		DEPTH_COMPONENT16,
		DEPTH_COMPONENT24,
		DEPTH_COMPONENT32,
		DEPTH_COMPONENT32F,
		DEPTH24_STENCIL8,
		DEPTH32F_STENCIL8,
		STENCIL_INDEX1,
		STENCIL_INDEX4,
		STENCIL_INDEX8,
		STENCIL_INDEX16
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

				uint32_t layers = 0;
				uint32_t levels = 1;

				uint32_t samples = 0;
				bool fixedSampleLocations = false;
			};

			struct UpdateParams
			{
				TextureCubeMapTarget cubeMapTarget = TextureCubeMapTarget::Undefined;

				const Buffer* buffer = nullptr;
				uint32_t bufferOffset = 0;

				void* data = nullptr;

				TextureFormat dataFormat = TextureFormat::Undefined;
				TextureDataType dataType = TextureDataType::Undefined;

				uint32_t offsetX = 0;
				uint32_t offsetY = 0;
				uint32_t offsetZ = 0;

				uint32_t width = 0;
				uint32_t height = 0;
				uint32_t depth = 0;

				uint32_t layer = 0;
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

			uint32_t getHandle() const;
			TextureTarget getTextureTarget() const;
			bool isValid() const;

			static void bind(const RawTexture& texture, TextureTarget target, uint32_t textureUnit = 0);
			static void unbind(TextureTarget target, uint32_t textureUnit = 0);

			~RawTexture();

		private:

			uint32_t _texture;
			TextureTarget _target;
	};
}
