///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2021-2023
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <SplayLibrary/Private/PrivateNotIncluded.hpp>

namespace spl
{
	namespace _spl
	{
		constexpr DebugMessageSource glToDebugMessageSource(GLenum source)
		{
			switch (source)
			{
				case GL_DEBUG_SOURCE_API:
					return DebugMessageSource::Api;
				case GL_DEBUG_SOURCE_SHADER_COMPILER:
					return DebugMessageSource::ShaderCompiler;
				case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
					return DebugMessageSource::WindowSystem;
				case GL_DEBUG_SOURCE_THIRD_PARTY:
					return DebugMessageSource::ThirdParty;
				case GL_DEBUG_SOURCE_APPLICATION:
					return DebugMessageSource::Application;
				case GL_DEBUG_SOURCE_OTHER:
					return DebugMessageSource::Other;
				default:
					assert(false);
					return DebugMessageSource::Other;
			}
		}

		constexpr DebugMessageType glToDebugMessageType(GLenum type)
		{
			switch (type)
			{
				case GL_DEBUG_TYPE_ERROR:
					return DebugMessageType::Error;
				case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
					return DebugMessageType::DeprecatedBehavior;
				case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
					return DebugMessageType::UndefinedBehavior;
				case GL_DEBUG_TYPE_PERFORMANCE:
					return DebugMessageType::Performance;
				case GL_DEBUG_TYPE_PORTABILITY:
					return DebugMessageType::Portability;
				case GL_DEBUG_TYPE_MARKER:
					return DebugMessageType::Marker;
				case GL_DEBUG_TYPE_PUSH_GROUP:
					return DebugMessageType::PushGroup;
				case GL_DEBUG_TYPE_POP_GROUP:
					return DebugMessageType::PopGroup;
				case GL_DEBUG_TYPE_OTHER:
					return DebugMessageType::Other;
				default:
					assert(false);
					return DebugMessageType::Other;
			}
		}

		constexpr DebugMessageSeverity glToDebugMessageSeverity(GLenum severity)
		{
			switch (severity)
			{
				case GL_DEBUG_SEVERITY_HIGH:
					return DebugMessageSeverity::High;
				case GL_DEBUG_SEVERITY_MEDIUM:
					return DebugMessageSeverity::Medium;
				case GL_DEBUG_SEVERITY_LOW:
					return DebugMessageSeverity::Low;
				case GL_DEBUG_SEVERITY_NOTIFICATION:
					return DebugMessageSeverity::Notification;
				default:
					assert(false);
					return DebugMessageSeverity::High;
			}
		}


		constexpr GLenum bufferTargetToGL(BufferTarget target)
		{
			switch (target)
			{
				case BufferTarget::Array:
					return GL_ARRAY_BUFFER;
				case BufferTarget::AtomicCounter:
					return GL_ATOMIC_COUNTER_BUFFER;
				case BufferTarget::CopyRead:
					return GL_COPY_READ_BUFFER;
				case BufferTarget::CopyWrite:
					return GL_COPY_WRITE_BUFFER;
				case BufferTarget::DispatchIndirect:
					return GL_DISPATCH_INDIRECT_BUFFER;
				case BufferTarget::ElementArray:
					return GL_ELEMENT_ARRAY_BUFFER;
				case BufferTarget::Parameter:
					return GL_PARAMETER_BUFFER;
				case BufferTarget::PixelPack:
					return GL_PIXEL_PACK_BUFFER;
				case BufferTarget::PixelUnpack:
					return GL_PIXEL_UNPACK_BUFFER;
				case BufferTarget::Query:
					return GL_QUERY_BUFFER;
				case BufferTarget::ShaderStorage:
					return GL_SHADER_STORAGE_BUFFER;
				case BufferTarget::Texture:
					return GL_TEXTURE_BUFFER;
				case BufferTarget::TransformFeedback:
					return GL_TRANSFORM_FEEDBACK_BUFFER;
				case BufferTarget::Uniform:
					return GL_UNIFORM_BUFFER;
				default:
					assert(false);
					return 0;
			}
		}

		constexpr GLenum bufferUsageToGL(BufferUsage usage)
		{
			switch (usage)
			{
				case BufferUsage::StreamDraw:
					return GL_STREAM_DRAW;
				case BufferUsage::StreamRead:
					return GL_STREAM_READ;
				case BufferUsage::StreamCopy:
					return GL_STREAM_COPY;
				case BufferUsage::StaticDraw:
					return GL_STATIC_DRAW;
				case BufferUsage::StaticRead:
					return GL_STATIC_READ;
				case BufferUsage::StaticCopy:
					return GL_STATIC_COPY;
				case BufferUsage::DynamicDraw:
					return GL_DYNAMIC_DRAW;
				case BufferUsage::DynamicRead:
					return GL_DYNAMIC_READ;
				case BufferUsage::DynamicCopy:
					return GL_DYNAMIC_COPY;
				default:
					assert(false);
					return 0;
			}
		}

		constexpr GLbitfield bufferStorageFlagsToGL(BufferStorageFlags::Flags flags)
		{
			return (
					(  -((flags & BufferStorageFlags::DynamicStorage)	>> 0) & GL_DYNAMIC_STORAGE_BIT)
					| (-((flags & BufferStorageFlags::MapRead)			>> 1) & GL_MAP_READ_BIT)
					| (-((flags & BufferStorageFlags::MapWrite)			>> 2) & GL_MAP_WRITE_BIT)
					| (-((flags & BufferStorageFlags::MapPersistent)	>> 3) & GL_MAP_PERSISTENT_BIT)
					| (-((flags & BufferStorageFlags::MapCoherent)		>> 4) & GL_MAP_COHERENT_BIT)
					| (-((flags & BufferStorageFlags::ClientStorage)	>> 5) & GL_CLIENT_STORAGE_BIT)
				);
		}
	
		constexpr GLenum primitiveTypeToGL(PrimitiveType primitiveType)
		{
			switch (primitiveType)
			{
				case PrimitiveType::Points:
					return GL_POINTS;
				case PrimitiveType::Lines:
					return GL_LINES;
				case PrimitiveType::LineStrip:
					return GL_LINE_STRIP;
				case PrimitiveType::LineLoop:
					return GL_LINE_LOOP;
				case PrimitiveType::Triangles:
					return GL_TRIANGLES;
				case PrimitiveType::TriangleStrip:
					return GL_TRIANGLE_STRIP;
				case PrimitiveType::TriangleFan:
					return GL_TRIANGLE_FAN;
				default:
					assert(false);
					return 0;
			}
		}
	
		constexpr GLenum framebufferTargetToGL(FramebufferTarget target)
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

		constexpr GLenum framebufferAttachmentToGL(FramebufferAttachment attachment)
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
	
		constexpr GLenum textureTargetToGL(TextureTarget target)
		{
			switch (target)
			{
				case TextureTarget::Texture1D:
					return GL_TEXTURE_1D;
				case TextureTarget::Texture2D:
					return GL_TEXTURE_2D;
				case TextureTarget::Texture3D:
					return GL_TEXTURE_3D;
				case TextureTarget::Array1D:
					return GL_TEXTURE_1D_ARRAY;
				case TextureTarget::Array2D:
					return GL_TEXTURE_2D_ARRAY;
				case TextureTarget::Rectangle:
					return GL_TEXTURE_RECTANGLE;
				case TextureTarget::Buffer:
					return GL_TEXTURE_BUFFER;
				case TextureTarget::CubeMap:
					return GL_TEXTURE_CUBE_MAP;
				case TextureTarget::CubeMapArray:
					return GL_TEXTURE_CUBE_MAP_ARRAY;
				case TextureTarget::Multisample2D:
					return GL_TEXTURE_2D_MULTISAMPLE;
				case TextureTarget::Multisample2DArray:
					return GL_TEXTURE_2D_MULTISAMPLE_ARRAY;
				default:
					assert(false);
					return 0;
			}
		}

		constexpr GLenum textureFormatToGL(TextureFormat format)
		{
			switch (format)
			{
				case TextureFormat::StencilIndex:
					return GL_STENCIL_INDEX;
				case TextureFormat::DepthComponent:
					return GL_DEPTH_COMPONENT;
				case TextureFormat::DepthStencil:
					return GL_DEPTH_STENCIL;
				case TextureFormat::R:
					return GL_RED;
				case TextureFormat::G:
					return GL_GREEN;
				case TextureFormat::B:
					return GL_BLUE;
				case TextureFormat::RG:
					return GL_RG;
				case TextureFormat::RGB:
					return GL_RGB;
				case TextureFormat::RGBA:
					return GL_RGBA;
				case TextureFormat::BGR:
					return GL_BGR;
				case TextureFormat::BGRA:
					return GL_BGRA;
				case TextureFormat::iR:
					return GL_RED_INTEGER;
				case TextureFormat::iG:
					return GL_GREEN_INTEGER;
				case TextureFormat::iB:
					return GL_BLUE_INTEGER;
				case TextureFormat::iRG:
					return GL_RG_INTEGER;
				case TextureFormat::iRGB:
					return GL_RGB_INTEGER;
				case TextureFormat::iRGBA:
					return GL_RGBA_INTEGER;
				case TextureFormat::iBGR:
					return GL_BGR_INTEGER;
				case TextureFormat::iBGRA:
					return GL_BGRA_INTEGER;
				default:
					assert(false);
					return 0;
			}
		}

		constexpr GLenum textureDataTypeToGL(TextureDataType dataType)
		{
			switch (dataType)
			{
				case TextureDataType::UnsignedByte:
					return GL_UNSIGNED_BYTE;
				case TextureDataType::Byte:
					return GL_BYTE;
				case TextureDataType::UnsignedShort:
					return GL_UNSIGNED_SHORT;
				case TextureDataType::Short:
					return GL_SHORT;
				case TextureDataType::UnsignedInt:
					return GL_UNSIGNED_INT;
				case TextureDataType::Int:
					return GL_INT;
				case TextureDataType::HalfFloat:
					return GL_HALF_FLOAT;
				case TextureDataType::Float:
					return GL_FLOAT;
				case TextureDataType::UnsignedByte_3_3_2:
					return GL_UNSIGNED_BYTE_3_3_2;
				case TextureDataType::UnsignedByte_2_3_3_Rev:
					return GL_UNSIGNED_BYTE_2_3_3_REV;
				case TextureDataType::UnsignedShort_5_6_5:
					return GL_UNSIGNED_SHORT_5_6_5;
				case TextureDataType::UnsignedShort_5_6_5_Rev:
					return GL_UNSIGNED_SHORT_5_6_5_REV;
				case TextureDataType::UnsignedShort_4_4_4_4:
					return GL_UNSIGNED_SHORT_4_4_4_4;
				case TextureDataType::UnsignedShort_4_4_4_4_Rev:
					return GL_UNSIGNED_SHORT_4_4_4_4_REV;
				case TextureDataType::UnsignedShort_5_5_5_1:
					return GL_UNSIGNED_SHORT_5_5_5_1;
				case TextureDataType::UnsignedShort_1_5_5_5_Rev:
					return GL_UNSIGNED_SHORT_1_5_5_5_REV;
				case TextureDataType::UnsignedInt_8_8_8_8:
					return GL_UNSIGNED_INT_8_8_8_8;
				case TextureDataType::UnsignedInt_8_8_8_8_Rev:
					return GL_UNSIGNED_INT_8_8_8_8_REV;
				case TextureDataType::UnsignedInt_10_10_10_2:
					return GL_UNSIGNED_INT_10_10_10_2;
				case TextureDataType::UnsignedInt_2_10_10_10_Rev:
					return GL_UNSIGNED_INT_2_10_10_10_REV;
				case TextureDataType::UnsignedInt_24_8:
					return GL_UNSIGNED_INT_24_8;
				case TextureDataType::UnsignedInt_10F_11F_11F_Rev:
					return GL_UNSIGNED_INT_10F_11F_11F_REV;
				case TextureDataType::UnsignedInt_5_9_9_9_Rev:
					return GL_UNSIGNED_INT_5_9_9_9_REV;
				case TextureDataType::Float32_UnsignedInt_24_8_Rev:
					return GL_FLOAT_32_UNSIGNED_INT_24_8_REV;
				default:
					assert(false);
					return 0;
			}
		}

		constexpr GLenum textureInternalFormatToGL(TextureInternalFormat internalFormat)
		{
			switch (internalFormat)
			{
				case TextureInternalFormat::R_u8:
					return GL_R8UI;
				case TextureInternalFormat::R_i8:
					return GL_R8I;
				case TextureInternalFormat::R_nu8:
					return GL_R8;
				case TextureInternalFormat::R_ni8:
					return GL_R8_SNORM;
				case TextureInternalFormat::R_u16:
					return GL_R16UI;
				case TextureInternalFormat::R_i16:
					return GL_R16I;
				case TextureInternalFormat::R_f16:
					return GL_R16F;
				case TextureInternalFormat::R_nu16:
					return GL_R16;
				case TextureInternalFormat::R_ni16:
					return GL_R16_SNORM;
				case TextureInternalFormat::R_u32:
					return GL_R32UI;
				case TextureInternalFormat::R_i32:
					return GL_R32I;
				case TextureInternalFormat::R_f32:
					return GL_R32F;
				case TextureInternalFormat::RG_u8:
					return GL_RG8UI;
				case TextureInternalFormat::RG_i8:
					return GL_RG8I;
				case TextureInternalFormat::RG_nu8:
					return GL_RG8;
				case TextureInternalFormat::RG_ni8:
					return GL_RG8_SNORM;
				case TextureInternalFormat::RG_u16:
					return GL_RG16UI;
				case TextureInternalFormat::RG_i16:
					return GL_RG16I;
				case TextureInternalFormat::RG_f16:
					return GL_RG16F;
				case TextureInternalFormat::RG_nu16:
					return GL_RG16;
				case TextureInternalFormat::RG_ni16:
					return GL_RG16_SNORM;
				case TextureInternalFormat::RG_u32:
					return GL_RG32UI;
				case TextureInternalFormat::RG_i32:
					return GL_RG32I;
				case TextureInternalFormat::RG_f32:
					return GL_RG32F;
				case TextureInternalFormat::RGB_u8:
					return GL_RGB8UI;
				case TextureInternalFormat::RGB_i8:
					return GL_RGB8I;
				case TextureInternalFormat::RGB_nu8:
					return GL_RGB8;
				case TextureInternalFormat::RGB_ni8:
					return GL_RGB8_SNORM;
				case TextureInternalFormat::RGB_u16:
					return GL_RGB16UI;
				case TextureInternalFormat::RGB_i16:
					return GL_RGB16I;
				case TextureInternalFormat::RGB_f16:
					return GL_RGB16F;
				case TextureInternalFormat::RGB_nu16:
					return GL_RGB16;
				case TextureInternalFormat::RGB_ni16:
					return GL_RGB16_SNORM;
				case TextureInternalFormat::RGB_u32:
					return GL_RGB32UI;
				case TextureInternalFormat::RGB_i32:
					return GL_RGB32I;
				case TextureInternalFormat::RGB_f32:
					return GL_RGB32F;
				case TextureInternalFormat::RGBA_u8:
					return GL_RGBA8UI;
				case TextureInternalFormat::RGBA_i8:
					return GL_RGBA8I;
				case TextureInternalFormat::RGBA_nu8:
					return GL_RGBA8;
				case TextureInternalFormat::RGBA_ni8:
					return GL_RGBA8_SNORM;
				case TextureInternalFormat::RGBA_u16:
					return GL_RGBA16UI;
				case TextureInternalFormat::RGBA_i16:
					return GL_RGBA16I;
				case TextureInternalFormat::RGBA_f16:
					return GL_RGBA16F;
				case TextureInternalFormat::RGBA_nu16:
					return GL_RGBA16;
				case TextureInternalFormat::RGBA_ni16:
					return GL_RGBA16_SNORM;
				case TextureInternalFormat::RGBA_u32:
					return GL_RGBA32UI;
				case TextureInternalFormat::RGBA_i32:
					return GL_RGBA32I;
				case TextureInternalFormat::RGBA_f32:
					return GL_RGBA32F;
				case TextureInternalFormat::Depth_nu16:
					return GL_DEPTH_COMPONENT16;
				case TextureInternalFormat::Depth_nu24:
					return GL_DEPTH_COMPONENT24;
				case TextureInternalFormat::Depth_nu32:
					return GL_DEPTH_COMPONENT32;
				case TextureInternalFormat::Depth_f32:
					return GL_DEPTH_COMPONENT32F;
				case TextureInternalFormat::Stencil_u1:
					return GL_STENCIL_INDEX1;
				case TextureInternalFormat::Stencil_u4:
					return GL_STENCIL_INDEX4;
				case TextureInternalFormat::Stencil_u8:
					return GL_STENCIL_INDEX8;
				case TextureInternalFormat::Stencil_u16:
					return GL_STENCIL_INDEX16;
				case TextureInternalFormat::Depth_nu24_Stencil_u8:
					return GL_DEPTH24_STENCIL8;
				case TextureInternalFormat::Depth_f32_Stencil_u8:
					return GL_DEPTH32F_STENCIL8;
				case TextureInternalFormat::RGB_nu4:
					return GL_RGB4;
				case TextureInternalFormat::RGB_nu5:
					return GL_RGB5;
				case TextureInternalFormat::RGB_nu10:
					return GL_RGB10;
				case TextureInternalFormat::RGB_nu12:
					return GL_RGB12;
				case TextureInternalFormat::R_nu3_G_nu3_B_nu2:
					return GL_R3_G3_B2;
				case TextureInternalFormat::R_nu5_G_nu6_B_nu5:
					return GL_RGB565;
				case TextureInternalFormat::R_f11_G_f11_B_f10:
					return GL_R11F_G11F_B10F;
				case TextureInternalFormat::RGBA_nu2:
					return GL_RGBA2;
				case TextureInternalFormat::RGBA_nu4:
					return GL_RGBA4;
				case TextureInternalFormat::RGBA_nu12:
					return GL_RGBA12;
				case TextureInternalFormat::RGB_nu5_A_nu1:
					return GL_RGB5_A1;
				case TextureInternalFormat::RGB_u10_A_u2:
					return GL_RGB10_A2UI;
				case TextureInternalFormat::RGB_nu10_A_nu2:
					return GL_RGB10_A2;
				default:
					assert(false);
					return 0;
			}
		}
	}
}
