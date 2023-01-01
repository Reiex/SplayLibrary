///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2019-2022
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SplayLibrary/SplayLibrary.hpp>
#include <SplayLibrary/Private/Private.hpp>

namespace spl
{
	Framebuffer::Framebuffer() :
		_framebuffer(),
		_textureAttachments(),
		_renderBufferAttachments()
	{
		glCreateFramebuffers(1, &_framebuffer);
	}

	Framebuffer::Framebuffer(Window* window) :
		_framebuffer(0),
		_textureAttachments(),
		_renderBufferAttachments()
	{
	}

	const TextureBase* Framebuffer::getTextureAttachment(FramebufferAttachment attachment) const
	{
		assert(_framebuffer != 0);

		const auto it = _textureAttachments.find(attachment);
		if (it != _textureAttachments.end())
		{
			return it->second;
		}
		else
		{
			return nullptr;
		}
	}

	void Framebuffer::createNewRenderBufferAttachment(FramebufferAttachment attachment, TextureInternalFormat internalFormat, const scp::u32vec2& size, uint32_t samples)
	{
		assert(_framebuffer != 0);
		assert(framebufferAttachmentToGL(attachment) != 0);

		auto textureIt = _textureAttachments.find(attachment);
		auto renderBufferIt = _renderBufferAttachments.find(attachment);

		if (textureIt != _textureAttachments.end())
		{
			delete textureIt->second;
			_textureAttachments.erase(textureIt);
		}
		else if (renderBufferIt != _renderBufferAttachments.end())
		{
			delete renderBufferIt->second;
		}

		// TODO: Check that the render buffer type and format correspond to the attachment
		_renderBufferAttachments[attachment] = new RenderBuffer(internalFormat, size, samples);
		glNamedFramebufferRenderbuffer(_framebuffer, framebufferAttachmentToGL(attachment), GL_RENDERBUFFER, _renderBufferAttachments[attachment]->getHandle());
	}

	const RenderBuffer* Framebuffer::getRenderBufferAttachment(FramebufferAttachment attachment) const
	{
		assert(_framebuffer != 0);

		const auto it = _renderBufferAttachments.find(attachment);
		if (it != _renderBufferAttachments.end())
		{
			return it->second;
		}
		else
		{
			return nullptr;
		}
	}

	void Framebuffer::removeAttachment(FramebufferAttachment attachment)
	{
		assert(_framebuffer != 0);

		auto textureIt = _textureAttachments.find(attachment);
		auto renderBufferIt = _renderBufferAttachments.find(attachment);

		if (textureIt != _textureAttachments.end())
		{
			delete textureIt->second;
			_textureAttachments.erase(textureIt);
		}
		else if (renderBufferIt != _renderBufferAttachments.end())
		{
			delete renderBufferIt->second;
		}
	}

	uint32_t Framebuffer::getHandle() const
	{
		return _framebuffer;
	}

	void Framebuffer::bind(const Framebuffer& framebuffer, FramebufferTarget target)
	{
		glBindFramebuffer(framebufferTargetToGL(target), framebuffer._framebuffer);
	}

	void Framebuffer::clear(bool color, bool depth, bool stencil)
	{
		GLbitfield bitfield = 0;
		
		if (color)
		{
			bitfield |= GL_COLOR_BUFFER_BIT;
		}
		if (depth)
		{
			bitfield |= GL_DEPTH_BUFFER_BIT;
		}
		if (stencil)
		{
			bitfield |= GL_STENCIL_BUFFER_BIT;
		}

		glClear(bitfield);
	}

	Framebuffer::~Framebuffer()
	{
		if (_framebuffer != 0)
		{
			glDeleteFramebuffers(1, &_framebuffer);
		}
	}

	void Framebuffer::_attachTexture(FramebufferAttachment attachment)
	{
		assert(framebufferAttachmentToGL(attachment) != 0);
		// TODO: Choose level / layer (glNamedFramebufferTextureLayer ?)
		// TODO: Check that the texture type and format correspond to the attachment
		glNamedFramebufferTexture(_framebuffer, framebufferAttachmentToGL(attachment), _textureAttachments[attachment]->getRawTexture().getHandle(), 0);
	}
}