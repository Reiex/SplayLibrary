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
	VertexArray::VertexArray() :
		_vao(0)
	{
		glCreateVertexArrays(1, &_vao);
	}

	void VertexArray::bindElementBuffer(const Buffer& buffer)
	{
		assert(buffer.isValid());

		glVertexArrayElementBuffer(_vao, buffer.getHandle());
	}

	void VertexArray::bindArrayBuffer(const Buffer& buffer, uint32_t bindingIndex, uintptr_t offset, uint32_t stride)
	{
		assert(buffer.isValid());

		glVertexArrayVertexBuffer(_vao, bindingIndex, buffer.getHandle(), offset, stride);
	}

	void VertexArray::bindArrayBuffer(const Buffer* buffers, uint32_t count, uint32_t firstIndex, const uintptr_t* offsets, const uint32_t* strides)
	{
		uint32_t* names = reinterpret_cast<uint32_t*>(alloca(sizeof(uint32_t) * count));
		for (uint32_t i = 0; i < count; ++i)
		{
			assert(buffers[i].isValid());
			names[i] = buffers[i].getHandle();
		}

		glVertexArrayVertexBuffers(_vao, firstIndex, count, names, reinterpret_cast<const GLintptr*>(offsets), reinterpret_cast<const GLsizei*>(strides));
	}

	void VertexArray::setAttribute(uint32_t attributeIndex, GlslType type, uint32_t offsetInBuffer, bool normalized)
	{
		// TODO
	}

	void VertexArray::bindAttribute(uint32_t attributeIndex, uint32_t bindingIndex)
	{
		glVertexArrayAttribBinding(_vao, attributeIndex, bindingIndex);
	}

	uint32_t VertexArray::getHandle() const
	{
		return _vao;
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &_vao);
	}
}
