#pragma once

#include <SplayLibrary/3D/Mesh.hpp>

namespace spl
{
	template<typename VertexType>
	Mesh<VertexType>::Mesh(const std::vector<VertexType>& vertices, DrawableStorage type) :
		_vertices(vertices),
		_indices()
	{
		_indices.resize(vertices.size());
		for (uint32_t i = 0; i < _indices.size(); ++i)
		{
			_indices[i] = i;
		}

		create(_vertices.data(), _vertices.size() * sizeof(VertexType), _indices.data(), _indices.size() * sizeof(uint32_t), type, VertexType::getVertexAttributes());
	}

	template<typename VertexType>
	Mesh<VertexType>::Mesh(const std::vector<VertexType>& vertices, const std::vector<uint32_t> indices, DrawableStorage type) :
		_vertices(vertices),
		_indices(indices)
	{
		create(_vertices.data(), _vertices.size() * sizeof(VertexType), _indices.data(), _indices.size() * sizeof(uint32_t), type, VertexType::getVertexAttributes());
	}
}
