///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2021-2023
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SplayLibrary/SplayLibrary.hpp>
#include <SplayLibrary/Private/Private.hpp>

namespace spl
{
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
