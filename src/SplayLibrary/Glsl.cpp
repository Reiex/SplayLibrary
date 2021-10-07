#include <SplayLibrary/SplayLibrary.hpp>
#include <SplayLibrary/Private.hpp>

#define SPLD_VEC(vecName, vecSize, eltType)																														\
SPLD_VEC_EXTERNAL_OP(vecName, vecSize, eltType)																													\
SPLD_VEC_SPECIAL_FUNC(vecName, vecSize, eltType)

#define SPLD_VEC_EXTERNAL_OP(vecName, vecSize, eltType) SPLD_##vecName##_EXTERNAL_OP(vecName, vecSize, eltType)


#define SPLD_vec_EXTERNAL_OP(vecName, vecSize, eltType)																											\
SPLD_VEC_EXTERNAL_OP_U_ARITH(vecName, vecSize, eltType)																											\
SPLD_VEC##vecSize##_EXTERNAL_OP_S_ARITH(vecName, vecSize, eltType)																								\
SPLD_VEC##vecSize##_EXTERNAL_OP_CMP(vecName, vecSize, eltType)

#define SPLD_dvec_EXTERNAL_OP(vecName, vecSize, eltType)																										\
SPLD_VEC_EXTERNAL_OP_U_ARITH(vecName, vecSize, eltType)																											\
SPLD_VEC##vecSize##_EXTERNAL_OP_S_ARITH(vecName, vecSize, eltType)																								\
SPLD_VEC##vecSize##_EXTERNAL_OP_CMP(vecName, vecSize, eltType)

#define SPLD_ivec_EXTERNAL_OP(vecName, vecSize, eltType)																										\
SPLD_VEC_EXTERNAL_OP_U_ARITH(vecName, vecSize, eltType)																											\
SPLD_VEC##vecSize##_EXTERNAL_OP_S_ARITH(vecName, vecSize, eltType)																								\
SPLD_VEC##vecSize##_EXTERNAL_OP_CMP(vecName, vecSize, eltType)

#define SPLD_uvec_EXTERNAL_OP(vecName, vecSize, eltType) 																										\
SPLD_VEC_EXTERNAL_OP_U_ARITH(vecName, vecSize, eltType)																											\
SPLD_VEC##vecSize##_EXTERNAL_OP_CMP(vecName, vecSize, eltType)

#define SPLD_bvec_EXTERNAL_OP(vecName, vecSize, eltType) 																										\
SPLD_VEC##vecSize##_EXTERNAL_OP_LOGIC(vecName, vecSize, eltType)																								\
SPLD_VEC##vecSize##_EXTERNAL_OP_CMP(vecName, vecSize, eltType)


#define SPLD_VEC_EXTERNAL_OP_U_ARITH(vecName, vecSize, eltType)																									\
vecName##vecSize operator+(const vecName##vecSize##& u, const vecName##vecSize##& v) { vecName##vecSize w(u); return w += v; }									\
vecName##vecSize operator-(const vecName##vecSize##& u, const vecName##vecSize##& v) { vecName##vecSize w(u); return w -= v; }									\
vecName##vecSize operator*(const vecName##vecSize##& u, const vecName##vecSize##& v) { vecName##vecSize w(u); return w *= v; }									\
vecName##vecSize operator/(const vecName##vecSize##& u, const vecName##vecSize##& v) { vecName##vecSize w(u); return w /= v; }									\
																																								\
vecName##vecSize operator+(const vecName##vecSize##& u, eltType x) { vecName##vecSize v(u); return v += x; }													\
vecName##vecSize operator-(const vecName##vecSize##& u, eltType x) { vecName##vecSize v(u); return v -= x; }													\
vecName##vecSize operator*(const vecName##vecSize##& u, eltType x) { vecName##vecSize v(u); return v *= x; }													\
vecName##vecSize operator/(const vecName##vecSize##& u, eltType x) { vecName##vecSize v(u); return v /= x; }													\
																																								\
vecName##vecSize operator+(eltType x, const vecName##vecSize##& u) { vecName##vecSize v(u); return v += x; }													\
vecName##vecSize operator-(eltType x, const vecName##vecSize##& u) { vecName##vecSize v(u); return v -= x; }													\
vecName##vecSize operator*(eltType x, const vecName##vecSize##& u) { vecName##vecSize v(u); return v *= x; }													\
vecName##vecSize operator/(eltType x, const vecName##vecSize##& u) { vecName##vecSize v(u); return v /= x; }


#define SPLD_VEC2_EXTERNAL_OP_S_ARITH(vecName, vecSize, eltType)																								\
vecName##2 operator+(const vecName##2& u) { return u; }																											\
vecName##2 operator-(const vecName##2& u) { return { -u.x, -u.y }; }

#define SPLD_VEC3_EXTERNAL_OP_S_ARITH(vecName, vecSize, eltType)																								\
vecName##3 operator+(const vecName##3& u) { return u; }																											\
vecName##3 operator-(const vecName##3& u) { return { -u.x, -u.y, -u.z }; }

#define SPLD_VEC4_EXTERNAL_OP_S_ARITH(vecName, vecSize, eltType)																								\
vecName##4 operator+(const vecName##4& u) { return u; }																											\
vecName##4 operator-(const vecName##4& u) { return { -u.x, -u.y, -u.z, -u.w }; }


#define SPLD_VEC2_EXTERNAL_OP_LOGIC(vecName, vecSize, eltType)																									\
vecName##2 operator||(const vecName##2& u, const vecName##2& v) { return { u.x || v.x, u.y || v.y }; }															\
vecName##2 operator&&(const vecName##2& u, const vecName##2& v) { return { u.x && v.x, u.y && v.y }; }															\
																																								\
vecName##2 operator||(const vecName##2& u, eltType x) { return { u.x || x, u.y || x }; }																		\
vecName##2 operator&&(const vecName##2& u, eltType x) { return { u.x && x, u.y && x }; }																		\
																																								\
vecName##2 operator||(eltType x, const vecName##2& u) { return { u.x || x, u.y || x }; }																		\
vecName##2 operator&&(eltType x, const vecName##2& u) { return { u.x && x, u.y && x }; }

#define SPLD_VEC3_EXTERNAL_OP_LOGIC(vecName, vecSize, eltType)																									\
vecName##3 operator||(const vecName##3& u, const vecName##3& v) { return { u.x || v.x, u.y || v.y, u.z || v.z }; }												\
vecName##3 operator&&(const vecName##3& u, const vecName##3& v) { return { u.x && v.x, u.y && v.y, u.z && v.z }; }												\
																																								\
vecName##3 operator||(const vecName##3& u, eltType x) { return { u.x || x, u.y || x, u.z || x }; }																\
vecName##3 operator&&(const vecName##3& u, eltType x) { return { u.x && x, u.y && x, u.z && x }; }																\
																																								\
vecName##3 operator||(eltType x, const vecName##3& u) { return { u.x || x, u.y || x, u.z || x }; }																\
vecName##3 operator&&(eltType x, const vecName##3& u) { return { u.x && x, u.y && x, u.z && x }; }

#define SPLD_VEC4_EXTERNAL_OP_LOGIC(vecName, vecSize, eltType)																									\
vecName##4 operator||(const vecName##4& u, const vecName##4& v) { return { u.x || v.x, u.y || v.y, u.z || v.z, u.w || v.w }; }									\
vecName##4 operator&&(const vecName##4& u, const vecName##4& v) { return { u.x && v.x, u.y && v.y, u.z && v.z, u.w && v.w }; }									\
																																								\
vecName##4 operator||(const vecName##4& u, eltType x) { return { u.x || x, u.y || x, u.z || x, u.w || x }; }													\
vecName##4 operator&&(const vecName##4& u, eltType x) { return { u.x && x, u.y && x, u.z && x, u.w && x }; }													\
																																								\
vecName##4 operator||(eltType x, const vecName##4& u) { return { u.x || x, u.y || x, u.z || x, u.w || x }; }													\
vecName##4 operator&&(eltType x, const vecName##4& u) { return { u.x && x, u.y && x, u.z && x, u.w && x }; }


#define SPLD_VEC2_EXTERNAL_OP_CMP(vecName, vecSize, eltType)																									\
bool operator==(const vecName##2& u, const vecName##2& v) { return u.x == v.x && u.y == v.y; }																	\
bool operator!=(const vecName##2& u, const vecName##2& v) { return u.x != v.x || u.y != v.y; }

#define SPLD_VEC3_EXTERNAL_OP_CMP(vecName, vecSize, eltType)																									\
bool operator==(const vecName##3& u, const vecName##3& v) { return u.x == v.x && u.y == v.y && u.z == v.z; }													\
bool operator!=(const vecName##3& u, const vecName##3& v) { return u.x != v.x || u.y != v.y || u.z != v.z; }

#define SPLD_VEC4_EXTERNAL_OP_CMP(vecName, vecSize, eltType)																									\
bool operator==(const vecName##4& u, const vecName##4& v) { return u.x == v.x && u.y == v.y && u.z == v.z && u.w == v.w; }										\
bool operator!=(const vecName##4& u, const vecName##4& v) { return u.x != v.x || u.y != v.y || u.z != v.z || u.w != v.w; }


#define SPLD_VEC_SPECIAL_FUNC(vecName, vecSize, eltType) SPLD_##vecName##_SPECIAL_FUNC(vecName, vecSize, eltType)


#define SPLD_vec_SPECIAL_FUNC(vecName, vecSize, eltType)																										\
SPLD_VEC_REAL_FUNC(vecName, vecSize, eltType)																													\
SPLD_VEC##vecSize##_REAL_FUNC(vecName, vecSize, eltType)

#define SPLD_dvec_SPECIAL_FUNC(vecName, vecSize, eltType)																										\
SPLD_VEC_REAL_FUNC(vecName, vecSize, eltType)																													\
SPLD_VEC##vecSize##_REAL_FUNC(vecName, vecSize, eltType)

#define SPLD_ivec_SPECIAL_FUNC(vecName, vecSize, eltType)
#define SPLD_uvec_SPECIAL_FUNC(vecName, vecSize, eltType)
#define SPLD_bvec_SPECIAL_FUNC(vecName, vecSize, eltType)


#define SPLD_VEC_REAL_FUNC(vecName, vecSize, eltType)																											\
eltType length(const vecName##vecSize##& v) { return std::sqrt(dot(v, v)); }																					\
eltType distance(const vecName##vecSize##& u, const vecName##vecSize##& v) { return length(v - u); }															\
vecName##vecSize normalize(const vecName##vecSize##& v) { return v / length(v); }																				\
vecName##vecSize faceforward(const vecName##vecSize##& n, const vecName##vecSize##& i, const vecName##vecSize##& nRef) { return dot(nref, i) < 0 ? n : -n; }	\
vecName##vecSize reflect(const vecName##vecSize##& i, const vecName##vecSize##& n) { return i - 2 * dot(n, i) * n; }											\
vecName##vecSize refract(const vecName##vecSize##& i, const vecName##vecSize##& n, eltType eta)																	\
{																																								\
	const eltType d = dot(n, i);																																\
	const eltType k = 1 - eta * eta * (1 - d * d);																												\
	return k < 0 ? 0 : eta * I - (eta * d + sqrt(k)) * N;																										\
}

#define SPLD_VEC2_REAL_FUNC(vecName, vecSize, eltType)																											\
eltType dot(const vecName##2& u, const vecName##2& v) { return u.x * v.x + u.y * v.y; }

#define SPLD_VEC3_REAL_FUNC(vecName, vecSize, eltType)																											\
eltType dot(const vecName##3& u, const vecName##3& v) { return u.x * v.x + u.y * v.y + u.z * v.z; }																\
vecName##3 cross(const vecName##3& u, const vecName##3& v) { return { u[1]*v[2] - u[2]*v[1], u[2] * v[0] - u[2] * v[2], u[0] * v[1] - u[1] * v[0] }; }

#define SPLD_VEC4_REAL_FUNC(vecName, vecSize, eltType)																											\
eltType dot(const vecName##4& u, const vecName##4& v) { return u.x * v.x + u.y * v.y + u.z * v.z + u.w * v.w; }

namespace spl
{
	SPLD_VEC_EXTERNAL_OP(vec, 2, float);
	SPLD_VEC_EXTERNAL_OP(vec, 3, float);
	SPLD_VEC_EXTERNAL_OP(vec, 4, float);

	SPLD_VEC_EXTERNAL_OP(dvec, 2, double);
	SPLD_VEC_EXTERNAL_OP(dvec, 3, double);
	SPLD_VEC_EXTERNAL_OP(dvec, 4, double);

	SPLD_VEC_EXTERNAL_OP(ivec, 2, int32_t);
	SPLD_VEC_EXTERNAL_OP(ivec, 3, int32_t);
	SPLD_VEC_EXTERNAL_OP(ivec, 4, int32_t);

	SPLD_VEC_EXTERNAL_OP(uvec, 2, uint32_t);
	SPLD_VEC_EXTERNAL_OP(uvec, 3, uint32_t);
	SPLD_VEC_EXTERNAL_OP(uvec, 4, uint32_t);

	SPLD_VEC_EXTERNAL_OP(bvec, 2, uint32_t);
	SPLD_VEC_EXTERNAL_OP(bvec, 3, uint32_t);
	SPLD_VEC_EXTERNAL_OP(bvec, 4, uint32_t);
}
