#include <SplayLibrary/SplayLibrary.hpp>
#include <SplayLibrary/Private/Private.hpp>

#define SPLD_VEC(vecName, vecSize, eltType)																														\
SPLD_VEC_EXTERNAL_OP(vecName, vecSize, eltType)																													\
SPLD_VEC_SPECIAL_FUNC(vecName, vecSize, eltType)


// Vec external operators

#define SPLD_VEC_EXTERNAL_OP(vecName, vecSize, eltType)																											\
SPLD_##vecName##_EXTERNAL_OP(vecName, vecSize, eltType)																											\
SPLD_VEC##vecSize##_EXTERNAL_OP_CMP(vecName, vecSize, eltType)																									\
SPLD_VEC##vecSize##_EXTERNAL_OP_STREAM(vecName, vecSize, eltType)


#define SPLD_vec_EXTERNAL_OP(vecName, vecSize, eltType)																											\
SPLD_VEC_EXTERNAL_OP_U_ARITH(vecName, vecSize, eltType)																											\
SPLD_VEC##vecSize##_EXTERNAL_OP_S_ARITH(vecName, vecSize, eltType)

#define SPLD_dvec_EXTERNAL_OP(vecName, vecSize, eltType)																										\
SPLD_VEC_EXTERNAL_OP_U_ARITH(vecName, vecSize, eltType)																											\
SPLD_VEC##vecSize##_EXTERNAL_OP_S_ARITH(vecName, vecSize, eltType)

#define SPLD_ivec_EXTERNAL_OP(vecName, vecSize, eltType)																										\
SPLD_VEC_EXTERNAL_OP_U_ARITH(vecName, vecSize, eltType)																											\
SPLD_VEC_EXTERNAL_OP_BITWISE(vecName, vecSize, eltType)																											\
SPLD_VEC##vecSize##_EXTERNAL_OP_S_ARITH(vecName, vecSize, eltType)

#define SPLD_uvec_EXTERNAL_OP(vecName, vecSize, eltType) 																										\
SPLD_VEC_EXTERNAL_OP_U_ARITH(vecName, vecSize, eltType)																											\
SPLD_VEC_EXTERNAL_OP_BITWISE(vecName, vecSize, eltType)

#define SPLD_bvec_EXTERNAL_OP(vecName, vecSize, eltType) 																										\
SPLD_VEC##vecSize##_EXTERNAL_OP_LOGIC(vecName, vecSize, eltType)


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


#define SPLD_VEC_EXTERNAL_OP_BITWISE(vecName, vecSize, eltType)																									\
vecName##vecSize operator|(const vecName##vecSize##& u, const vecName##vecSize##& v) { vecName##vecSize w(u); return w |= v; }									\
vecName##vecSize operator&(const vecName##vecSize##& u, const vecName##vecSize##& v) { vecName##vecSize w(u); return w &= v; }									\
vecName##vecSize operator^(const vecName##vecSize##& u, const vecName##vecSize##& v) { vecName##vecSize w(u); return w ^= v; }


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


#define SPLD_VEC2_EXTERNAL_OP_STREAM(vecName, vecSize, eltType)																									\
std::ostream& operator<<(std::ostream& stream, const vecName##vecSize##& u) { stream << "vec2(" << u.x << ", " << u.y << ")"; return stream; }

#define SPLD_VEC3_EXTERNAL_OP_STREAM(vecName, vecSize, eltType)																									\
std::ostream& operator<<(std::ostream& stream, const vecName##vecSize##& u) { stream << "vec3(" << u.x << ", " << u.y << ", " << u.z << ")"; return stream; }

#define SPLD_VEC4_EXTERNAL_OP_STREAM(vecName, vecSize, eltType)																									\
std::ostream& operator<<(std::ostream& stream, const vecName##vecSize##& u)																						\
{																																								\
	stream << "vec4(" << u.x << ", " << u.y << ", " << u.z << ", " << u.w << ")";																				\
	return stream;																																				\
}


// Vec special functions

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
vecName##vecSize radians(const vecName##vecSize& u) { return u * std::numbers::pi / 180.0; }																	\
vecName##vecSize degrees(const vecName##vecSize& u) { return u * 180.0 / std::numbers::pi; }																	\
vecName##vecSize inversesqrt(const vecName##vecSize& u) { return 1.0 / sqrt(u); }																				\
vecName##vecSize fract(const vecName##vecSize& u) { return u - floor(u); }																						\
vecName##vecSize mod(const vecName##vecSize& u, const vecName##vecSize& v) { return u - v * floor(u / v); }														\
vecName##vecSize mod(const vecName##vecSize& u, eltType x) { return u - x * floor(u / x); }																		\
eltType length(const vecName##vecSize##& u) { return std::sqrt(dot(u, u)); }																					\
eltType distance(const vecName##vecSize##& u, const vecName##vecSize##& v) { return length(v - u); }															\
vecName##vecSize normalize(const vecName##vecSize##& u) { return u / length(u); }																				\
vecName##vecSize faceforward(const vecName##vecSize##& n, const vecName##vecSize##& i, const vecName##vecSize##& nRef) { return dot(nRef, i) < 0 ? n : -n; }	\
vecName##vecSize reflect(const vecName##vecSize##& i, const vecName##vecSize##& n) { return i - 2 * dot(n, i) * n; }											\
vecName##vecSize refract(const vecName##vecSize##& i, const vecName##vecSize##& n, eltType eta)																	\
{																																								\
	const eltType d = dot(n, i);																																\
	const eltType k = 1 - eta * eta * (1 - d * d);																												\
	return k < 0 ? 0 : eta * i - (eta * d + std::sqrt(k)) * n;																									\
}

#define SPLD_VEC2_REAL_FUNC(vecName, vecSize, eltType)																											\
vecName##2 sin(const vecName##2& u) { return { std::sin(u.x), std::sin(u.y) }; }																				\
vecName##2 cos(const vecName##2& u) { return { std::cos(u.x), std::cos(u.y) }; }																				\
vecName##2 tan(const vecName##2& u) { return { std::tan(u.x), std::tan(u.y) }; }																				\
vecName##2 asin(const vecName##2& u) { return { std::asin(u.x), std::asin(u.y) }; }																				\
vecName##2 acos(const vecName##2& u) { return { std::acos(u.x), std::acos(u.y) }; }																				\
vecName##2 atan(const vecName##2& y, const vecName##2& x) { return { std::atan2(y.x, x.x), std::atan2(y.y, x.y) }; }											\
vecName##2 atan(const vecName##2& u) { return { std::atan(u.x), std::atan(u.y) }; }																				\
vecName##2 sinh(const vecName##2& u) { return { std::sinh(u.x), std::sinh(u.y) }; }																				\
vecName##2 cosh(const vecName##2& u) { return { std::cosh(u.x), std::cosh(u.y) }; }																				\
vecName##2 tanh(const vecName##2& u) { return { std::tanh(u.x), std::tanh(u.y) }; }																				\
vecName##2 asinh(const vecName##2& u) { return { std::asinh(u.x), std::asinh(u.y) }; }																			\
vecName##2 acosh(const vecName##2& u) { return { std::acosh(u.x), std::acosh(u.y) }; }																			\
vecName##2 atanh(const vecName##2& u) { return { std::atanh(u.x), std::atanh(u.y) }; }																			\
vecName##2 pow(const vecName##2& u, const vecName##2& p) { return { std::pow(u.x, p.x), std::pow(u.y, p.y) }; }													\
vecName##2 exp(const vecName##2& u) { return { std::exp(u.x), std::exp(u.y) }; }																				\
vecName##2 log(const vecName##2& u) { return { std::log(u.x), std::log(u.y) }; }																				\
vecName##2 exp2(const vecName##2& u) { return { std::exp2(u.x), std::exp2(u.y) }; }																				\
vecName##2 log2(const vecName##2& u) { return { std::log2(u.x), std::log2(u.y) }; }																				\
vecName##2 sqrt(const vecName##2& u) { return { std::sqrt(u.x), std::sqrt(u.y) }; }																				\
vecName##2 floor(const vecName##2& u) { return { std::floor(u.x), std::floor(u.y) }; }																			\
vecName##2 trunc(const vecName##2& u) { return { std::trunc(u.x), std::trunc(u.y) }; }																			\
vecName##2 round(const vecName##2& u) { return { std::round(u.x), std::round(u.y) }; }																			\
vecName##2 ceil(const vecName##2& u) { return { std::ceil(u.x), std::ceil(u.y) }; }																				\
eltType dot(const vecName##2& u, const vecName##2& v) { return u.x * v.x + u.y * v.y; }

#define SPLD_VEC3_REAL_FUNC(vecName, vecSize, eltType)																											\
vecName##3 sin(const vecName##3& u) { return { std::sin(u.x), std::sin(u.y), std::sin(u.z) }; }																	\
vecName##3 cos(const vecName##3& u) { return { std::cos(u.x), std::cos(u.y), std::cos(u.z) }; }																	\
vecName##3 tan(const vecName##3& u) { return { std::tan(u.x), std::tan(u.y), std::tan(u.z) }; }																	\
vecName##3 asin(const vecName##3& u) { return { std::asin(u.x), std::asin(u.y), std::asin(u.z) }; }																\
vecName##3 acos(const vecName##3& u) { return { std::acos(u.x), std::acos(u.y), std::acos(u.z) }; }																\
vecName##3 atan(const vecName##3& y, const vecName##3& x) { return { std::atan2(y.x, x.x), std::atan2(y.y, x.y), std::atan2(y.z, x.z) }; }						\
vecName##3 atan(const vecName##3& u) { return { std::atan(u.x), std::atan(u.y), std::atan(u.z) }; }																\
vecName##3 sinh(const vecName##3& u) { return { std::sinh(u.x), std::sinh(u.y), std::sinh(u.z) }; }																\
vecName##3 cosh(const vecName##3& u) { return { std::cosh(u.x), std::cosh(u.y), std::cosh(u.z) }; }																\
vecName##3 tanh(const vecName##3& u) { return { std::tanh(u.x), std::tanh(u.y), std::tanh(u.z) }; }																\
vecName##3 asinh(const vecName##3& u) { return { std::asinh(u.x), std::asinh(u.y), std::asinh(u.z) }; }															\
vecName##3 acosh(const vecName##3& u) { return { std::acosh(u.x), std::acosh(u.y), std::acosh(u.z) }; }															\
vecName##3 atanh(const vecName##3& u) { return { std::atanh(u.x), std::atanh(u.y), std::atanh(u.z) }; }															\
vecName##3 pow(const vecName##3& u, const vecName##3& p) { return { std::pow(u.x, p.x), std::pow(u.y, p.y), std::pow(u.z, p.z) }; }								\
vecName##3 exp(const vecName##3& u) { return { std::exp(u.x), std::exp(u.y), std::exp(u.z) }; }																	\
vecName##3 log(const vecName##3& u) { return { std::log(u.x), std::log(u.y), std::log(u.z) }; }																	\
vecName##3 exp2(const vecName##3& u) { return { std::exp2(u.x), std::exp2(u.y), std::exp2(u.z) }; }																\
vecName##3 log2(const vecName##3& u) { return { std::log2(u.x), std::log2(u.y), std::log2(u.z) }; }																\
vecName##3 sqrt(const vecName##3& u) { return { std::sqrt(u.x), std::sqrt(u.y), std::sqrt(u.z) }; }																\
vecName##3 floor(const vecName##3& u) { return { std::floor(u.x), std::floor(u.y), std::floor(u.z) }; }															\
vecName##3 trunc(const vecName##3& u) { return { std::trunc(u.x), std::trunc(u.y), std::trunc(u.z) }; }															\
vecName##3 round(const vecName##3& u) { return { std::round(u.x), std::round(u.y), std::round(u.z) }; }															\
vecName##3 ceil(const vecName##3& u) { return { std::ceil(u.x), std::ceil(u.y), std::ceil(u.z) }; }																\
eltType dot(const vecName##3& u, const vecName##3& v) { return u.x * v.x + u.y * v.y + u.z * v.z; }																\
vecName##3 cross(const vecName##3& u, const vecName##3& v) { return { u[1]*v[2] - u[2]*v[1], u[2]*v[0] - u[0]*v[2], u[0]*v[1] - u[1]*v[0] }; }

#define SPLD_VEC4_REAL_FUNC(vecName, vecSize, eltType)																											\
vecName##4 sin(const vecName##4& u) { return { std::sin(u.x), std::sin(u.y), std::sin(u.z), std::sin(u.w) }; }													\
vecName##4 cos(const vecName##4& u) { return { std::cos(u.x), std::cos(u.y), std::cos(u.z), std::cos(u.w) }; }													\
vecName##4 tan(const vecName##4& u) { return { std::tan(u.x), std::tan(u.y), std::tan(u.z), std::tan(u.w) }; }													\
vecName##4 asin(const vecName##4& u) { return { std::asin(u.x), std::asin(u.y), std::asin(u.z), std::asin(u.w) }; }												\
vecName##4 acos(const vecName##4& u) { return { std::acos(u.x), std::acos(u.y), std::acos(u.z), std::acos(u.w) }; }												\
vecName##4 atan(const vecName##4& y, const vecName##4& x) { return { std::atan2(y.x, x.x), std::atan2(y.y, x.y), std::atan2(y.z, x.z), std::atan2(y.w, x.w) }; }\
vecName##4 atan(const vecName##4& u) { return { std::atan(u.x), std::atan(u.y), std::atan(u.z), std::atan(u.w) }; }												\
vecName##4 sinh(const vecName##4& u) { return { std::sinh(u.x), std::sinh(u.y), std::sinh(u.z), std::sinh(u.w) }; }												\
vecName##4 cosh(const vecName##4& u) { return { std::cosh(u.x), std::cosh(u.y), std::cosh(u.z), std::cosh(u.w) }; }												\
vecName##4 tanh(const vecName##4& u) { return { std::tanh(u.x), std::tanh(u.y), std::tanh(u.z), std::tanh(u.w) }; }												\
vecName##4 asinh(const vecName##4& u) { return { std::asinh(u.x), std::asinh(u.y), std::asinh(u.z), std::asinh(u.w) }; }										\
vecName##4 acosh(const vecName##4& u) { return { std::acosh(u.x), std::acosh(u.y), std::acosh(u.z), std::acosh(u.w) }; }										\
vecName##4 atanh(const vecName##4& u) { return { std::atanh(u.x), std::atanh(u.y), std::atanh(u.z), std::atanh(u.w) }; }										\
vecName##4 pow(const vecName##4& u, const vecName##4& p) { return { std::pow(u.x, p.x), std::pow(u.y, p.y), std::pow(u.z, p.z), std::pow(u.w, p.w) }; }			\
vecName##4 exp(const vecName##4& u) { return { std::exp(u.x), std::exp(u.y), std::exp(u.z), std::exp(u.w) }; }													\
vecName##4 log(const vecName##4& u) { return { std::log(u.x), std::log(u.y), std::log(u.z), std::log(u.w) }; }													\
vecName##4 exp2(const vecName##4& u) { return { std::exp2(u.x), std::exp2(u.y), std::exp2(u.z), std::exp2(u.w) }; }												\
vecName##4 log2(const vecName##4& u) { return { std::log2(u.x), std::log2(u.y), std::log2(u.z), std::log2(u.w) }; }												\
vecName##4 sqrt(const vecName##4& u) { return { std::sqrt(u.x), std::sqrt(u.y), std::sqrt(u.z), std::sqrt(u.w) }; }												\
vecName##4 floor(const vecName##4& u) { return { std::floor(u.x), std::floor(u.y), std::floor(u.z), std::floor(u.w) }; }										\
vecName##4 trunc(const vecName##4& u) { return { std::trunc(u.x), std::trunc(u.y), std::trunc(u.z), std::trunc(u.w) }; }										\
vecName##4 round(const vecName##4& u) { return { std::round(u.x), std::round(u.y), std::round(u.z), std::round(u.w) }; }										\
vecName##4 ceil(const vecName##4& u) { return { std::ceil(u.x), std::ceil(u.y), std::ceil(u.z), std::ceil(u.w)}; }												\
eltType dot(const vecName##4& u, const vecName##4& v) { return u.x * v.x + u.y * v.y + u.z * v.z + u.w * v.w; }

namespace spl
{
	SPLD_VEC(vec, 2, float);
	SPLD_VEC(vec, 3, float);
	SPLD_VEC(vec, 4, float);

	SPLD_VEC(dvec, 2, double);
	SPLD_VEC(dvec, 3, double);
	SPLD_VEC(dvec, 4, double);

	SPLD_VEC(ivec, 2, int32_t);
	SPLD_VEC(ivec, 3, int32_t);
	SPLD_VEC(ivec, 4, int32_t);

	SPLD_VEC(uvec, 2, uint32_t);
	SPLD_VEC(uvec, 3, uint32_t);
	SPLD_VEC(uvec, 4, uint32_t);

	SPLD_VEC(bvec, 2, uint32_t);
	SPLD_VEC(bvec, 3, uint32_t);
	SPLD_VEC(bvec, 4, uint32_t);
}
