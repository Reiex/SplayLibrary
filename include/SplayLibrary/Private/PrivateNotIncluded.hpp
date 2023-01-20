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

		constexpr GLenum bufferTargetToGLenum(BufferTarget target);
		constexpr GLenum bufferUsageToGLenum(BufferUsage usage);
		constexpr GLbitfield bufferStorageFlagsToGLbitfield(BufferStorageFlags::Flags flags);
		constexpr GLbitfield bufferMapAccessFlagsToGLbitfield(BufferMapAccessFlags::Flags flags);

		constexpr GLenum shaderStageToGLenum(ShaderStage::Stage stage);
		constexpr GLbitfield shaderStageToGLbitfield(ShaderStage::Stage stage);
		constexpr GLenum shaderProgramInterfaceToGLenum(ShaderProgramInterface programInterface);

		constexpr GLenum textureTargetToGLenum(TextureTarget target);
		constexpr GLenum textureFormatToGLenum(TextureFormat format);
		constexpr GLenum textureDataTypeToGLenum(TextureDataType dataType);
		constexpr GLenum textureInternalFormatToGLenum(TextureInternalFormat internalFormat);

		constexpr GLenum framebufferTargetToGLenum(FramebufferTarget target);
		constexpr GLenum framebufferAttachmentToGLenum(FramebufferAttachment attachment);

		constexpr GLenum primitiveTypeToGLenum(PrimitiveType primitiveType);
	}
}

#include <SplayLibrary/Private/templates/PrivateNotIncluded.hpp>
