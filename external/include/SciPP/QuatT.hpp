#pragma once

#include <SciPP/Quat.hpp>

namespace scp
{
	// Constructors

	template<typename T>
	Quat<T>::Quat() :
		a(0),
		b(0),
		c(0),
		d(0)
	{
	}

	template<typename T>
	Quat<T>::Quat(int64_t x) :
		a(x),
		b(0),
		c(0),
		d(0)
	{
	}
	
	template<typename T>
	Quat<T>::Quat(const T& x) :
		a(x),
		b(0),
		c(0),
		d(0)
	{
	}
	
	template<typename T>
	Quat<T>::Quat(const T& aValue, const T& bValue, const T& cValue, const T& dValue) :
		a(aValue),
		b(bValue),
		c(cValue),
		d(dValue)
	{
	}
	
	template<typename T>
	Quat<T>::Quat(const std::array<T, 4> values) :
		a(values[0]),
		b(values[1]),
		c(values[2]),
		d(values[3])
	{
	}


	// Internal operators

	template<typename T>
	Quat<T>& Quat<T>::operator+=(const Quat<T>& q)
	{
		a += q.a;
		b += q.b;
		c += q.c;
		d += q.d;

		return *this;
	}
	
	template<typename T>
	Quat<T>& Quat<T>::operator-=(const Quat<T>& q)
	{
		a -= q.a;
		b -= q.b;
		c -= q.c;
		d -= q.d;

		return *this;
	}
	
	template<typename T>
	Quat<T>& Quat<T>::operator*=(const Quat<T>& q)
	{
		T newA = a*q.a - b*q.b - c*q.c - d*q.d;
		T newB = a*q.b + b*q.a + c*q.d - d*q.c;
		T newC = a*q.c - b*q.d + c*q.a + d*q.b;
		T newD = a*q.d + b*q.c - c*q.b + d*q.a;

		a = newA;
		b = newB;
		c = newC;
		d = newD;

		return *this;
	}
	
	template<typename T>
	Quat<T>& Quat<T>::operator/=(const T& x)
	{
		a /= x;
		b /= x;
		c /= x;
		d /= x;

		return *this;
	}


	// Specific functions

	template<typename T>
	Quat<T> Quat<T>::inverse() const
	{
		assert(a != 0 || b != 0 || c != 0 || d != 0);

		T l(normSq());

		return { a / l, -b / l, -c / l, -d / l };
	}

	template<typename T>
	T Quat<T>::normSq() const
	{
		return a * a + b * b + c * c + d * d;
	}

	template<typename T>
	T Quat<T>::norm() const
	{
		return sqrt(normSq());
	}



	// External operators

	template<typename T>
	Quat<T> operator+(const Quat<T>& p, const Quat<T>& q)
	{
		Quat<T> r(p);
		r += q;

		return r;
	}

	template<typename T>
	Quat<T>&& operator+(Quat<T>&& p, const Quat<T>& q)
	{
		p += q;
		return std::move(p);
	}

	template<typename T>
	Quat<T>&& operator+(const Quat<T>& p, Quat<T>&& q)
	{
		q += p;
		return std::move(q);
	}

	template<typename T>
	Quat<T>&& operator+(Quat<T>&& p, Quat<T>&& q)
	{
		p += q;
		return std::move(p);
	}


	template<typename T>
	Quat<T> operator-(const Quat<T>& p, const Quat<T>& q)
	{
		Quat<T> r(p);
		r -= q;

		return r;
	}

	template<typename T>
	Quat<T>&& operator-(Quat<T>&& p, const Quat<T>& q)
	{
		p -= q;
		return std::move(p);
	}

	template<typename T>
	Quat<T>&& operator-(const Quat<T>& p, Quat<T>&& q)
	{
		q -= p;
		return -std::move(q);
	}

	template<typename T>
	Quat<T>&& operator-(Quat<T>&& p, Quat<T>&& q)
	{
		p -= q;
		return std::move(p);
	}


	template<typename T>
	Quat<T> operator*(const Quat<T>& p, const Quat<T>& q)
	{
		Quat<T> r(p);
		r *= q;

		return r;
	}

	template<typename T>
	Quat<T>&& operator*(Quat<T>&& p, const Quat<T>& q)
	{
		p *= q;
		return std::move(p);
	}

	template<typename T>
	Quat<T>&& operator*(Quat<T>&& p, Quat<T>&& q)
	{
		p *= q;
		return std::move(p);
	}


	template<typename T>
	Quat<T> operator/(const Quat<T>& q, const T& x)
	{
		Quat<T> r(q);
		r /= x;

		return r;
	}

	template<typename T>
	Quat<T>&& operator/(Quat<T>&& q, const T& x)
	{
		q /= x;
		return std::move(q);
	}


	template<typename T>
	Quat<T> operator-(const Quat<T>& q)
	{
		return Quat<T>(-q.a, -q.b, -q.c, -q.d);
	}

	template<typename T>
	Quat<T>&& operator-(Quat<T>&& q)
	{
		q.a = -q.a;
		q.b = -q.b;
		q.c = -q.c;
		q.d = -q.d;

		return std::move(q);
	}


	template<typename T>
	Quat<T> operator+(const Quat<T>& q)
	{
		return q;
	}

	template<typename T>
	Quat<T>&& operator+(Quat<T>&& q)
	{
		return std::move(q);
	}


	// Comparators

	template<typename T>
	bool operator==(const Quat<T>& p, const Quat<T>& q)
	{
		return p.a == q.a && p.b == q.b && p.c == q.c && p.d == q.d;
	}

	template<typename T>
	bool operator!=(const Quat<T>& p, const Quat<T>& q)
	{
		return !(p == q);
	}
}
