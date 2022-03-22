#pragma once

#include <SplayLibrary/Core/types.hpp>

namespace spl
{
	class Framebuffer
	{
		public:

			Framebuffer();
			Framebuffer(const Framebuffer& framebuffer) = delete;
			Framebuffer(Framebuffer&& framebuffer) = delete;

			Framebuffer& operator=(const Framebuffer& framebuffer) = delete;
			Framebuffer& operator=(Framebuffer&& framebuffer) = delete;

			~Framebuffer();

		private:

			uint32_t framebuffer;
	};
}
