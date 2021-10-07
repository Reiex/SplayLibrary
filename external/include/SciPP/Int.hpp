#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file Int.hpp
/// \brief Functions and classes for big integers manipulations.
/// \author Reiex
/// 
/// For a more detailed description, see class Int.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SciPP/types.hpp>

namespace scp
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \class Int
	/// \brief Class for big integers manipulations
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class Int
	{
		public:

			Int();							///< Default constructor. Init the integer to 0.
			Int(int64_t x);					///< Init the integer to x.
			Int(const std::string& str);	///< Init the integer from a string.
			Int(const Int& x) = default;
			Int(Int&& x) = default;

			Int& operator=(const Int& x) = default;
			Int& operator=(Int&& x) = default;

			Int& operator+=(const Int& x);
			Int& operator-=(const Int& x);
			Int& operator*=(const Int& x);
			Int& operator/=(const Int& x);
			Int& operator%=(const Int& x);
			Int& operator<<=(uint64_t x);
			Int& operator>>=(uint64_t x);

			Int& operator++();
			Int operator++(int);
			Int& operator--();
			Int operator--(int);

			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \brief Returns the string corresponding to the integer.
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			std::string toString() const;
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \brief Returns, if possible, the integer with the type int64_t.
			/// 
			/// If the integer is too big (or too small) to be converted to `int64_t`, then the function throws an error.
			///
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			int64_t toInt() const;

			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \brief Compare two big integers.
			///
			/// Returns `0` if the integers are equals, `1` if `this > x` and `-1` if `this < x`.
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			int compare(const Int& x) const;
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \brief Transform the integer into its opposite.
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			void neg();

			~Int() = default;

		private:

			std::vector<uint32_t> _values;
			bool _sign;

			friend std::ostream& operator<<(std::ostream& stream, const Int& x);
			friend std::istream& operator>>(std::istream& stream, Int& x);
	};


	// External operators

	Int operator+(const Int& x, const Int& y);
	Int&& operator+(Int&& x, const Int& y);
	Int&& operator+(const Int& x, Int&& y);
	Int&& operator+(Int&& x, Int&& y);

	Int operator-(const Int& x, const Int& y);
	Int&& operator-(Int&& x, const Int& y);
	Int&& operator-(const Int& x, Int&& y);
	Int&& operator-(Int&& x, Int&& y);

	Int operator*(const Int& x, const Int& y);
	Int&& operator*(Int&& x, const Int& y);
	Int&& operator*(const Int& x, Int&& y);
	Int&& operator*(Int&& x, Int&& y);

	Int operator/(const Int& x, const Int& y);
	Int&& operator/(Int&& x, const Int& y);
	Int&& operator/(Int&& x, Int&& y);

	Int operator%(const Int& x, const Int& y);
	Int&& operator%(Int&& x, const Int& y);
	Int&& operator%(Int&& x, Int&& y);

	Int operator<<(const Int& x, uint64_t y);
	Int&& operator<<(Int&& x, uint64_t y);

	Int operator>>(const Int& x, uint64_t y);
	Int&& operator>>(Int&& x, uint64_t y);

	Int operator-(const Int& x);
	Int&& operator-(Int&& x);
	
	Int operator+(const Int& x);
	Int&& operator+(Int&& x);


	// Comparators

	bool operator==(const Int& x, const Int& y);
	bool operator!=(const Int& x, const Int& y);
	bool operator>(const Int& x, const Int& y);
	bool operator<(const Int& x, const Int& y);
	bool operator>=(const Int& x, const Int& y);
	bool operator<=(const Int& x, const Int& y);


	// I/O

	std::ostream& operator<<(std::ostream& stream, const Int& x);
	std::istream& operator>>(std::istream& stream, Int& x);
}