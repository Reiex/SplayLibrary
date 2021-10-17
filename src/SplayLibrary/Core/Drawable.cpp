#include <SplayLibrary/Core/Core.hpp>
#include <SplayLibrary/Core/Private.hpp>

namespace spl
{
	namespace
	{
		BufferUsage drawableStorageToBufferUsage(DrawableStorage storage)
		{
			switch (storage)
			{
			case DrawableStorage::Immutable:
				return BufferUsage::Undefined;
			case DrawableStorage::Static:
				return BufferUsage::StaticDraw;
			case DrawableStorage::Dynamic:
				return BufferUsage::DynamicDraw;
			case DrawableStorage::Stream:
				return BufferUsage::StreamDraw;
			default:
				assert(false);
				return BufferUsage::Undefined;
			}
		}

		BufferStorageFlags::Flags drawableStorageToBufferStorageFlags(DrawableStorage storage)
		{
			switch (storage)
			{
			case DrawableStorage::Immutable:
			case DrawableStorage::Static:
			case DrawableStorage::Dynamic:
			case DrawableStorage::Stream:
				return BufferStorageFlags::None;
			default:
				assert(false);
				return BufferStorageFlags::None;
			}
		}
	}

	Drawable::Drawable() :
		_vao(0),
		_vbo(),
		_vboStorage(DrawableStorage::Static),
		_ebo(),
		_eboStorage(DrawableStorage::Static),
		_indicesCount(0)
	{
		glGenVertexArrays(1, &_vao);
	}

	void Drawable::setVertexAttributes(const std::vector<VertexAttribute>& attributes)
	{
		assert(_vbo.isValid());
		assert(_ebo.isValid());
		assert(_vao != 0);

		glBindVertexArray(_vao);
		Buffer::bind(_vbo, BufferBindingTarget::Array);
		Buffer::bind(_ebo, BufferBindingTarget::ElementArray);

		for (const VertexAttribute& attrib : attributes)
		{
			uint32_t size = static_cast<uint32_t>(attrib.type) >> 4;
			uint32_t typeIndicator = static_cast<uint32_t>(attrib.type) & 0xF;

			GLenum type = GL_UNSIGNED_INT;
			switch (typeIndicator)
			{
			case 0:
				type = GL_FLOAT;
				break;
			case 1:
				type = GL_INT;
				break;
			case 2:
				type = GL_UNSIGNED_INT;
				break;
			default:
				assert(false);
			}

			glVertexAttribPointer(attrib.index, size, type, attrib.normalized, attrib.stride, reinterpret_cast<void*>(static_cast<size_t>(attrib.offset)));
			glEnableVertexAttribArray(attrib.index);
			glVertexAttribDivisor(attrib.index, attrib.divisor);
		}

		glBindVertexArray(0);
		Buffer::unbind(BufferBindingTarget::Array);
		Buffer::unbind(BufferBindingTarget::ElementArray);
	}

	void Drawable::createVertices(const void* vertices, uint32_t size, DrawableStorage storage)
	{
		if (drawableStorageToBufferUsage(storage) != BufferUsage::Undefined)
		{
			_vbo.createNew(size, drawableStorageToBufferUsage(storage), vertices);
		}
		else
		{
			_vbo.createNew(size, drawableStorageToBufferStorageFlags(storage), vertices);
		}

		_vboStorage = storage;
	}

	void Drawable::updateVertices(const void* vertices, uint32_t size, uint32_t offset)
	{
		assert(_vbo.isValid());

		if (offset + size > _vbo.getSize())
		{
			Buffer newVbo;
			if (drawableStorageToBufferUsage(_vboStorage) != BufferUsage::Undefined)
			{
				newVbo.createNew(offset + size, drawableStorageToBufferUsage(_vboStorage));
			}
			else
			{
				newVbo.createNew(offset + size, drawableStorageToBufferStorageFlags(_vboStorage));
			}

			newVbo.copyFrom(_vbo);
			_vbo = std::move(newVbo);
		}

		_vbo.update(vertices, size, offset);
	}

	void Drawable::destroyVertices()
	{
		_vbo.destroy();
	}

	void Drawable::createIndices(const uint32_t* indices, uint32_t count, DrawableStorage storage)
	{
		const uint32_t size = count * sizeof(uint32_t);

		if (drawableStorageToBufferUsage(storage) != BufferUsage::Undefined)
		{
			_ebo.createNew(size, drawableStorageToBufferUsage(storage), indices);
		}
		else
		{
			_ebo.createNew(size, drawableStorageToBufferStorageFlags(storage), indices);
		}

		_eboStorage = storage;
		_indicesCount = count;
	}

	void Drawable::updateIndices(const uint32_t* indices, uint32_t count, uint32_t startIndex)
	{
		assert(_ebo.isValid());

		const uint32_t offset = startIndex * sizeof(uint32_t);
		const uint32_t size = count * sizeof(uint32_t);

		if (offset + size > _ebo.getSize())
		{
			Buffer newEbo;
			if (drawableStorageToBufferUsage(_eboStorage) != BufferUsage::Undefined)
			{
				newEbo.createNew(offset + size, drawableStorageToBufferUsage(_eboStorage));
			}
			else
			{
				newEbo.createNew(offset + size, drawableStorageToBufferStorageFlags(_eboStorage));
			}

			newEbo.copyFrom(_ebo);
			_ebo = std::move(newEbo);
		}

		_ebo.update(indices, size, offset);
	}

	void Drawable::setIndicesCount(uint32_t count)
	{
		assert(!_ebo.isValid() || count * sizeof(uint32_t) < _ebo.getSize());

		_indicesCount = count;
	}

	void Drawable::destroyIndices()
	{
		_ebo.destroy();
	}

	void Drawable::draw() const
	{
		glBindVertexArray(_vao);
		glDrawElements(GL_TRIANGLES, _indicesCount, GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);
	}

	Drawable::~Drawable()
	{
		glDeleteVertexArrays(1, &_vao);
		destroyVertices();
		destroyIndices();
	}
}