///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2021-2023
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SplayLibrary/Core/Core.hpp>
#include <SplayLibrary/Private/PrivateNotIncluded.hpp>

namespace spl
{
	Buffer::Buffer() :
		_buffer(0),
		_size(0),
		_usage(BufferUsage::Undefined),
		_storageFlags(BufferStorageFlags::None),
		_mapPtr(nullptr),
		_mapAccess(BufferMapAccessFlags::None),
		_mapSize(0),
		_mapOffset(0)
	{
	}

	Buffer::Buffer(uintptr_t size, BufferUsage usage, const void* data) : Buffer()
	{
		createNew(size, usage, data);
	}

	Buffer::Buffer(uintptr_t size, BufferStorageFlags::Flags flags, const void* data) : Buffer()
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

	void Buffer::createNew(uintptr_t size, BufferUsage usage, const void* data)
	{
		assert(size != 0);
		assert(_spl::bufferUsageToGLenum(usage) != 0);

		if (hasImmutableStorage())
		{
			destroy();
			glCreateBuffers(1, &_buffer);
		}

		glNamedBufferData(_buffer, size, data, _spl::bufferUsageToGLenum(usage));

		_size = size;
		_usage = usage;

		_mapPtr = nullptr;
		_mapAccess = BufferMapAccessFlags::None;
		_mapSize = 0;
		_mapOffset = 0;
	}

	void Buffer::createNew(uintptr_t size, BufferStorageFlags::Flags flags, const void* data)
	{
		assert(size != 0);
		assert(!(flags & BufferStorageFlags::MapPersistent) || (flags & BufferStorageFlags::MapRead) || (flags & BufferStorageFlags::MapWrite));
		assert(!(flags & BufferStorageFlags::MapCoherent) || (flags & BufferStorageFlags::MapPersistent));

		if (hasImmutableStorage())
		{
			destroy();
			glCreateBuffers(1, &_buffer);
		}

		glNamedBufferStorage(_buffer, size, data, _spl::bufferStorageFlagsToGLbitfield(flags));

		_size = size;
		_storageFlags = flags;

		_mapPtr = nullptr;
		_mapAccess = BufferMapAccessFlags::None;
		_mapSize = 0;
		_mapOffset = 0;
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
				createNew(buffer._size, buffer._storageFlags);
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
				createNew(buffer._size, _storageFlags);
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
		_storageFlags = buffer._storageFlags;

		_mapPtr = buffer._mapPtr;
		_mapAccess = buffer._mapAccess;
		_mapSize = buffer._mapSize;
		_mapOffset = buffer._mapOffset;


		buffer._buffer = 0;
		buffer._size = 0;
		buffer._usage = BufferUsage::Undefined;
		buffer._storageFlags = BufferStorageFlags::None;

		buffer._mapPtr = nullptr;
		buffer._mapAccess = BufferMapAccessFlags::None;
		buffer._mapSize = 0;
		buffer._mapOffset = 0;
	}

	void Buffer::update(const void* data, uintptr_t size, uintptr_t dstOffset)
	{
		size = size == -1 ? _size : size;

		assert(isValid());
		assert(data);
		assert(dstOffset + size <= _size);
		assert(!isMapped() || (_mapAccess & BufferMapAccessFlags::Persistent));

		if (_usage != BufferUsage::Undefined || (_storageFlags & BufferStorageFlags::DynamicStorage))
		{
			glNamedBufferSubData(_buffer, dstOffset, size, data);
		}
		else
		{
			Buffer tmp(size, BufferStorageFlags::None, data);
			update(tmp, size, dstOffset, 0);
		}
	}

	void Buffer::update(const Buffer& data, uintptr_t size, uintptr_t dstOffset, uintptr_t srcOffset)
	{
		size = size == -1 ? _size : size;

		assert(isValid());
		assert(data.isValid());
		assert(dstOffset + size <= _size);
		assert(srcOffset + size <= data._size);
		assert(&data != this || srcOffset + size <= dstOffset || dstOffset + size <= srcOffset);
		assert(!isMapped() || (_mapAccess & BufferMapAccessFlags::Persistent));

		glCopyNamedBufferSubData(data._buffer, _buffer, srcOffset, dstOffset, size);
	}

	void Buffer::map(BufferMapAccessFlags::Flags flags, uintptr_t size, uintptr_t offset)
	{
		assert(isValid());
		assert(!isMapped());
		assert((_storageFlags & BufferStorageFlags::MapRead) || !(flags & BufferMapAccessFlags::Read));
		assert((_storageFlags & BufferStorageFlags::MapWrite) || !(flags & BufferMapAccessFlags::Write));
		assert((_storageFlags & BufferStorageFlags::MapPersistent) || !(flags & BufferMapAccessFlags::Persistent));
		assert((_storageFlags & BufferStorageFlags::MapCoherent) || !(flags & BufferMapAccessFlags::Coherent));
		assert((flags & BufferMapAccessFlags::Read) || (flags & BufferMapAccessFlags::Write));
		assert(!(flags & BufferMapAccessFlags::Coherent) || (flags & BufferMapAccessFlags::Persistent));
		assert(!(flags & BufferMapAccessFlags::InvalidateRange) || !(flags & BufferMapAccessFlags::Read));
		assert(!(flags & BufferMapAccessFlags::InvalidateBuffer) || !(flags & BufferMapAccessFlags::Read));
		assert(!(flags & BufferMapAccessFlags::FlushExplicit) || (flags & BufferMapAccessFlags::Write));
		assert(!(flags & BufferMapAccessFlags::Unsynchronized) || !(flags & BufferMapAccessFlags::Read));

		if (size == -1)
		{
			assert(offset == 0);

			_mapPtr = glMapNamedBufferRange(_buffer, 0, _size, _spl::bufferMapAccessFlagsToGLbitfield(flags));
			_mapAccess = flags;
			_mapSize = _size;
			_mapOffset = 0;
		}
		else
		{
			assert(offset + size <= _size);

			_mapPtr = glMapNamedBufferRange(_buffer, offset, size, _spl::bufferMapAccessFlagsToGLbitfield(flags));
			_mapAccess = flags;
			_mapSize = size;
			_mapOffset = offset;
		}
	}

	void Buffer::flush(uintptr_t size, uintptr_t offset)
	{
		size = size == -1 ? _mapSize : size;

		assert(isValid());
		assert(isMapped());
		assert(_mapAccess & BufferMapAccessFlags::FlushExplicit);
		assert(offset + size <= _mapSize);

		glFlushMappedNamedBufferRange(_buffer, offset, size);
	}

	bool Buffer::unmap()
	{
		assert(isValid());
		assert(isMapped());

		_mapPtr = nullptr;
		_mapAccess = BufferMapAccessFlags::None;
		_mapSize = 0;
		_mapOffset = 0;

		return glUnmapNamedBuffer(_buffer);
	}

	void Buffer::invalidate(uintptr_t size, uintptr_t offset)
	{
		assert(isValid());

		if (size == -1)
		{
			assert(offset == 0);
			assert(!isMapped() || (_mapAccess & BufferMapAccessFlags::Persistent));

			glInvalidateBufferData(_buffer);
		}
		else
		{
			assert(!isMapped() || (_mapAccess & BufferMapAccessFlags::Persistent) || offset >= _mapOffset + _mapSize || offset + size <= _mapOffset);

			glInvalidateBufferSubData(_buffer, offset, size);
		}

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
		_storageFlags = BufferStorageFlags::None;

		_mapPtr = nullptr;
		_mapAccess = BufferMapAccessFlags::None;
		_mapSize = 0;
		_mapOffset = 0;
	}

	uint32_t Buffer::getHandle() const
	{
		return _buffer;
	}

	uintptr_t Buffer::getSize() const
	{
		return _size;
	}

	BufferUsage Buffer::getUsage() const
	{
		return _usage;
	}

	BufferStorageFlags::Flags Buffer::getStorageFlags() const
	{
		return _storageFlags;
	}

	const void* Buffer::getMapPointer() const
	{
		return _mapPtr;
	}

	void* Buffer::getMapPointer()
	{
		return _mapPtr;
	}

	BufferMapAccessFlags::Flags Buffer::getMapAccessFlags() const
	{
		return _mapAccess;
	}

	uintptr_t Buffer::getMapOffset() const
	{
		return _mapOffset;
	}

	uintptr_t Buffer::getMapSize() const
	{
		return _mapSize;
	}

	bool Buffer::isValid() const
	{
		return _buffer != 0;
	}

	bool Buffer::hasImmutableStorage() const
	{
		return _usage == BufferUsage::Undefined;
	}

	bool Buffer::isMapped() const
	{
		return _mapPtr != nullptr;
	}

	Buffer::~Buffer()
	{
		destroy();
	}

	void Buffer::bind(const Buffer& buffer, BufferTarget target, uint32_t index, uintptr_t size, uintptr_t offset)
	{
		assert(buffer.isValid());
		assert(_spl::bufferTargetToGLenum(target) != 0);

		Context* context = ContextManager::getCurrentContext();
		assert(context);

		if (_spl::isIndexedBufferTarget(target))
		{
			assert(index != -1);	// TODO: Check index is valid (not just -1 but the glGetInteger thing)

			if (size == -1)
			{
				assert(offset == 0);

				glBindBufferBase(_spl::bufferTargetToGLenum(target), index, buffer._buffer);
			}
			else
			{
				assert(offset + size <= buffer._size);

				glBindBufferRange(_spl::bufferTargetToGLenum(target), index, buffer._buffer, offset, size);
			}

			std::vector<const Buffer*>& contextBuffers = context->_indexedBufferBindings[_spl::bufferTargetContextIndex(target)];
			if (index >= contextBuffers.size())
			{
				contextBuffers.resize(index + 1, nullptr);
			}

			contextBuffers[index] = &buffer;
		}
		else
		{
			assert(index == -1);
			assert(size == -1);
			assert(offset == 0);

			glBindBuffer(_spl::bufferTargetToGLenum(target), buffer._buffer);

			context->_bufferBindings[_spl::bufferTargetContextIndex(target)] = &buffer;
		}
	}

	void Buffer::bind(const Buffer* const* buffers, uint32_t count, BufferTarget target, uint32_t firstIndex, const uintptr_t* sizes, const uintptr_t* offsets)
	{
		assert(_spl::bufferTargetToGLenum(target) != 0);
		assert(_spl::isIndexedBufferTarget(target));
		assert(firstIndex != -1);	// TODO: Check index is valid (not just -1 but the glGetInteger thing)

		// Get current context buffers and resize the vector if necessary

		Context* context = ContextManager::getCurrentContext();
		assert(context);

		std::vector<const Buffer*>& contextBuffers = context->_indexedBufferBindings[_spl::bufferTargetContextIndex(target)];
		if (firstIndex + count > contextBuffers.size())
		{
			contextBuffers.resize(firstIndex + count, nullptr);
		}

		// Create an array with all buffer names and update current context buffers

		uint32_t* names = reinterpret_cast<uint32_t*>(alloca(sizeof(uint32_t) * count));
		for (uint32_t i = 0, j = firstIndex; i < count; ++i, ++j)
		{
			if (buffers[i] == nullptr)
			{
				names[i] = 0;
				contextBuffers[j] = nullptr;
			}
			else
			{
				assert(buffers[i]->isValid());
				names[i] = buffers[i]->_buffer;
				contextBuffers[j] = buffers[i];
			}
		}

		// Bind the buffers

		if (sizes == nullptr)
		{
			assert(offsets == nullptr);

			glBindBuffersBase(_spl::bufferTargetToGLenum(target), firstIndex, count, names);
		}
		else
		{
			for (uint32_t i = 0; i < count; ++i)
			{
				if (buffers[i] != nullptr)
				{
					assert(offsets[i] + sizes[i] <= buffers[i]->_size);
				}
			}

			glBindBuffersRange(_spl::bufferTargetToGLenum(target), firstIndex, count, names, reinterpret_cast<const GLintptr*>(offsets), reinterpret_cast<const GLsizeiptr*>(sizes));
		}
	}

	void Buffer::unbind(BufferTarget target, uint32_t index, uint32_t count)
	{
		assert(_spl::bufferTargetToGLenum(target) != 0);

		Context* context = ContextManager::getCurrentContext();
		assert(context);

		if (_spl::isIndexedBufferTarget(target))
		{
			assert(index != -1);

			if (count == 1)
			{
				glBindBufferBase(_spl::bufferTargetToGLenum(target), index, 0);
			}
			else
			{
				glBindBuffersBase(_spl::bufferTargetToGLenum(target), index, count, nullptr);
			}

			std::vector<const Buffer*>& contextBuffers = context->_indexedBufferBindings[_spl::bufferTargetContextIndex(target)];
			if (index < contextBuffers.size())
			{
				contextBuffers[index] = nullptr;
			}
			else
			{
				contextBuffers.resize(index + 1, nullptr);
			}
		}
		else
		{
			assert(index == -1);

			glBindBuffer(_spl::bufferTargetToGLenum(target), 0);

			context->_bufferBindings[_spl::bufferTargetContextIndex(target)] = nullptr;
		}
	}

	void Buffer::_clear(TextureInternalFormat internalFormat, uintptr_t offset, uintptr_t size, TextureFormat format, TextureDataType type, const void* data, uint32_t granularity)
	{
		assert(isValid());
		assert(!isMapped() || (_mapAccess & BufferMapAccessFlags::Persistent));

		if (size == -1)
		{
			assert(offset == 0);
			assert(_size % granularity == 0);

			glClearNamedBufferData(_buffer, _spl::textureInternalFormatToGLenum(internalFormat), _spl::textureFormatToGLenum(format), _spl::textureDataTypeToGLenum(type), data);
		}
		else
		{
			assert(offset + size <= _size);
			assert(offset % granularity == 0);
			assert(size % granularity == 0);

			glClearNamedBufferSubData(_buffer, _spl::textureInternalFormatToGLenum(internalFormat), offset, size, _spl::textureFormatToGLenum(format), _spl::textureDataTypeToGLenum(type), data);
		}
	}
}
