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
	Mesh<VertexType>::Mesh(const std::filesystem::path& path, DrawableStorage verticesStorage, DrawableStorage indicesStorage) : Mesh<VertexType>()
	{
		if (!std::filesystem::exists(path))
		{
			return;
		}

		bool loadSuccess = false;
		if (path.extension() == ".obj")
		{
			loadSuccess = loadObj(path);
		}

		if (loadSuccess)
		{
			Drawable::createNewVertices(_vertices.data(), _vertices.size() * sizeof(VertexType), verticesStorage);
			Drawable::createNewIndices(_indices.data(), _indices.size(), indicesStorage);
			Drawable::setVertexAttributes(VertexType::getVertexAttributes());
		}
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

	template<typename VertexType>
	bool Mesh<VertexType>::loadObj(const std::filesystem::path& path)
	{
		dsk::ObjFile objFile;
		if (!objFile.loadFromFile(path))
		{
			return false;
		}

		for (const std::vector<dsk::obj::Vertex>& objFace : objFile.faces)
		{
			if (objFace.size() != 3)
			{
				return false;
			}

			for (const dsk::obj::Vertex& objVertex : objFace)
			{
				DefaultVertex vertex;
				if (objVertex.position)
				{
					vertex.pos = { (float)objVertex.position->x, (float)objVertex.position->y, (float)objVertex.position->z };
					vertex.pos /= 100; // TODO: Enlever ça dès que possible !
				}

				if (objVertex.normal)
				{
					vertex.normal = { (float)objVertex.normal->x, (float)objVertex.normal->y, (float)objVertex.normal->z };
				}

				if (objVertex.texCoord)
				{
					vertex.texCoords = { (float)objVertex.texCoord->x, (float)objVertex.texCoord->y };
				}

				_vertices.push_back(vertex);
				_indices.push_back(_indices.size());
			}
		}

		return true;
	}
}
