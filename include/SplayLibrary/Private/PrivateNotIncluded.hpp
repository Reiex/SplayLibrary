///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2021-2023
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <SplayLibrary/Private/PrivateIncluded.hpp>

namespace spl
{
	namespace _spl
	{
		constexpr GLenum bufferTargetToGLenum(BufferTarget target);
		constexpr GLenum bufferUsageToGLenum(BufferUsage usage);
		constexpr GLbitfield bufferStorageFlagsToGLbitfield(BufferStorageFlags::Flags flags);
		constexpr GLbitfield bufferMapAccessFlagsToGLbitfield(BufferMapAccessFlags::Flags flags);

		constexpr GLenum compareFuncToGLenum(CompareFunc func);
		constexpr GLenum textureCompareModeToGLenum(TextureCompareMode mode);
		constexpr GLenum textureFilteringToGLenum(TextureFiltering filtering);
		constexpr GLenum textureWrappingToGLenum(TextureWrapping wrapping);

		constexpr GLenum textureTargetToGLenum(TextureTarget target);
		constexpr GLenum textureFormatToGLenum(TextureFormat format);
		constexpr GLenum textureDataTypeToGLenum(TextureDataType dataType);
		constexpr GLenum textureInternalFormatToGLenum(TextureInternalFormat internalFormat);

		constexpr GLenum shaderStageToGLenum(ShaderStage::Stage stage);
		constexpr GLbitfield shaderStageToGLbitfield(ShaderStage::Stage stage);
		constexpr GLenum shaderProgramInterfaceToGLenum(ShaderProgramInterface programInterface);
		constexpr GlslType glToGlslType(GLenum type);

		constexpr GLenum primitiveTypeToGLenum(PrimitiveType primitiveType);
		constexpr GLenum indexTypeToGLenum(IndexType indexType);

		constexpr GLenum framebufferTargetToGLenum(FramebufferTarget target);
		constexpr GLenum attachmentIndexToGLenum(uint32_t index);

		constexpr DebugMessageSource glToDebugMessageSource(GLenum source);
		constexpr DebugMessageType glToDebugMessageType(GLenum type);
		constexpr DebugMessageSeverity glToDebugMessageSeverity(GLenum severity);
		constexpr ContextReleaseBehaviour glToContextReleaseBehaviour(GLenum behaviour);
		constexpr ProvokingVertexConvention glToProvokingVertexConvention(GLenum convention);
		constexpr ContextFlags::Flags glToContextFlags(GLbitfield flags);
		constexpr ContextProfileMask::Flags glToContextProfileMask(GLbitfield flags);
		constexpr GLenum blendEquationToGLenum(BlendEquation equation);
		constexpr GLenum blendFuncToGLenum(BlendFunc func);
	}
}

#include <SplayLibrary/Private/templates/PrivateNotIncluded.hpp>
