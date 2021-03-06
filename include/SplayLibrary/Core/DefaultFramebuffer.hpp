#pragma once

#include <SplayLibrary/Core/types.hpp>
#include <SplayLibrary/Core/Framebuffer.hpp>

namespace spl
{
	class DefaultFramebuffer : public Framebuffer
	{
		public:

			DefaultFramebuffer() = delete;
			DefaultFramebuffer(const DefaultFramebuffer& framebuffer) = delete;
			DefaultFramebuffer(DefaultFramebuffer&& framebuffer) = delete;

			DefaultFramebuffer& operator=(const DefaultFramebuffer& framebuffer) = delete;
			DefaultFramebuffer& operator=(DefaultFramebuffer&& framebuffer) = delete;

		private:

			DefaultFramebuffer(Window* window);
			
			using Framebuffer::createNewTextureAttachment;
			using Framebuffer::getTextureAttachment;
			using Framebuffer::createNewRenderBufferAttachment;
			using Framebuffer::getRenderBufferAttachment;
			using Framebuffer::removeAttachment;
			
			~DefaultFramebuffer() = default;

		friend class Window;
	};
}
