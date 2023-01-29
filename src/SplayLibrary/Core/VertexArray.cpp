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

	void VertexArray::setAttributeFormat(uint32_t attributeIndex, GlslType type, uint32_t offsetInBuffer)
	{
		switch (type)
		{
			case GlslType::Float:
				glVertexArrayAttribFormat(_vao, attributeIndex, 1, GL_FLOAT, false, offsetInBuffer);
				break;
			case GlslType::FloatVec2:
				glVertexArrayAttribFormat(_vao, attributeIndex, 2, GL_FLOAT, false, offsetInBuffer);
				break;
			case GlslType::FloatVec3:
				glVertexArrayAttribFormat(_vao, attributeIndex, 3, GL_FLOAT, false, offsetInBuffer);
				break;
			case GlslType::FloatVec4:
				glVertexArrayAttribFormat(_vao, attributeIndex, 4, GL_FLOAT, false, offsetInBuffer);
				break;
			case GlslType::Double:
				glVertexArrayAttribLFormat(_vao, attributeIndex, 1, GL_DOUBLE, offsetInBuffer);
				break;
			case GlslType::DoubleVec2:
				glVertexArrayAttribLFormat(_vao, attributeIndex, 2, GL_DOUBLE, offsetInBuffer);
				break;
			case GlslType::DoubleVec3:
				glVertexArrayAttribLFormat(_vao, attributeIndex, 3, GL_DOUBLE, offsetInBuffer);
				break;
			case GlslType::DoubleVec4:
				glVertexArrayAttribLFormat(_vao, attributeIndex, 4, GL_DOUBLE, offsetInBuffer);
				break;
			case GlslType::Int:
				glVertexArrayAttribIFormat(_vao, attributeIndex, 1, GL_INT, offsetInBuffer);
				break;
			case GlslType::IntVec2:
				glVertexArrayAttribIFormat(_vao, attributeIndex, 2, GL_INT, offsetInBuffer);
				break;
			case GlslType::IntVec3:
				glVertexArrayAttribIFormat(_vao, attributeIndex, 3, GL_INT, offsetInBuffer);
				break;
			case GlslType::IntVec4:
				glVertexArrayAttribIFormat(_vao, attributeIndex, 4, GL_INT, offsetInBuffer);
				break;
			case GlslType::UnsignedInt:
				glVertexArrayAttribIFormat(_vao, attributeIndex, 1, GL_UNSIGNED_INT, offsetInBuffer);
				break;
			case GlslType::UnsignedIntVec2:
				glVertexArrayAttribIFormat(_vao, attributeIndex, 2, GL_UNSIGNED_INT, offsetInBuffer);
				break;
			case GlslType::UnsignedIntVec3:
				glVertexArrayAttribIFormat(_vao, attributeIndex, 3, GL_UNSIGNED_INT, offsetInBuffer);
				break;
			case GlslType::UnsignedIntVec4:
				glVertexArrayAttribIFormat(_vao, attributeIndex, 4, GL_UNSIGNED_INT, offsetInBuffer);
				break;
			case GlslType::FloatMat2x2:
				glVertexArrayAttribFormat(_vao, attributeIndex, 2, GL_FLOAT, false, offsetInBuffer);
				glVertexArrayAttribFormat(_vao, attributeIndex + 1, 2, GL_FLOAT, false, offsetInBuffer + 2);
				break;
			case GlslType::FloatMat2x3:
				glVertexArrayAttribFormat(_vao, attributeIndex, 3, GL_FLOAT, false, offsetInBuffer);
				glVertexArrayAttribFormat(_vao, attributeIndex + 1, 3, GL_FLOAT, false, offsetInBuffer + 3);
				break;
			case GlslType::FloatMat2x4:
				glVertexArrayAttribFormat(_vao, attributeIndex, 4, GL_FLOAT, false, offsetInBuffer);
				glVertexArrayAttribFormat(_vao, attributeIndex + 1, 4, GL_FLOAT, false, offsetInBuffer + 4);
				break;
			case GlslType::FloatMat3x2:
				glVertexArrayAttribFormat(_vao, attributeIndex, 2, GL_FLOAT, false, offsetInBuffer);
				glVertexArrayAttribFormat(_vao, attributeIndex + 1, 2, GL_FLOAT, false, offsetInBuffer + 2);
				glVertexArrayAttribFormat(_vao, attributeIndex + 2, 2, GL_FLOAT, false, offsetInBuffer + 4);
				break;
			case GlslType::FloatMat3x3:
				glVertexArrayAttribFormat(_vao, attributeIndex, 3, GL_FLOAT, false, offsetInBuffer);
				glVertexArrayAttribFormat(_vao, attributeIndex + 1, 3, GL_FLOAT, false, offsetInBuffer + 3);
				glVertexArrayAttribFormat(_vao, attributeIndex + 2, 3, GL_FLOAT, false, offsetInBuffer + 6);
				break;
			case GlslType::FloatMat3x4:
				glVertexArrayAttribFormat(_vao, attributeIndex, 4, GL_FLOAT, false, offsetInBuffer);
				glVertexArrayAttribFormat(_vao, attributeIndex + 1, 4, GL_FLOAT, false, offsetInBuffer + 4);
				glVertexArrayAttribFormat(_vao, attributeIndex + 2, 4, GL_FLOAT, false, offsetInBuffer + 8);
				break;
			case GlslType::FloatMat4x2:
				glVertexArrayAttribFormat(_vao, attributeIndex, 2, GL_FLOAT, false, offsetInBuffer);
				glVertexArrayAttribFormat(_vao, attributeIndex + 1, 2, GL_FLOAT, false, offsetInBuffer + 2);
				glVertexArrayAttribFormat(_vao, attributeIndex + 2, 2, GL_FLOAT, false, offsetInBuffer + 4);
				glVertexArrayAttribFormat(_vao, attributeIndex + 3, 2, GL_FLOAT, false, offsetInBuffer + 6);
				break;
			case GlslType::FloatMat4x3:
				glVertexArrayAttribFormat(_vao, attributeIndex, 3, GL_FLOAT, false, offsetInBuffer);
				glVertexArrayAttribFormat(_vao, attributeIndex + 1, 3, GL_FLOAT, false, offsetInBuffer + 3);
				glVertexArrayAttribFormat(_vao, attributeIndex + 2, 3, GL_FLOAT, false, offsetInBuffer + 6);
				glVertexArrayAttribFormat(_vao, attributeIndex + 3, 3, GL_FLOAT, false, offsetInBuffer + 9);
				break;
			case GlslType::FloatMat4x4:
				glVertexArrayAttribFormat(_vao, attributeIndex, 4, GL_FLOAT, false, offsetInBuffer);
				glVertexArrayAttribFormat(_vao, attributeIndex + 1, 4, GL_FLOAT, false, offsetInBuffer + 4);
				glVertexArrayAttribFormat(_vao, attributeIndex + 2, 4, GL_FLOAT, false, offsetInBuffer + 8);
				glVertexArrayAttribFormat(_vao, attributeIndex + 3, 4, GL_FLOAT, false, offsetInBuffer + 12);
				break;
			case GlslType::DoubleMat2x2:
				glVertexArrayAttribLFormat(_vao, attributeIndex, 2, GL_DOUBLE, offsetInBuffer);
				glVertexArrayAttribLFormat(_vao, attributeIndex + 1, 2, GL_DOUBLE, offsetInBuffer + 2);
				break;
			case GlslType::DoubleMat2x3:
				glVertexArrayAttribLFormat(_vao, attributeIndex, 3, GL_DOUBLE, offsetInBuffer);
				glVertexArrayAttribLFormat(_vao, attributeIndex + 1, 3, GL_DOUBLE, offsetInBuffer + 3);
				break;
			case GlslType::DoubleMat2x4:
				glVertexArrayAttribLFormat(_vao, attributeIndex, 4, GL_DOUBLE, offsetInBuffer);
				glVertexArrayAttribLFormat(_vao, attributeIndex + 1, 4, GL_DOUBLE, offsetInBuffer + 4);
				break;
			case GlslType::DoubleMat3x2:
				glVertexArrayAttribLFormat(_vao, attributeIndex, 2, GL_DOUBLE, offsetInBuffer);
				glVertexArrayAttribLFormat(_vao, attributeIndex + 1, 2, GL_DOUBLE, offsetInBuffer + 2);
				glVertexArrayAttribLFormat(_vao, attributeIndex + 2, 2, GL_DOUBLE, offsetInBuffer + 4);
				break;
			case GlslType::DoubleMat3x3:
				glVertexArrayAttribLFormat(_vao, attributeIndex, 3, GL_DOUBLE, offsetInBuffer);
				glVertexArrayAttribLFormat(_vao, attributeIndex + 1, 3, GL_DOUBLE, offsetInBuffer + 3);
				glVertexArrayAttribLFormat(_vao, attributeIndex + 2, 3, GL_DOUBLE, offsetInBuffer + 6);
				break;
			case GlslType::DoubleMat3x4:
				glVertexArrayAttribLFormat(_vao, attributeIndex, 4, GL_DOUBLE, offsetInBuffer);
				glVertexArrayAttribLFormat(_vao, attributeIndex + 1, 4, GL_DOUBLE, offsetInBuffer + 4);
				glVertexArrayAttribLFormat(_vao, attributeIndex + 2, 4, GL_DOUBLE, offsetInBuffer + 8);
				break;
			case GlslType::DoubleMat4x2:
				glVertexArrayAttribLFormat(_vao, attributeIndex, 2, GL_DOUBLE, offsetInBuffer);
				glVertexArrayAttribLFormat(_vao, attributeIndex + 1, 2, GL_DOUBLE, offsetInBuffer + 2);
				glVertexArrayAttribLFormat(_vao, attributeIndex + 2, 2, GL_DOUBLE, offsetInBuffer + 4);
				glVertexArrayAttribLFormat(_vao, attributeIndex + 3, 2, GL_DOUBLE, offsetInBuffer + 6);
				break;
			case GlslType::DoubleMat4x3:
				glVertexArrayAttribLFormat(_vao, attributeIndex, 3, GL_DOUBLE, offsetInBuffer);
				glVertexArrayAttribLFormat(_vao, attributeIndex + 1, 3, GL_DOUBLE, offsetInBuffer + 3);
				glVertexArrayAttribLFormat(_vao, attributeIndex + 2, 3, GL_DOUBLE, offsetInBuffer + 6);
				glVertexArrayAttribLFormat(_vao, attributeIndex + 3, 3, GL_DOUBLE, offsetInBuffer + 9);
				break;
			case GlslType::DoubleMat4x4:
				glVertexArrayAttribLFormat(_vao, attributeIndex, 4, GL_DOUBLE, offsetInBuffer);
				glVertexArrayAttribLFormat(_vao, attributeIndex + 1, 4, GL_DOUBLE, offsetInBuffer + 4);
				glVertexArrayAttribLFormat(_vao, attributeIndex + 2, 4, GL_DOUBLE, offsetInBuffer + 8);
				glVertexArrayAttribLFormat(_vao, attributeIndex + 3, 4, GL_DOUBLE, offsetInBuffer + 12);
				break;
			default:
				assert(false);
				break;
		}
	}

	void VertexArray::setAttributeEnabled(uint32_t attributeIndex, bool enabled)
	{
		if (enabled)
		{
			glEnableVertexArrayAttrib(_vao, attributeIndex);
		}
		else
		{
			glDisableVertexArrayAttrib(_vao, attributeIndex);
		}
	}

	void VertexArray::setAttributeBinding(uint32_t attributeIndex, uint32_t bindingIndex)
	{
		glVertexArrayAttribBinding(_vao, attributeIndex, bindingIndex);
	}

	void VertexArray::setBindingDivisor(uint32_t bindingIndex, uint32_t divisor)
	{
		glVertexArrayBindingDivisor(_vao, bindingIndex, divisor);
	}

	void VertexArray::drawArrays(PrimitiveType type, uint32_t first, uint32_t count, uint32_t instanceCount, uint32_t baseInstance) const
	{
		assert(_spl::primitiveTypeToGLenum(type) != 0);

		glBindVertexArray(_vao);
		glDrawArraysInstancedBaseInstance(_spl::primitiveTypeToGLenum(type), first, count, instanceCount, baseInstance);
		glBindVertexArray(0);
	}

	void VertexArray::drawElements(PrimitiveType primitiveType, IndexType indexType, uintptr_t first, uint32_t count, uint32_t instanceCount, uint32_t baseInstance, uint32_t baseVertex) const
	{
		assert(_spl::primitiveTypeToGLenum(primitiveType) != 0);
		assert(_spl::indexTypeToGLenum(indexType) != 0);

		glBindVertexArray(_vao);
		glDrawElementsInstancedBaseVertexBaseInstance(_spl::primitiveTypeToGLenum(primitiveType), count, _spl::indexTypeToGLenum(indexType), reinterpret_cast<const void*>(first), instanceCount, baseVertex, baseInstance);
		glBindVertexArray(0);
	}

	void VertexArray::multiDrawArrays(PrimitiveType type, const uint32_t* firsts, const uint32_t* counts, uint32_t drawCount) const
	{
		assert(_spl::primitiveTypeToGLenum(type) != 0);

		glBindVertexArray(_vao);
		glMultiDrawArrays(_spl::primitiveTypeToGLenum(type), reinterpret_cast<const GLint*>(firsts), reinterpret_cast<const GLsizei*>(counts), drawCount);
		glBindVertexArray(0);
	}

	void VertexArray::multiDrawElements(PrimitiveType primitiveType, IndexType indexType, const uintptr_t* firsts, const uint32_t* counts, uint32_t drawCount, const uint32_t* baseVertex) const
	{
		assert(_spl::primitiveTypeToGLenum(primitiveType) != 0);
		assert(_spl::indexTypeToGLenum(indexType) != 0);

		glBindVertexArray(_vao);

		if (baseVertex)
		{
			glMultiDrawElementsBaseVertex(_spl::primitiveTypeToGLenum(primitiveType), reinterpret_cast<const GLsizei*>(counts), _spl::indexTypeToGLenum(indexType), reinterpret_cast<const void* const*>(firsts), drawCount, reinterpret_cast<const GLint*>(baseVertex));
		}
		else
		{
			glMultiDrawElements(_spl::primitiveTypeToGLenum(primitiveType), reinterpret_cast<const GLsizei*>(counts), _spl::indexTypeToGLenum(indexType), reinterpret_cast<const void* const*>(firsts), drawCount);
		}

		glBindVertexArray(0);
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
