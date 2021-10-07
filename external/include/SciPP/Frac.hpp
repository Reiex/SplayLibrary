#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file Frac.hpp
/// \brief Functions and classes for fractions manipulation.
/// \author Reiex
/// 
/// For a more detailed description, see class Frac and class Rational.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SciPP/types.hpp>

namespace scp
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \class Frac
	/// \brief Class for fractions manipulations.
	/// 
	/// The class Frac is not only intended to be used with integers but can represent any algebraic fraction.
	/// For example, with T=Polynomial, the class represents a rational fraction.
	///
	/// For representing rational numbers (arithmetic fraction) especially, see class Rational.
	///
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T>
	class Frac
	{
		public:
		
			Frac();								///< Default constructor. Init the fraction to T(0)/T(1).
			Frac(int64_t x);					///< Init the fraction to T(x)/T(1).
			Frac(const T& x);					///< Init the fraction to x/T(1).
			Frac(const T& p, const T& q);		///< Init the fraction p/q.
			Frac(const Frac<T>& a) = default;
			Frac(Frac<T>&& a) = default;

			Frac<T>& operator=(const Frac<T>& a) = default;
			Frac<T>& operator=(Frac<T>&& a) = default;

			Frac<T>& operator+=(const Frac<T>& a);
			Frac<T>& operator-=(const Frac<T>& a);
			Frac<T>& operator*=(const Frac<T>& a);
			Frac<T>& operator/=(const Frac<T>& a);

			const T& num() const;	///< Returns the numerator of the fraction.
			const T& denom() const;	///< Returns the denominator of the fraction.

			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \brief Compare two fractions.
			///
			/// Returns `0` if the fractions are equals, `1` if `this > x` and `-1` if `this < x`.
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			int compare(const Frac<T>& x) const;
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \brief Transform the fraction into its opposite.
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			void neg();

			~Frac() = default;

		private:

			void simplify();	///< Reduces the fraction by dividing by gcd(_p, _q) and allowing only _p to be negative.

			T _p;
			T _q;
	};


	// External operators

	template<typename T>
	Frac<T> operator+(const Frac<T>& a, const Frac<T>& b);
	template<typename T>
	Frac<T>&& operator+(Frac<T>&& a, const Frac<T>& b);
	template<typename T>
	Frac<T>&& operator+(const Frac<T>& a, Frac<T>&& b);
	template<typename T>
	Frac<T>&& operator+(Frac<T>&& a, Frac<T>&& b);

	template<typename T>
	Frac<T> operator-(const Frac<T>& a, const Frac<T>& b);
	template<typename T>
	Frac<T>&& operator-(Frac<T>&& a, const Frac<T>& b);
	template<typename T>
	Frac<T>&& operator-(const Frac<T>& a, Frac<T>&& b);
	template<typename T>
	Frac<T>&& operator-(Frac<T>&& a, Frac<T>&& b);

	template<typename T>
	Frac<T> operator*(const Frac<T>& a, const Frac<T>& b);
	template<typename T>
	Frac<T>&& operator*(Frac<T>&& a, const Frac<T>& b);
	template<typename T>
	Frac<T>&& operator*(const Frac<T>& a, Frac<T>&& b);
	template<typename T>
	Frac<T>&& operator*(Frac<T>&& a, Frac<T>&& b);

	template<typename T>
	Frac<T> operator/(const Frac<T>& a, const Frac<T>& b);
	template<typename T>
	Frac<T>&& operator/(Frac<T>&& a, const Frac<T>& b);
	template<typename T>
	Frac<T>&& operator/(Frac<T>&& a, Frac<T>&& b);

	template<typename T>
	Frac<T> operator-(const Frac<T>& a);
	template<typename T>
	Frac<T>&& operator-(Frac<T>&& a);
	
	template<typename T>
	Frac<T> operator+(const Frac<T>& a);
	template<typename T>
	Frac<T>&& operator+(Frac<T>&& a);


	// Comparators

	template<typename T>
	bool operator==(const Frac<T>& a, const Frac<T>& b);
	template<typename T>
	bool operator!=(const Frac<T>& a, const Frac<T>& b);
	template<typename T>
	bool operator>(const Frac<T>& a, const Frac<T>& b);
	template<typename T>
	bool operator<(const Frac<T>& a, const Frac<T>& b);
	template<typename T>
	bool operator>=(const Frac<T>& a, const Frac<T>& b);
	template<typename T>
	bool operator<=(const Frac<T>& a, const Frac<T>& b);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \class Rational
	/// \brief Class for rational numbers manipulation.
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class Rational: public Frac<Int>
	{
		public:

			Rational();								///< Default constructor. Init the rational to 0/1.
			Rational(int16_t x);					///< Init the rational to x/1.
			Rational(int32_t x);					///< Init the rational to x/1.
			Rational(int64_t x);					///< Init the rational to x/1.
			Rational(const Int& x);					///< Init the rational to x/1.
			Rational(const Int& p, const Int& q);	///< Init the rational to p/q.
			Rational(float x);						///< Init the rational to an approximation of x.
			Rational(double x);						///< Init the rational to an approximation of x.
			Rational(long double x);				///< Init the rational to an approximation of x.
			Rational(const Frac<Int>& x);			///< Init the rational to x.

			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \brief Returns a string with the integer part, a comma and the n first decimals of x.
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			std::string decimals(uint64_t n) const;
	};


	// External operators

	Rational operator+(const Rational& a, const Rational& b);
	Rational&& operator+(Rational&& a, const Rational& b);
	Rational&& operator+(const Rational& a, Rational&& b);
	Rational&& operator+(Rational&& a, Rational&& b);

	Rational operator-(const Rational& a, const Rational& b);
	Rational&& operator-(Rational&& a, const Rational& b);
	Rational&& operator-(const Rational& a, Rational&& b);
	Rational&& operator-(Rational&& a, Rational&& b);

	Rational operator*(const Rational& a, const Rational& b);
	Rational&& operator*(Rational&& a, const Rational& b);
	Rational&& operator*(const Rational& a, Rational&& b);
	Rational&& operator*(Rational&& a, Rational&& b);

	Rational operator/(const Rational& a, const Rational& b);
	Rational&& operator/(Rational&& a, const Rational& b);
	Rational&& operator/(Rational&& a, Rational&& b);

	Rational operator-(const Rational& a);
	Rational&& operator-(Rational&& a);

	Rational operator+(const Rational& a);
	Rational&& operator+(Rational&& a);


	// Comparators

	bool operator==(const Rational& a, const Rational& b);
	bool operator!=(const Rational& a, const Rational& b);
	bool operator>(const Rational& a, const Rational& b);
	bool operator<(const Rational& a, const Rational& b);
	bool operator>=(const Rational& a, const Rational& b);
	bool operator<=(const Rational& a, const Rational& b);


	// I/O

	std::ostream& operator<<(std::ostream& stream, const Rational& x);
	std::istream& operator>>(std::istream& stream, Rational& x);
}

#include <SciPP/FracT.hpp>
