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
	Drawable::Drawable() :
		_vao(0),
		_vbo(),
		_vboStorage(DrawableStorage::Static),
		_ebo(),
		_eboStorage(DrawableStorage::Static),
		_indicesCount(0),
		_needsAttributesUpdate(false)
	{
		glCreateVertexArrays(1, &_vao);
	}

	void Drawable::draw(PrimitiveType primitiveType, uint32_t indicesCount) const
	{
		assert((0 < indicesCount && indicesCount <= _indicesCount) || indicesCount == -1);

		glBindVertexArray(_vao);
		glDrawElements(primitiveTypeToGL(primitiveType), std::min(indicesCount, _indicesCount), GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);
	}

	void Drawable::setVertexAttributes(const std::vector<VertexAttribute>& attributes)
	{
		assert(_vbo.isValid());
		assert(_ebo.isValid());
		assert(_vao != 0);

		glBindVertexArray(_vao);
		Buffer::bind(_vbo, BufferTarget::Array);
		Buffer::bind(_ebo, BufferTarget::ElementArray);

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
		Buffer::unbind(BufferTarget::Array);
		Buffer::unbind(BufferTarget::ElementArray);

		_needsAttributesUpdate = false;
	}

	void Drawable::createNewVertices(const void* vertices, uint32_t size, DrawableStorage storage)
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
		_needsAttributesUpdate = true;
	}

	void Drawable::updateVertices(DrawableStorage storage)
	{
		updateVertices(nullptr, 0, storage, 0);
	}

	void Drawable::updateVertices(const void* vertices, uint32_t size, uint32_t offset)
	{
		updateVertices(vertices, size, _vboStorage, offset);
	}

	void Drawable::updateVertices(const void* vertices, uint32_t size, DrawableStorage storage, uint32_t offset)
	{
		assert(_vbo.isValid());

		if (offset + size > _vbo.getSize() || storage != _vboStorage)
		{
			_vboStorage = storage;
			const uint32_t newSize = std::max(_vbo.getSize(), offset + size);

			Buffer newVbo;
			if (drawableStorageToBufferUsage(_vboStorage) != BufferUsage::Undefined)
			{
				newVbo.createNew(newSize, drawableStorageToBufferUsage(_vboStorage));
			}
			else
			{
				newVbo.createNew(newSize, drawableStorageToBufferStorageFlags(_vboStorage));
			}

			newVbo.copyFrom(_vbo);
			_vbo = std::move(newVbo);
			_needsAttributesUpdate = true;
		}

		if (size > 0)
		{
			_vbo.update(vertices, size, offset);
		}
	}

	void Drawable::destroyVertices()
	{
		_vbo.destroy();
	}

	void Drawable::createNewIndices(const uint32_t* indices, uint32_t count, DrawableStorage storage)
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
		_needsAttributesUpdate = true;
	}

	void Drawable::updateIndices(DrawableStorage storage)
	{
		updateIndices(nullptr, 0, storage, 0);
	}

	void Drawable::updateIndices(const uint32_t* indices, uint32_t count, uint32_t startIndex)
	{
		updateIndices(indices, count, _eboStorage, startIndex);
	}

	void Drawable::updateIndices(const uint32_t* indices, uint32_t count, DrawableStorage storage, uint32_t startIndex)
	{
		assert(_ebo.isValid());

		const uint32_t offset = startIndex * sizeof(uint32_t);
		const uint32_t size = count * sizeof(uint32_t);

		if (offset + size > _ebo.getSize() || storage != _eboStorage)
		{
			_eboStorage = storage;
			const uint32_t newSize = std::max(_ebo.getSize(), offset + size);

			Buffer newEbo;
			if (drawableStorageToBufferUsage(_eboStorage) != BufferUsage::Undefined)
			{
				newEbo.createNew(newSize, drawableStorageToBufferUsage(_eboStorage));
			}
			else
			{
				newEbo.createNew(newSize, drawableStorageToBufferStorageFlags(_eboStorage));
			}

			newEbo.copyFrom(_ebo);
			_ebo = std::move(newEbo);
			_indicesCount = newSize / sizeof(uint32_t);
			_needsAttributesUpdate = true;
		}

		if (size > 0)
		{
			_ebo.update(indices, size, offset);
		}
	}

	void Drawable::destroyIndices()
	{
		_ebo.destroy();
	}

	DrawableStorage Drawable::getVerticesStorage() const
	{
		return _vboStorage;
	}

	DrawableStorage Drawable::getIndicesStorage() const
	{
		return _eboStorage;
	}

	bool Drawable::needsAttributesUpdate() const
	{
		return _needsAttributesUpdate;
	}

	bool Drawable::isValid() const
	{
		return _vao != 0 && _vbo.isValid() && _ebo.isValid() && !_needsAttributesUpdate;
	}

	Drawable::~Drawable()
	{
		glDeleteVertexArrays(1, &_vao);
		destroyVertices();
		destroyIndices();
	}
}