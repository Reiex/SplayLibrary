#pragma once

#include <SciPP/misc.hpp>

namespace scp
{
	template<typename TBase, typename TPow>
	TBase pow(TBase const& x, TPow n)
	{
		if (n < 0)
		{
			throw std::runtime_error("Cannot call pow with n < 0.");
		}

		if (n == 0)
		{
			return 1;
		}

		if (n == 1)
		{
			return x;
		}

		TPow k(n - 1);
		TBase r(x), p(x);

		while (k != 0)
		{
			if (k % 2 == 0)
			{
				p *= p;
				k /= 2;
			}
			else
			{
				r *= p;
				k -= 1;
			}
		}

		return r;
	}
	
	template<typename T>
	T fact(const T& n)
	{
		if (n == 0)
		{
			return 1;
		}

		return n * fact(n - 1);
	}

	template<typename T>
	T gcd(const T& a, const T& b)
	{
		if (a == 0 || b == 0)
		{
			return 1;
		}

		T u(a), v(b), r(u % v);

		while (r != 0)
		{
			u = v;
			v = r;
			r = u % v;
		}

		if (v < 0)
		{
			return -v;
		}
		
		return v;
	}

	template<typename T>
	T lcm(const T& a, const T& b)
	{
		T r((a * b) / gcd(a, b));

		if (r < 0)
		{
			return -r;
		}

		return r;
	}

	template<typename T>
	T binom(const T& n, const T& p)
	{
		if (p > n || p < 0)
		{
			return 0;
		}

		T num = 1, denom = 1;

		for (T i = 0; i < p; ++i)
		{
			num *= n - i;
			denom *= p - i;
		}

		return num / denom;
	}

	template<typename T>
	bool isPrime(const T& n)
	{
		if (n <= 2)
		{
			return n == 2;
		}

		for (T i = 3; i * i <= n; i += 2)
		{
			if (n % i == 0)
			{
				return false;
			}
		}

		return true;
	}

	template<typename T>
	std::vector<std::pair<T, uint64_t>> primeFactors(const T& n)
	{
		T copy(n);

		std::vector<std::pair<T, uint64_t>> factors;

		uint64_t j = 0;
		while (copy % 2 == 0)
		{
			++j;
			copy >>= 1;
		}

		if (j != 0)
		{
			factors.push_back({ T(2), j });
		}

		for (T i = 3; i * i <= copy; i += 2)
		{
			j = 0;
			while (copy % i == 0)
			{
				++j;
				copy /= i;
			}

			if (j != 0)
			{
				factors.push_back({ i, j });
			}
		}

		if (copy != 1)
		{
			factors.push_back({ copy, 1 });
		}

		return factors;
	}

	template<typename T>
	std::vector<T> divisors(const T& n)
	{
		if (n == 0)
		{
			return {};
		}

		T copy(n);
		if constexpr (std::is_signed<T>::value)
		{
			if (copy < 0)
			{
				copy = -copy;
			}
		}

		if (copy == 1)
		{
			return { 1 };
		}

		std::vector<T> divisors;
		for (T i = 1; i*i <= copy; ++i)
		{
			if (copy % i == 0)
			{
				divisors.push_back(i);
			}
		}

		int64_t i = divisors.size() - 1;
		if (divisors.back() * divisors.back() == copy)
		{
			--i;
		}

		for (; i >= 0; --i)
		{
			divisors.push_back(copy / divisors[i]);
		}

		return divisors;
	}
}
