#pragma once

#include <SplayLibrary/Core/types.hpp>

// GLSL Vec

#define SPLD_VEC(vecName, vecSize, eltType)																														\
struct vecName##vecSize																																			\
{																																								\
	SPLD_VEC##vecSize##_CONSTRUCTORS(vecName, vecSize, eltType)																									\
	SPLD_##vecName##_INTERNAL_OP(vecName, vecSize, eltType)																										\
	SPLD_VEC##vecSize##_ACCESSORS(vecName, vecSize, eltType)																									\
};																																								\
																																								\
SPLD_VEC_EXTERNAL_OP(vecName, vecSize, eltType)																													\
SPLD_VEC_SPECIAL_FUNC(vecName, vecSize, eltType)


// Vec constructors

#define SPLD_VEC2_CONSTRUCTORS(vecName, vecSize, eltType)																										\
vecName##2() = default; 																																		\
vecName##2(eltType value) : x(value), y(value) {} 																												\
vecName##2(eltType xValue, eltType yValue) : x(xValue), y(yValue) {}																							\
vecName##2(std::initializer_list<eltType> tab) : x(tab.begin()[0]), y(tab.begin()[1]) { assert(tab.size() == 2); }
																																								
#define SPLD_VEC3_CONSTRUCTORS(vecName, vecSize, eltType)																										\
vecName##3() = default;																																			\
vecName##3(eltType value) : x(value), y(value), z(value) {}																										\
vecName##3(eltType xValue, eltType yValue, eltType zValue) : x(xValue), y(yValue), z(zValue) {}																	\
vecName##3(std::initializer_list<eltType> tab) : x(tab.begin()[0]), y(tab.begin()[1]), z(tab.begin()[2]) { assert(tab.size() == 3); }							\
vecName##3(const vecName##2& v, eltType zValue) : x(v.x), y(v.y), z(zValue) {}																					\
vecName##3(eltType xValue, const vecName##2& v) : x(xValue), y(v.x), z(v.y) {}

#define SPLD_VEC4_CONSTRUCTORS(vecName, vecSize, eltType)																										\
vecName##4() = default;																																			\
vecName##4(eltType value) : x(value), y(value), z(value), w(value) {}																							\
vecName##4(eltType xValue, eltType yValue, eltType zValue, eltType wValue) : x(xValue), y(yValue), z(zValue), w(wValue) {}										\
vecName##4(std::initializer_list<eltType> tab) : x(tab.begin()[0]), y(tab.begin()[1]), z(tab.begin()[2]), w(tab.begin()[3]) { assert(tab.size() == 4); }		\
vecName##4(const vecName##2& v, eltType zValue, eltType wValue) : x(v.x), y(v.y), z(zValue), w(wValue) {}														\
vecName##4(eltType xValue, const vecName##2& v, eltType wValue) : x(xValue), y(v.x), z(v.y), w(wValue) {}														\
vecName##4(eltType xValue, eltType yValue, const vecName##2& v) : x(xValue), y(yValue), z(v.x), w(v.y) {}														\
vecName##4(const vecName##2& u, const vecName##2& v) : x(u.x), y(u.y), z(v.x), w(v.y) {}																		\
vecName##4(const vecName##3& v, eltType wValue) : x(v.x), y(v.y), z(v.z), w(wValue) {}																			\
vecName##4(eltType xValue, const vecName##3& v) : x(xValue), y(v.x), z(v.y), w(v.z) {}


// Vec internal operators

#define SPLD_vec_INTERNAL_OP(vecName, vecSize, eltType) SPLD_VEC##vecSize##_INTERNAL_OP_ARITH(vecName, vecSize, eltType)
#define SPLD_dvec_INTERNAL_OP(vecName, vecSize, eltType) SPLD_VEC##vecSize##_INTERNAL_OP_ARITH(vecName, vecSize, eltType)
#define SPLD_ivec_INTERNAL_OP(vecName, vecSize, eltType) SPLD_VEC##vecSize##_INTERNAL_OP_ARITH(vecName, vecSize, eltType)
#define SPLD_uvec_INTERNAL_OP(vecName, vecSize, eltType) SPLD_VEC##vecSize##_INTERNAL_OP_ARITH(vecName, vecSize, eltType)
#define SPLD_bvec_INTERNAL_OP(vecName, vecSize, eltType)

\
#define SPLD_VEC2_INTERNAL_OP_ARITH(vecName, vecSize, eltType)																									\
vecName##2& operator+=(const vecName##2& v) { x += v.x; y += v.y; return *this; }																				\
vecName##2& operator-=(const vecName##2& v) { x -= v.x; y -= v.y; return *this; }																				\
vecName##2& operator*=(const vecName##2& v) { x *= v.x; y *= v.y; return *this; }																				\
vecName##2& operator/=(const vecName##2& v) { x /= v.x; y /= v.y; return *this; }

#define SPLD_VEC3_INTERNAL_OP_ARITH(vecName, vecSize, eltType)																									\
vecName##3& operator+=(const vecName##3& v) { x += v.x; y += v.y; z += v.z; return *this; }																		\
vecName##3& operator-=(const vecName##3& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }																		\
vecName##3& operator*=(const vecName##3& v) { x *= v.x; y *= v.y; z *= v.z; return *this; }																		\
vecName##3& operator/=(const vecName##3& v) { x /= v.x; y /= v.y; z /= v.z; return *this; }

#define SPLD_VEC4_INTERNAL_OP_ARITH(vecName, vecSize, eltType)																									\
vecName##4& operator+=(const vecName##4& v) { x += v.x; y += v.y; z += v.z; w += v.w; return *this;}															\
vecName##4& operator-=(const vecName##4& v) { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }															\
vecName##4& operator*=(const vecName##4& v) { x *= v.x; y *= v.y; z *= v.z; w *= v.w; return *this; }															\
vecName##4& operator/=(const vecName##4& v) { x /= v.x; y /= v.y; z /= v.z; w /= v.w; return *this; }


// Vec accessors

#define SPLD_VEC2_ACCESSORS(vecName, vecSize, eltType)																											\
eltType& operator[](uint8_t i) { assert(i < 2); switch (i) { case 0: return x; default: return y; } }															\
const eltType& operator[](uint8_t i) const { assert(i < 2); switch (i) { case 0: return x; default: return y; } }												\
eltType x, y;																																					

#define SPLD_VEC3_ACCESSORS(vecName, vecSize, eltType)																											\
eltType& operator[](uint8_t i) { assert(i < 2); switch (i) { case 0: return x; case 1: return y; default: return z; } }											\
const eltType& operator[](uint8_t i) const { assert(i < 3); switch (i) { case 0: return x; case 1: return y; default: return z; } }								\
eltType x, y, z;																																				

#define SPLD_VEC4_ACCESSORS(vecName, vecSize, eltType)																											\
eltType& operator[](uint8_t i) { assert(i < 2); switch (i) { case 0: return x; case 1: return y; case 2: return z; default: return w; } }						\
const eltType& operator[](uint8_t i) const { assert(i < 4); switch (i) { case 0: return x; case 1: return y; case 2: return z; default: return w; } }			\
eltType x, y, z, w;


// Vec external operators

#define SPLD_VEC_EXTERNAL_OP(vecName, vecSize, eltType) SPLD_##vecName##_EXTERNAL_OP(vecName, vecSize, eltType)


#define SPLD_vec_EXTERNAL_OP(vecName, vecSize, eltType) 																										\
SPLD_VEC_EXTERNAL_OP_U_ARITH(vecName, vecSize, eltType)																											\
SPLD_VEC_EXTERNAL_OP_S_ARITH(vecName, vecSize, eltType)																											\
SPLD_VEC_EXTERNAL_OP_CMP(vecName, vecSize, eltType)

#define SPLD_dvec_EXTERNAL_OP(vecName, vecSize, eltType) 																										\
SPLD_VEC_EXTERNAL_OP_U_ARITH(vecName, vecSize, eltType)																											\
SPLD_VEC_EXTERNAL_OP_S_ARITH(vecName, vecSize, eltType)																											\
SPLD_VEC_EXTERNAL_OP_CMP(vecName, vecSize, eltType)

#define SPLD_ivec_EXTERNAL_OP(vecName, vecSize, eltType) 																										\
SPLD_VEC_EXTERNAL_OP_U_ARITH(vecName, vecSize, eltType)																											\
SPLD_VEC_EXTERNAL_OP_S_ARITH(vecName, vecSize, eltType)																											\
SPLD_VEC_EXTERNAL_OP_CMP(vecName, vecSize, eltType)

#define SPLD_uvec_EXTERNAL_OP(vecName, vecSize, eltType) 																										\
SPLD_VEC_EXTERNAL_OP_U_ARITH(vecName, vecSize, eltType)																											\
SPLD_VEC_EXTERNAL_OP_CMP(vecName, vecSize, eltType)

#define SPLD_bvec_EXTERNAL_OP(vecName, vecSize, eltType) 																										\
SPLD_VEC_EXTERNAL_OP_LOGIC(vecName, vecSize, eltType)																											\
SPLD_VEC_EXTERNAL_OP_CMP(vecName, vecSize, eltType)


#define SPLD_VEC_EXTERNAL_OP_U_ARITH(vecName, vecSize, eltType)																									\
vecName##vecSize operator+(const vecName##vecSize##& u, const vecName##vecSize##& v);																			\
vecName##vecSize operator-(const vecName##vecSize##& u, const vecName##vecSize##& v);																			\
vecName##vecSize operator*(const vecName##vecSize##& u, const vecName##vecSize##& v);																			\
vecName##vecSize operator/(const vecName##vecSize##& u, const vecName##vecSize##& v);																			\
																																								\
vecName##vecSize operator+(const vecName##vecSize##& u, eltType x);																								\
vecName##vecSize operator-(const vecName##vecSize##& u, eltType x);																								\
vecName##vecSize operator*(const vecName##vecSize##& u, eltType x);																								\
vecName##vecSize operator/(const vecName##vecSize##& u, eltType x);																								\
																																								\
vecName##vecSize operator+(eltType x, const vecName##vecSize##& u);																								\
vecName##vecSize operator-(eltType x, const vecName##vecSize##& u);																								\
vecName##vecSize operator*(eltType x, const vecName##vecSize##& u);																								\
vecName##vecSize operator/(eltType x, const vecName##vecSize##& u);


#define SPLD_VEC_EXTERNAL_OP_S_ARITH(vecName, vecSize, eltType)																									\
vecName##vecSize operator+(const vecName##vecSize##& u);																										\
vecName##vecSize operator-(const vecName##vecSize##& u);


#define SPLD_VEC_EXTERNAL_OP_LOGIC(vecName, vecSize, eltType)																									\
vecName##vecSize operator||(const vecName##vecSize##& u, const vecName##vecSize##& v);																			\
vecName##vecSize operator&&(const vecName##vecSize##& u, const vecName##vecSize##& v);																			\
																																								\
vecName##vecSize operator||(const vecName##vecSize##& u, eltType x);																							\
vecName##vecSize operator&&(const vecName##vecSize##& u, eltType x);																							\
																																								\
vecName##vecSize operator||(eltType x, const vecName##vecSize##& u);																							\
vecName##vecSize operator&&(eltType x, const vecName##vecSize##& u);

#define SPLD_VEC_EXTERNAL_OP_CMP(vecName, vecSize, eltType)																										\
bool operator==(const vecName##vecSize##& u, const vecName##vecSize##& v);																						\
bool operator!=(const vecName##vecSize##& u, const vecName##vecSize##& v);


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
eltType dot(const vecName##vecSize##& u, const vecName##vecSize##& v);																							\
eltType length(const vecName##vecSize##& v);																													\
eltType distance(const vecName##vecSize##& u, const vecName##vecSize##& v);																						\
vecName##vecSize normalize(const vecName##vecSize##& v);																										\
vecName##vecSize faceforward(const vecName##vecSize##& n, const vecName##vecSize##& i, const vecName##vecSize##& nRef);											\
vecName##vecSize reflect(const vecName##vecSize##& i, const vecName##vecSize##& n);																				\
vecName##vecSize refract(const vecName##vecSize##& i, const vecName##vecSize##& n, eltType eta);


#define SPLD_VEC2_REAL_FUNC(vecName, vecSize, eltType)

#define SPLD_VEC3_REAL_FUNC(vecName, vecSize, eltType)																											\
vecName##3 cross(const vecName##3& u, const vecName##3& v);

#define SPLD_VEC4_REAL_FUNC(vecName, vecSize, eltType)


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


	template<typename EltType, uint8_t Col, uint8_t Row, typename ColType>
	struct _Mat
	{
		_Mat() = default;
		_Mat(EltType diagValue);
		_Mat(std::initializer_list<EltType> tab);
		_Mat(const _Mat<EltType, Col, Row, ColType>& A) = default;

		_Mat<EltType, Col, Row, ColType>& operator=(const _Mat<EltType, Col, Row, ColType>& A) = default;

		ColType& operator[](uint8_t i);
		const ColType& operator[](uint8_t i) const;

		_Mat<EltType, Col, Row, ColType>& operator+=(const _Mat<EltType, Col, Row, ColType>& A);
		_Mat<EltType, Col, Row, ColType>& operator-=(const _Mat<EltType, Col, Row, ColType>& A);

		~_Mat() = default;

		EltType val[Col * Row];
	};

	template<typename EltType, uint8_t Col, uint8_t Row, typename ColType>
	_Mat<EltType, Col, Row, ColType> operator+(const _Mat<EltType, Col, Row, ColType>& A, const _Mat<EltType, Col, Row, ColType>& B);
	template<typename EltType, uint8_t Col, uint8_t Row, typename ColType>
	_Mat<EltType, Col, Row, ColType> operator-(const _Mat<EltType, Col, Row, ColType>& A, const _Mat<EltType, Col, Row, ColType>& B);

	template<typename EltType, uint8_t RowA, uint8_t ColARowB, uint8_t ColB, typename ColAType, typename ColBType>
	_Mat<EltType, ColB, RowA, ColBType> operator*(const _Mat<EltType, ColARowB, RowA, ColAType>& A, const _Mat<EltType, ColB, ColARowB, ColBType>& B);
}

#undef SPLD_VEC
#undef SPLD_VEC2_CONSTRUCTORS
#undef SPLD_VEC3_CONSTRUCTORS
#undef SPLD_VEC4_CONSTRUCTORS
#undef SPLD_vec_INTERNAL_OP
#undef SPLD_dvec_INTERNAL_OP
#undef SPLD_ivec_INTERNAL_OP
#undef SPLD_uvec_INTERNAL_OP
#undef SPLD_bvec_INTERNAL_OP
#undef SPLD_VEC2_INTERNAL_OP_ARITH
#undef SPLD_VEC3_INTERNAL_OP_ARITH
#undef SPLD_VEC4_INTERNAL_OP_ARITH
#undef SPLD_VEC2_ACCESSORS
#undef SPLD_VEC3_ACCESSORS
#undef SPLD_VEC4_ACCESSORS
#undef SPLD_VEC_EXTERNAL_OP
#undef SPLD_vec_EXTERNAL_OP
#undef SPLD_dvec_EXTERNAL_OP
#undef SPLD_ivec_EXTERNAL_OP
#undef SPLD_uvec_EXTERNAL_OP
#undef SPLD_bvec_EXTERNAL_OP
#undef SPLD_VEC_EXTERNAL_OP_U_ARITH
#undef SPLD_VEC_EXTERNAL_OP_S_ARITH
#undef SPLD_VEC_EXTERNAL_OP_LOGIC
#undef SPLD_VEC_EXTERNAL_OP_CMP
#undef SPLD_VEC_SPECIAL_FUNC
#undef SPLD_vec_SPECIAL_FUNC
#undef SPLD_dvec_SPECIAL_FUNC
#undef SPLD_ivec_SPECIAL_FUNC
#undef SPLD_uvec_SPECIAL_FUNC
#undef SPLD_bvec_SPECIAL_FUNC
#undef SPLD_VEC_REAL_FUNC
#undef SPLD_VEC2_REAL_FUNC
#undef SPLD_VEC3_REAL_FUNC
#undef SPLD_VEC4_REAL_FUNC

#include <SplayLibrary/Core/GlslT.hpp>
