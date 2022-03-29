#pragma once

#include <SplayLibrary/Core/types.hpp>
#include <SplayLibrary/Core/Framebuffer.hpp>

namespace spl
{
	class WindowFramebuffer : public Framebuffer
	{
		public:

			WindowFramebuffer() = delete;
			WindowFramebuffer(const WindowFramebuffer& framebuffer) = delete;
			WindowFramebuffer(WindowFramebuffer&& framebuffer) = delete;

			WindowFramebuffer& operator=(const WindowFramebuffer& framebuffer) = delete;
			WindowFramebuffer& operator=(WindowFramebuffer&& framebuffer) = delete;

		private:

			WindowFramebuffer(Window* window);
			
			using Framebuffer::createNewTextureAttachment;
			using Framebuffer::getTextureAttachment;
			using Framebuffer::createNewRenderBufferAttachment;
			using Framebuffer::getRenderBufferAttachment;
			using Framebuffer::removeAttachment;
			
			~WindowFramebuffer() = default;

		friend class Window;
	};
}
