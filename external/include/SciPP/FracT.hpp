#pragma once

#include <SciPP/Frac.hpp>

namespace scp
{
	// Constructors

	template<typename T>
	Frac<T>::Frac() :
		_p(0),
		_q(1)
	{
	}

	template<typename T>
	Frac<T>::Frac(int64_t x) :
		_p(x),
		_q(1)
	{
	}

	template<typename T>
	Frac<T>::Frac(const T& x) :
		_p(x),
		_q(1)
	{
	}

	template<typename T>
	Frac<T>::Frac(const T& p, const T& q) :
		_p(p),
		_q(q)
	{
		if (q == 0)
		{
			throw std::runtime_error("Cannot init a Frac with the denominator equal to 0.");
		}

		simplify();
	}


	// Internal operators

	template<typename T>
	Frac<T>& Frac<T>::operator+=(const Frac<T>& a)
	{
		T p = _p * a._q + a._p * _q;
		T q = _q * a._q;

		_p = p;
		_q = q;

		simplify();

		return *this;
	}

	template<typename T>
	Frac<T>& Frac<T>::operator-=(const Frac<T>& a)
	{
		T p = _p * a._q - a._p * _q;
		T q = _q * a._q;

		_p = p;
		_q = q;

		simplify();

		return *this;
	}

	template<typename T>
	Frac<T>& Frac<T>::operator*=(const Frac<T>& a)
	{
		_p *= a._p;
		_q *= a._q;

		simplify();

		return *this;
	}

	template<typename T>
	Frac<T>& Frac<T>::operator/=(const Frac<T>& a)
	{
		T p = _p * a._q;
		T q = _q * a._p;

		_p = p;
		_q = q;

		simplify();

		return *this;
	}


	// Specific methods

	template<typename T>
	const T& Frac<T>::num() const
	{
		return _p;
	}

	template<typename T>
	const T& Frac<T>::denom() const
	{
		return _q;
	}

	template<typename T>
	int Frac<T>::compare(const Frac<T>& x) const
	{
		T a = _p * x._q;
		T b = _q * x._p;

		if (a > b)
		{
			return 1;
		}
		else if (a < b)
		{
			return -1;
		}
		else
		{
			return 0;
		}
	}

	template<typename T>
	void Frac<T>::neg()
	{
		_p = -_p;
	}


	// Private members

	template<typename T>
	void Frac<T>::simplify()
	{
		if (_q < 0)
		{
			_q = -_q;
			_p = -_p;
		}

		if (_p == 0)
		{
			_q = 1;
			return;
		}

		T x(gcd(_p, _q));
		_p /= x;
		_q /= x;
	}


	// External operators

	template<typename T>
	Frac<T> operator+(const Frac<T>& a, const Frac<T>& b)
	{
		Frac<T> c(a);
		c += b;

		return c;
	}

	template<typename T>
	Frac<T>&& operator+(Frac<T>&& a, const Frac<T>& b)
	{
		a += b;
		return std::move(a);
	}

	template<typename T>
	Frac<T>&& operator+(const Frac<T>& a, Frac<T>&& b)
	{
		b += a;
		return std::move(b);
	}
	
	template<typename T>
	Frac<T>&& operator+(Frac<T>&& a, Frac<T>&& b)
	{
		a += b;
		return std::move(a);
	}
	

	template<typename T>
	Frac<T> operator-(const Frac<T>& a, const Frac<T>& b)
	{
		Frac<T> c(a);
		c -= b;

		return c;
	}

	template<typename T>
	Frac<T>&& operator-(Frac<T>&& a, const Frac<T>& b)
	{
		a -= b;
		return std::move(a);
	}

	template<typename T>
	Frac<T>&& operator-(const Frac<T>& a, Frac<T>&& b)
	{
		b -= a;
		return -std::move(b);
	}
	
	template<typename T>
	Frac<T>&& operator-(Frac<T>&& a, Frac<T>&& b)
	{
		a -= b;
		return std::move(a);
	}
	

	template<typename T>
	Frac<T> operator*(const Frac<T>& a, const Frac<T>& b)
	{
		Frac<T> c(a);
		c *= b;

		return c;
	}

	template<typename T>
	Frac<T>&& operator*(Frac<T>&& a, const Frac<T>& b)
	{
		a *= b;
		return std::move(a);
	}

	template<typename T>
	Frac<T>&& operator*(const Frac<T>& a, Frac<T>&& b)
	{
		b *= a;
		return std::move(b);
	}
	
	template<typename T>
	Frac<T>&& operator*(Frac<T>&& a, Frac<T>&& b)
	{
		a *= b;
		return std::move(a);
	}
	

	template<typename T>
	Frac<T> operator/(const Frac<T>& a, const Frac<T>& b)
	{
		Frac<T> c(a);
		c /= b;

		return c;
	}

	template<typename T>
	Frac<T>&& operator/(Frac<T>&& a, const Frac<T>& b)
	{
		a /= b;
		return std::move(a);
	}
	
	template<typename T>
	Frac<T>&& operator/(Frac<T>&& a, Frac<T>&& b)
	{
		a /= b;
		return std::move(a);
	}
	

	template<typename T>
	Frac<T> operator-(const Frac<T>& a)
	{
		return Frac<T>(-a.num(), a.denom());
	}

	template<typename T>
	Frac<T>&& operator-(Frac<T>&& a)
	{
		a.neg();
		return std::move(a);
	}


	template<typename T>
	Frac<T> operator+(const Frac<T>& a)
	{
		return a;
	}

	template<typename T>
	Frac<T>&& operator+(Frac<T>&& a)
	{
		return std::move(a);
	}


	// Comparators

	template<typename T>
	bool operator==(const Frac<T>& a, const Frac<T>& b)
	{
		return a.compare(b) == 0;
	}

	template<typename T>
	bool operator!=(const Frac<T>& a, const Frac<T>& b)
	{
		return a.compare(b) != 0;
	}

	template<typename T>
	bool operator>(const Frac<T>& a, const Frac<T>& b)
	{
		return a.compare(b) > 0;
	}

	template<typename T>
	bool operator<(const Frac<T>& a, const Frac<T>& b)
	{
		return a.compare(b) < 0;
	}

	template<typename T>
	bool operator>=(const Frac<T>& a, const Frac<T>& b)
	{
		return a.compare(b) >= 0;
	}

	template<typename T>
	bool operator<=(const Frac<T>& a, const Frac<T>& b)
	{
		return a.compare(b) <= 0;
	}
}
