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
	RawTexture::RawTexture() :
		_texture(0),
		_creationParams()
	{
	}

	void RawTexture::createNew(const CreationParams& params)
	{
		assert(_spl::textureTargetToGL(params.target) != 0);
		assert(_spl::textureInternalFormatToGL(params.internalFormat) != 0);

		destroy();

		const uint32_t internalFormatGL = _spl::textureInternalFormatToGL(params.internalFormat);

		_creationParams = params;
		glCreateTextures(_spl::textureTargetToGL(params.target), 1, &_texture);

		switch (params.target)
		{
			case TextureTarget::Texture1D:
			{
				assert(params.levels > 0);
				assert(params.width > 0);

				glTextureStorage1D(_texture, params.levels, internalFormatGL, params.width);

				break;
			}
			case TextureTarget::Texture2D:
			case TextureTarget::Array1D:
			{
				assert(params.levels > 0);
				assert(params.width > 0);
				assert(params.height > 0);

				glTextureStorage2D(_texture, params.levels, internalFormatGL, params.width, params.height);

				break;
			}
			case TextureTarget::Texture3D:
			case TextureTarget::Array2D:
			{
				assert(params.levels > 0);
				assert(params.width > 0);
				assert(params.height > 0);
				assert(params.depth > 0);

				glTextureStorage3D(_texture, params.levels, internalFormatGL, params.width, params.height, params.depth);

				break;
			}
			case TextureTarget::Rectangle:
			{
				assert(params.levels == 1);
				assert(params.width > 0);
				assert(params.height > 0);

				glTextureStorage2D(_texture, params.levels, internalFormatGL, params.width, params.height);

				break;
			}
			case TextureTarget::Buffer:
			{
				assert(params.buffer != nullptr);
				assert(params.bufferSize > 0);

				Buffer::bind(*params.buffer, BufferTarget::Texture);
				glTextureBufferRange(_texture, internalFormatGL, params.buffer->getHandle(), params.bufferOffset, params.bufferSize);
				Buffer::unbind(BufferTarget::Texture);

				break;
			}
			case TextureTarget::CubeMap:
			{
				assert(params.levels > 0);
				assert(params.width > 0);
				assert(params.height > 0);
				assert(params.depth == 6);

				glTextureStorage2D(_texture, params.levels, internalFormatGL, params.width, params.height);

				break;
			}
			case TextureTarget::CubeMapArray:
			{
				assert(params.levels > 0);
				assert(params.width > 0);
				assert(params.height > 0);
				assert(params.depth > 0 && params.depth % 6 == 0);

				glTextureStorage3D(_texture, params.levels, internalFormatGL, params.width, params.height, params.depth);

				break;
			}
			case TextureTarget::Multisample2D:
			{
				assert(params.samples > 0);
				assert(params.width > 0);
				assert(params.height > 0);

				glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, _texture);
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, params.samples, internalFormatGL, params.width, params.height, params.fixedSampleLocations);
				glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);

				break;
			}
			case TextureTarget::Multisample2DArray:
			{
				assert(params.samples > 0);
				assert(params.width > 0);
				assert(params.height > 0);
				assert(params.depth > 0);

				glBindTexture(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, _texture);
				glTexImage3DMultisample(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, params.samples, internalFormatGL, params.width, params.height, params.depth, params.fixedSampleLocations);
				glBindTexture(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, 0);

				break;
			}
			default:
			{
				assert(false);
				destroy();
				break;
			}
		}
	}

	void RawTexture::update(const UpdateParams& params)
	{
		assert(isValid());
		assert((params.data == nullptr) != (params.buffer == nullptr));
		assert(_spl::textureFormatToGL(params.dataFormat) != 0);
		assert(_spl::textureDataTypeToGL(params.dataType) != 0);

		const uint32_t formatGL = _spl::textureFormatToGL(params.dataFormat);
		const uint32_t dataTypeGL = _spl::textureDataTypeToGL(params.dataType);

		const void* data = params.data;
		if (params.buffer)
		{
			Buffer::bind(*params.buffer, BufferTarget::PixelUnpack);
			data = reinterpret_cast<void*>(params.bufferOffset);
		}
		else
		{
			Buffer::unbind(BufferTarget::PixelUnpack);
		}

		switch (_creationParams.target)
		{
			case TextureTarget::Texture1D:
			{
				assert(params.level < _creationParams.levels);
				assert(params.width > 0 && params.offsetX + params.width <= _creationParams.width);

				glTextureSubImage1D(_texture, params.level, params.offsetX, params.width, formatGL, dataTypeGL, data);

				break;
			}
			case TextureTarget::Texture2D:
			case TextureTarget::Array1D:
			case TextureTarget::Rectangle:
			{
				assert(params.level < _creationParams.levels);
				assert(params.width > 0 && params.offsetX + params.width <= _creationParams.width);
				assert(params.height > 0 && params.offsetY + params.height <= _creationParams.height);

				glTextureSubImage2D(_texture, params.level, params.offsetX, params.offsetY, params.width, params.height, formatGL, dataTypeGL, data);

				break;
			}
			case TextureTarget::Texture3D:
			case TextureTarget::Array2D:
			case TextureTarget::CubeMap:
			case TextureTarget::CubeMapArray:
			{
				assert(params.level < _creationParams.levels);
				assert(params.width > 0 && params.offsetX + params.width <= _creationParams.width);
				assert(params.height > 0 && params.offsetY + params.height <= _creationParams.height);
				assert(params.depth > 0 && params.offsetZ + params.depth <= _creationParams.depth);

				glTextureSubImage3D(_texture, params.level, params.offsetX, params.offsetY, params.offsetZ, params.width, params.height, params.depth, formatGL, dataTypeGL, data);

				break;
			}
			case TextureTarget::Buffer:
			case TextureTarget::Multisample2D:
			case TextureTarget::Multisample2DArray:
			{
				assert(false);	// These textures cannot be updated this way.
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
	}

	void RawTexture::destroy()
	{
		if (_texture != 0)
		{
			glDeleteTextures(1, &_texture);
			_texture = 0;
			_creationParams = CreationParams();
		}
	}

	uint32_t RawTexture::getHandle() const
	{
		return _texture;
	}

	const RawTexture::CreationParams& RawTexture::getCreationParams() const
	{
		return _creationParams;
	}

	bool RawTexture::isValid() const
	{
		return _texture != 0;
	}

	void RawTexture::bind(const RawTexture& texture, TextureTarget target, uint32_t textureUnit)
	{
		assert(texture.isValid());
		assert(texture._creationParams.target == target);
		// TODO: Verifier textureUnit valide

		glActiveTexture(GL_TEXTURE0 + textureUnit);
		glBindTexture(_spl::textureTargetToGL(target), texture._texture);
	}

	void RawTexture::unbind(TextureTarget target, uint32_t textureUnit)
	{
		assert(_spl::textureTargetToGL(target) != 0);
		// TODO: Verifier textureUnit valide

		glActiveTexture(GL_TEXTURE0 + textureUnit);
		glBindTexture(_spl::textureTargetToGL(target), 0);
	}

	RawTexture::~RawTexture()
	{
		destroy();
	}


	RenderBuffer::RenderBuffer(TextureInternalFormat internalFormat, const scp::u32vec2& size, uint32_t samples) :
		_renderBuffer(0),
		_internalFormat(internalFormat),
		_size(size)
	{
		assert(_spl::textureInternalFormatToGL(internalFormat) != 0);

		glCreateRenderbuffers(1, &_renderBuffer);
		glNamedRenderbufferStorageMultisample(_renderBuffer, samples, _spl::textureInternalFormatToGL(internalFormat), size.x, size.y);
	}

	uint32_t RenderBuffer::getHandle() const
	{
		return _renderBuffer;
	}

	TextureInternalFormat RenderBuffer::getInternalFormat() const
	{
		return _internalFormat;
	}

	const scp::u32vec2& RenderBuffer::getSize() const
	{
		return _size;
	}

	RenderBuffer::~RenderBuffer()
	{
		glDeleteRenderbuffers(1, &_renderBuffer);
	}
}
