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
	Texture2D::Texture2D() : Texture()
	{
	}

	Texture2D::Texture2D(uint32_t width, uint32_t height, TextureInternalFormat internalFormat, uint32_t levels) : Texture2D()
	{
		createNew(width, height, internalFormat, levels);
	}

	Texture2D::Texture2D(const std::filesystem::path& path, TextureInternalFormat internalFormat, uint32_t levels) : Texture2D()
	{
		createNew(path, internalFormat, levels);
	}

	void Texture2D::createNew(uint32_t width, uint32_t height, TextureInternalFormat internalFormat, uint32_t levels)
	{
		TextureCreationParams creationParams;
		creationParams.target = TextureTarget::Texture2D;
		creationParams.internalFormat = internalFormat;
		creationParams.width = width;
		creationParams.height = height;
		creationParams.levels = levels;

		createNew(creationParams);
	}

	void Texture2D::createNew(const std::filesystem::path& path, TextureInternalFormat internalFormat, uint32_t levels)
	{
		Texture::ImageLoadInfos infos;
		_loadImageFromFile(path, internalFormat, infos);

		TextureCreationParams creationParams;
		creationParams.target = TextureTarget::Texture2D;
		creationParams.internalFormat = internalFormat;
		creationParams.width = infos.width;
		creationParams.height = infos.height;
		creationParams.levels = levels;

		createNew(creationParams);
		
		TextureUpdateParams updateParams;
		updateParams.data = infos.data;
		updateParams.dataFormat = infos.format;
		updateParams.dataType = infos.dataType;
		updateParams.width = infos.width;
		updateParams.height = infos.height;

		update(updateParams);

		(*infos.imageFree)(infos.image);
	}
}
