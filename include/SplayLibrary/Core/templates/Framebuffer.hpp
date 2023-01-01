///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2019-2022
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <SplayLibrary/Core/Framebuffer.hpp>

namespace spl
{
	template<typename TextureType, typename... Args>
	void Framebuffer::createNewTextureAttachment(FramebufferAttachment attachment, Args&&... args)
	{
		assert(_framebuffer != 0);

		auto textureIt = _textureAttachments.find(attachment);
		auto renderBufferIt = _renderBufferAttachments.find(attachment);

		if (textureIt != _textureAttachments.end())
		{
			delete textureIt->second;
		}
		else if (renderBufferIt != _renderBufferAttachments.end())
		{
			delete renderBufferIt->second;
			_renderBufferAttachments.erase(renderBufferIt);
		}

		_textureAttachments[attachment] = new TextureType(args...);
		_attachTexture(attachment);
	}
}
