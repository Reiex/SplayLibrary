///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2021-2023
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <SplayLibrary/SplayLibraryTypes.hpp>

namespace spl
{
	namespace _spl
	{
		constexpr bool isIndexedBufferTarget(BufferTarget target);

		template<CGenType TValue> constexpr GlslType genTypeToGlslType();
		template<scp::CMat TMat> constexpr GlslType matTypeToGlslType();

		template<CGenType TValue> constexpr TextureInternalFormat genTypeToTextureInternalFormat();
		constexpr TextureFormat textureInternalFormatToTextureFormat(TextureInternalFormat internalFormat);
		constexpr TextureDataType textureInternalFormatToTextureDataType(TextureInternalFormat internalFormat);
		constexpr uint8_t textureInternalFormatToComponentCount(TextureInternalFormat internalFormat);

		constexpr BufferUsage drawableStorageToBufferUsage(DrawableStorage storage);
		constexpr BufferStorageFlags::Flags drawableStorageToBufferStorageFlags(DrawableStorage storage);
	}
}

#include <SplayLibrary/Private/templates/PrivateIncluded.hpp>
