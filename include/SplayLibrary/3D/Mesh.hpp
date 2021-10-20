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
			
			/*
			Renommer Mesh en DrawableMesh et faire une classe Mesh purement CPU:
				- Pour gérer plus facilement les algorithmes sur Mesh
				- Pour permettre les compute shader (dump SSBO)
				- Pour pouvoir gérer les Mesh en multithread
			*/

			Mesh(const std::string& filename, DrawableStorage verticesStorage = DrawableStorage::Static, DrawableStorage indicesStorage = DrawableStorage::Static);
			Mesh(const std::vector<VertexType>& vertices, DrawableStorage verticesStorage = DrawableStorage::Static, DrawableStorage indicesStorage = DrawableStorage::Static);
			Mesh(const std::vector<VertexType>& vertices, const std::vector<uint32_t> indices, DrawableStorage verticesStorage = DrawableStorage::Static, DrawableStorage indicesStorage = DrawableStorage::Static);
			Mesh(const Mesh<VertexType>& mesh) = delete;
			Mesh(Mesh<VertexType>&& mesh) = delete;

			Mesh<VertexType>& operator=(const Mesh<VertexType>& mesh) = delete;
			Mesh<VertexType>& operator=(Mesh<VertexType>&& mesh) = delete;

			void loadFromFile(const std::string& filename, DrawableStorage verticesStorage = DrawableStorage::Static, DrawableStorage indicesStorage = DrawableStorage::Static);

			void updateVertices(const std::vector<VertexType>& vertices);
			void updateIndices(const std::vector<uint32_t>& indices);
			void updateVertices(const std::vector<VertexType>& vertices, DrawableStorage storage);
			void updateIndices(const std::vector<uint32_t>& indices, DrawableStorage storage);

			virtual bool isValid() const;

			~Mesh() = default;

		protected:

			Mesh();

			static void readFromFile(const std::string& filename, std::vector<VertexType>& vertices, std::vector<uint32_t>& indices);

			std::vector<VertexType> _vertices;
			std::vector<uint32_t> _indices;
	};
}

#include <SplayLibrary/3D/MeshT.hpp>
