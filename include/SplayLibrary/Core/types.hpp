///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2019-2022
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

#include <SciPP/SciPP.hpp>
#include <DejaVu/DejaVu.hpp>


namespace spl
{
	enum class BufferTarget;
	enum class BufferUsage;
	namespace BufferStorageFlags { enum Flags; }
	class Buffer;

	struct VertexAttribute;
	enum class DrawableStorage;
	class Drawable;


	enum class TextureTarget;
	enum class TextureCubeMapTarget;
	enum class TextureFormat;
	enum class TextureDataType;
	enum class TextureInternalFormat;
	class RawTexture;
	class RenderBuffer;

	class TextureBase;
	class Texture2D;


	class Shader;


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

	class Window;

	class Context;
	class ContextManager;
}
