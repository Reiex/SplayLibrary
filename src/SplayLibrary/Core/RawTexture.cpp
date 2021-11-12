#include <SplayLibrary/SplayLibrary.hpp>
#include <SplayLibrary/Core/Private.hpp>

namespace spl
{
	namespace
	{
		GLenum textureTargetToGL(TextureTarget target)
		{
			switch (target)
			{
			case TextureTarget::Texture1D:
				return GL_TEXTURE_1D;
			case TextureTarget::Texture2D:
				return GL_TEXTURE_2D;
			case TextureTarget::Texture3D:
				return GL_TEXTURE_3D;
			case TextureTarget::Array1D:
				return GL_TEXTURE_1D_ARRAY;
			case TextureTarget::Array2D:
				return GL_TEXTURE_2D_ARRAY;
			case TextureTarget::Rectangle:
				return GL_TEXTURE_RECTANGLE;
			case TextureTarget::Buffer:
				return GL_TEXTURE_BUFFER;
			case TextureTarget::CubeMap:
				return GL_TEXTURE_CUBE_MAP;
			case TextureTarget::CubeMapArray:
				return GL_TEXTURE_CUBE_MAP_ARRAY;
			case TextureTarget::Multisample2D:
				return GL_TEXTURE_2D_MULTISAMPLE;
			case TextureTarget::Multisample2DArray:
				return GL_TEXTURE_2D_MULTISAMPLE_ARRAY;
			default:
				assert(false);
				return 0;
			}
		}

		GLenum textureCubeMapTargetToGL(TextureCubeMapTarget target)
		{
			switch (target)
			{
			case TextureCubeMapTarget::PositiveX:
				return GL_TEXTURE_CUBE_MAP_POSITIVE_X;
			case TextureCubeMapTarget::NegativeX:
				return GL_TEXTURE_CUBE_MAP_NEGATIVE_X;
			case TextureCubeMapTarget::PositiveY:
				return GL_TEXTURE_CUBE_MAP_POSITIVE_Y;
			case TextureCubeMapTarget::NegativeY:
				return GL_TEXTURE_CUBE_MAP_NEGATIVE_Y;
			case TextureCubeMapTarget::PositiveZ:
				return GL_TEXTURE_CUBE_MAP_POSITIVE_Z;
			case TextureCubeMapTarget::NegativeZ:
				return GL_TEXTURE_CUBE_MAP_NEGATIVE_Z;
			default:
				assert(false);
				return 0;
			}
		}
	
		GLenum textureFormatToGL(TextureFormat format)
		{
			switch (format)
			{
			case TextureFormat::StencilIndex:
				return GL_STENCIL_INDEX;
			case TextureFormat::DepthComponent:
				return GL_DEPTH_COMPONENT;
			case TextureFormat::DepthStencil:
				return GL_DEPTH_STENCIL;
			case TextureFormat::R:
				return GL_RED;
			case TextureFormat::G:
				return GL_GREEN;
			case TextureFormat::B:
				return GL_BLUE;
			case TextureFormat::RG:
				return GL_RG;
			case TextureFormat::RGB:
				return GL_RGB;
			case TextureFormat::RGBA:
				return GL_RGBA;
			case TextureFormat::BGR:
				return GL_BGR;
			case TextureFormat::BGRA:
				return GL_BGRA;
			case TextureFormat::iR:
				return GL_RED_INTEGER;
			case TextureFormat::iG:
				return GL_GREEN_INTEGER;
			case TextureFormat::iB:
				return GL_BLUE_INTEGER;
			case TextureFormat::iRG:
				return GL_RG_INTEGER;
			case TextureFormat::iRGB:
				return GL_RGB_INTEGER;
			case TextureFormat::iRGBA:
				return GL_RGBA_INTEGER;
			case TextureFormat::iBGR:
				return GL_BGR_INTEGER;
			case TextureFormat::iBGRA:
				return GL_BGRA_INTEGER;
			default:
				assert(false);
				return 0;
			}
		}
	
		GLenum textureDataTypeToGL(TextureDataType dataType)
		{
			switch (dataType)
			{
			case TextureDataType::UnsignedByte:
				return GL_UNSIGNED_BYTE;
			case TextureDataType::Byte:
				return GL_BYTE;
			case TextureDataType::UnsignedShort:
				return GL_UNSIGNED_SHORT;
			case TextureDataType::Short:
				return GL_SHORT;
			case TextureDataType::UnsignedInt:
				return GL_UNSIGNED_INT;
			case TextureDataType::Int:
				return GL_INT;
			case TextureDataType::HalfFloat:
				return GL_HALF_FLOAT;
			case TextureDataType::Float:
				return GL_FLOAT;
			case TextureDataType::UnsignedByte_3_3_2:
				return GL_UNSIGNED_BYTE_3_3_2;
			case TextureDataType::UnsignedByte_2_3_3_Rev:
				return GL_UNSIGNED_BYTE_2_3_3_REV;
			case TextureDataType::UnsignedShort_5_6_5:
				return GL_UNSIGNED_SHORT_5_6_5;
			case TextureDataType::UnsignedShort_5_6_5_Rev:
				return GL_UNSIGNED_SHORT_5_6_5_REV;
			case TextureDataType::UnsignedShort_4_4_4_4:
				return GL_UNSIGNED_SHORT_4_4_4_4;
			case TextureDataType::UnsignedShort_4_4_4_4_Rev:
				return GL_UNSIGNED_SHORT_4_4_4_4_REV;
			case TextureDataType::UnsignedShort_5_5_5_1:
				return GL_UNSIGNED_SHORT_5_5_5_1;
			case TextureDataType::UnsignedShort_1_5_5_5_Rev:
				return GL_UNSIGNED_SHORT_1_5_5_5_REV;
			case TextureDataType::UnsignedInt_8_8_8_8:
				return GL_UNSIGNED_INT_8_8_8_8;
			case TextureDataType::UnsignedInt_8_8_8_8_Rev:
				return GL_UNSIGNED_INT_8_8_8_8_REV;
			case TextureDataType::UnsignedInt_10_10_10_2:
				return GL_UNSIGNED_INT_10_10_10_2;
			case TextureDataType::UnsignedInt_2_10_10_10_Rev:
				return GL_UNSIGNED_INT_2_10_10_10_REV;
			case TextureDataType::UnsignedInt_24_8:
				return GL_UNSIGNED_INT_24_8;
			case TextureDataType::UnsignedInt_10F_11F_11F_Rev:
				return GL_UNSIGNED_INT_10F_11F_11F_REV;
			case TextureDataType::UnsignedInt_5_9_9_9_Rev:
				return GL_UNSIGNED_INT_5_9_9_9_REV;
			case TextureDataType::Float32_UnsignedInt_24_8_Rev:
				return GL_FLOAT_32_UNSIGNED_INT_24_8_REV;
			default:
				assert(false);
				return 0;
			}
		}
		
		GLenum textureInternalFormatToGL(TextureInternalFormat internalFormat)
		{
			switch (internalFormat)
			{
			case TextureInternalFormat::R8:
				return GL_R8;
			case TextureInternalFormat::R8_SNORM:
				return GL_R8_SNORM;
			case TextureInternalFormat::R16:
				return GL_R16;
			case TextureInternalFormat::R16_SNORM:
				return GL_R16_SNORM;
			case TextureInternalFormat::RG8:
				return GL_RG8;
			case TextureInternalFormat::RG8_SNORM:
				return GL_RG8_SNORM;
			case TextureInternalFormat::R3_G3_B2:
				return GL_R3_G3_B2;
			case TextureInternalFormat::RGB4:
				return GL_RGB4;
			case TextureInternalFormat::RGB5:
				return GL_RGB5;
			case TextureInternalFormat::RGB565:
				return GL_RGB565;
			case TextureInternalFormat::RGB8:
				return GL_RGB8;
			case TextureInternalFormat::RGB8_SNORM:
				return GL_RGB8_SNORM;
			case TextureInternalFormat::RGB10:
				return GL_RGB10;
			case TextureInternalFormat::RGB12:
				return GL_RGB12;
			case TextureInternalFormat::RGB16:
				return GL_RGB16;
			case TextureInternalFormat::RGB16_SNORM:
				return GL_RGB16_SNORM;
			case TextureInternalFormat::SRGB8:
				return GL_SRGB8;
			case TextureInternalFormat::SRGB8_ALPHA8:
				return GL_SRGB8_ALPHA8;
			case TextureInternalFormat::R16F:
				return GL_R16F;
			case TextureInternalFormat::RG16F:
				return GL_RG16F;
			case TextureInternalFormat::RGB16F:
				return GL_RGB16F;
			case TextureInternalFormat::RGBA16F:
				return GL_RGBA16F;
			case TextureInternalFormat::R32F:
				return GL_R32F;
			case TextureInternalFormat::RG32F:
				return GL_RG32F;
			case TextureInternalFormat::RGB32F:
				return GL_RGB32F;
			case TextureInternalFormat::RGBA32F:
				return GL_RGBA32F;
			case TextureInternalFormat::R11F_G11F_B10F:
				return GL_R11F_G11F_B10F;
			case TextureInternalFormat::RGB9_E5:
				return GL_RGB9_E5;
			case TextureInternalFormat::R8I:
				return GL_R8I;
			case TextureInternalFormat::R8UI:
				return GL_R8UI;
			case TextureInternalFormat::R16I:
				return GL_R16I;
			case TextureInternalFormat::R16UI:
				return GL_R16UI;
			case TextureInternalFormat::R32I:
				return GL_R32I;
			case TextureInternalFormat::R32UI:
				return GL_R32UI;
			case TextureInternalFormat::RG8I:
				return GL_RG8I;
			case TextureInternalFormat::RG8UI:
				return GL_RG8UI;
			case TextureInternalFormat::RG16I:
				return GL_RG16I;
			case TextureInternalFormat::RG16UI:
				return GL_RG16UI;
			case TextureInternalFormat::RG32I:
				return GL_RG32I;
			case TextureInternalFormat::RG32UI:
				return GL_RG32UI;
			case TextureInternalFormat::RGB8I:
				return GL_RGB8I;
			case TextureInternalFormat::RGB8UI:
				return GL_RGB8UI;
			case TextureInternalFormat::RGB16I:
				return GL_RGB16I;
			case TextureInternalFormat::RGB16UI:
				return GL_RGB16UI;
			case TextureInternalFormat::RGB32I:
				return GL_RGB32I;
			case TextureInternalFormat::RGB32UI:
				return GL_RGB32UI;
			case TextureInternalFormat::RGBA8I:
				return GL_RGBA8I;
			case TextureInternalFormat::RGBA8UI:
				return GL_RGBA8UI;
			case TextureInternalFormat::RGBA16I:
				return GL_RGBA16I;
			case TextureInternalFormat::RGBA16UI:
				return GL_RGBA16UI;
			case TextureInternalFormat::RGBA32I:
				return GL_RGBA32I;
			case TextureInternalFormat::RGBA32UI:
				return GL_RGBA32UI;
			case TextureInternalFormat::DEPTH_COMPONENT16:
				return GL_DEPTH_COMPONENT16;
			case TextureInternalFormat::DEPTH_COMPONENT24:
				return GL_DEPTH_COMPONENT24;
			case TextureInternalFormat::DEPTH_COMPONENT32:
				return GL_DEPTH_COMPONENT32;
			case TextureInternalFormat::DEPTH_COMPONENT32F:
				return GL_DEPTH_COMPONENT32F;
			case TextureInternalFormat::DEPTH24_STENCIL8:
				return GL_DEPTH24_STENCIL8;
			case TextureInternalFormat::DEPTH32F_STENCIL8:
				return GL_DEPTH32F_STENCIL8;
			case TextureInternalFormat::STENCIL_INDEX1:
				return GL_STENCIL_INDEX1;
			case TextureInternalFormat::STENCIL_INDEX4:
				return GL_STENCIL_INDEX4;
			case TextureInternalFormat::STENCIL_INDEX8:
				return GL_STENCIL_INDEX8;
			case TextureInternalFormat::STENCIL_INDEX16:
				return GL_STENCIL_INDEX16;
			default:
				assert(false);
				return 0;
			}
		}
	}

	RawTexture::RawTexture() :
		_texture(0),
		_target(TextureTarget::Undefined)
	{
	}

	void RawTexture::createNew(const CreationParams& params)
	{
		assert(textureTargetToGL(params.target) != 0);
		assert(textureInternalFormatToGL(params.internalFormat) != 0);

		destroy();

		_target = params.target;

		const uint32_t targetGL = textureTargetToGL(params.target);
		const uint32_t internalFormatGL = textureInternalFormatToGL(params.internalFormat);

		glGenTextures(1, &_texture);
		glBindTexture(targetGL, _texture);

		switch (_target)
		{
			case TextureTarget::Texture1D:
			{
				assert(params.levels > 0);
				assert(params.width > 0);

				glTexStorage1D(targetGL, params.levels, internalFormatGL, params.width);

				break;
			}
			case TextureTarget::Texture2D:
			{
				assert(params.levels > 0);
				assert(params.width > 0);
				assert(params.height > 0);

				glTexStorage2D(targetGL, params.levels, internalFormatGL, params.width, params.height);

				break;
			}
			case TextureTarget::Texture3D:
			{
				assert(params.levels > 0);
				assert(params.width > 0);
				assert(params.height > 0);
				assert(params.depth > 0);

				glTexStorage3D(targetGL, params.levels, internalFormatGL, params.width, params.height, params.depth);

				break;
			}
			case TextureTarget::Array1D:
			{
				assert(params.levels > 0);
				assert(params.width > 0);
				assert(params.layers > 0);

				glTexStorage2D(targetGL, params.levels, internalFormatGL, params.width, params.layers);

				break;
			}
			case TextureTarget::Array2D:
			{
				assert(params.levels > 0);
				assert(params.width > 0);
				assert(params.height > 0);
				assert(params.layers > 0);

				glTexStorage3D(targetGL, params.levels, internalFormatGL, params.width, params.height, params.layers);

				break;
			}
			case TextureTarget::Rectangle:
			{
				assert(params.width > 0);
				assert(params.height > 0);

				glTexStorage2D(targetGL, 1, internalFormatGL, params.width, params.height);

				break;
			}
			case TextureTarget::Buffer:
			{
				assert(params.buffer != nullptr);
				assert(params.bufferSize > 0);

				Buffer::bind(*params.buffer, BufferTarget::Texture);
				glTexBufferRange(targetGL, internalFormatGL, params.buffer->getHandle(), params.bufferOffset, params.bufferSize);
				Buffer::unbind(BufferTarget::Texture);

				break;
			}
			case TextureTarget::CubeMap:
			{
				assert(params.levels > 0);
				assert(params.width > 0);
				assert(params.height > 0);

				glTexStorage2D(targetGL, params.levels, internalFormatGL, params.width, params.height);

				break;
			}
			case TextureTarget::CubeMapArray:
			{
				assert(params.levels > 0);
				assert(params.width > 0);
				assert(params.height > 0);
				assert(params.layers > 0 && params.layers % 6 == 0);

				glTexStorage3D(targetGL, params.levels, internalFormatGL, params.width, params.height, params.layers);

				break;
			}
			case TextureTarget::Multisample2D:
			{
				assert(params.samples > 0);
				assert(params.width > 0);
				assert(params.height > 0);

				glTexImage2DMultisample(targetGL, params.samples, internalFormatGL, params.width, params.height, params.fixedSampleLocations);

				break;
			}
			case TextureTarget::Multisample2DArray:
			{
				assert(params.samples > 0);
				assert(params.width > 0);
				assert(params.height > 0);
				assert(params.depth > 0);

				glTexImage3DMultisample(targetGL, params.samples, internalFormatGL, params.width, params.height, params.depth, params.fixedSampleLocations);

				break;
			}
			default:
			{
				assert(false);
				destroy();
				break;
			}
		}

		glBindTexture(targetGL, 0);
	}

	void RawTexture::update(const UpdateParams& params)
	{
		assert(isValid());
		assert(textureFormatToGL(params.dataFormat) != 0);
		assert(textureDataTypeToGL(params.dataType) != 0);
		assert((params.data == nullptr) != (params.buffer == nullptr));

		const uint32_t targetGL = textureTargetToGL(_target);
		const uint32_t formatGL = textureFormatToGL(params.dataFormat);
		const uint32_t dataTypeGL = textureDataTypeToGL(params.dataType);

		void* data = params.data;
		if (params.buffer)
		{
			Buffer::bind(*params.buffer, BufferTarget::PixelUnpack);
			data = reinterpret_cast<void*>(params.bufferOffset);
		}
		else
		{
			Buffer::unbind(BufferTarget::PixelUnpack);
		}

		glBindTexture(targetGL, _texture);

		switch (_target)
		{
			case TextureTarget::Texture1D:
			{
				assert(params.width > 0);

				glTexSubImage1D(targetGL, params.level, params.offsetX, params.width, formatGL, dataTypeGL, data);

				break;
			}
			case TextureTarget::Texture2D:
			{
				assert(params.width > 0);
				assert(params.height > 0);

				glTexSubImage2D(targetGL, params.level, params.offsetX, params.offsetY, params.width, params.height, formatGL, dataTypeGL, data);

				break;
			}
			case TextureTarget::Texture3D:
			{
				assert(params.width > 0);
				assert(params.height > 0);
				assert(params.depth > 0);

				glTexSubImage3D(targetGL, params.level, params.offsetX, params.offsetY, params.offsetZ, params.width, params.height, params.depth, formatGL, dataTypeGL, data);

				break;
			}
			case TextureTarget::Array1D:
			{
				assert(params.width > 0);

				glTexSubImage2D(targetGL, params.level, params.offsetX, params.layer, params.width, 1, formatGL, dataTypeGL, data);
			}
			case TextureTarget::Array2D:
			{
				assert(params.width > 0);
				assert(params.height > 0);

				glTexSubImage3D(targetGL, params.level, params.offsetX, params.offsetY, params.layer, params.width, params.height, 1, formatGL, dataTypeGL, data);

				break;
			}
			case TextureTarget::Rectangle:
			{
				assert(params.width > 0);
				assert(params.height > 0);

				glTexSubImage2D(targetGL, 0, params.offsetX, params.offsetY, params.width, params.height, formatGL, dataTypeGL, data);

				break;
			}
			case TextureTarget::Buffer:
			{
				assert(false);
				break;
			}
			case TextureTarget::CubeMap:
			{
				assert(textureCubeMapTargetToGL(params.cubeMapTarget) != 0);
				assert(params.width > 0);
				assert(params.height > 0);

				glTexSubImage2D(textureCubeMapTargetToGL(params.cubeMapTarget), 0, params.offsetX, params.offsetY, params.width, params.height, formatGL, dataTypeGL, data);

				break;
			}
			case TextureTarget::CubeMapArray:
			{
				break;
				// TODO
			}
			case TextureTarget::Multisample2D:
			{
				assert(false);
				break;
			}
			case TextureTarget::Multisample2DArray:
			{
				assert(false);
				break;
			}
			default:
			{
				assert(false);
				break;
			}
		}

		if (params.buffer)
		{
			Buffer::unbind(BufferTarget::PixelUnpack);
		}

		glBindTexture(targetGL, 0);
	}

	void RawTexture::destroy()
	{
		if (_texture != 0)
		{
			glDeleteTextures(1, &_texture);
			_texture = 0;
			_target = TextureTarget::Undefined;
		}
	}

	uint32_t RawTexture::getHandle() const
	{
		return _texture;
	}

	TextureTarget RawTexture::getTextureTarget() const
	{
		return _target;
	}

	bool RawTexture::isValid() const
	{
		return _texture != 0;
	}

	void RawTexture::bind(const RawTexture& texture, TextureTarget target, uint32_t textureUnit)
	{
		assert(texture.isValid());
		assert(texture._target == target);
		// TODO: Verifier textureUnit valide

		glActiveTexture(GL_TEXTURE0 + textureUnit);
		glBindTexture(textureTargetToGL(target), texture._texture);
	}

	void RawTexture::unbind(TextureTarget target, uint32_t textureUnit)
	{
		assert(textureTargetToGL(target) != 0);
		// TODO: Verifier textureUnit valide

		glActiveTexture(GL_TEXTURE0 + textureUnit);
		glBindTexture(textureTargetToGL(target), 0);
	}

	RawTexture::~RawTexture()
	{
		destroy();
	}
}