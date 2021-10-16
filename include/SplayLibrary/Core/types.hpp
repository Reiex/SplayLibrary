#pragma once

#include <atomic>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <memory>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

#include <SciPP/SciPP.hpp>


namespace spl
{
	template<typename EltType, uint8_t Col, uint8_t Row, typename ColType> struct _Mat;

	struct vec2; struct vec3; struct vec4;
	struct dvec2; struct dvec3; struct dvec4;
	struct ivec2; struct ivec3; struct ivec4;
	struct uvec2; struct uvec3; struct uvec4;
	struct bvec2; struct bvec3; struct bvec4;

	typedef _Mat<float, 2, 2, vec2> mat2x2;
	typedef _Mat<float, 3, 2, vec3> mat3x2;
	typedef _Mat<float, 4, 2, vec4> mat4x2;
	typedef _Mat<float, 2, 3, vec2> mat2x3;
	typedef _Mat<float, 3, 3, vec3> mat3x3;
	typedef _Mat<float, 4, 3, vec4> mat4x3;
	typedef _Mat<float, 2, 4, vec2> mat2x4;
	typedef _Mat<float, 3, 4, vec3> mat3x4;
	typedef _Mat<float, 4, 4, vec4> mat4x4;
	typedef mat2x2 mat2;
	typedef mat3x3 mat3;
	typedef mat4x4 mat4;

	typedef _Mat<double, 2, 2, dvec2> dmat2x2;
	typedef _Mat<double, 3, 2, dvec3> dmat3x2;
	typedef _Mat<double, 4, 2, dvec4> dmat4x2;
	typedef _Mat<double, 2, 3, dvec2> dmat2x3;
	typedef _Mat<double, 3, 3, dvec3> dmat3x3;
	typedef _Mat<double, 4, 3, dvec4> dmat4x3;
	typedef _Mat<double, 2, 4, dvec2> dmat2x4;
	typedef _Mat<double, 3, 4, dvec3> dmat3x4;
	typedef _Mat<double, 4, 4, dvec4> dmat4x4;
	typedef dmat2x2 dmat2;
	typedef dmat3x3 dmat3;
	typedef dmat4x4 dmat4;

	enum class BufferBindingTarget;
	enum class BufferUsage;
	namespace BufferStorageFlags { enum Flags; }
	class Buffer;

	struct VertexAttribute;
	enum class DrawableStorage;
	class Drawable;

	struct Event;
	struct ResizeEvent;
	
	class RenderWindow;

	class Shader;
}
