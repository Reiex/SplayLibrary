///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2021-2023
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <SplayLibrary/Core/CoreDecl.hpp>
#include <SplayLibrary/Private/PrivateIncluded.hpp>

namespace spl
{
	template<CGenType TClearValue>
	void Buffer::clear(const TClearValue& clearValue, uintptr_t size, uintptr_t offset)
	{
		static_assert(_spl::genTypeToTextureInternalFormat<TClearValue>() != TextureInternalFormat::Undefined);

		constexpr TextureInternalFormat internalFormat = _spl::genTypeToTextureInternalFormat<TClearValue>();
		constexpr TextureFormat format = _spl::textureInternalFormatToTextureFormat(internalFormat);
		constexpr TextureDataType dataType = _spl::textureInternalFormatToTextureDataType(internalFormat);

		_clear(internalFormat, offset, size, format, dataType, &clearValue, sizeof(TClearValue));
	}
}
