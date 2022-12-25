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
	using uvec2 = scp::u32vec2;	using uvec3 = scp::u32vec3;	using uvec4 = scp::u32vec4;
	using ivec2 = scp::i32vec2;	using ivec3 = scp::i32vec3;	using ivec4 = scp::i32vec4;
	using vec2 = scp::f32vec2;	using vec3 = scp::f32vec3;	using vec4 = scp::f32vec4;
	using dvec2 = scp::f64vec2;	using dvec3 = scp::f64vec3;	using dvec4 = scp::f64vec4;

	using mat2x2 = scp::f32mat2x2;	using mat2x3 = scp::f32mat2x3;	using mat2x4 = scp::f32mat2x4;
	using mat3x2 = scp::f32mat3x2;	using mat3x3 = scp::f32mat3x3;	using mat3x4 = scp::f32mat3x4;
	using mat4x2 = scp::f32mat4x2;	using mat4x3 = scp::f32mat4x3;	using mat4x4 = scp::f32mat4x4;
	using mat2 = mat2x2; using mat3 = mat3x3; using mat4 = mat4x4;
 
	using dmat2x2 = scp::f64mat2x2;	using dmat2x3 = scp::f64mat2x3;	using dmat2x4 = scp::f64mat2x4;
	using dmat3x2 = scp::f64mat3x2;	using dmat3x3 = scp::f64mat3x3;	using dmat3x4 = scp::f64mat3x4;
	using dmat4x2 = scp::f64mat4x2;	using dmat4x3 = scp::f64mat4x3;	using dmat4x4 = scp::f64mat4x4;
	using dmat2 = dmat2x2; using dmat3 = dmat3x3; using dmat4 = dmat4x4;


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
