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
		_attachments(Context::getCurrentContext()->getImplementationDependentValues().general.maxColorAttachments + 2, nullptr)
	{
		glCreateFramebuffers(1, &_framebuffer);
	}

	Framebuffer::Framebuffer(Window* window) :
		_framebuffer(0),
		_attachments()
	{
	}

	void Framebuffer::attachRenderbuffer(FramebufferAttachment attachment, uint32_t attachmentIndex, Renderbuffer* renderbuffer)
	{
		assert(isValid());
		assert(renderbuffer == nullptr || renderbuffer->isValid());
		assert(attachmentIndex == 0 || attachment == FramebufferAttachment::ColorAttachment);

		attachmentIndex += static_cast<uint32_t>(attachment);
		
		assert(attachmentIndex < _attachments.size());

		if (_attachments[attachmentIndex] != renderbuffer)
		{
			if (_attachments[attachmentIndex] != nullptr)
			{
				uint32_t i = 0;
				while (i < _attachments.size() && (_attachments[i] != _attachments[attachmentIndex] || i == attachmentIndex))
				{
					++i;
				}

				if (i == _attachments.size())
				{
					_attachments[attachmentIndex]->_framebufferAttached.erase(this);
				}
			}

			_attachments[attachmentIndex] = renderbuffer;
			_attachments[attachmentIndex]->_framebufferAttached.insert(this);

			const uint32_t name = renderbuffer ? renderbuffer->getHandle() : 0;
			glNamedFramebufferRenderbuffer(_framebuffer, _spl::attachmentIndexToGLenum(attachmentIndex), GL_RENDERBUFFER, name);
		}

		_updateDrawBuffers();
	}

	void Framebuffer::attachTexture(FramebufferAttachment attachment, uint32_t attachmentIndex, Texture* texture, uint32_t layer, uint32_t level)
	{
		assert(isValid());
		assert(texture == nullptr || texture->isValid());
		assert(attachmentIndex == 0 || attachment == FramebufferAttachment::ColorAttachment);

		attachmentIndex += static_cast<uint32_t>(attachment);

		assert(attachmentIndex < _attachments.size());

		if (_attachments[attachmentIndex] != texture)
		{
			if (_attachments[attachmentIndex] != nullptr)
			{
				uint32_t i = 0;
				while (i < _attachments.size() && (_attachments[i] != _attachments[attachmentIndex] || i == attachmentIndex))
				{
					++i;
				}

				if (i == _attachments.size())
				{
					_attachments[attachmentIndex]->_framebufferAttached.erase(this);
				}
			}

			_attachments[attachmentIndex] = texture;
			_attachments[attachmentIndex]->_framebufferAttached.insert(this);

			if (texture == nullptr)
			{
				glNamedFramebufferRenderbuffer(_framebuffer, _spl::attachmentIndexToGLenum(attachmentIndex), GL_RENDERBUFFER, 0);
			}
			else
			{
				const TextureCreationParams& params = texture->getCreationParams();

				assert(params.target != TextureTarget::Buffer);
				assert(level < params.levels);

				if (layer == -1)
				{
					glNamedFramebufferTexture(_framebuffer, _spl::attachmentIndexToGLenum(attachmentIndex), texture->getHandle(), level);
				}
				else
				{
					assert(
						params.target == TextureTarget::Texture3D
						|| params.target == TextureTarget::Array1D
						|| params.target == TextureTarget::Array2D
						|| params.target == TextureTarget::CubeMap
						|| params.target == TextureTarget::CubeMapArray
						|| params.target == TextureTarget::Multisample2DArray
					);
					assert(layer < params.depth);

					glNamedFramebufferTextureLayer(_framebuffer, _spl::attachmentIndexToGLenum(attachmentIndex), texture->getHandle(), level, layer);
				}
			}
		}

		_updateDrawBuffers();
	}

	bool Framebuffer::isValid() const
	{
		return _framebuffer != 0;
	}

	uint32_t Framebuffer::getHandle() const
	{
		return _framebuffer;
	}

	Framebuffer::~Framebuffer()
	{
		if (_framebuffer != 0)
		{
			for (FramebufferAttachable* attachment : _attachments)
			{
				if (attachment != nullptr)
				{
					attachment->_framebufferAttached.erase(this);
				}
			}

			glDeleteFramebuffers(1, &_framebuffer);
		}
	}

	void Framebuffer::bind(FramebufferTarget target, const Framebuffer* framebuffer)
	{
		Context::getCurrentContext()->_state.framebufferBindings[ContextState::framebufferTargetToIndex(target)] = framebuffer;

		if (framebuffer)
		{
			glBindFramebuffer(_spl::framebufferTargetToGLenum(target), framebuffer->_framebuffer);
		}
		else
		{
			glBindFramebuffer(_spl::framebufferTargetToGLenum(target), 0);
		}
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

	void Framebuffer::_removeAttachment(const FramebufferAttachable* attachment)
	{
		for (FramebufferAttachable*& elt : _attachments)
		{
			if (elt == attachment)
			{
				elt = nullptr;
			}
		}
	}

	void Framebuffer::_updateDrawBuffers()
	{
		std::vector<GLenum> drawBuffers;
		for (uint32_t i = 2; i < _attachments.size(); ++i)
		{
			if (_attachments[i] != nullptr)
			{
				drawBuffers.push_back(_spl::attachmentIndexToGLenum(i));
			}
		}

		glNamedFramebufferDrawBuffers(_framebuffer, drawBuffers.size(), drawBuffers.data());
	}
}
