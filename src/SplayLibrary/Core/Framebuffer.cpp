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
	Framebuffer::Framebuffer() :
		_framebuffer(),
		_textureAttachments(),
		_renderbufferAttachments()
	{
		glCreateFramebuffers(1, &_framebuffer);
	}

	Framebuffer::Framebuffer(Window* window) :
		_framebuffer(0),
		_textureAttachments(),
		_renderbufferAttachments()
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

	void Framebuffer::createNewRenderbufferAttachment(FramebufferAttachment attachment, TextureInternalFormat internalFormat, uint32_t width, uint32_t height, uint32_t samples)
	{
		assert(_framebuffer != 0);

		auto textureIt = _textureAttachments.find(attachment);
		auto renderbufferIt = _renderbufferAttachments.find(attachment);

		if (textureIt != _textureAttachments.end())
		{
			delete textureIt->second;
			_textureAttachments.erase(textureIt);
		}
		else if (renderbufferIt != _renderbufferAttachments.end())
		{
			delete renderbufferIt->second;
		}

		// TODO: Check that the render buffer type and format correspond to the attachment
		_renderbufferAttachments[attachment] = new Renderbuffer(internalFormat, width, height, samples);
		glNamedFramebufferRenderbuffer(_framebuffer, _spl::framebufferAttachmentToGLenum(attachment), GL_RENDERBUFFER, _renderbufferAttachments[attachment]->getHandle());
	}

	const Renderbuffer* Framebuffer::getRenderbufferAttachment(FramebufferAttachment attachment) const
	{
		assert(_framebuffer != 0);

		const auto it = _renderbufferAttachments.find(attachment);
		if (it != _renderbufferAttachments.end())
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
		auto renderbufferIt = _renderbufferAttachments.find(attachment);

		if (textureIt != _textureAttachments.end())
		{
			delete textureIt->second;
			_textureAttachments.erase(textureIt);
		}
		else if (renderbufferIt != _renderbufferAttachments.end())
		{
			delete renderbufferIt->second;
		}

		_updateDrawBuffers();
	}

	uint32_t Framebuffer::getHandle() const
	{
		return _framebuffer;
	}

	void Framebuffer::bind(const Framebuffer& framebuffer, FramebufferTarget target)
	{
		Context* context = Context::getCurrentContext();
		assert(context);

		context->_framebufferBindings[static_cast<uint32_t>(target)] = &framebuffer;

		glBindFramebuffer(_spl::framebufferTargetToGLenum(target), framebuffer._framebuffer);
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
		// TODO: Choose level / layer (glNamedFramebufferTextureLayer ?)
		// TODO: Check that the texture type and format correspond to the attachment
		glNamedFramebufferTexture(_framebuffer, _spl::framebufferAttachmentToGLenum(attachment), _textureAttachments[attachment]->getRawTexture().getHandle(), 0);

		_updateDrawBuffers();
	}

	void Framebuffer::_updateDrawBuffers()
	{
		std::vector<GLenum> drawBuffers;
		for (const std::pair<const FramebufferAttachment, TextureBase*>& textureAttachment : _textureAttachments)
		{
			if (textureAttachment.first != FramebufferAttachment::DepthAttachment
				&& textureAttachment.first != FramebufferAttachment::StencilAttachment
				&& textureAttachment.first != FramebufferAttachment::DepthStencilAttachment)
			{
				drawBuffers.push_back(_spl::framebufferAttachmentToGLenum(textureAttachment.first));
			}
		}

		glNamedFramebufferDrawBuffers(_framebuffer, drawBuffers.size(), drawBuffers.data());
	}
}