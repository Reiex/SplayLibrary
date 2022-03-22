#pragma once

#include <SplayLibrary/Core/Texture2D.hpp>

namespace spl
{
	template<typename PixelType>
	Texture2D::Texture2D(const djv::Img<PixelType>& image, TextureInternalFormat internalFormat) : Texture2D()
	{
		createNew(image, internalFormat);
	}

	template<typename PixelType>
	void Texture2D::createNew(const djv::Img<PixelType>& image, TextureInternalFormat internalFormat)
	{
		const uvec2 size(image.width(), image.height());
		createNew(size, internalFormat);
		update(image, uvec2(0, 0));

		_size = size;
	}

	template<typename PixelType>
	void Texture2D::update(const djv::Img<PixelType>& image, const uvec2& offset)
	{
		RawTexture::UpdateParams params;
		params.data = nullptr;
		params.dataFormat = TextureFormat::Undefined;
		params.dataType = TextureDataType::Undefined;
		params.width = image.width();
		params.height = image.height();
		params.offsetX = offset.x;
		params.offsetY = offset.y;

		TextureBase::createDejaVuImgBuffer<PixelType>(image, _texture.getCreationParams().internalFormat, (void*&) params.data, params.dataFormat, params.dataType);

		_texture.update(params);

		delete params.data;
	}
}
