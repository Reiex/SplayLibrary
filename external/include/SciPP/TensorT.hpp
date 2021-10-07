#pragma once

#include <SciPP/Tensor.hpp>

namespace scp
{
	template<uint64_t N>
	template<typename T>
	TensorIterator<N>::TensorIterator(const Tensor<T, N>& a, bool end)
	{
		std::memcpy(_shape, a.shape(), sizeof(uint64_t) * N);
		std::memset(_pos.indices, 0, sizeof(uint64_t) * N);
		_pos.globalIndex = 0;

		if (end)
		{
			_pos.indices[0] = _shape[0];
			_pos.globalIndex = a.globalLength();
		}
	}

	template<uint64_t N>
	TensorIterator<N>::TensorIterator(const uint64_t* shape, const uint64_t* indices, uint64_t globalIndex)
	{
		std::memcpy(_shape, shape, sizeof(uint64_t) * N);
		std::memcpy(_pos.indices, indices, sizeof(uint64_t) * N);
		_pos.globalIndex = globalIndex;
	}

	template<uint64_t N>
	TensorIterator<N>::TensorIterator(const uint64_t* shape, bool end)
	{
		std::memcpy(_shape, shape, sizeof(uint64_t) * N);
		std::memset(_pos.indices, 0, sizeof(uint64_t) * N);
		_pos.globalIndex = 0;

		if (end)
		{
			_pos.indices[0] = _shape[0];
			_pos.globalIndex = 1;
			for (uint64_t i = 0; i < N; ++i)
			{
				_pos.globalIndex *= _shape[i];
			}
		}
	}

	template<uint64_t N>
	const TensorPosition<N>& TensorIterator<N>::operator*() const
	{
		return _pos;
	}

	template<uint64_t N>
	const TensorPosition<N>* TensorIterator<N>::operator->() const
	{
		return &_pos;
	}

	template<uint64_t N>
	TensorIterator<N>& TensorIterator<N>::operator++()
	{
		uint64_t i;
		for (i = N - 1; _pos.indices[i] == _shape[i] - 1 && i != 0; --i)
		{
			_pos.indices[i] = 0;
		}

		++_pos.indices[i];
		++_pos.globalIndex;

		return *this;
	}

	template<uint64_t N>
	TensorIterator<N> TensorIterator<N>::operator++(int)
	{
		TensorIterator<N> copy(_shape, _pos.indices, _pos.globalindex);

		operator++();

		return copy;
	}

	template<uint64_t N>
	bool TensorIterator<N>::operator==(const TensorIterator<N>& iterator) const
	{
		return !std::memcmp(this, &iterator, sizeof(TensorIterator<N>));
	}

	template<uint64_t N>
	bool TensorIterator<N>::operator!=(const TensorIterator<N>& iterator) const
	{
		return std::memcmp(this, &iterator, sizeof(TensorIterator<N>));
	}


	// Constructors

	template<typename T, uint64_t N>
	Tensor<T, N>::Tensor() :
		_values(nullptr),
		_tree(nullptr),
		_shape(nullptr),
		_treeOffset(1),
		_length(0),
		_owner(true),
		_moved(true)
	{
	}

	template<typename T, uint64_t N>
	void Tensor<T, N>::initSubTensor(T* values, uint64_t* shape, uint64_t length, uint64_t treeLength)
	{
		_values = values;
		if constexpr (N == 1)
		{
			_tree = values;
			_treeOffset = 1;
		}
		else
		{
			_tree = reinterpret_cast<SubTensor*>(this + 1);
			_treeOffset = treeLength / shape[0];

			uint64_t subLength = length / shape[0];
			for (uint64_t i = 0; i < shape[0]; ++i)
			{
				_tree[i*_treeOffset].initSubTensor(_values + i*subLength, shape + 1, subLength, _treeOffset - 1);
			}
		}
		_shape = shape;
		_length = length;
		_owner = false;
		_moved = false;
	}

	template<typename T, uint64_t N>
	Tensor<T, N>::Tensor(const uint64_t* shape, const T& x) : Tensor()
	{
		_shape = new uint64_t[N];
		std::memcpy(_shape, shape, sizeof(uint64_t) * N);

		_length = 1;
		uint64_t *it = _shape, *end = _shape + N;
		while (it != end)
		{
			_length *= *it;
			++it;
		}
		assert(_length != 0);

		_values = new T[_length];

		if constexpr (N == 1)
		{
			_tree = _values;
			_treeOffset = 1;
		}
		else
		{
			uint64_t treeLength = 0;
			it = _shape + N - 2;
			end = _shape - 1;
			while (it != end)
			{
				treeLength = (treeLength + 1) * *it;
				--it;
			}

			_tree = new SubTensor[treeLength];
			_treeOffset = treeLength / _shape[0];

			uint64_t subLength = _length / _shape[0];
			for (uint64_t i = 0; i < _shape[0]; ++i)
			{
				_tree[i*_treeOffset].initSubTensor(_values + i*subLength, _shape + 1, subLength, _treeOffset - 1);
			}
		}
		std::fill<T*, T>(_values, _values + _length, x);

		_owner = true;
		_moved = false;
	}

	template<typename T, uint64_t N>
	Tensor<T, N>::Tensor(const uint64_t* shape, int64_t x) : Tensor(shape, T(x))
	{
	}

	template<typename T, uint64_t N>
	Tensor<T, N>::Tensor(const std::vector<uint64_t>& shape, const T& x) : Tensor(shape.data(), x)
	{
		assert(shape.size() == N);
	}

	template<typename T, uint64_t N>
	Tensor<T, N>::Tensor(const std::vector<uint64_t>& shape, int64_t x) : Tensor(shape, T(x))
	{
	}
	
	template<typename T, uint64_t N>
	Tensor<T, N>::Tensor(const Tensor<T, N>& a) : Tensor()
	{
		assert(!a._moved);

		_shape = new uint64_t[N];
		std::memcpy(_shape, a._shape, sizeof(uint64_t) * N);

		_length = a._length;
		uint64_t treeLength = _length / _shape[N - 1];

		_values = new T[_length];
		if constexpr (N == 1)
		{
			_tree = _values;
			_treeOffset = 1;
		}
		else
		{
			uint64_t treeLength = 0;
			uint64_t *it = _shape + N - 2, *end = _shape - 1;
			while (it != end)
			{
				treeLength = (treeLength + 1) * *it;
				--it;
			}

			_tree = new SubTensor[treeLength];

			_treeOffset = treeLength / _shape[0];
			uint64_t subLength = _length / _shape[0];
			for (uint64_t i = 0; i < _shape[0]; ++i)
			{
				_tree[i*_treeOffset].initSubTensor(_values + i*subLength, _shape + 1, subLength, _treeOffset - 1);
			}
		}

		std::copy<T*, T*>(a._values, a._values + a._length, _values);

		_owner = true;
		_moved = false;
	}
	
	template<typename T, uint64_t N>
	Tensor<T, N>::Tensor(Tensor<T, N>&& a) :
		_values(a._values),
		_tree(a._tree),
		_shape(a._shape),
		_treeOffset(a._treeOffset),
		_length(a._length),
		_owner(true),
		_moved(false)
	{
		assert(!a._moved);
		assert(a._owner);

		a._values = nullptr;
		a._tree = nullptr;
		a._shape = nullptr;
		a._treeOffset = 1;
		a._length = 0;
		a._owner = true;
		a._moved = true;
	}


	// Assignment operators

	template<typename T, uint64_t N>
	Tensor<T, N>& Tensor<T, N>::operator=(const Tensor<T, N>& a)
	{
		assert(!_moved);
		assert(!a._moved);
		assert(!std::memcmp(_shape, a._shape, sizeof(uint64_t) * N));

		std::copy<T*, T*>(a._values, a._values + a._length, _values);

		return *this;
	}
	
	template<typename T, uint64_t N>
	Tensor<T, N>& Tensor<T, N>::operator=(Tensor<T, N>&& a)
	{
		assert(!_moved);
		assert(!a._moved);
		assert(!std::memcmp(_shape, a._shape, sizeof(uint64_t) * N));

		if (_owner)
		{
			free();

			_values = a._values;
			_tree = a._tree;
			_shape = a._shape;
			_treeOffset = a._treeOffset;
			_length = a._length;
			_owner = a._owner;
			_moved = false;

			a._values = nullptr;
			a._tree = nullptr;
			a._shape = nullptr;
			a._treeOffset = 1;
			a._length = 0;
			a._owner = true;
			a._moved = true;
		}
		else
		{
			std::copy<T*, T*>(a._values, a._values + a._length, _values);
		}

		return *this;
	}
	

	// Accessors

	template<typename T, uint64_t N>
	uint64_t Tensor<T, N>::globalLength() const
	{
		assert(!_moved);
		return _length;
	}

	template<typename T, uint64_t N>
	const uint64_t* Tensor<T, N>::shape() const
	{
		assert(!_moved);
		return _shape;
	}

	template<typename T, uint64_t N>
	uint64_t Tensor<T, N>::shape(uint64_t i) const
	{
		assert(!_moved);
		assert(i < N);
		return _shape[i];
	}

	template<typename T, uint64_t N>
	typename Tensor<T, N>::SubTensor& Tensor<T, N>::operator[](uint64_t i)
	{
		assert(!_moved);
		assert(i < _shape[0]);
		return _tree[i*_treeOffset];
	}
	
	template<typename T, uint64_t N>
	const typename Tensor<T, N>::SubTensor& Tensor<T, N>::operator[](uint64_t i) const
	{
		assert(!_moved);
		assert(i < _shape[0]);
		return _tree[i*_treeOffset];
	}

	template<typename T, uint64_t N>
	T& Tensor<T, N>::get(const uint64_t* indices)
	{
		assert(!_moved);
		assert(indices[0] < _shape[0]);
		uint64_t index = indices[0];
		for (uint64_t i = 1; i < N; ++i)
		{
			assert(indices[i] < _shape[i]);
			index = index * _shape[i] + indices[i];
		}

		return _values[index];
	}

	template<typename T, uint64_t N>
	const T& Tensor<T, N>::get(const uint64_t* indices) const
	{
		assert(!_moved);
		assert(indices[0] < _shape[0]);
		uint64_t index = indices[0];
		for (uint64_t i = 1; i < N; ++i)
		{
			assert(indices[i] < _shape[i]);
			index = index * _shape[i] + indices[i];
		}

		return _values[index];
	}

	template<typename T, uint64_t N>
	T& Tensor<T, N>::get(uint64_t globalIndex)
	{
		assert(!_moved);
		assert(globalIndex < _length);

		return _values[globalIndex];
	}

	template<typename T, uint64_t N>
	const T& Tensor<T, N>::get(uint64_t globalIndex) const
	{
		assert(!_moved);
		assert(globalIndex < _length);

		return _values[globalIndex];
	}

	template<typename T, uint64_t N>
	TensorIterator<N> Tensor<T, N>::begin() const
	{
		assert(!_moved);
		return TensorIterator<N>(*this);
	}

	template<typename T, uint64_t N>
	TensorIterator<N> Tensor<T, N>::end() const
	{
		assert(!_moved);
		return TensorIterator<N>(*this, true);
	}


	// Internal operators

	template<typename T, uint64_t N>
	Tensor<T, N>& Tensor<T, N>::operator+=(const Tensor<T, N>& a)
	{
		assert(!_moved);
		assert(!a._moved);
		assert(!std::memcmp(_shape, a._shape, sizeof(uint64_t) * N));

		for (uint64_t i = 0; i < _length; ++i)
		{
			_values[i] += a._values[i];
		}

		return *this;
	}
	
	template<typename T, uint64_t N>
	Tensor<T, N>& Tensor<T, N>::operator-=(const Tensor<T, N>& a)
	{
		assert(!_moved);
		assert(!a._moved);
		assert(!std::memcmp(_shape, a._shape, sizeof(uint64_t) * N));

		for (uint64_t i = 0; i < _length; ++i)
		{
			_values[i] -= a._values[i];
		}

		return *this;
	}
	
	template<typename T, uint64_t N>
	Tensor<T, N>& Tensor<T, N>::operator*=(T x)
	{
		assert(!_moved);

		for (uint64_t i = 0; i < _length; ++i)
		{
			_values[i] *= x;
		}

		return *this;
	}
	
	template<typename T, uint64_t N>
	Tensor<T, N>& Tensor<T, N>::operator/=(T x)
	{
		assert(!_moved);

		for (uint64_t i = 0; i < _length; ++i)
		{
			_values[i] /= x;
		}

		return *this;
	}


	// Specific methods

	template<typename T, uint64_t N>
	const T& Tensor<T, N>::minElement() const
	{
		T* minElt = _values;
		for (uint64_t i = 1; i < _length; ++i)
		{
			if (*minElt > _values[i])
			{
				minElt = _values + i;
			}
		}

		return *minElt;
	}

	template<typename T, uint64_t N>
	const T& Tensor<T, N>::maxElement() const
	{
		T* maxElt = _values;
		for (uint64_t i = 1; i < _length; ++i)
		{
			if (*maxElt < _values[i])
			{
				maxElt = _values + i;
			}
		}

		return *maxElt;
	}

	template<typename T, uint64_t N>
	T Tensor<T, N>::normSq() const
	{
		T result(0);
		for (uint64_t i = 0; i < _length; ++i)
		{
			result += _values[i] * _values[i];
		}

		return result;
	}

	template<typename T, uint64_t N>
	T Tensor<T, N>::norm() const
	{
		return std::sqrt(normSq());
	}

	template<typename T, uint64_t N>
	Tensor<T, N - 2> Tensor<T, N>::contract(uint64_t i, uint64_t j) const
	{
		static_assert(N > 2);
		assert(i != j);
		assert(_shape[i] == _shape[j]);

		if (i > j)
		{
			std::swap(i, j);
		}

		uint64_t shape[N - 2];
		if (i != 0)
		{
			std::memcpy(shape, _shape, i * sizeof(uint64_t));
		}
		if (i != j - 1)
		{
			std::memcpy(shape + i, _shape + i + 1, (j - i - 1) * sizeof(uint64_t));
		}
		if (j != N - 1)
		{
			std::memcpy(shape + j - 1, _shape + j + 1, (N - j - 1) * sizeof(uint64_t));
		}

		Tensor<T, N - 2> contraction(shape);

		for (uint64_t k = 0; k < _shape[i]; ++k)
		{
			for (const TensorPosition<N - 2>& pos : contraction)
			{
				uint64_t indices[N];
				indices[i] = k;
				indices[j] = k;
				if (i != 0)
				{
					std::memcpy(indices, pos.indices, i * sizeof(uint64_t));
				}
				if (i != j - 1)
				{
					std::memcpy(indices + i + 1, pos.indices + i, (j - i - 1) * sizeof(uint64_t));
				}
				if (j != N - 1)
				{
					std::memcpy(indices + j + 1, pos.indices + j - 1, (N - j - 1) * sizeof(uint64_t));
				}

				contraction.get(pos.globalIndex) += get(indices);
			}
		}

		return contraction;
	}


	// Destructors

	template<typename T, uint64_t N>
	void Tensor<T, N>::free()
	{
		if (!_moved)
		{
			if (_owner)
			{
				delete[] _values;
				if constexpr (N != 1)
				{
					delete[] _tree;
				}
				delete[] _shape;
			}

			_values = nullptr;
			_tree = nullptr;
			_shape = nullptr;
		}

		_treeOffset = 1;
		_length = 1;
		_owner = true;
		_moved = true;
	}

	template<typename T, uint64_t N>
	Tensor<T, N>::~Tensor()
	{
		free();
	}


	// External operators

	template<typename T, uint64_t N>
	Tensor<T, N> operator+(const Tensor<T, N>& a, const Tensor<T, N>& b)
	{
		Tensor<T, N> c(a);
		c += b;

		return c;
	}

	template<typename T, uint64_t N>
	Tensor<T, N>&& operator+(Tensor<T, N>&& a, const Tensor<T, N>& b)
	{
		a += b;
		return std::move(a);
	}

	template<typename T, uint64_t N>
	Tensor<T, N>&& operator+(const Tensor<T, N>& a, Tensor<T, N>&& b)
	{
		b += a;
		return std::move(b);
	}

	template<typename T, uint64_t N>
	Tensor<T, N>&& operator+(Tensor<T, N>&& a, Tensor<T, N>&& b)
	{
		a += b;
		return std::move(a);
	}


	template<typename T, uint64_t N>
	Tensor<T, N> operator-(const Tensor<T, N>& a, const Tensor<T, N>& b)
	{
		Tensor<T, N> c(a);
		c -= b;

		return c;
	}

	template<typename T, uint64_t N>
	Tensor<T, N>&& operator-(Tensor<T, N>&& a, const Tensor<T, N>& b)
	{
		a -= b;
		return std::move(a);
	}

	template<typename T, uint64_t N>
	Tensor<T, N>&& operator-(const Tensor<T, N>& a, Tensor<T, N>&& b)
	{
		b -= a;
		return -std::move(b);
	}

	template<typename T, uint64_t N>
	Tensor<T, N>&& operator-(Tensor<T, N>&& a, Tensor<T, N>&& b)
	{
		a -= b;
		return std::move(a);
	}


	template<typename T, uint64_t N, uint64_t M>
	Tensor<T, N + M> tensorProduct(const Tensor<T, N>& a, const Tensor<T, M>& b)
	{
		uint64_t shape[N + M];
		std::memcpy(shape, a.shape(), sizeof(uint64_t) * N);
		std::memcpy(shape + N, b.shape(), sizeof(uint64_t) * M);

		Tensor<T, N + M> c(shape);
		for (const TensorPosition<N + M>& pos : c)
		{
			c.get(pos.indices) = a.get(pos.indices) * b.get(pos.indices + N);
		}

		return c;
	}

	template<typename T, uint64_t N, uint64_t M>
	Tensor<T, N + M - 2> contractedTensorProduct(const Tensor<T, N>& a, const Tensor<T, M>& b)
	{
		static_assert(N + M > 2);
		assert(a.shape(N - 1) == b.shape(0));

		uint64_t shape[N + M - 2];
		std::memcpy(shape, a.shape(), (N - 1) * sizeof(uint64_t));
		std::memcpy(shape + N - 1, b.shape() + 1, (M - 1) * sizeof(uint64_t));

		Tensor<T, N + M - 2> r(shape);

		for (uint64_t k = 0; k < b.shape(0); ++k)
		{
			for (const TensorPosition<N + M - 2>&pos : r)
			{
				uint64_t aIndices[N];
				std::memcpy(aIndices, pos.indices, (N - 1) * sizeof(uint64_t));
				aIndices[N - 1] = k;

				uint64_t bIndices[M];
				std::memcpy(bIndices + 1, pos.indices + N - 1, (M - 1) * sizeof(uint64_t));
				bIndices[0] = k;

				r.get(pos.globalIndex) += a.get(aIndices) * b.get(bIndices);
			}
		}

		return r;
	}

	template<typename T, uint64_t N>
	Tensor<T, N> hadamardProduct(const Tensor<T, N>& a, const Tensor<T, N>& b)
	{
		assert(!std::memcmp(a.shape(), b.shape(), sizeof(uint64_t) * N));

		Tensor<T, N> c(a.shape());

		for (const TensorPosition<N>& pos : c)
		{
			c.get(pos.globalIndex) = a.get(pos.globalIndex) * b.get(pos.globalIndex);
		}

		return c;
	}

	template<typename T, uint64_t N>
	T dotProduct(const Tensor<T, N>& a, const Tensor<T, N>& b)
	{
		assert(!std::memcmp(a.shape(), b.shape(), sizeof(uint64_t) * N));

		T result(0);
		for (const TensorPosition<N>& pos : a)
		{
			result += a.get(pos.globalIndex) * b.get(pos.globalIndex);
		}

		return result;
	}


	template<typename T, uint64_t N>
	Tensor<T, N> operator*(const Tensor<T, N>& a, const T& x)
	{
		Tensor<T, N> b(a);
		b *= x;

		return b;
	}

	template<typename T, uint64_t N>
	Tensor<T, N>&& operator*(Tensor<T, N>&& a, const T& x)
	{
		a *= x;
		return std::move(a);
	}

	template<typename T, uint64_t N>
	Tensor<T, N> operator*(const T& x, const Tensor<T, N>& a)
	{
		Tensor<T, N> b(a);
		b *= x;

		return b;
	}

	template<typename T, uint64_t N>
	Tensor<T, N>&& operator*(const T& x, Tensor<T, N>&& a)
	{
		a *= x;
		return std::move(a);
	}


	template<typename T, uint64_t N>
	Tensor<T, N> operator/(const Tensor<T, N>& a, const T& x)
	{
		Tensor<T, N> b(a);
		b /= x;

		return b;
	}

	template<typename T, uint64_t N>
	Tensor<T, N>&& operator/(Tensor<T, N>&& a, const T& x)
	{
		a /= x;
		return std::move(a);
	}


	template<typename T, uint64_t N>
	Tensor<T, N> operator-(const Tensor<T, N>& a)
	{
		Tensor<T, N> b(a.shape());
		for (const TensorPosition<N>& pos : b)
		{
			b.get(pos.globalIndex) = -a.get(pos.globalIndex);
		}

		return b;
	}

	template<typename T, uint64_t N>
	Tensor<T, N>&& operator-(Tensor<T, N>&& a)
	{
		for (const TensorPosition<N>& pos : a)
		{
			a.get(pos.globalIndex) = -a.get(pos.globalIndex);
		}

		return std::move(a);
	}


	template<typename T, uint64_t N>
	Tensor<T, N> operator+(const Tensor<T, N>& a)
	{
		return a;
	}

	template<typename T, uint64_t N>
	Tensor<T, N>&& operator+(Tensor<T, N>&& a)
	{
		return std::move(a);
	}


	// Comparators

	template<typename T, uint64_t N>
	bool operator==(const Tensor<T, N>& a, const Tensor<T, N>& b)
	{
		if (std::memcmp(a.shape(), b.shape(), sizeof(uint64_t) * N))
		{
			return false;
		}

		for (const TensorPosition<N>& pos : a)
		{
			if (a.get(pos.globalIndex) != b.get(pos.globalIndex))
			{
				return false;
			}
		}

		return true;
	}

	template<typename T, uint64_t N>
	bool operator!=(const Tensor<T, N>& a, const Tensor<T, N>& b)
	{
		return !(a == b);
	}


	// Specific functions

	template<typename T, uint64_t N>
	Tensor<T, N> convolution(const Tensor<T, N>& a, const Tensor<T, N>& kernel, ConvolutionMethod method)
	{
		for (uint64_t i = 0; i < N; i++)
		{
			assert(kernel.shape(i) % 2 == 1);
			assert(kernel.shape(i) <= a.shape(i));
		}

		Tensor<T, N> b(a.shape());

		uint64_t offset[N];
		for (uint64_t i = 0; i < N; i++)
		{
			offset[i] = kernel.shape(i) / 2;
		}

		for (const TensorPosition<N>& pos : a)
		{
			b.get(pos.globalIndex) = T(0);

			for (const TensorPosition<N>& kernelPos : kernel)
			{
				int64_t offsetedIndices[N];
				bool setToZero(false);
				for (uint64_t i = 0; i < N; i++)
				{
					offsetedIndices[i] = int64_t(pos.indices[i]) + int64_t(kernelPos.indices[i]) - int64_t(offset[i]);

					switch (method)
					{
						case ConvolutionMethod::Zero:
							setToZero = (offsetedIndices[i] < 0 || offsetedIndices[i] >= a.shape(i));
							break;
						case ConvolutionMethod::Continuous:
							offsetedIndices[i] = std::max<int64_t>(std::min<int64_t>(offsetedIndices[i], a.shape(i) - 1), 0);
							break;
						case ConvolutionMethod::Periodic:
							offsetedIndices[i] = (offsetedIndices[i] + a.shape(i)) % a.shape(i);
							break;
						default:
							assert(false);
					}

					if (setToZero)
					{
						break;
					}
				}

				if (!setToZero)
				{
					b.get(pos.globalIndex) += a.get(reinterpret_cast<uint64_t*>(offsetedIndices)) * kernel.get(kernelPos.globalIndex);
				}
			}
		}

		return b;
	}

	namespace
	{
		template<typename T, uint64_t N>
		void _cooleyTukey(Tensor<std::complex<T>, N>& a, const std::array<std::vector<std::complex<T>>, N>& exponentials, const uint64_t* shape, const uint64_t* offset, uint64_t* stride)
		{
			// Directly exit if it is a single variable

			for (uint64_t i = 0; i < N; ++i)
			{
				if (shape[i] != 1)
				{
					break;
				}

				if (i == N - 1)
				{
					return;
				}
			}

			// Useful variables

			uint64_t cellShape[N];
			for (uint64_t i = 0; i < N; ++i)
			{
				cellShape[i] = shape[i];
				for (uint64_t j = 2; j < shape[i]; ++j)
				{
					if (shape[i] % j == 0)
					{
						cellShape[i] = j;
						break;
					}
				}
			}

			uint64_t subShape[N];
			for (uint64_t i = 0; i < N; ++i)
			{
				subShape[i] = shape[i] / cellShape[i];
			}

			uint64_t subOffset[N];
			for (uint64_t i = 0; i < N; ++i)
			{
				subOffset[i] = offset[i] * cellShape[i];
			}

			// Compute fft of each sub tensor

			for (TensorIterator<N> it(cellShape), end(cellShape, true); it != end; ++it)
			{
				for (uint64_t i = 0; i < N; ++i)
				{
					stride[i] += it->indices[i] * offset[i];
				}

				_cooleyTukey(a, exponentials, subShape, subOffset, stride);

				for (uint64_t i = 0; i < N; ++i)
				{
					stride[i] -= it->indices[i] * offset[i];
				}
			}

			// Store the coefficients calculated before merging them

			Tensor<std::complex<T>, N> tmp(shape);
			for (const TensorPosition<N>& pos : tmp)
			{
				uint64_t indices[N];
				for (uint64_t i = 0; i < N; ++i)
				{
					indices[i] = stride[i] + pos.indices[i] * offset[i];
				}

				tmp.get(pos.globalIndex) = a.get(indices);
			}

			// Iterate over a sub tensor and merge each cell asociated

			for (TensorIterator<N> subIt(subShape), subEnd(subShape, true); subIt != subEnd; ++subIt)
			{
				// Compute the position of the corner of the cell on 'a' and on 'tmp'

				uint64_t aCellIndices[N], tmpCellIndices[N];
				for (uint64_t i = 0; i < N; ++i)
				{
					aCellIndices[i] = stride[i] + subIt->indices[i] * offset[i];
					tmpCellIndices[i] = subIt->indices[i] * cellShape[i];
				}

				// Merge the elements of the cell of 'tmp' into the elements of the cell of 'a'

				for (TensorIterator<N> aCellIt(cellShape), aCellEnd(cellShape, true); aCellIt != aCellEnd; ++aCellIt)
				{
					uint64_t aIndices[N];
					for (uint64_t i = 0; i < N; ++i)
					{
						aIndices[i] = aCellIndices[i] + aCellIt->indices[i] * subShape[i] * offset[i];
					}

					a.get(aIndices) = std::complex<T>(0, 0);

					for (TensorIterator<N> tmpCellIt(cellShape), tmpCellEnd(cellShape, true); tmpCellIt != tmpCellEnd; ++tmpCellIt)
					{
						uint64_t tmpIndices[N];
						for (uint64_t i = 0; i < N; ++i)
						{
							tmpIndices[i] = tmpCellIndices[i] + tmpCellIt->indices[i];
						}

						std::complex<T> factor = std::complex<T>(1, 0);
						for (uint64_t i = 0; i < N; ++i)
						{
							factor *= exponentials[i][((subIt->indices[i] * tmpCellIt->indices[i]) % shape[i]) * offset[i]];
							factor *= exponentials[i][((tmpCellIt->indices[i] * aCellIt->indices[i]) % cellShape[i]) * subShape[i] * offset[i]];
						}

						a.get(aIndices) += factor * tmp.get(tmpIndices);
					}
				}
			}
		}
	}

	template<typename T, uint64_t N>
	Tensor<std::complex<T>, N> fft(const Tensor<std::complex<T>, N>& a)
	{
		Tensor<std::complex<T>, N> b(a);

		uint64_t shape[N];
		std::memcpy(shape, a.shape(), sizeof(uint64_t) * N);

		uint64_t stride[N];
		std::memset(stride, 0, sizeof(uint64_t) * N);

		uint64_t offset[N];
		std::fill<uint64_t*, uint64_t>(offset, offset + N, 1);

		std::array<std::vector<std::complex<T>>, N> exponentials;
		for (uint64_t i = 0; i < N; ++i)
		{
			exponentials[i].resize(shape[i]);
			for (uint64_t j = 0; j < shape[i]; ++j)
			{
				exponentials[i][j] = std::exp(std::complex<T>(0, -2 * pi * j / shape[i]));
			}
		}

		_cooleyTukey(b, exponentials, shape, offset, stride);

		return b;
	}

	template<typename T, uint64_t N>
	Tensor<std::complex<T>, N> ifft(const Tensor<std::complex<T>, N>& a)
	{
		Tensor<std::complex<T>, N> b(a);

		uint64_t shape[N];
		std::memcpy(shape, a.shape(), sizeof(uint64_t) * N);

		uint64_t stride[N];
		std::memset(stride, 0, sizeof(uint64_t) * N);

		uint64_t offset[N];
		std::fill<uint64_t*, uint64_t>(offset, offset + N, 1);

		std::array<std::vector<std::complex<T>>, N> exponentials;
		for (uint64_t i = 0; i < N; ++i)
		{
			exponentials[i].resize(shape[i]);
			for (uint64_t j = 0; j < shape[i]; ++j)
			{
				exponentials[i][j] = std::exp(std::complex<T>(0, 2 * pi * j / shape[i]));
			}
		}

		_cooleyTukey(b, exponentials, shape, offset, stride);

		for (uint64_t i = 0; i < N; ++i)
		{
			b /= b.shape(i);
		}

		return b;
	}
}