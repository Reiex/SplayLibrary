#pragma once

#include <SciPP/Mat.hpp>

namespace scp
{
	// Constructors

	template<typename T>
	Mat<T>::Mat(const Tensor<T, 2>& tensor) : Tensor<T, 2>(tensor)
	{
	}

	template<typename T>
	Mat<T>::Mat(Tensor<T, 2>&& tensor) : Tensor<T, 2>(std::move(tensor))
	{
	}

	template<typename T>
	Mat<T>::Mat(uint64_t row, uint64_t col, int64_t x) : Tensor<T, 2>({ row, col }, x)
	{
	}
	
	template<typename T>
	Mat<T>::Mat(uint64_t row, uint64_t col, const T& x) : Tensor<T, 2>({ row, col }, x)
	{
	}
	
	template<typename T>
	Mat<T>::Mat(const std::vector<std::vector<T>>& values) : Tensor<T, 2>({ values.size(), values.size() == 0 ? 0 : values[0].size() })
	{
		const uint64_t m = this->shape(0), n = this->shape(1);

		for (uint64_t i(0); i < m; ++i)
		{
			assert(values[i].size() == n);
			for (uint64_t j(0); j < n; ++j)
			{
				(*this)[i][j] = values[i][j];
			}
		}
	}

	template<typename T>
	Mat<T> Mat<T>::identity(uint64_t size, int64_t x)
	{
		Mat<T> a(size, size);
		for (uint64_t i(0); i < size; ++i)
		{
			a[i][i] = x;
		}

		return a;
	}

	template<typename T>
	Mat<T> Mat<T>::identity(uint64_t size, const T& x)
	{
		Mat<T> a(size, size);
		for (uint64_t i(0); i < size; ++i)
		{
			a[i][i] = x;
		}

		return a;
	}


	// Assignment operators

	template<typename T>
	Mat<T>& Mat<T>::operator=(const Mat<T>& a)
	{
		Tensor<T, 2>::operator=(a);
		return *this;
	}

	template<typename T>
	Mat<T>& Mat<T>::operator=(Mat<T>&& a)
	{
		Tensor<T, 2>::operator=(std::move(a));
		return *this;
	}


	// Accessors

	template<typename T>
	Vec<T>& Mat<T>::operator[](uint64_t i)
	{
		return static_cast<Vec<T>&>(Tensor<T, 2>::operator[](i));
	}

	template<typename T>
	const Vec<T>& Mat<T>::operator[](uint64_t i) const
	{
		return static_cast<const Vec<T>&>(Tensor<T, 2>::operator[](i));
	}


	// Specific methods

	template<typename T>
	Mat<T> Mat<T>::inverse() const
	{
		assert(this->shape(0) == this->shape(1));

		const uint64_t n = this->shape(0);

		Mat<T> b(*this), inv(Mat<T>::identity(n));

		for (uint64_t j(0); j < n; ++j)
		{
			if (b[j][j] == 0)
			{
				for (uint64_t i(j + 1); i < n; ++i)
				{
					if (b[i][j] != 0)
					{
						inv[i] /= b[i][j];
						b[i] /= b[i][j];
						inv[j] += inv[i];
						b[j] += b[i];
						break;
					}
				}

				if (b[j][j] == 0)
					throw std::runtime_error("The matrix cannot be inverted.");
			}
			else
			{
				inv[j] /= b[j][j];
				b[j] /= b[j][j];
			}

			for (uint64_t i(j + 1); i < n; ++i)
			{
				if (b[i][j] != 0)
				{
					inv[i] -= b[i][j] * inv[j];
					b[i] -= b[i][j] * b[j];
				}
			}
		}

		for (uint64_t j(n - 1); j != UINT64_MAX; --j)
		{
			for (uint64_t i(j - 1); i != UINT64_MAX; --i)
			{
				if (b[i][j] != 0)
				{
					inv[i] -= b[i][j] * inv[j];
					b[i] -= b[i][j] * b[j];
				}
			}
		}

		return inv;
	}

	template<typename T>
	Mat<T> Mat<T>::transpose() const
	{
		const uint64_t m = this->shape(0), n = this->shape(1);
		Mat<T> b(n, m);
		for (uint64_t i(0); i < n; ++i)
		{
			for (uint64_t j(0); j < m; ++j)
			{
				b[i][j] = (*this)[j][i];
			}
		}

		return b;
	}

	template<typename T>
	T Mat<T>::det() const
	{
		assert(this->shape(0) == this->shape(1));

		const uint64_t n = this->shape(0);

		Mat<T> b(*this);

		for (uint64_t j(0); j < n; ++j)
		{
			if (b[j][j] == 0)
			{
				for (uint64_t i(j + 1); i < n; ++i)
				{
					if (b[i][j] != 0)
					{
						b[j] += b[i];
						break;
					}
				}

				if (b[j][j] == 0)
				{
					return 0;
				}
			}

			for (uint64_t i(j + 1); i < n; ++i)
			{
				b[i] -= (b[i][j] / b[j][j]) * b[j];
			}
		}

		T prod(b[0][0]);
		for (uint64_t i(1); i < n; ++i)
		{
			prod *= b[i][i];
		}

		return prod;
	}


	// External operators

	template<typename T>
	Mat<T> operator*(const Mat<T>& a, const Mat<T>& b)
	{
		assert(a.shape(1) == b.shape(0));

		const uint64_t m = a.shape(0), p = a.shape(1), n = b.shape(1);
		Mat<T> c(m, n);
		for (uint64_t i(0); i < m; ++i)
		{
			for (uint64_t j(0); j < n; ++j)
			{
				for (uint64_t k(0); k < p; ++k)
				{
					c[i][j] += a[i][k] * b[k][j];
				}
			}
		}
		
		return c;
	}
	

	// Specific functions

	namespace
	{
		template<typename T>
		T dct2DBase(uint64_t M, uint64_t N, uint64_t p, uint64_t q, uint64_t m, uint64_t n)
		{
			T r(2 * std::cos(pi * p * (m + 0.5) / M) * std::cos(pi * q * (n + 0.5) / N));

			if (p == 0)
			{
				r /= std::sqrt(2.0L);
			}

			if (q == 0)
			{
				r /= std::sqrt(2.0L);
			}

			return r;
		}
	}
	
	template<typename T>
	Mat<T> dct(const Mat<T>& f)
	{
		const uint64_t m = f.shape(0), n = f.shape(1);

		Mat<T> wM(m, m);
		Mat<T> wN(n, n);

		for (uint64_t i(0); i < m; i++)
		{
			for (uint64_t j(0); j < m; j++)
			{
				if (i == 0)
				{
					wM[i][j] = 1.L;
				}
				else
				{
					wM[i][j] = std::sqrt(2.f) * cos(pi * i * (j + 0.5) / m);
				}
			}
		}

		for (uint64_t i(0); i < n; i++)
		{
			for (uint64_t j(0); j < n; j++)
			{
				if (j == 0)
				{
					wN[i][j] = 1.L;
				}
				else
				{
					wN[i][j] = std::sqrt(2.f) * cos(pi * j * (i + 0.5) / n);
				}
			}
		}

		return wM * f * wN;
	}
	
	template<typename T>
	Mat<T> idct(const Mat<T>& fh)
	{
		const uint64_t m = fh.shape(0), n = fh.shape(1);

		Mat<T> wM(m, m);
		Mat<T> wN(n, n);

		for (uint64_t i(0); i < m; i++)
		{
			for (uint64_t j(0); j < m; j++)
			{
				if (j == 0)
				{
					wM[i][j] = 1.L;
				}
				else
				{
					wM[i][j] = std::sqrt(2.f) * cos(pi * j * (i + 0.5) / m);
				}
			}
		}

		for (uint64_t i(0); i < n; i++)
		{
			for (uint64_t j(0); j < n; j++)
			{
				if (i == 0)
				{
					wN[i][j] = 1.L / (m * n);
				}
				else
				{
					wN[i][j] = std::sqrt(2.f) * cos(pi * i * (j + 0.5) / n) / (m * n);
				}
			}
		}

		return wM * fh * wN;
	}
}
