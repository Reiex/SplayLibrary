#include <SplayLibrary/SplayLibrary.hpp>
#include <SplayLibrary/Core/Private.hpp>

namespace spl
{
	namespace
	{
		GLenum framebufferTargetToGL(FramebufferTarget target)
		{
			switch (target)
			{
			case FramebufferTarget::DrawFramebuffer:
				return GL_DRAW_FRAMEBUFFER;
			case FramebufferTarget::ReadFramebuffer:
				return GL_READ_FRAMEBUFFER;
			default:
				assert(false);
				return 0;
			}
		}

		GLenum framebufferAttachmentToGL(FramebufferAttachment attachment)
		{
			switch (attachment)
			{
			case FramebufferAttachment::DepthAttachment:
				return GL_DEPTH_ATTACHMENT;
			case FramebufferAttachment::StencilAttachment:
				return GL_STENCIL_ATTACHMENT;
			case FramebufferAttachment::DepthStencilAttachment:
				return GL_DEPTH_STENCIL_ATTACHMENT;
			case FramebufferAttachment::ColorAttachment0:
				return GL_COLOR_ATTACHMENT0;
			case FramebufferAttachment::ColorAttachment1:
				return GL_COLOR_ATTACHMENT1;
			case FramebufferAttachment::ColorAttachment2:
				return GL_COLOR_ATTACHMENT2;
			case FramebufferAttachment::ColorAttachment3:
				return GL_COLOR_ATTACHMENT3;
			case FramebufferAttachment::ColorAttachment4:
				return GL_COLOR_ATTACHMENT4;
			case FramebufferAttachment::ColorAttachment5:
				return GL_COLOR_ATTACHMENT5;
			case FramebufferAttachment::ColorAttachment6:
				return GL_COLOR_ATTACHMENT6;
			case FramebufferAttachment::ColorAttachment7:
				return GL_COLOR_ATTACHMENT7;
			case FramebufferAttachment::ColorAttachment8:
				return GL_COLOR_ATTACHMENT8;
			case FramebufferAttachment::ColorAttachment9:
				return GL_COLOR_ATTACHMENT9;
			case FramebufferAttachment::ColorAttachment10:
				return GL_COLOR_ATTACHMENT10;
			case FramebufferAttachment::ColorAttachment11:
				return GL_COLOR_ATTACHMENT11;
			case FramebufferAttachment::ColorAttachment12:
				return GL_COLOR_ATTACHMENT12;
			case FramebufferAttachment::ColorAttachment13:
				return GL_COLOR_ATTACHMENT13;
			case FramebufferAttachment::ColorAttachment14:
				return GL_COLOR_ATTACHMENT14;
			case FramebufferAttachment::ColorAttachment15:
				return GL_COLOR_ATTACHMENT15;
			case FramebufferAttachment::ColorAttachment16:
				return GL_COLOR_ATTACHMENT16;
			case FramebufferAttachment::ColorAttachment17:
				return GL_COLOR_ATTACHMENT17;
			case FramebufferAttachment::ColorAttachment18:
				return GL_COLOR_ATTACHMENT18;
			case FramebufferAttachment::ColorAttachment19:
				return GL_COLOR_ATTACHMENT19;
			case FramebufferAttachment::ColorAttachment20:
				return GL_COLOR_ATTACHMENT20;
			case FramebufferAttachment::ColorAttachment21:
				return GL_COLOR_ATTACHMENT21;
			case FramebufferAttachment::ColorAttachment22:
				return GL_COLOR_ATTACHMENT22;
			case FramebufferAttachment::ColorAttachment23:
				return GL_COLOR_ATTACHMENT23;
			case FramebufferAttachment::ColorAttachment24:
				return GL_COLOR_ATTACHMENT24;
			case FramebufferAttachment::ColorAttachment25:
				return GL_COLOR_ATTACHMENT25;
			case FramebufferAttachment::ColorAttachment26:
				return GL_COLOR_ATTACHMENT26;
			case FramebufferAttachment::ColorAttachment27:
				return GL_COLOR_ATTACHMENT27;
			case FramebufferAttachment::ColorAttachment28:
				return GL_COLOR_ATTACHMENT28;
			case FramebufferAttachment::ColorAttachment29:
				return GL_COLOR_ATTACHMENT29;
			case FramebufferAttachment::ColorAttachment30:
				return GL_COLOR_ATTACHMENT30;
			case FramebufferAttachment::ColorAttachment31:
				return GL_COLOR_ATTACHMENT31;
			default:
				assert(false);
				return 0;
			}
		}
	}

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

	void Framebuffer::attachTexture(FramebufferAttachment attachment)
	{
		assert(framebufferAttachmentToGL(attachment) != 0);
		// TODO: Choose level / layer (glNamedFramebufferTextureLayer ?)
		// TODO: Check that the texture type and format correspond to the attachment
		glNamedFramebufferTexture(_framebuffer, framebufferAttachmentToGL(attachment), _textureAttachments[attachment]->getRawTexture().getHandle(), 0);
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

	void Framebuffer::createNewRenderBufferAttachment(FramebufferAttachment attachment, TextureInternalFormat internalFormat, const uvec2& size, uint32_t samples)
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

	void Framebuffer::clearColor(const vec4& color)
	{
		glClearColor(color.x, color.y, color.z, color.w);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Framebuffer::clearDepth(double depth)
	{
		glClearDepth(depth);
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	void Framebuffer::clearStencil(int32_t stencil)
	{
		glClearStencil(stencil);
		glClear(GL_STENCIL_BUFFER_BIT);
	}

	Framebuffer::~Framebuffer()
	{
		if (_framebuffer != 0)
		{
			glDeleteFramebuffers(1, &_framebuffer);
		}
	}
}