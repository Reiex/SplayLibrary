#pragma once

#include <SplayLibrary/3D/types.hpp>

namespace spl
{
	struct DefaultVertex;

	struct VertexBase
	{
		VertexBase(const DefaultVertex& vertex);

		virtual void getDefaultVertex(DefaultVertex& vertex) const;
	};

	struct DefaultVertex : public VertexBase
	{
		DefaultVertex(const DefaultVertex& vertex);

		virtual void getDefaultVertex(DefaultVertex& vertex) const;

		vec3 pos;
		vec3 normal;
		vec2 texCoords;
	};

	template<typename VertexType = DefaultVertex>
	class Mesh : public Drawable
	{
		public:

			Mesh(const std::vector<VertexType>& vertices, DrawableStorage type = DrawableStorage::Static);
			Mesh(const std::vector<VertexType>& vertices, const std::vector<uint32_t> indices, DrawableStorage type = DrawableStorage::Static);
			// Mesh(const std::string& filename, DrawableStorage type = DrawableStorage::Static);

			// void updateVertices(const std::vector<VertexType>& vertices);
			// void updateVertices(const std::vector<VertexType>& vertices, const std::vector<uint32_t> indices);

		protected:

			std::vector<VertexType> _vertices;
			std::vector<uint32_t> _indices;
	};
}

#include <SplayLibrary/3D/MeshT.hpp>
