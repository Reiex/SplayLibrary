///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2021-2023
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <SplayLibrary/Core/CoreTypes.hpp>

namespace spl
{
	enum class BufferTarget
	{
		Array,
		AtomicCounter,
		CopyRead,
		CopyWrite,
		DispatchIndirect,
		DrawIndirect,
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


	/*
	
	Stream : Updated every frame
	Static : Updated very rarely - once every few seconds at most
	Dynamic : Other update frequencies (not at all frame, more often than once every few seconds...)

	Draw : Written by CPU, read by GPU
	Read : Written by GPU, read by CPU
	Copy : Written by GPU, read by GPU

	*/
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


	namespace BufferStorageFlags
	{
		enum Flags
		{
			None			= 0,
			DynamicStorage	= 1 << 0,
			MapRead			= 1 << 1,
			MapWrite		= 1 << 2,
			MapPersistent	= 1 << 3,
			MapCoherent		= 1 << 4,
			ClientStorage	= 1 << 5
		};
	}


	class Buffer
	{
		public:

			Buffer();
			Buffer(uintptr_t size, BufferUsage usage, const void* data = nullptr);
			Buffer(uintptr_t size, BufferStorageFlags::Flags flags, const void* data = nullptr);
			Buffer(const Buffer& buffer);
			Buffer(Buffer&& buffer);

			Buffer& operator=(const Buffer& buffer);
			Buffer& operator=(Buffer&& buffer);


			void createNew(uintptr_t size, BufferUsage usage, const void* data = nullptr);
			void createNew(uintptr_t size, BufferStorageFlags::Flags flags, const void* data = nullptr);
			void copyFrom(const Buffer& buffer);	// Destroy/Recreate the buffer iff (this is invalid) or (sizes are different)
			void moveFrom(Buffer&& buffer);

			void update(const void* data, uintptr_t size = -1, uintptr_t dstOffset = 0);
			void update(const Buffer& data, uintptr_t size = -1, uintptr_t dstOffset = 0, uintptr_t srcOffset = 0);
			template<CGenType TClearValue> void clear(const TClearValue& clearValue, uintptr_t size = -1, uintptr_t offset = 0);
			// TODO: mapping

			void destroy();


			uint32_t getHandle() const;
			uintptr_t getSize() const;
			BufferUsage getUsage() const;
			BufferStorageFlags::Flags getStorageFlags() const;
			bool isValid() const;


			static void bind(const Buffer& buffer, BufferTarget target, uint32_t index = -1, uintptr_t size = -1, uintptr_t offset = 0);
			static void unbind(BufferTarget target, uint32_t index = -1);
			// TODO : Binding of multiple buffers at the same time to indexed targets (glBindBuffersRange)

			~Buffer();

		private:

			void _clear(TextureInternalFormat internalFormat, uintptr_t offset, uintptr_t size, TextureFormat format, TextureDataType type, const void* data);

			uint32_t _buffer;
			uintptr_t _size;
			BufferUsage _usage;
			BufferStorageFlags::Flags _flags;
	};
}
