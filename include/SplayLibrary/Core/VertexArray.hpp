///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2021-2023
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <SplayLibrary/Core/CoreTypes.hpp>

namespace spl
{
	enum class PrimitiveType
	{
		Points,

		Lines,
		LineStrips,
		LineLoops,
		LinesAdjacency,
		LineStripsAdjacency,

		Triangles,
		TriangleStrips,
		TriangleFans,
		TrianglesAdjacency,
		TriangleStripsAdjacency,

		Patches

		// TODO: Adjacency
		// TODO: Patches
	};

	class VertexArray
	{
		public:

			VertexArray();
			VertexArray(const VertexArray& vertexArray) = delete;
			VertexArray(VertexArray&& vertexArray) = delete;

			VertexArray& operator=(const VertexArray& vertexArray) = delete;
			VertexArray& operator=(VertexArray&& vertexArray) = delete;

			// TODO: Current vertex attribute values

			void bindElementBuffer(const Buffer& buffer);
			void bindArrayBuffer(const Buffer& buffer, uint32_t bindingIndex, uintptr_t offset, uint32_t stride);
			void bindArrayBuffer(const Buffer* buffers, uint32_t count, uint32_t firstIndex, const uintptr_t* offsets, const uint32_t* strides);

			void setAttribute(uint32_t attributeIndex, GlslType type, uint32_t offsetInBuffer, bool normalized = false);
			void bindAttribute(uint32_t attributeIndex, uint32_t bindingIndex);

			uint32_t getHandle() const;

			~VertexArray();

		private:

			uint32_t _vao;
	};
}
