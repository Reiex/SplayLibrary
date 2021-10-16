#pragma once

#include <SplayLibrary/Core/types.hpp>

namespace spl
{
	struct VertexAttribute
	{
		enum class Type
		{
			Float = 0x10,
			Vec2 = 0x20,
			Vec3 = 0x30,
			Vec4 = 0x40,

			Int = 0x11,
			IVec2 = 0x21,
			IVec3 = 0x31,
			IVec4 = 0x41,

			UnsignedInt = 0x12,
			UVec2 = 0x22,
			UVec3 = 0x32,
			UVec4 = 0x42,
		};

		uint32_t index;
		Type type;
		uint32_t offset;
		uint32_t stride;
		bool normalized = false;
		uint32_t divisor = 0;
	};

	enum class DrawableStorage
	{
		Static,
		Dynamic,
		Stream
	};

	class Drawable
	{
		public:

			Drawable(const Drawable& mesh) = delete;
			Drawable(Drawable&& mesh) = delete;

			Drawable& operator=(const Drawable& mesh) = delete;
			Drawable& operator=(Drawable&& mesh) = delete;

			~Drawable();

		protected:

			/*
			DrawableStorage:
				Immutable
				Static
				Dynamic
				Stream
			*/

			Drawable();
			void create(const void* vertices, uint32_t verticesSize, const uint32_t* indices, uint32_t indicesSize, DrawableStorage type, const std::vector<VertexAttribute>& attributes);
			void destroy();

			virtual void draw() const;

		private:

			DrawableStorage _type;

			uint32_t _vao;
			Buffer _vbo;
			Buffer _ebo;

			uint32_t _indicesCount;

		friend RenderWindow;
	};
}
