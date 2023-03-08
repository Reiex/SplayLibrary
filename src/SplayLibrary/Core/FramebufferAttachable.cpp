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
	void FramebufferAttachable::_detachFramebuffers()
	{
		for (Framebuffer* framebuffer : _framebufferAttached)
		{
			framebuffer->_removeAttachment(this);
		}

		_framebufferAttached.clear();
	}
}
