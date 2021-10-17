#pragma once

#include <SplayLibrary/3D/types.hpp>

namespace spl
{
	struct VertexBase
	{
		VertexBase() = default;
		VertexBase(const DefaultVertex& vertex) {}

		static std::vector<spl::VertexAttribute> getVertexAttributes() { return {}; }

		virtual void getDefaultVertex(DefaultVertex& vertex) const = 0;
	};

	struct DefaultVertex : public VertexBase
	{
		DefaultVertex(const vec3& vPos = { 0.f, 0.f, 0.f }, const vec3& vNormal = { 0.f, 0.f, 0.f }, const vec2& vTexCoords = { 0.f, 0.f });
		DefaultVertex(const DefaultVertex& vertex) = default;

		static std::vector<spl::VertexAttribute> getVertexAttributes();

		virtual void getDefaultVertex(DefaultVertex& vertex) const;

		vec3 pos;
		vec3 normal;
		vec2 texCoords;
	};

	template<typename VertexType = DefaultVertex>
	class Mesh : public Drawable
	{
		public:

			// Mesh(const std::string& filename, DrawableStorage verticesStorage = DrawableStorage::Static, DrawableStorage indicesStorage = DrawableStorage::Static);
			Mesh(const std::vector<VertexType>& vertices, DrawableStorage verticesStorage = DrawableStorage::Static, DrawableStorage indicesStorage = DrawableStorage::Static);
			Mesh(const std::vector<VertexType>& vertices, const std::vector<uint32_t> indices, DrawableStorage verticesStorage = DrawableStorage::Static, DrawableStorage indicesStorage = DrawableStorage::Static);

			// G�rer les erreurs : Que faire en cas de mauvais format ? Retourner un bool ? Faire un isValid ? Les deux ?
			// void loadFromFile(const std::string& filename, DrawableStorage verticesStorage = DrawableStorage::Static, DrawableStorage indicesStorage = DrawableStorage::Static);

			// void updateVertices(const std::vector<VertexType>& vertices, DrawableStorage storage = DrawableStorage::Static);
			// void updateIndices(const std::vector<uint32_t>& indices, DrawableStorage storage = DrawableStorage::Static);
			void updateVertices(const std::vector<VertexType>& vertices);
			void updateIndices(const std::vector<uint32_t>& indices);

		protected:

			// void readFromFile(const std::string& filename);

			std::vector<VertexType> _vertices;
			std::vector<uint32_t> _indices;
	};
}

#include <SplayLibrary/3D/MeshT.hpp>
