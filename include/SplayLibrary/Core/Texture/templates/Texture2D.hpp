///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2019-2022
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <SplayLibrary/Core/Texture/Texture2D.hpp>

namespace spl
{
	template<djv::CPixel TPixel>
	Texture2D::Texture2D(const djv::Image<TPixel>& image, TextureInternalFormat internalFormat) : Texture2D()
	{
		createNew(image, internalFormat);
	}

	template<djv::CPixel TPixel>
	void Texture2D::createNew(const djv::Image<TPixel>& image, TextureInternalFormat internalFormat)
	{
		const uvec2 size(image.getWidth(), image.getHeight());
		createNew(size, internalFormat);
		update(image, uvec2(0, 0));

		_size = size;
	}

	template<djv::CPixel TPixel>
	void Texture2D::update(const djv::Image<TPixel>& image, const uvec2& offset)
	{
		RawTexture::UpdateParams params;
		params.data = nullptr;
		params.dataFormat = TextureFormat::Undefined;
		params.dataType = TextureDataType::Undefined;
		params.width = image.getWidth();
		params.height = image.getHeight();
		params.offsetX = offset.x;
		params.offsetY = offset.y;

		TextureBase::createDejaVuImgBuffer(image, _texture.getCreationParams().internalFormat, (void*&) params.data, params.dataFormat, params.dataType);

		_texture.update(params);

		delete params.data;
	}
}
