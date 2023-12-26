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
	Renderbuffer::Renderbuffer(uint32_t width, uint32_t height, TextureInternalFormat internalFormat, uint32_t samples) :
		_renderbuffer(0),
		_size(width, height),
		_internalFormat(internalFormat),
		_samples(samples)
	{
		glCreateRenderbuffers(1, &_renderbuffer);
		glNamedRenderbufferStorageMultisample(_renderbuffer, _samples, _spl::textureInternalFormatToGLenum(_internalFormat), _size.x, _size.y);
	}

	bool Renderbuffer::isValid() const
	{
		return _renderbuffer != 0;
	}

	uint32_t Renderbuffer::getHandle() const
	{
		return _renderbuffer;
	}

	const scp::u32vec2& Renderbuffer::getSize() const
	{
		return _size;
	}

	TextureInternalFormat Renderbuffer::getInternalFormat() const
	{
		return _internalFormat;
	}

	uint32_t Renderbuffer::getSampleCount() const
	{
		return _samples;
	}

	Renderbuffer::~Renderbuffer()
	{
		_detachFramebuffers();
		glDeleteRenderbuffers(1, &_renderbuffer);
	}
}
