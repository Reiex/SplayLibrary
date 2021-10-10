#pragma once

#include <SplayLibrary/3D/types.hpp>

namespace spl
{
	template<typename VertexType>
	class Mesh : public Drawable
	{
		public:

			Mesh(const std::vector<VertexType>& vertices, DrawableStorage type = DrawableStorage::Static);
			Mesh(const std::vector<VertexType>& vertices, const std::vector<uint32_t> indices, DrawableStorage type = DrawableStorage::Static);

			// void updateVertices(const std::vector<VertexType>& vertices);
			// void updateVertices(const std::vector<VertexType>& vertices, const std::vector<uint32_t> indices);

		private:

			std::vector<VertexType> _vertices;
			std::vector<uint32_t> _indices;
	};
}

#include <SplayLibrary/3D/MeshT.hpp>
