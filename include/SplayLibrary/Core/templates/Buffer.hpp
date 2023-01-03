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
	template<scp::CNumber TNumber>
	void Buffer::clear(const TNumber& value, uint32_t size, uint32_t dstOffset)
	{
		assert(isValid());
		assert(dstOffset + size <= _size);
		assert(dstOffset % sizeof(TNumber) == 0);
		assert(size % sizeof(TNumber) == 0);

		static_assert(sizeof(TNumber) == 1 || sizeof(TNumber) == 2 || sizeof(TNumber) == 4);

		if constexpr (sizeof(TNumber) == 1)
		{
			_clear(TextureInternalFormat::R8UI, dstOffset, size, TextureFormat::iR, TextureDataType::UnsignedByte, &value);
		}
		else if constexpr (sizeof(TNumber) == 2)
		{
			_clear(TextureInternalFormat::R16UI, dstOffset, size, TextureFormat::iR, TextureDataType::UnsignedShort, &value);
		}
		else if constexpr (sizeof(TNumber) == 4)
		{
			_clear(TextureInternalFormat::R32UI, dstOffset, size, TextureFormat::iR, TextureDataType::UnsignedInt, &value);
		}
	}

	template<scp::CVec TVec>
	void Buffer::clear(const TVec& value, uint32_t size, uint32_t dstOffset)
	{
		using TValue = typename TVec::ValueType;

		assert(isValid());
		assert(dstOffset + size <= _size);
		assert(dstOffset % sizeof(TVec) == 0);
		assert(size % sizeof(TVec) == 0);

		static_assert(sizeof(TValue) == 1 || sizeof(TValue) == 2 || sizeof(TValue) == 4);

		if constexpr (value.size == 2)
		{
			if constexpr (sizeof(TValue) == 1)
			{
				_clear(TextureInternalFormat::RG8UI, dstOffset, size, TextureFormat::iRG, TextureDataType::UnsignedByte, &value);
			}
			else if constexpr (sizeof(TValue) == 2)
			{
				_clear(TextureInternalFormat::RG16UI, dstOffset, size, TextureFormat::iRG, TextureDataType::UnsignedShort, &value);
			}
			else if constexpr (sizeof(TValue) == 4)
			{
				_clear(TextureInternalFormat::RG32UI, dstOffset, size, TextureFormat::iRG, TextureDataType::UnsignedInt, &value);
			}
		}
		else if constexpr (value.size == 3)
		{
			if constexpr (sizeof(TValue) == 1)
			{
				_clear(TextureInternalFormat::RGB8UI, dstOffset, size, TextureFormat::iRGB, TextureDataType::UnsignedByte, &value);
			}
			else if constexpr (sizeof(TValue) == 2)
			{
				_clear(TextureInternalFormat::RGB16UI, dstOffset, size, TextureFormat::iRGB, TextureDataType::UnsignedShort, &value);
			}
			else if constexpr (sizeof(TValue) == 4)
			{
				_clear(TextureInternalFormat::RGB32UI, dstOffset, size, TextureFormat::iRGB, TextureDataType::UnsignedInt, &value);
			}
		}
		else if constexpr (value.size == 4)
		{
			if constexpr (sizeof(TValue) == 1)
			{
				_clear(TextureInternalFormat::RGBA8UI, dstOffset, size, TextureFormat::iRGBA, TextureDataType::UnsignedByte, &value);
			}
			else if constexpr (sizeof(TValue) == 2)
			{
				_clear(TextureInternalFormat::RGBA16UI, dstOffset, size, TextureFormat::iRGBA, TextureDataType::UnsignedShort, &value);
			}
			else if constexpr (sizeof(TValue) == 4)
			{
				_clear(TextureInternalFormat::RGBA32UI, dstOffset, size, TextureFormat::iRGBA, TextureDataType::UnsignedInt, &value);
			}
		}
	}
}
