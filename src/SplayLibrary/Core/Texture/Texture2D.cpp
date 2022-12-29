///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2019-2022
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SplayLibrary/SplayLibrary.hpp>
#include <SplayLibrary/Private/Private.hpp>

namespace spl
{
	Texture2D::Texture2D() : TextureBase(),
		_size(0, 0)
	{
	}

	Texture2D::Texture2D(const uvec2& size, TextureInternalFormat internalFormat) : Texture2D()
	{
		createNew(size, internalFormat);
	}

	Texture2D::Texture2D(const uvec2& size, const uint8_t* data, TextureInternalFormat internalFormat) : Texture2D()
	{
		createNew(size, data, internalFormat);
	}

	Texture2D::Texture2D(const uvec2& size, const uint16_t* data, TextureInternalFormat internalFormat) : Texture2D()
	{
		createNew(size, data, internalFormat);
	}

	Texture2D::Texture2D(const uvec2& size, const uint32_t* data, TextureInternalFormat internalFormat) : Texture2D()
	{
		createNew(size, data, internalFormat);
	}

	Texture2D::Texture2D(const uvec2& size, const float* data, TextureInternalFormat internalFormat) : Texture2D()
	{
		createNew(size, data, internalFormat);
	}

	Texture2D::Texture2D(const std::filesystem::path& path, TextureInternalFormat internalFormat) : Texture2D()
	{
		createNew(path, internalFormat);
	}

	void Texture2D::createNew(const uvec2& size, TextureInternalFormat internalFormat)
	{
		RawTexture::CreationParams params;
		params.target = TextureTarget::Texture2D;
		params.internalFormat = internalFormat;
		params.width = size.x;
		params.height = size.y;

		_texture.createNew(params);

		_size = size;
	}

	void Texture2D::createNew(const uvec2& size, const uint8_t* data, TextureInternalFormat internalFormat)
	{
		createNew(size, internalFormat);
		update(size, data, uvec2(0, 0));
	}

	void Texture2D::createNew(const uvec2& size, const uint16_t* data, TextureInternalFormat internalFormat)
	{
		createNew(size, internalFormat);
		update(size, data, uvec2(0, 0));
	}

	void Texture2D::createNew(const uvec2& size, const uint32_t* data, TextureInternalFormat internalFormat)
	{
		createNew(size, internalFormat);
		update(size, data, uvec2(0, 0));
	}

	void Texture2D::createNew(const uvec2& size, const float* data, TextureInternalFormat internalFormat)
	{
		createNew(size, internalFormat);
		update(size, data, uvec2(0, 0));
	}

	void Texture2D::createNew(const std::filesystem::path& path, TextureInternalFormat internalFormat)
	{
		// TODO: Load only necessary components
		djv::Image<djv::Pixel<float, 4>> image(path.string());
		createNew(image, internalFormat);
	}

	void Texture2D::update(const uvec2& size, const uint8_t* data, const uvec2& offset)
	{
		RawTexture::UpdateParams params;
		params.data = data;
		params.dataFormat = TextureBase::getUsualTextureFormatOf(_texture.getCreationParams().internalFormat);
		params.dataType = TextureDataType::UnsignedByte;
		params.width = size.x;
		params.height = size.y;
		params.offsetX = offset.x;
		params.offsetY = offset.y;

		_texture.update(params);
	}

	void Texture2D::update(const uvec2& size, const uint16_t* data, const uvec2& offset)
	{
		RawTexture::UpdateParams params;
		params.data = data;
		params.dataFormat = TextureBase::getUsualTextureFormatOf(_texture.getCreationParams().internalFormat);
		params.dataType = TextureDataType::UnsignedShort;
		params.width = size.x;
		params.height = size.y;
		params.offsetX = offset.x;
		params.offsetY = offset.y;

		_texture.update(params);
	}

	void Texture2D::update(const uvec2& size, const uint32_t* data, const uvec2& offset)
	{
		RawTexture::UpdateParams params;
		params.data = data;
		params.dataFormat = TextureBase::getUsualTextureFormatOf(_texture.getCreationParams().internalFormat);
		params.dataType = TextureDataType::UnsignedInt;
		params.width = size.x;
		params.height = size.y;
		params.offsetX = offset.x;
		params.offsetY = offset.y;

		_texture.update(params);
	}

	void Texture2D::update(const uvec2& size, const float* data, const uvec2& offset)
	{
		RawTexture::UpdateParams params;
		params.data = data;
		params.dataFormat = TextureBase::getUsualTextureFormatOf(_texture.getCreationParams().internalFormat);
		params.dataType = TextureDataType::Float;
		params.width = size.x;
		params.height = size.y;
		params.offsetX = offset.x;
		params.offsetY = offset.y;

		_texture.update(params);
	}

	void Texture2D::update(const std::filesystem::path& path, const uvec2& offset)
	{
		// TODO: Load only necessary components
		djv::Image<djv::Pixel<float, 4>> image(path.string());
		update(image, offset);
	}

	void Texture2D::destroy()
	{
		_texture.destroy();
		_size = { 0, 0 };
	}

	const uvec2& Texture2D::getSize() const
	{
		return _size;
	}

	Texture2D::~Texture2D()
	{
		destroy();
	}
}
