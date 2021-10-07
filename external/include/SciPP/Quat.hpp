#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file Quat.hpp
/// \brief Functions and classes for quaternions manipulations.
/// \author Reiex
/// 
/// For a more detailed description, see class Quat.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SciPP/types.hpp>

namespace scp
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \class Quat
	/// \brief Class for quaternions manipulations
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T>
	struct Quat
	{
		Quat();																		///< Default constructor. Init the quaternion to 0.
		Quat(int64_t x);															///< Init the quaternion to the real `T(x)`.
		Quat(const T& x);															///< Init the quaternion to the real `x`.
		Quat(const T& aValue, const T& bValue, const T& cValue, const T& dValue);	///< Init the quaternion to `a + bi + cj + dk`.
		Quat(const std::array<T, 4> values);										///< Init the quaternion with the 4 values `{a, b, c, d}` to `a + bi + cj + dk`.
		Quat(const Quat<T>& q) = default;
		Quat(Quat<T>&& q) = default;

		Quat<T>& operator=(const Quat<T>& q) = default;
		Quat<T>& operator=(Quat<T>&& q) = default;

		Quat<T>& operator+=(const Quat<T>& q);
		Quat<T>& operator-=(const Quat<T>& q);
		Quat<T>& operator*=(const Quat<T>& q);
		Quat<T>& operator/=(const T& x);

		Quat<T> inverse() const;	///< Returns the inverse of a quaternion.
		T normSq() const;			///< Returns the square of the euclidian norm of a quaternion.
		T norm() const;				///< Returns the euclidian norm of a quaternion.

		~Quat() = default;

		T a;
		T b;
		T c;
		T d;
	};

	// External operators

	template<typename T>
	Quat<T> operator+(const Quat<T>& p, const Quat<T>& q);
	template<typename T>
	Quat<T>&& operator+(Quat<T>&& p, const Quat<T>& q);
	template<typename T>
	Quat<T>&& operator+(const Quat<T>& p, Quat<T>&& q);
	template<typename T>
	Quat<T>&& operator+(Quat<T>&& p, Quat<T>&& q);

	template<typename T>
	Quat<T> operator-(const Quat<T>& p, const Quat<T>& q);
	template<typename T>
	Quat<T>&& operator-(Quat<T>&& p, const Quat<T>& q);
	template<typename T>
	Quat<T>&& operator-(const Quat<T>& p, Quat<T>&& q);
	template<typename T>
	Quat<T>&& operator-(Quat<T>&& p, Quat<T>&& q);

	template<typename T>
	Quat<T> operator*(const Quat<T>& p, const Quat<T>& q);
	template<typename T>
	Quat<T>&& operator*(Quat<T>&& p, const Quat<T>& q);
	template<typename T>
	Quat<T>&& operator*(Quat<T>&& p, Quat<T>&& q);

	template<typename T>
	Quat<T> operator/(const Quat<T>& q, const T& x);
	template<typename T>
	Quat<T>&& operator/(Quat<T>&& q, const T& x);

	template<typename T>
	Quat<T> operator-(const Quat<T>& q);
	template<typename T>
	Quat<T>&& operator-(Quat<T>&& q);

	template<typename T>
	Quat<T> operator+(const Quat<T>& q);
	template<typename T>
	Quat<T>&& operator+(Quat<T>&& q);

	// Comparators

	template<typename T>
	bool operator==(const Quat<T>& p, const Quat<T>& q);
	template<typename T>
	bool operator!=(const Quat<T>& p, const Quat<T>& q);
}

#include <SciPP/QuatT.hpp>
