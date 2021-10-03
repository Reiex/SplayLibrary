#pragma once

#include <SplayLibrary/Glsl.hpp>

namespace spl
{
	template<typename ElementType, uint8_t N, typename AliasType>
	ElementType& _vec<ElementType, N, AliasType>::operator[](uint8_t i)
	{
		assert(i < N);
		return static_cast<ElementType*>(this)[i];
	}

	template<typename ElementType, uint8_t N, typename AliasType>
	const ElementType& _vec<ElementType, N, AliasType>::operator[](uint8_t i) const
	{
		assert(i < N);
		return static_cast<const ElementType*>(this)[i];
	}

	template<typename ElementType, uint8_t N, typename AliasType>
	AliasType& _vec<ElementType, N, AliasType>::operator+=(const _vec<ElementType, N, AliasType>& v)
	{
		ElementType* thisElt = static_cast<ElementType*>(this);

		for (uint8_t i = 0; i < N; ++i)
		{
			thisElt[i] += v[i];
		}

		return *static_cast<AliasType*>(this);
	}

	template<typename ElementType, uint8_t N, typename AliasType>
	AliasType& _vec<ElementType, N, AliasType>::operator-=(const _vec<ElementType, N, AliasType>& v)
	{
		ElementType* thisElt = static_cast<ElementType*>(this);

		for (uint8_t i = 0; i < N; ++i)
		{
			thisElt[i] -= v[i];
		}

		return *static_cast<AliasType*>(this);
	}

	template<typename ElementType, uint8_t N, typename AliasType>
	AliasType& _vec<ElementType, N, AliasType>::operator*=(const _vec<ElementType, N, AliasType>& v)
	{
		ElementType* thisElt = static_cast<ElementType*>(this);

		for (uint8_t i = 0; i < N; ++i)
		{
			thisElt[i] *= v[i];
		}

		return *static_cast<AliasType*>(this);
	}

	template<typename ElementType, uint8_t N, typename AliasType>
	AliasType& _vec<ElementType, N, AliasType>::operator/=(const _vec<ElementType, N, AliasType>& v)
	{
		ElementType* thisElt = static_cast<ElementType*>(this);

		for (uint8_t i = 0; i < N; ++i)
		{
			thisElt[i] /= v[i];
		}

		return *static_cast<AliasType*>(this);
	}

	template<typename ElementType, uint8_t N, typename AliasType>
	AliasType& _vec<ElementType, N, AliasType>::operator+=(ElementType x)
	{
		ElementType* thisElt = static_cast<ElementType*>(this);

		for (uint8_t i = 0; i < N; ++i)
		{
			thisElt[i] += x;
		}

		return *static_cast<AliasType*>(this);
	}

	template<typename ElementType, uint8_t N, typename AliasType>
	AliasType& _vec<ElementType, N, AliasType>::operator-=(ElementType x)
	{
		ElementType* thisElt = static_cast<ElementType*>(this);

		for (uint8_t i = 0; i < N; ++i)
		{
			thisElt[i] -= x;
		}

		return *static_cast<AliasType*>(this);
	}

	template<typename ElementType, uint8_t N, typename AliasType>
	AliasType& _vec<ElementType, N, AliasType>::operator*=(ElementType x)
	{
		ElementType* thisElt = static_cast<ElementType*>(this);

		for (uint8_t i = 0; i < N; ++i)
		{
			thisElt[i] *= x;
		}

		return *static_cast<AliasType*>(this);
	}

	template<typename ElementType, uint8_t N, typename AliasType>
	AliasType& _vec<ElementType, N, AliasType>::operator/=(ElementType x)
	{
		ElementType* thisElt = static_cast<ElementType*>(this);

		for (uint8_t i = 0; i < N; ++i)
		{
			thisElt[i] /= x;
		}

		return *static_cast<AliasType*>(this);
	}


	template<typename ElementType, typename AliasType>
	AliasType cross(const _vec<ElementType, 3, AliasType>& u, const _vec<ElementType, 3, AliasType>& v)
	{
		return AliasType({ u[1] * v[2] - u[2] * v[1],
						   u[2] * v[0] - u[2] * v[2],
						   u[0] * v[1] - u[1] * v[0] });
	}

	template<typename ElementType, uint8_t N, typename AliasType>
	ElementType dot(const _vec<ElementType, N, AliasType>& u, const _vec<ElementType, N, AliasType>& v)
	{
		ElementType r = 0;
		for (uint8_t i = 0; i < N; ++i)
		{
			r += u[i] * v[i];
		}

		return r;
	}

	template<typename ElementType, uint8_t N, typename AliasType>
	ElementType length(const _vec<ElementType, N, AliasType>& v)
	{
		return std::sqrt(dot(v, v));
	}

	template<typename ElementType, uint8_t N, typename AliasType>
	ElementType distance(const _vec<ElementType, N, AliasType>& u, const _vec<ElementType, N, AliasType>& v)
	{
		return length(v - u);
	}

	template<typename ElementType, uint8_t N, typename AliasType>
	AliasType normalize(const _vec<ElementType, N, AliasType>& v)
	{
		return v / length(v);
	}

	template<typename ElementType, uint8_t N, typename AliasType>
	AliasType faceforward(const _vec<ElementType, N, AliasType>& n, const _vec<ElementType, N, AliasType>& i, const _vec<ElementType, N, AliasType>& nRef)
	{
		if (dot(nRef, i) < 0)
		{
			return n;
		}
		else
		{
			return -n;
		}
	}

	template<typename ElementType, uint8_t N, typename AliasType>
	AliasType reflect(const _vec<ElementType, N, AliasType>& i, const _vec<ElementType, N, AliasType>& n)
	{
		return i - 2 * dot(n, i) * n;
	}

	template<typename ElementType, uint8_t N, typename AliasType>
	AliasType refract(const _vec<ElementType, N, AliasType>& i, const _vec<ElementType, N, AliasType>& n, ElementType eta)
	{
		ElementType d = dot(n, i);
		ElementType k = 1 - eta * eta * (1 - d * d);

		if (k < 0)
		{
			return 0;
		}
		else
		{
			return eta * i - (eta * dot(n, i) + std::sqrt(k)) * n;
		}
	}


	template<typename ElementType, uint8_t N, typename AliasType>
	AliasType operator+(const _vec<ElementType, N, AliasType>& u, const _vec<ElementType, N, AliasType>& v)
	{
		_vec<ElementType, N, AliasType> w(u);
		return w += v;
	}

	template<typename ElementType, uint8_t N, typename AliasType>
	AliasType operator-(const _vec<ElementType, N, AliasType>& u, const _vec<ElementType, N, AliasType>& v)
	{
		_vec<ElementType, N, AliasType> w(u);
		return w -= v;
	}

	template<typename ElementType, uint8_t N, typename AliasType>
	AliasType operator*(const _vec<ElementType, N, AliasType>& u, const _vec<ElementType, N, AliasType>& v)
	{
		_vec<ElementType, N, AliasType> w(u);
		return w *= v;
	}

	template<typename ElementType, uint8_t N, typename AliasType>
	AliasType operator/(const _vec<ElementType, N, AliasType>& u, const _vec<ElementType, N, AliasType>& v)
	{
		_vec<ElementType, N, AliasType> w(u);
		return w /= v;
	}


	template<typename ElementType, uint8_t N, typename AliasType>
	AliasType operator+(const _vec<ElementType, N, AliasType>& u, ElementType x)
	{
		_vec<ElementType, N, AliasType> v(u);
		return v += x;
	}

	template<typename ElementType, uint8_t N, typename AliasType>
	AliasType operator-(const _vec<ElementType, N, AliasType>& u, ElementType x)
	{
		_vec<ElementType, N, AliasType> v(u);
		return v -= x;
	}

	template<typename ElementType, uint8_t N, typename AliasType>
	AliasType operator*(const _vec<ElementType, N, AliasType>& u, ElementType x)
	{
		_vec<ElementType, N, AliasType> v(u);
		return v *= x;
	}

	template<typename ElementType, uint8_t N, typename AliasType>
	AliasType operator/(const _vec<ElementType, N, AliasType>& u, ElementType x)
	{
		_vec<ElementType, N, AliasType> v(u);
		return v /= x;
	}

	template<typename ElementType, uint8_t N, typename AliasType>
	AliasType operator+(ElementType x, const _vec<ElementType, N, AliasType>& u)
	{
		_vec<ElementType, N, AliasType> v(u);
		return v += x;
	}

	template<typename ElementType, uint8_t N, typename AliasType>
	AliasType operator-(ElementType x, const _vec<ElementType, N, AliasType>& u)
	{
		_vec<ElementType, N, AliasType> v(u);
		return v -= x;
	}

	template<typename ElementType, uint8_t N, typename AliasType>
	AliasType operator*(ElementType x, const _vec<ElementType, N, AliasType>& u)
	{
		_vec<ElementType, N, AliasType> v(u);
		return v *= x;
	}

	template<typename ElementType, uint8_t N, typename AliasType>
	AliasType operator/(ElementType x, const _vec<ElementType, N, AliasType>& u)
	{
		_vec<ElementType, N, AliasType> v(u);
		return v /= x;
	}


	template<typename ElementType>
	_vec2<ElementType>::_vec2(ElementType value) :
		x(value),
		y(value)
	{
	}

	template<typename ElementType>
	_vec2<ElementType>::_vec2(ElementType xValue, ElementType yValue) :
		x(xValue),
		y(yValue)
	{
	}

	template<typename ElementType>
	_vec2<ElementType>::_vec2(std::initializer_list<ElementType> tab) :
		x(tab.begin()[0]),
		y(tab.begin()[1])
	{
		assert(tab.size() == 2);
	}

	template<typename ElementType>
	_vec2<ElementType>::_vec2(const _vec<ElementType, 2, _vec2<ElementType>>&v) :
		x(v[0]),
		y(v[1])
	{
	}


	template<typename ElementType>
	_vec3<ElementType>::_vec3(ElementType value) :
		x(value),
		y(value),
		z(value)
	{
	}

	template<typename ElementType>
	_vec3<ElementType>::_vec3(ElementType xValue, ElementType yValue, ElementType zValue) :
		x(xValue),
		y(yValue),
		z(zValue)
	{
	}

	template<typename ElementType>
	_vec3<ElementType>::_vec3(std::initializer_list<ElementType> tab) :
		x(tab.begin()[0]),
		y(tab.begin()[1]),
		z(tab.begin()[2])
	{
		assert(tab.size() == 3);
	}

	template<typename ElementType>
	_vec3<ElementType>::_vec3(const _vec<ElementType, 3, _vec3<ElementType>>& v) :
		x(v[0]),
		y(v[1]),
		z(v[2])
	{
	}

	template<typename ElementType>
	_vec3<ElementType>::_vec3(const _vec2<ElementType>& v, ElementType zValue) :
		x(v.x),
		y(v.y),
		z(zValue)
	{
	}

	template<typename ElementType>
	_vec3<ElementType>::_vec3(ElementType xValue, const _vec2<ElementType>& v) :
		x(xValue),
		y(v.x),
		z(v.y)
	{
	}


	template<typename ElementType>
	_vec4<ElementType>::_vec4(ElementType value) :
		x(value),
		y(value),
		z(value),
		w(value)
	{
	}

	template<typename ElementType>
	_vec4<ElementType>::_vec4(ElementType xValue, ElementType yValue, ElementType zValue, ElementType wValue) :
		x(xValue),
		y(yValue),
		z(zValue),
		w(wValue)
	{
	}

	template<typename ElementType>
	_vec4<ElementType>::_vec4(std::initializer_list<ElementType> tab) :
		x(tab.begin()[0]),
		y(tab.begin()[1]),
		z(tab.begin()[2]),
		w(tab.begin()[3])
	{
		assert(tab.size() == 4);
	}

	template<typename ElementType>
	_vec4<ElementType>::_vec4(const _vec<ElementType, 4, _vec4<ElementType>>& v) :
		x(v[0]),
		y(v[1]),
		z(v[2]),
		w(v[3])
	{
	}

	template<typename ElementType>
	_vec4<ElementType>::_vec4(const _vec2<ElementType>& v, ElementType zValue, ElementType wValue) :
		x(v.x),
		y(v.y),
		z(zValue),
		w(wValue)
	{
	}

	template<typename ElementType>
	_vec4<ElementType>::_vec4(ElementType xValue, const _vec2<ElementType>& v, ElementType wValue) :
		x(xValue),
		y(v.x),
		z(v.y),
		w(wValue)
	{
	}

	template<typename ElementType>
	_vec4<ElementType>::_vec4(ElementType xValue, ElementType yValue, const _vec2<ElementType>& v) :
		x(xValue),
		y(yValue),
		z(v.x),
		w(v.y)
	{
	}

	template<typename ElementType>
	_vec4<ElementType>::_vec4(const _vec2<ElementType>& u, const _vec2<ElementType>& v) :
		x(u.x),
		y(u.y),
		z(v.x),
		w(v.y)
	{
	}

	template<typename ElementType>
	_vec4<ElementType>::_vec4(const _vec3<ElementType>& v, ElementType wValue) :
		x(v.x),
		y(v.y),
		z(v.z),
		w(wValue)
	{
	}

	template<typename ElementType>
	_vec4<ElementType>::_vec4(ElementType xValue, const _vec3<ElementType>& v) :
		x(xValue),
		y(v.x),
		z(v.y),
		w(v.z)
	{
	}

	
	template<typename ElementType, uint8_t M, uint8_t N, typename ColumnType, typename RowType>
	_mat<ElementType, M, N, ColumnType, RowType>::_mat(ElementType diagValue)
	{
		constexpr uint8_t size = M * N;
		constexpr uint8_t offset = M + 1;

		std::memset(data, 0, sizeof(ElementType) * size);

		for (uint8_t i = 0; i < size; i += offset)
		{
			data[i] = diagValue;
		}
	}

	template<typename ElementType, uint8_t M, uint8_t N, typename ColumnType, typename RowType>
	_mat<ElementType, M, N, ColumnType, RowType>::_mat(std::initializer_list<ElementType> diag)
	{
		constexpr uint8_t size = M * N;
		constexpr uint8_t offset = M + 1;
		constexpr uint8_t diagSize = M > N ? N : M;

		assert(diag.size() == diagSize);

		std::memset(data, 0, sizeof(ElementType) * size);

		for (uint8_t i = 0, k = 0; k < diagSize; i += offset, ++k)
		{
			data[i] = diag.begin()[k];
		}
	}

	template<typename ElementType, uint8_t M, uint8_t N, typename ColumnType, typename RowType>
	_mat<ElementType, M, N, ColumnType, RowType>::_mat(std::initializer_list<ColumnType> columns)
	{
		assert(columns.size() == N);

		uint8_t k = 0;
		for (uint8_t j = 0; j < N; ++j)
		{
			for (uint8_t i = 0; i < M; ++i, ++k)
			{
				data[k] = columns.begin()[j][i];
			}
		}
	}

	template<typename ElementType, uint8_t M, uint8_t N, typename ColumnType, typename RowType>
	ColumnType& _mat<ElementType, M, N, ColumnType, RowType>::operator[](uint8_t i)
	{
		assert(i < N);
		return *static_cast<ColumnType*>(data + i * M);
	}

	template<typename ElementType, uint8_t M, uint8_t N, typename ColumnType, typename RowType>
	const ColumnType& _mat<ElementType, M, N, ColumnType, RowType>::operator[](uint8_t i) const
	{
		assert(i < N);
		return *static_cast<ColumnType*>(data + i * M);
	}

	template<typename ElementType, uint8_t M, uint8_t N, typename ColumnType, typename RowType>
	_mat<ElementType, M, N, ColumnType, RowType>& _mat<ElementType, M, N, ColumnType, RowType>::operator+=(const _mat<ElementType, M, N, ColumnType, RowType>& M)
	{
		constexpr uint8_t size = M * N;
		for (uint8_t k = 0; k < size; ++k)
		{
			data[k] += M.data[k];
		}

		return *this;
	}

	template<typename ElementType, uint8_t M, uint8_t N, typename ColumnType, typename RowType>
	_mat<ElementType, M, N, ColumnType, RowType>& _mat<ElementType, M, N, ColumnType, RowType>::operator-=(const _mat<ElementType, M, N, ColumnType, RowType>& M)
	{
		constexpr uint8_t size = M * N;
		for (uint8_t k = 0; k < size; ++k)
		{
			data[k] -= M.data[k];
		}

		return *this;
	}

	template<typename ElementType, uint8_t M, uint8_t N, typename ColumnType, typename RowType>
	_mat<ElementType, M, N, ColumnType, RowType>& _mat<ElementType, M, N, ColumnType, RowType>::operator/=(const _mat<ElementType, M, N, ColumnType, RowType>& M)
	{
		constexpr uint8_t size = M * N;
		for (uint8_t k = 0; k < size; ++k)
		{
			data[k] /= M.data[k];
		}

		return *this;
	}

	template<typename ElementType, uint8_t M, uint8_t N, typename ColumnType, typename RowType>
	_mat<ElementType, M, N, ColumnType, RowType>& _mat<ElementType, M, N, ColumnType, RowType>::operator+=(ElementType x)
	{
		constexpr uint8_t size = M * N;
		for (uint8_t k = 0; k < size; ++k)
		{
			data[k] += x;
		}

		return *this;
	}

	template<typename ElementType, uint8_t M, uint8_t N, typename ColumnType, typename RowType>
	_mat<ElementType, M, N, ColumnType, RowType>& _mat<ElementType, M, N, ColumnType, RowType>::operator-=(ElementType x)
	{
		constexpr uint8_t size = M * N;
		for (uint8_t k = 0; k < size; ++k)
		{
			data[k] -= x;
		}

		return *this;
	}

	template<typename ElementType, uint8_t M, uint8_t N, typename ColumnType, typename RowType>
	_mat<ElementType, M, N, ColumnType, RowType>& _mat<ElementType, M, N, ColumnType, RowType>::operator/=(ElementType x)
	{
		constexpr uint8_t size = M * N;
		for (uint8_t k = 0; k < size; ++k)
		{
			data[k] /= x;
		}

		return *this;
	}

	template<typename ElementType, uint8_t M, uint8_t N, typename ColumnType, typename RowType>
	_mat<ElementType, M, N, ColumnType, RowType>& _mat<ElementType, M, N, ColumnType, RowType>::operator*=(ElementType x)
	{
		constexpr uint8_t size = M * N;
		for (uint8_t k = 0; k < size; ++k)
		{
			data[k] *= x;
		}

		return *this;
	}


	template<typename ElementType, uint8_t M, uint8_t N, typename ColumnType, typename RowType>
	_mat<ElementType, N, M, RowType, ColumnType> transpose(const _mat<ElementType, M, N, ColumnType, RowType>& A)
	{
		_mat<ElementType, N, M, RowType, ColumnType> R;

		for (uint8_t i = 0; i < M; ++i)
		{
			for (uint8_t j = 0; j < N; ++j)
			{
				R[i][j] = A[j][i];
			}
		}

		return R;
	}

	template<typename ElementType, uint8_t M, uint8_t N, typename ColumnType, typename RowType>
	_mat<ElementType, M, N, ColumnType, RowType> operator+(const _mat<ElementType, M, N, ColumnType, RowType>& A, const _mat<ElementType, M, N, ColumnType, RowType>& B)
	{
		_mat<ElementType, M, N, ColumnType, RowType> C(A);
		return C += B;
	}

	template<typename ElementType, uint8_t M, uint8_t N, typename ColumnType, typename RowType>
	_mat<ElementType, M, N, ColumnType, RowType> operator-(const _mat<ElementType, M, N, ColumnType, RowType>& A, const _mat<ElementType, M, N, ColumnType, RowType>& B)
	{
		_mat<ElementType, M, N, ColumnType, RowType> C(A);
		return C -= B;
	}

	template<typename ElementType, uint8_t M, uint8_t N, uint8_t P, typename ColumnType, typename CommonType, typename RowType>
	_mat<ElementType, M, P, ColumnType, RowType> operator*(const _mat<ElementType, M, N, ColumnType, CommonType>& A, const _mat<ElementType, N, P, CommonType, RowType>& B)
	{
		_mat<ElementType, M, P, ColumnType, RowType> R;

		for (uint8_t i = 0; i < M; ++i)
		{
			for (uint8_t j = 0; j < P; ++j)
			{
				R[j][i] = 0;
				for (uint8_t k = 0; k < N; ++k)
				{
					R[j][i] += A[k][i] * B[j][k];
				}
			}
		}

		return R;
	}

	template<typename ElementType, uint8_t M, uint8_t N, typename ColumnType, typename RowType>
	_mat<ElementType, M, N, ColumnType, RowType> operator/(const _mat<ElementType, M, N, ColumnType, RowType>& A, const _mat<ElementType, M, N, ColumnType, RowType>& B)
	{
		_mat<ElementType, M, N, ColumnType, RowType> C(A);
		return C /= B;
	}


	template<typename ElementType, uint8_t M, uint8_t N, typename ColumnType, typename RowType>
	_mat<ElementType, M, N, ColumnType, RowType> operator+(const _mat<ElementType, M, N, ColumnType, RowType>& A, ElementType x)
	{
		_mat<ElementType, M, N, ColumnType, RowType> B(A);
		return B += x;
	}

	template<typename ElementType, uint8_t M, uint8_t N, typename ColumnType, typename RowType>
	_mat<ElementType, M, N, ColumnType, RowType> operator-(const _mat<ElementType, M, N, ColumnType, RowType>& A, ElementType x)
	{
		_mat<ElementType, M, N, ColumnType, RowType> B(A);
		return B -= x;
	}

	template<typename ElementType, uint8_t M, uint8_t N, typename ColumnType, typename RowType>
	_mat<ElementType, M, N, ColumnType, RowType> operator*(const _mat<ElementType, M, N, ColumnType, RowType>& A, ElementType x)
	{
		_mat<ElementType, M, N, ColumnType, RowType> B(A);
		return B *= x;
	}

	template<typename ElementType, uint8_t M, uint8_t N, typename ColumnType, typename RowType>
	_mat<ElementType, M, N, ColumnType, RowType> operator/(const _mat<ElementType, M, N, ColumnType, RowType>& A, ElementType x)
	{
		_mat<ElementType, M, N, ColumnType, RowType> B(A);
		return B /= x;
	}

	template<typename ElementType, uint8_t M, uint8_t N, typename ColumnType, typename RowType>
	_mat<ElementType, M, N, ColumnType, RowType> operator+(ElementType x, const _mat<ElementType, M, N, ColumnType, RowType>& A)
	{
		_mat<ElementType, M, N, ColumnType, RowType> B(A);
		return B += x;
	}

	template<typename ElementType, uint8_t M, uint8_t N, typename ColumnType, typename RowType>
	_mat<ElementType, M, N, ColumnType, RowType> operator-(ElementType x, const _mat<ElementType, M, N, ColumnType, RowType>& A)
	{
		_mat<ElementType, M, N, ColumnType, RowType> B(A);
		return B -= x;
	}

	template<typename ElementType, uint8_t M, uint8_t N, typename ColumnType, typename RowType>
	_mat<ElementType, M, N, ColumnType, RowType> operator*(ElementType x, const _mat<ElementType, M, N, ColumnType, RowType>& A)
	{
		_mat<ElementType, M, N, ColumnType, RowType> B(A);
		return B *= x;
	}

	template<typename ElementType, uint8_t M, uint8_t N, typename ColumnType, typename RowType>
	_mat<ElementType, M, N, ColumnType, RowType> operator/(ElementType x, const _mat<ElementType, M, N, ColumnType, RowType>& A)
	{
		_mat<ElementType, M, N, ColumnType, RowType> B(A);
		return B /= x;
	}


	template<typename ElementType, uint8_t M, uint8_t N, typename ColumnType, typename RowType>
	ColumnType operator*(const _mat<ElementType, M, N, ColumnType, RowType>& A, const RowType& v)
	{
		ColumnType r = 0;

		for (uint8_t i = 0; i < M; ++i)
		{
			for (uint8_t j = 0; j < N; ++j)
			{
				r[i] += A[j][i] * v[i];
			}
		}

		return r;
	}

	template<typename ElementType, uint8_t M, uint8_t N, typename ColumnType, typename RowType>
	RowType operator*(const ColumnType& v, const _mat<ElementType, M, N, ColumnType, RowType>& A)
	{
		RowType r = 0;
		
		for (uint8_t j = 0; j < N; ++j)
		{
			r += dot(v, A[j]);
		}

		return r;
	}
}