///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2021-2023
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <algorithm>
#include <atomic>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdarg>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <SciPP/SciPPTypes.hpp>
#include <Diskon/DiskonTypes.hpp>
#include <DejaVu/DejaVuTypes.hpp>


namespace spl
{
	template<typename T> concept CGenType = scp::CVec<T> || scp::CNumber<T>;


	enum class BufferTarget;
	enum class BufferUsage;
	namespace BufferStorageFlags { enum Flags; }
	namespace BufferMapAccessFlags { enum Flags; }
	class Buffer;


	struct VertexAttribute;
	enum class DrawableStorage;
	enum class PrimitiveType;
	class Drawable;


	enum class TextureTarget;
	enum class TextureFormat;
	enum class TextureDataType;
	enum class TextureInternalFormat : uint64_t;
	class RawTexture;
	class RenderBuffer;

	class TextureBase;
	class Texture2D;


	class Shader;
	enum class ShaderStage;
	class ShaderModule;
	class ShaderProgram;
	class ShaderPipeline;


	enum class FramebufferTarget;
	enum class FramebufferAttachment;
	class Framebuffer;
	class DefaultFramebuffer;

	enum class EventType;
	struct Event;
	enum class KeyboardKey;
	enum class ButtonAction;
	namespace KeyboardModifier { enum ModifierFlags; };
	struct KeyboardEvent;
	struct TextEvent;
	struct MouseMoveEvent;
	struct MouseEnterWindowEvent;
	struct MouseLeaveWindowEvent;
	struct MouseButtonEvent;
	struct ScrollEvent;
	struct ResizeEvent;
	
	enum class CursorMode;
	class Window;

	enum class DebugMessageSource;
	enum class DebugMessageType;
	enum class DebugMessageSeverity;
	struct DebugMessage;
	class Context;
	class ContextManager;
}
