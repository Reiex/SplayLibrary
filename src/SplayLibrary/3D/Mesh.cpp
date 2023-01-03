///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2021-2023
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SplayLibrary/3D/3D.hpp>
#include <SplayLibrary/Private/PrivateNotIncluded.hpp>

namespace spl
{
	DefaultVertex::DefaultVertex(const scp::f32vec3& vPos, const scp::f32vec3& vNormal, const scp::f32vec2& vTexCoords) :
		pos(vPos),
		normal(vNormal),
		texCoords(vTexCoords)
	{
	}

	std::vector<spl::VertexAttribute> DefaultVertex::getVertexAttributes()
	{
		scp::f32vec3 pos = { 0.f, 0.f, 0.f };
		scp::f32vec3 normal = { 0.f, 0.f, 0.f };
		scp::f32vec2 texCoords = { 0.f, 0.f };

		return {
			{0,	spl::VertexAttribute::Type::Vec3,	offsetof(DefaultVertex, pos),		sizeof(DefaultVertex)},
			{1,	spl::VertexAttribute::Type::Vec3,	offsetof(DefaultVertex, normal),	sizeof(DefaultVertex)},
			{2,	spl::VertexAttribute::Type::Vec2,	offsetof(DefaultVertex, texCoords),	sizeof(DefaultVertex)}
		};
	}

	void DefaultVertex::getDefaultVertex(DefaultVertex& vertex) const
	{
		vertex = *this;
	}
}
