#include <SplayLibrary/SplayLibrary.hpp>
#include <SplayLibrary/Core/Private.hpp>

namespace spl
{
	DefaultVertex::DefaultVertex(const vec3& vPos, const vec3& vNormal, const vec2& vTexCoords) :
		pos(vPos),
		normal(vNormal),
		texCoords(vTexCoords)
	{
	}

	std::vector<spl::VertexAttribute> DefaultVertex::getVertexAttributes()
	{
		vec3 pos = { 0.f, 0.f, 0.f };
		vec3 normal = { 0.f, 0.f, 0.f };
		vec2 texCoords = { 0.f, 0.f };

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
