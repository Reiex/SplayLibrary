#pragma once

#include <SplayLibrary/3D/Mesh.hpp>

namespace spl
{
	template<typename VertexType>
	Mesh<VertexType>::Mesh() :
		_vertices(),
		_indices()
	{
	}

	template<typename VertexType>
	Mesh<VertexType>::Mesh(const std::string& filename, DrawableStorage verticesStorage, DrawableStorage indicesStorage)
	{
		readFromFile(filename, _vertices, _indices);

		Drawable::createNewVertices(_vertices.data(), _vertices.size() * sizeof(VertexType), verticesStorage);
		Drawable::createNewIndices(_indices.data(), _indices.size(), indicesStorage);
		Drawable::setVertexAttributes(VertexType::getVertexAttributes());
	}

	template<typename VertexType>
	Mesh<VertexType>::Mesh(const std::vector<VertexType>& vertices, DrawableStorage verticesStorage, DrawableStorage indicesStorage) : Mesh<VertexType>()
	{
		_vertices = vertices;

		_indices.resize(vertices.size());
		for (uint32_t i = 0; i < _indices.size(); ++i)
		{
			_indices[i] = i;
		}

		Drawable::createNewVertices(_vertices.data(), _vertices.size() * sizeof(VertexType), verticesStorage);
		Drawable::createNewIndices(_indices.data(), _indices.size(), indicesStorage);
		Drawable::setVertexAttributes(VertexType::getVertexAttributes());
	}

	template<typename VertexType>
	Mesh<VertexType>::Mesh(const std::vector<VertexType>& vertices, const std::vector<uint32_t> indices, DrawableStorage verticesStorage, DrawableStorage indicesStorage) : Mesh<VertexType>()
	{
		_vertices = vertices;
		_indices = indices;

		Drawable::createNewVertices(_vertices.data(), _vertices.size() * sizeof(VertexType), verticesStorage);
		Drawable::createNewIndices(_indices.data(), _indices.size(), indicesStorage);
		Drawable::setVertexAttributes(VertexType::getVertexAttributes());
	}

	template<typename VertexType>
	void Mesh<VertexType>::readFromFile(const std::string& filename, std::vector<VertexType>& vertices, std::vector<uint32_t>& indices)
	{
		vertices = {
		{ { 1.f,  0.f, 0.0f} },
		{ { 0.f,  1.f, 0.0f} },
		{ {-1.f,  0.f, 0.0f} },
		{ { 0.f, -1.f, 0.0f} }
		};

		indices = {
			0, 1, 2,
			0, 2, 3
		};
	}

	template<typename VertexType>
	void Mesh<VertexType>::loadFromFile(const std::string& filename, DrawableStorage verticesStorage, DrawableStorage indicesStorage)
	{
		std::vector<VertexType> vertices;
		std::vector<uint32_t> indices;

		readFromFile(filename, vertices, indices);

		updateVertices(vertices, verticesStorage);
		updateIndices(indices, indicesStorage);
	}

	template<typename VertexType>
	void Mesh<VertexType>::updateVertices(const std::vector<VertexType>& vertices)
	{
		_vertices = vertices;
		Drawable::updateVertices(_vertices.data(), _vertices.size() * sizeof(VertexType));

		if (needsAttributesUpdate())
		{
			Drawable::setVertexAttributes(VertexType::getVertexAttributes());
		}
	}

	template<typename VertexType>
	void Mesh<VertexType>::updateIndices(const std::vector<uint32_t>& indices)
	{
		_indices = indices;
		Drawable::updateIndices(_indices.data(), _indices.size());

		if (needsAttributesUpdate())
		{
			Drawable::setVertexAttributes(VertexType::getVertexAttributes());
		}
	}

	template<typename VertexType>
	void Mesh<VertexType>::updateVertices(const std::vector<VertexType>& vertices, DrawableStorage storage)
	{
		_vertices = vertices;
		Drawable::updateVertices(_vertices.data(), _vertices.size() * sizeof(VertexType), storage);

		if (needsAttributesUpdate())
		{
			Drawable::setVertexAttributes(VertexType::getVertexAttributes());
		}
	}

	template<typename VertexType>
	void Mesh<VertexType>::updateIndices(const std::vector<uint32_t>& indices, DrawableStorage storage)
	{
		_indices = indices;
		Drawable::updateIndices(_indices.data(), _indices.size(), storage);

		if (needsAttributesUpdate())
		{
			Drawable::setVertexAttributes(VertexType::getVertexAttributes());
		}
	}

	template<typename VertexType>
	bool Mesh<VertexType>::isValid() const
	{
		return Drawable::isValid() && _vertices.size() > 0 && _indices.size() > 0;
	}
}
