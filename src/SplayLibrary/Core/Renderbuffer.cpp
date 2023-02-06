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
	Renderbuffer::Renderbuffer(TextureInternalFormat internalFormat, uint32_t width, uint32_t height, uint32_t samples) :
		_renderbuffer(0),
		_internalFormat(internalFormat),
		_size(width, height)
	{
		assert(_spl::textureInternalFormatToGLenum(internalFormat) != 0);

		glCreateRenderbuffers(1, &_renderbuffer);
		glNamedRenderbufferStorageMultisample(_renderbuffer, samples, _spl::textureInternalFormatToGLenum(_internalFormat), _size.x, _size.y);
	}

	uint32_t Renderbuffer::getHandle() const
	{
		return _renderbuffer;
	}

	TextureInternalFormat Renderbuffer::getInternalFormat() const
	{
		return _internalFormat;
	}

	const scp::u32vec2& Renderbuffer::getSize() const
	{
		return _size;
	}

	Renderbuffer::~Renderbuffer()
	{
		glDeleteRenderbuffers(1, &_renderbuffer);
	}
}
