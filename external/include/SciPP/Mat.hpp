#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file Mat.hpp
/// \brief Functions and classes for matrices manipulations.
/// \author Reiex
/// 
/// For a more detailed description, see class Mat.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SciPP/types.hpp>
#include <SciPP/Tensor.hpp>
#include <SciPP/Vec.hpp>

namespace scp
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \class Mat
	/// \brief Class for matrices manipulations.
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T>
	class Mat : public Tensor<T, 2>
	{
		public:

			Mat() = delete;
			Mat(const Tensor<T, 2>& tensor);				///< Init the matrix from a tensor of order 2.
			Mat(Tensor<T, 2>&& tensor);						///< Init the matrix from a tensor or order 2.
			Mat(uint64_t row, uint64_t col, int64_t x = 0);	///< Init the matrix with `T(x)` everywhere.
			Mat(uint64_t row, uint64_t col, const T& x);	///< Init the matrix with `x` everywhere.
			Mat(const std::vector<std::vector<T>>& values);	///< Init the matrix directly.
			Mat(const Mat<T>& a) = default;
			Mat(Mat<T>&& a) = default;

			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \brief Returns the identity matrix multiplied by `T(x)`.
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			static Mat<T> identity(uint64_t size, int64_t x = 1);
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \brief Returns the identity matrix multiplied by `x`.
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			static Mat<T> identity(uint64_t size, const T& x);

			Mat<T>& operator=(const Mat<T>& a);
			Mat<T>& operator=(Mat<T>&& a);

			Vec<T>& operator[](uint64_t i);
			const Vec<T>& operator[](uint64_t i) const;

			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \brief Compute the inverse of the matrix.
			/// 
			/// If the matrix has no inverse, an `std::runtime_error` is thrown.
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			Mat<T> inverse() const;
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \brief Compute the transpose of the matrix.
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			Mat<T> transpose() const;
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \brief Compute the determinant of the matrix.
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			T det() const;

			~Mat() = default;
	};

	// External operators

	template<typename T>
	Mat<T> operator*(const Mat<T>& a, const Mat<T>& b);

	template<typename T>
	Vec<T> operator*(const Mat<T>& a, const Vec<T>& b);
	template<typename T>
	Vec<T> operator*(const Vec<T>& a, const Mat<T>& b);

	// Specific functions

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \relates Mat
	/// \brief Discrete Cosine Transform of a matrix. (Type II corrected)
	/// 
	/// The DCT computed is not centered (its origin is (0, 0)). It is the responsibility of the user to center the DFT
	/// if he wants to.
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T>
	Mat<T> dct(const Mat<T>& f);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \relates Mat
	/// \brief Inverse Discrete Cosine Transform of a matrix. (Type II corrected)
	/// 
	/// The specter taken as argument must not be centered: its origin must be (0, 0).
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T>
	Mat<T> idct(const Mat<T>& fh);
}

#include <SciPP/MatT.hpp>
