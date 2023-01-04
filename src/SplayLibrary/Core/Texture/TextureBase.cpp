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
	const RawTexture& TextureBase::getRawTexture() const
	{
		return _texture;
	}

	RawTexture& TextureBase::getRawTexture()
	{
		return _texture;
	}

	bool TextureBase::isValid() const
	{
		return _texture.isValid();
	}
}
