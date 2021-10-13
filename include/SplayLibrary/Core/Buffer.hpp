#pragma once

#include <SplayLibrary/Core/types.hpp>

namespace spl
{
	enum class BufferBindingTarget
	{
		Array,
		AtomicCounter,
		CopyRead,
		CopyWrite,
		DispatchIndirect,
		ElementArray,
		Parameter,
		PixelPack,
		PixelUnpack,
		Query,
		ShaderStorage,
		Texture,
		TransformFeedback,
		Uniform
	};

	enum class BufferUsage
	{
		Undefined,
		StreamDraw,
		StreamRead,
		StreamCopy,
		StaticDraw,
		StaticRead,
		StaticCopy,
		DynamicDraw,
		DynamicRead,
		DynamicCopy
	};

	enum class BufferStorageFlags
	{
		None			= 0,
		DynamicStorage	= 1 << 0,
		MapRead			= 1 << 1,
		MapWrite		= 1 << 2,
		MapPersistent	= 1 << 3,
		MapCoherent		= 1 << 4,
		ClientStorage	= 1 << 5
	};

	BufferStorageFlags operator|(BufferStorageFlags a, BufferStorageFlags b);
	BufferStorageFlags operator&(BufferStorageFlags a, BufferStorageFlags b);

	/*
	A buffer is an encapsulation of an OpenGL buffer.
	The user chooses the properties of the underlying OpenGL buffer.
	All the operations remains possible (might be at high cost).
	*/
	class Buffer
	{
		public:

			Buffer();
			Buffer(uint32_t size, const void* data, BufferUsage usage);
			Buffer(uint32_t size, const void* data, BufferStorageFlags flags);
			Buffer(const Buffer& buffer);
			Buffer(Buffer&& buffer);

			Buffer& operator=(const Buffer& buffer);
			Buffer& operator=(Buffer&& buffer);

			void createNew(uint32_t size, const void* data, BufferUsage usage);
			void createNew(uint32_t size, const void* data, BufferStorageFlags flags);
			void copyFrom(const Buffer& buffer);
			void moveFrom(Buffer&& buffer);
			// void update(uint32_t offset, uint32_t size, const void* data);
			// void update(uint32_t srcOffset, uint32_t dstOffset, uint32_t size, const Buffer& data);
			void destroy();

			bool isValid() const;

			static void bind(const Buffer& buffer, BufferBindingTarget target);
			static void unbind(BufferBindingTarget target);

			~Buffer();

		private:

			uint32_t _buffer;
			uint32_t _size;
			BufferUsage _usage;
			BufferStorageFlags _flags;

	};
}
