///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2019-2022
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
		DefaultVertex(const scp::f32vec3& vPos = { 0.f, 0.f, 0.f }, const scp::f32vec3& vNormal = { 0.f, 0.f, 0.f }, const scp::f32vec2& vTexCoords = { 0.f, 0.f });
		DefaultVertex(const DefaultVertex& vertex) = default;

		static std::vector<spl::VertexAttribute> getVertexAttributes();

		virtual void getDefaultVertex(DefaultVertex& vertex) const;

		scp::f32vec3 pos;
		scp::f32vec3 normal;
		scp::f32vec2 texCoords;
	};

	template<typename VertexType = DefaultVertex>
	class Mesh : public Drawable
	{
		public:

			Mesh(const std::filesystem::path& path, DrawableStorage verticesStorage = DrawableStorage::Static, DrawableStorage indicesStorage = DrawableStorage::Static);
			Mesh(const std::vector<VertexType>& vertices, DrawableStorage verticesStorage = DrawableStorage::Static, DrawableStorage indicesStorage = DrawableStorage::Static);
			Mesh(const std::vector<VertexType>& vertices, const std::vector<uint32_t> indices, DrawableStorage verticesStorage = DrawableStorage::Static, DrawableStorage indicesStorage = DrawableStorage::Static);
			Mesh(const Mesh<VertexType>& mesh) = delete;
			Mesh(Mesh<VertexType>&& mesh) = delete;

			Mesh<VertexType>& operator=(const Mesh<VertexType>& mesh) = delete;
			Mesh<VertexType>& operator=(Mesh<VertexType>&& mesh) = delete;

			void updateVertices(const std::vector<VertexType>& vertices);
			void updateIndices(const std::vector<uint32_t>& indices);
			void updateVertices(const std::vector<VertexType>& vertices, DrawableStorage storage);
			void updateIndices(const std::vector<uint32_t>& indices, DrawableStorage storage);

			virtual bool isValid() const;

			~Mesh() = default;

		protected:

			bool _loadObj(const std::filesystem::path& path);

			Mesh();

			std::vector<VertexType> _vertices;
			std::vector<uint32_t> _indices;
	};
}

#include <SplayLibrary/3D/templates/Mesh.hpp>
