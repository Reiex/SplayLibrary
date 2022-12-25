///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2019-2022
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SplayLibrary/SplayLibrary.hpp>
#include <SplayLibrary/Private/Private.hpp>

namespace spl
{
	namespace
	{
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
					(-((flags & BufferStorageFlags::DynamicStorage) >> 0) & GL_DYNAMIC_STORAGE_BIT)
				|	(-((flags & BufferStorageFlags::MapRead)		>> 1) & GL_MAP_READ_BIT)
				|	(-((flags & BufferStorageFlags::MapWrite)		>> 2) & GL_MAP_WRITE_BIT)
				|	(-((flags & BufferStorageFlags::MapPersistent)	>> 3) & GL_MAP_PERSISTENT_BIT)
				|	(-((flags & BufferStorageFlags::MapCoherent)	>> 4) & GL_MAP_COHERENT_BIT)
				|	(-((flags & BufferStorageFlags::ClientStorage)	>> 5) & GL_CLIENT_STORAGE_BIT)
			);
		}
	}

	Buffer::Buffer() :
		_buffer(0),
		_size(0),
		_usage(BufferUsage::Undefined),
		_flags(BufferStorageFlags::None)
	{
	}

	Buffer::Buffer(uint32_t size, BufferUsage usage, const void* data) : Buffer()
	{
		createNew(size, usage, data);
	}

	Buffer::Buffer(uint32_t size, BufferStorageFlags::Flags flags, const void* data) : Buffer()
	{
		createNew(size, flags, data);
	}

	Buffer::Buffer(const Buffer& buffer) : Buffer()
	{
		copyFrom(buffer);
	}

	Buffer::Buffer(Buffer&& buffer) : Buffer()
	{
		moveFrom(std::move(buffer));
	}

	Buffer& Buffer::operator=(const Buffer& buffer)
	{
		copyFrom(buffer);
		return *this;
	}

	Buffer& Buffer::operator=(Buffer&& buffer)
	{
		moveFrom(std::move(buffer));
		return *this;
	}

	void Buffer::createNew(uint32_t size, BufferUsage usage, const void* data)
	{
		assert(size > 0);
		assert(bufferUsageToGL(usage) != 0);

		if (_usage == BufferUsage::Undefined)
		{
			destroy();
			glCreateBuffers(1, &_buffer);
		}

		glNamedBufferData(_buffer, size, data, bufferUsageToGL(usage));

		_size = size;
		_usage = usage;
		_flags = BufferStorageFlags::None;
	}

	void Buffer::createNew(uint32_t size, BufferStorageFlags::Flags flags, const void* data)
	{
		assert(size > 0);
		// TODO: Is it legal to not have dynamic_storage_bit but map_write_bit ?
		assert(!(flags & BufferStorageFlags::MapCoherent) || (flags & BufferStorageFlags::MapPersistent));
		assert(!(flags & BufferStorageFlags::MapPersistent) || (flags & BufferStorageFlags::MapRead) || (flags & BufferStorageFlags::MapWrite));

		if (_usage == BufferUsage::Undefined)
		{
			destroy();
			glCreateBuffers(1, &_buffer);
		}

		glNamedBufferStorage(_buffer, size, data, bufferStorageFlagsToGL(flags));

		_size = size;
		_usage = BufferUsage::Undefined;
		_flags = flags;
	}

	void Buffer::copyFrom(const Buffer& buffer)
	{
		assert(buffer.isValid());

		if (!isValid())
		{
			if (buffer._usage != BufferUsage::Undefined)
			{
				createNew(buffer._size, buffer._usage);
			}
			else
			{
				createNew(buffer._size, buffer._flags);
			}
		}
		else if (_size != buffer._size)
		{
			if (_usage != BufferUsage::Undefined)
			{
				createNew(buffer._size, _usage);
			}
			else
			{
				createNew(buffer._size, _flags);
			}
		}

		update(buffer, buffer._size);
	}

	void Buffer::moveFrom(Buffer&& buffer)
	{
		destroy();

		_buffer = buffer._buffer;
		_size = buffer._size;
		_usage = buffer._usage;
		_flags = buffer._flags;

		buffer._buffer = 0;
		buffer._size = 0;
		buffer._usage = BufferUsage::Undefined;
		buffer._flags = BufferStorageFlags::None;
	}

	void Buffer::update(const void* data, uint32_t size, uint32_t dstOffset)
	{
		assert(data);
		assert(isValid());
		assert(dstOffset + size <= _size);

		// TODO: Check for mappings, cannot be updated that way for some kinds of mappings...

		if (_usage != BufferUsage::Undefined || (_flags & BufferStorageFlags::DynamicStorage))
		{
			glNamedBufferSubData(_buffer, dstOffset, size, data);
		}
		else
		{
			Buffer tmp(size, BufferStorageFlags::None, data);
			update(tmp, size, dstOffset, 0);
		}
	}

	void Buffer::update(const Buffer& data, uint32_t size, uint32_t dstOffset, uint32_t srcOffset)
	{
		assert(isValid());
		assert(dstOffset + size <= _size);
		assert(data.isValid());
		assert(srcOffset + size <= data._size);

		glCopyNamedBufferSubData(data._buffer, _buffer, srcOffset, dstOffset, size);
	}

	void Buffer::destroy()
	{
		if (_buffer != 0)
		{
			glDeleteBuffers(1, &_buffer);
		}

		_buffer = 0;
		_size = 0;
		_usage = BufferUsage::Undefined;
		_flags = BufferStorageFlags::None;
	}

	uint32_t Buffer::getHandle() const
	{
		return _buffer;
	}

	uint32_t Buffer::getSize() const
	{
		return _size;
	}

	BufferUsage Buffer::getUsage() const
	{
		return _usage;
	}

	BufferStorageFlags::Flags Buffer::getStorageFlags() const
	{
		return _flags;
	}

	bool Buffer::isValid() const
	{
		return _buffer != 0;
	}

	void Buffer::bind(const Buffer& buffer, BufferTarget target)
	{
		assert(buffer.isValid());
		assert(bufferTargetToGL(target) != 0);

		glBindBuffer(bufferTargetToGL(target), buffer._buffer);
	}

	void Buffer::unbind(BufferTarget target)
	{
		assert(bufferTargetToGL(target) != 0);

		glBindBuffer(bufferTargetToGL(target), 0);
	}

	Buffer::~Buffer()
	{
		destroy();
	}
}
