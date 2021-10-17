#pragma once

#include <SplayLibrary/3D/Mesh.hpp>

namespace spl
{
	template<typename VertexType>
	Mesh<VertexType>::Mesh(const std::vector<VertexType>& vertices, DrawableStorage verticesStorage, DrawableStorage indicesStorage) :
		_vertices(vertices),
		_indices()
	{
		_indices.resize(vertices.size());
		for (uint32_t i = 0; i < _indices.size(); ++i)
		{
			_indices[i] = i;
		}

		createVertices(_vertices.data(), _vertices.size() * sizeof(VertexType), verticesStorage);
		createIndices(_indices.data(), _indices.size(), indicesStorage);
		setVertexAttributes(VertexType::getVertexAttributes());
	}

	template<typename VertexType>
	Mesh<VertexType>::Mesh(const std::vector<VertexType>& vertices, const std::vector<uint32_t> indices, DrawableStorage verticesStorage, DrawableStorage indicesStorage) :
		_vertices(vertices),
		_indices(indices)
	{
		createVertices(_vertices.data(), _vertices.size() * sizeof(VertexType), verticesStorage);
		createIndices(_indices.data(), _indices.size(), indicesStorage);
		setVertexAttributes(VertexType::getVertexAttributes());
	}

	template<typename VertexType>
	void Mesh<VertexType>::updateVertices(const std::vector<VertexType>& vertices)
	{
		_vertices = vertices;
		Drawable::updateVertices(vertices.data(), vertices.size() * sizeof(VertexType));
	}

	template<typename VertexType>
	void Mesh<VertexType>::updateIndices(const std::vector<uint32_t>& indices)
	{
		_indices = indices;
		Drawable::updateIndices(indices.data(), indices.size());
	}
}
