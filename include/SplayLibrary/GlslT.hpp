#pragma once

#include <SplayLibrary/Glsl.hpp>

namespace spl
{
	template<typename EltType, uint8_t Col, uint8_t Row, typename ColType>
	_Mat<EltType, Col, Row, ColType>::_Mat(EltType diagValue)
	{
		constexpr uint8_t n = std::min(Col, Row);
		constexpr uint8_t offset = Col + 1;
		constexpr uint8_t size = Col * Row;

		for (uint8_t i = 0, k = 0; i < n; ++i, k += offset)
		{
			val[offset] = diagValue;
		}
	}

	template<typename EltType, uint8_t Col, uint8_t Row, typename ColType>
	_Mat<EltType, Col, Row, ColType>::_Mat(std::initializer_list<EltType> tab)
	{
		constexpr uint8_t size = Col * Row;
		static_assert(size == tab.size());

		std::memcpy(val, tab.begin(), static_cast<size_t>(size) * sizeof(EltType));
	}

	template<typename EltType, uint8_t Col, uint8_t Row, typename ColType>
	ColType& _Mat<EltType, Col, Row, ColType>::operator[](uint8_t i)
	{
		assert(i < Row);
		return *reinterpret_cast<ColType*>(val + Col * i);
	}

	template<typename EltType, uint8_t Col, uint8_t Row, typename ColType>
	const ColType& _Mat<EltType, Col, Row, ColType>::operator[](uint8_t i) const
	{
		assert(i < Row);
		return *reinterpret_cast<ColType*>(val + Col * i);
	}

	template<typename EltType, uint8_t Col, uint8_t Row, typename ColType>
	_Mat<EltType, Col, Row, ColType>& _Mat<EltType, Col, Row, ColType>::operator+=(const _Mat<EltType, Col, Row, ColType>& A)
	{
		constexpr uint8_t size = Col * Row;
		for (uint8_t i = 0; i < size; ++i)
		{
			val[i] += A[i];
		}

		return *this;
	}

	template<typename EltType, uint8_t Col, uint8_t Row, typename ColType>
	_Mat<EltType, Col, Row, ColType>& _Mat<EltType, Col, Row, ColType>::operator-=(const _Mat<EltType, Col, Row, ColType>& A)
	{
		constexpr uint8_t size = Col * Row;
		for (uint8_t i = 0; i < size; ++i)
		{
			val[i] -= A[i];
		}

		return *this;
	}


	template<typename EltType, uint8_t Col, uint8_t Row, typename ColType>
	_Mat<EltType, Col, Row, ColType> operator+(const _Mat<EltType, Col, Row, ColType>& A, const _Mat<EltType, Col, Row, ColType>& B)
	{
		_Mat<EltType, Col, Row, ColType> C(A);
		return C += B;
	}

	template<typename EltType, uint8_t Col, uint8_t Row, typename ColType>
	_Mat<EltType, Col, Row, ColType> operator-(const _Mat<EltType, Col, Row, ColType>& A, const _Mat<EltType, Col, Row, ColType>& B)
	{
		_Mat<EltType, Col, Row, ColType> C(A);
		return C -= B;
	}

	template<typename EltType, uint8_t RowA, uint8_t ColARowB, uint8_t ColB, typename ColAType, typename ColBType>
	_Mat<EltType, ColB, RowA, ColBType> operator*(const _Mat<EltType, ColARowB, RowA, ColAType>& A, const _Mat<EltType, ColB, ColARowB, ColBType>& B)
	{
		_Mat<EltType, Col, Row, ColType> C(0);

		for (uint8_t i = 0; i < RowA; ++i)
		{
			for (uint8_t j = 0; j < ColB; ++j)
			{
				for (uint8_t k = 0; k < ColARowB; ++k)
				{
					C[j][i] += A[k][i] * B[j][k];
				}
			}
		}

		return C;
	}
}
