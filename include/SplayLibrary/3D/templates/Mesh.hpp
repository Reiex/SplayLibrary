///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2021-2023
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <SplayLibrary/3D/3DDecl.hpp>
#include <SplayLibrary/Private/PrivateIncluded.hpp>

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
			loadSuccess = _loadObj(path);
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
	bool Mesh<VertexType>::_loadObj(const std::filesystem::path& path)
	{
		dsk::fmt::ObjIStream objIStream;
		objIStream.setSource(path);

		dsk::fmt::obj::File objFile;
		objIStream.readFile(objFile);

		for (const dsk::fmt::obj::Face& face : objFile.faces)
		{
			if (face.vertices.size() != 3)
			{
				return false;
			}

			for (const dsk::fmt::obj::FaceVertex& vertex : face.vertices)
			{
				DefaultVertex outVertex;
				
				if (vertex.position != UINT64_MAX)
				{
					outVertex.pos.x = objFile.positions[vertex.position].x;
					outVertex.pos.y = objFile.positions[vertex.position].y;
					outVertex.pos.z = objFile.positions[vertex.position].z;
				}

				if (vertex.normal != UINT64_MAX)
				{
					outVertex.normal.x = objFile.normals[vertex.normal].i;
					outVertex.normal.y = objFile.normals[vertex.normal].j;
					outVertex.normal.z = objFile.normals[vertex.normal].k;
				}

				if (vertex.texCoord != UINT64_MAX)
				{
					outVertex.texCoords.x = objFile.texCoords[vertex.texCoord].u;
					outVertex.texCoords.y = objFile.texCoords[vertex.texCoord].v;
				}

				_vertices.push_back(outVertex);
				_indices.push_back(_indices.size());
			}
		}

		return true;
	}
}
