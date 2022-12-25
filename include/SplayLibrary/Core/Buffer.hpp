///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2019-2022
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <SplayLibrary/Core/types.hpp>

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
			Buffer(uint32_t size, BufferUsage usage, const void* data = nullptr);
			Buffer(uint32_t size, BufferStorageFlags::Flags flags, const void* data = nullptr);
			Buffer(const Buffer& buffer);
			Buffer(Buffer&& buffer);

			Buffer& operator=(const Buffer& buffer);
			Buffer& operator=(Buffer&& buffer);


			void createNew(uint32_t size, BufferUsage usage, const void* data = nullptr);
			void createNew(uint32_t size, BufferStorageFlags::Flags flags, const void* data = nullptr);
			void copyFrom(const Buffer& buffer);	// Destroy/Recreate the buffer iff (this is invalid) or (sizes are different)
			void moveFrom(Buffer&& buffer);

			void update(const void* data, uint32_t size, uint32_t dstOffset = 0);
			void update(const Buffer& data, uint32_t size, uint32_t dstOffset = 0, uint32_t srcOffset = 0);
			// TODO: clearing
			// TODO: mapping

			void destroy();


			uint32_t getHandle() const;
			uint32_t getSize() const;
			BufferUsage getUsage() const;
			BufferStorageFlags::Flags getStorageFlags() const;
			bool isValid() const;


			static void bind(const Buffer& buffer, BufferTarget target);
			static void unbind(BufferTarget target);

			// TODO : Binding to indexed targets

			~Buffer();

		private:

			uint32_t _buffer;
			uint32_t _size;
			BufferUsage _usage;
			BufferStorageFlags::Flags _flags;
	};
}
