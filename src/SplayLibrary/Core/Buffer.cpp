#include <SplayLibrary/Core/Core.hpp>
#include <SplayLibrary/Core/Private.hpp>

namespace spl
{
	namespace
	{
		GLenum bufferBindingTargetToGL(BufferBindingTarget target)
		{
			switch (target)
			{
			case BufferBindingTarget::Array:
				return GL_ARRAY_BUFFER;
			case BufferBindingTarget::AtomicCounter:
				return GL_ATOMIC_COUNTER_BUFFER;
			case BufferBindingTarget::CopyRead:
				return GL_COPY_READ_BUFFER;
			case BufferBindingTarget::CopyWrite:
				return GL_COPY_WRITE_BUFFER;
			case BufferBindingTarget::DispatchIndirect:
				return GL_DISPATCH_INDIRECT_BUFFER;
			case BufferBindingTarget::ElementArray:
				return GL_ELEMENT_ARRAY_BUFFER;
			case BufferBindingTarget::Parameter:
				return GL_PARAMETER_BUFFER;
			case BufferBindingTarget::PixelPack:
				return GL_PIXEL_PACK_BUFFER;
			case BufferBindingTarget::PixelUnpack:
				return GL_PIXEL_UNPACK_BUFFER;
			case BufferBindingTarget::Query:
				return GL_QUERY_BUFFER;
			case BufferBindingTarget::ShaderStorage:
				return GL_SHADER_STORAGE_BUFFER;
			case BufferBindingTarget::Texture:
				return GL_TEXTURE_BUFFER;
			case BufferBindingTarget::TransformFeedback:
				return GL_TRANSFORM_FEEDBACK_BUFFER;
			case BufferBindingTarget::Uniform:
				return GL_UNIFORM_BUFFER;
			default:
				assert(false);
				return 0;
			}
		}

		GLenum bufferUsageToGL(BufferUsage usage)
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

		GLbitfield bufferStorageFlagsToGL(BufferStorageFlags::Flags flags)
		{
			GLbitfield flagsGL = 0;

			if (flags & BufferStorageFlags::DynamicStorage)
			{
				flagsGL &= GL_DYNAMIC_STORAGE_BIT;
			}
			if (flags & BufferStorageFlags::MapRead)
			{
				flagsGL &= GL_MAP_READ_BIT;
			}
			if (flags & BufferStorageFlags::MapWrite)
			{
				flagsGL &= GL_MAP_WRITE_BIT;
			}
			if (flags & BufferStorageFlags::MapPersistent)
			{
				flagsGL &= GL_MAP_PERSISTENT_BIT;
			}
			if (flags & BufferStorageFlags::MapCoherent)
			{
				flagsGL &= GL_MAP_COHERENT_BIT;
			}
			if (flags & BufferStorageFlags::ClientStorage)
			{
				flagsGL &= GL_CLIENT_STORAGE_BIT;
			}

			return flagsGL;
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

		destroy();

		glCreateBuffers(1, &_buffer);
		glNamedBufferData(_buffer, size, data, bufferUsageToGL(usage));

		_size = size;
		_usage = usage;
		_flags = BufferStorageFlags::None;
	}

	void Buffer::createNew(uint32_t size, BufferStorageFlags::Flags flags, const void* data)
	{
		assert(size > 0);

		destroy();

		glCreateBuffers(1, &_buffer);
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

		const uint32_t size = std::min(_size, buffer._size);
		glCopyNamedBufferSubData(buffer._buffer, _buffer, 0, 0, size);
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
		assert(data != nullptr);
		assert(isValid());
		assert(dstOffset + size <= _size);

		if (_usage != BufferUsage::Undefined || _flags & BufferStorageFlags::DynamicStorage)
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
		assert(_buffer != 0 || (_size == 0 && _usage == BufferUsage::Undefined && _flags == BufferStorageFlags::None));

		if (_buffer != 0)
		{
			glDeleteBuffers(1, &_buffer);

			_buffer = 0;
			_size = 0;
			_usage = BufferUsage::Undefined;
			_flags = BufferStorageFlags::None;
		}
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

	void Buffer::bind(const Buffer& buffer, BufferBindingTarget target)
	{
		assert(buffer.isValid());
		assert(bufferBindingTargetToGL(target) != 0);

		glBindBuffer(bufferBindingTargetToGL(target), buffer._buffer);
	}

	void Buffer::unbind(BufferBindingTarget target)
	{
		assert(bufferBindingTargetToGL(target) != 0);

		glBindBuffer(bufferBindingTargetToGL(target), 0);
	}

	Buffer::~Buffer()
	{
		destroy();
	}
}