#include <SplayLibrary/Core/Core.hpp>
#include <SplayLibrary/Core/Private.hpp>

namespace spl
{
	Drawable::Drawable() :
		_type(DrawableStorage::Static),
		_vao(0),
		_vbo(),
		_ebo(),
		_indicesCount(0)
	{
	}

	void Drawable::create(const void* vertices, uint32_t verticesSize, const uint32_t* indices, uint32_t indicesSize, DrawableStorage type, const std::vector<VertexAttribute>& attributes)
	{
		assert(_vao == 0);

		_type = type;
		_indicesCount = indicesSize / sizeof(uint32_t);

		BufferUsage usage = BufferUsage::StaticDraw;
		switch (_type)
		{
		case DrawableStorage::Static:
			usage = BufferUsage::StaticDraw;
			break;
		case DrawableStorage::Stream:
			usage = BufferUsage::StreamDraw;
			break;
		case DrawableStorage::Dynamic:
			usage = BufferUsage::DynamicDraw;
			break;
		default:
			assert(false);
		}

		glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);

		_vbo.createNew(verticesSize, vertices, usage);
		_ebo.createNew(indicesSize, indices, usage);

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

			glVertexAttribPointer(attrib.index, size, type, attrib.normalized, attrib.stride, reinterpret_cast<void*>(attrib.offset));
			glEnableVertexAttribArray(attrib.index);
			glVertexAttribDivisor(attrib.index, attrib.divisor);
		}

		glBindVertexArray(0);
		Buffer::unbind(BufferBindingTarget::Array);
		Buffer::unbind(BufferBindingTarget::ElementArray);
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

		_vbo.destroy();
		_ebo.destroy();

		_vao = 0;
	}

	Drawable::~Drawable()
	{
		destroy();
	}
}