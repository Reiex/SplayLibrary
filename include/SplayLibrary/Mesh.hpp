#pragma once

#include <SplayLibrary/types.hpp>

namespace spl
{
	template<typename VertexType>
	class Mesh
	{
		public:

			Mesh(const std::vector<VertexType>& vertices);
			Mesh(const std::vector<VertexType>& vertices, const std::vector<uint32_t> indices);

		private:

			void draw(/* projection, view, model */) const;

			mat4 _model;

			uint32_t _vao;
			uint32_t _vbo;
			uint32_t _ebo;
	};
}
