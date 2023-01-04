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
	void Buffer::clear(const TClearValue& clearValue, uint32_t size, uint32_t dstOffset)
	{
		assert(isValid());
		assert(dstOffset + size <= _size);
		assert(dstOffset % sizeof(TClearValue) == 0);
		assert(size % sizeof(TClearValue) == 0);

		static_assert(_spl::genTypeToTextureInternalFormat<TClearValue>() != TextureInternalFormat::Undefined);

		constexpr TextureInternalFormat internalFormat = _spl::genTypeToTextureInternalFormat<TClearValue>();
		constexpr TextureFormat format = _spl::textureInternalFormatToTextureFormat(internalFormat);
		constexpr TextureDataType dataType = _spl::textureInternalFormatToTextureDataType(internalFormat);

		_clear(internalFormat, dstOffset, size, format, dataType, &clearValue);
	}
}
