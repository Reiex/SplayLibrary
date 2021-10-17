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
		Immutable,
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

			Drawable();

			void setVertexAttributes(const std::vector<VertexAttribute>& attributes);

			void createVertices(const void* vertices, uint32_t size, DrawableStorage storage = DrawableStorage::Static);
			void updateVertices(const void* vertices, uint32_t size, uint32_t offset = 0);
			void destroyVertices();

			void createIndices(const uint32_t* indices, uint32_t count, DrawableStorage storage = DrawableStorage::Static);
			void updateIndices(const uint32_t* indices, uint32_t count, uint32_t startIndex = 0);
			void setIndicesCount(uint32_t count);
			void destroyIndices();

			virtual void draw() const;

		private:

			uint32_t _vao;
			Buffer _vbo;
			DrawableStorage _vboStorage;
			Buffer _ebo;
			DrawableStorage _eboStorage;

			uint32_t _indicesCount;

		friend RenderWindow;
	};
}
