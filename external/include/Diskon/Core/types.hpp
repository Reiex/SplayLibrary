#pragma once

#include <algorithm>
#include <array>
#include <bit>
#include <cassert>
#include <cctype>
#include <concepts>
#include <cstdint>
#include <deque>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <optional>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace dsk
{
	template<uint8_t BitSize, typename TInt> class BaseInt;
	template<uint8_t BitSize> class SignedInt;
	template<uint8_t BitSize> class UnsignedInt;

	template<uint8_t ExpSize, uint8_t MantissaSize> class Float;
	using Half = Float<5, 10>;


	namespace huffman
	{
		enum class NodeType;
		class Node;
	}
	class HuffmanTree;
}
