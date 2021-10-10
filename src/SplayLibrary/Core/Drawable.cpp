#include <SplayLibrary/Core/Core.hpp>
#include <SplayLibrary/Core/Private.hpp>

namespace spl
{
	Drawable::Drawable() :
		_type(DrawableStorage::Static),
		_vao(0),
		_vbo(0),
		_ebo(0),
		_indicesCount(0)
	{
	}

	void Drawable::create(const void* vertices, uint32_t verticesSize, const uint32_t* indices, uint32_t indicesSize, DrawableStorage type, const std::vector<VertexAttribute>& attributes)
	{
		assert(_vao == 0);
		assert(_vbo == 0);
		assert(_ebo == 0);

		_type = type;
		_indicesCount = indicesSize / sizeof(uint32_t);

		GLenum usage = GL_STATIC_DRAW;
		switch (_type)
		{
		case DrawableStorage::Static:
			usage = GL_STATIC_DRAW;
			break;
		case DrawableStorage::Stream:
			usage = GL_STREAM_DRAW;
			break;
		case DrawableStorage::Dynamic:
			usage = GL_DYNAMIC_DRAW;
			break;
		default:
			assert(false);
		}

		glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);

		glGenBuffers(1, &_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, usage);

		glGenBuffers(1, &_ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, usage);

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

			glVertexAttribPointer(attrib.index, size, type, attrib.normalized, attrib.stride, reinterpret_cast<void*>(attrib.offset));
			glEnableVertexAttribArray(attrib.index);
			glVertexAttribDivisor(attrib.index, attrib.divisor);
		}

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void Drawable::draw() const
	{
		glBindVertexArray(_vao);
		glDrawElements(GL_TRIANGLES, _indicesCount, GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);
	}

	void Drawable::destroy()
	{
		if (_vao != 0)
		{
			glDeleteVertexArrays(1, &_vao);
		}

		if (_vbo != 0)
		{
			glDeleteBuffers(1, &_vbo);
		}

		if (_ebo != 0)
		{
			glDeleteBuffers(1, &_ebo);
		}

		_vao = 0;
		_vbo = 0;
		_ebo = 0;
	}

	Drawable::~Drawable()
	{
		destroy();
	}
}