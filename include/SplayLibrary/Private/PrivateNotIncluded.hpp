///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2021-2023
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <SplayLibrary/Core/glad/glad.hpp>
#include <GLFW/glfw3.h>

#include <SplayLibrary/Private/PrivateIncluded.hpp>

namespace spl
{
	namespace _spl
	{
		constexpr DebugMessageSource glToDebugMessageSource(GLenum source);
		constexpr DebugMessageType glToDebugMessageType(GLenum type);
		constexpr DebugMessageSeverity glToDebugMessageSeverity(GLenum severity);

		constexpr GLenum bufferTargetToGL(BufferTarget target);
		constexpr GLenum bufferUsageToGL(BufferUsage usage);
		constexpr GLbitfield bufferStorageFlagsToGL(BufferStorageFlags::Flags flags);
		constexpr GLbitfield bufferMapAccessFlagsToGL(BufferMapAccessFlags::Flags flags);

		constexpr GLenum primitiveTypeToGL(PrimitiveType primitiveType);

		constexpr GLenum framebufferTargetToGL(FramebufferTarget target);
		constexpr GLenum framebufferAttachmentToGL(FramebufferAttachment attachment);

		constexpr GLenum textureTargetToGL(TextureTarget target);
		constexpr GLenum textureFormatToGL(TextureFormat format);
		constexpr GLenum textureDataTypeToGL(TextureDataType dataType);
		constexpr GLenum textureInternalFormatToGL(TextureInternalFormat internalFormat);
	}
}

#include <SplayLibrary/Private/templates/PrivateNotIncluded.hpp>
