///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2019-2022
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <DejaVu/Core/Core.hpp>

namespace djv
{
	namespace proc
	{
		template<typename T> concept ProcessiblePixel = PixelConcept<T> && std::floating_point<typename T::ComponentType>;
	}
}

#pragma region djvPixelMacros

#define DJV_PROC_PIXEL_RIGHT(BBehaviour, it, itRight, width, height, preWidth, preHeight, i, j)	\
if (i == 0)																						\
{																								\
	itRight = it + 1;																			\
}																								\
else if (i < preWidth)																			\
{																								\
	++itRight;																					\
}																								\
else																							\
{																								\
	if constexpr (BBehaviour == scp::BorderBehaviour::Zero)										\
	{																							\
		itRight = &colors::black<typename TPixel::componentCount, TPixel::componentCount>;		\
	}																							\
	else if constexpr (BBehaviour == scp::BorderBehaviour::Continuous)							\
	{																							\
		itRight = it;																			\
	}																							\
	else if constexpr (BBehaviour == scp::BorderBehaviour::Periodic)							\
	{																							\
		itRight = it - preWidth;																\
	}																							\
}

#define DJV_PROC_PIXEL_LEFT(BBehaviour, it, itLeft, width, height, preWidth, preHeight, i, j)	\
if (i > 1)																						\
{																								\
	++itLeft;																					\
}																								\
else if (i == 1)																				\
{																								\
	itLeft = it - 1;																			\
}																								\
else																							\
{																								\
	if constexpr (BBehaviour == scp::BorderBehaviour::Zero)										\
	{																							\
		itLeft = &colors::black<typename TPixel::componentCount, TPixel::componentCount>;		\
	}																							\
	else if constexpr (BBehaviour == scp::BorderBehaviour::Continuous)							\
	{																							\
		itLeft = it;																			\
	}																							\
	else if constexpr (BBehaviour == scp::BorderBehaviour::Periodic)							\
	{																							\
		itLeft = it + preWidth;																	\
	}																							\
}

#define DJV_PROC_PIXEL_DOWN(BBehaviour, it, itDown, width, height, preWidth, preHeight, i, j)		\
if (i == 0 && j == 0)																				\
{																									\
	itDown = it + width;																			\
}																									\
else if (j < preHeight || (j == preHeight && i != 0 && BBehaviour != scp::BorderBehaviour::Zero))	\
{																									\
	++itDown;																						\
}																									\
else if (i == 0 && j == preHeight)																	\
{																									\
	if constexpr (BBehaviour == scp::BorderBehaviour::Zero)											\
	{																								\
		itDown = &colors::black<typename TPixel::componentCount, TPixel::componentCount>;			\
	}																								\
	else if constexpr (BBehaviour == scp::BorderBehaviour::Continuous)								\
	{																								\
		itDown = it;																				\
	}																								\
	else if constexpr (BBehaviour == scp::BorderBehaviour::Periodic)								\
	{																								\
		itDown = it - preHeight * width;															\
	}																								\
}

#define DJV_PROC_PIXEL_UP(BBehaviour, it, itUp, width, height, preWidth, preHeight, i, j)				\
if (j > 1 || (j == 1 && i != 0) || ((i != 0 || j != 0) && BBehaviour != scp::BorderBehaviour::Zero))	\
{																										\
	++itUp;																								\
}																										\
else if (i == 0 && j == 0)																				\
{																										\
	if constexpr (BBehaviour == scp::BorderBehaviour::Zero)												\
	{																									\
		itUp = &colors::black<typename TPixel::componentCount, TPixel::componentCount>;					\
	}																									\
	else if constexpr (BBehaviour == scp::BorderBehaviour::Continuous)									\
	{																									\
		itUp = it;																						\
	}																									\
	else if constexpr (BBehaviour == scp::BorderBehaviour::Periodic)									\
	{																									\
		itUp = it + preHeight * width;																	\
	}																									\
}

#define DJV_PROC_PIXEL_RIGHT_DOWN(BBehaviour, it, itRightDown, width, height, preWidth, preHeight, i, j)	\
if (i == 0)																									\
{																											\
	if (j == preHeight)																						\
	{																										\
		if constexpr (BBehaviour == scp::BorderBehaviour::Zero)												\
		{																									\
			itRightDown = &colors::black<typename TPixel::componentCount, TPixel::componentCount>;			\
		}																									\
		else if constexpr (BBehaviour == scp::BorderBehaviour::Continuous)									\
		{																									\
			itRightDown = it + 1;																			\
		}																									\
		else if constexpr (BBehaviour == scp::BorderBehaviour::Periodic)									\
		{																									\
			itRightDown = it - preHeight * width + 1;														\
		}																									\
	}																										\
	else																									\
	{																										\
		itRightDown = it + width + 1;																		\
	}																										\
}																											\
else if (i < preWidth)																						\
{																											\
	if constexpr (BBehaviour == scp::BorderBehaviour::Zero)													\
	{																										\
		if (j < preHeight)																					\
		{																									\
			++itRightDown;																					\
		}																									\
	}																										\
	else																									\
	{																										\
		++itRightDown;																						\
	}																										\
}																											\
else																										\
{																											\
	if constexpr (BBehaviour == scp::BorderBehaviour::Zero)													\
	{																										\
		/* Nothing */																						\
	}																										\
	else if constexpr (BBehaviour == scp::BorderBehaviour::Continuous)										\
	{																										\
		if (j == preHeight)																					\
		{																									\
			itRightDown = it;																				\
		}																									\
		else																								\
		{																									\
			itRightDown = it + width;																		\
		}																									\
	}																										\
	else if constexpr (BBehaviour == scp::BorderBehaviour::Periodic)										\
	{																										\
		if (j == preHeight)																					\
		{																									\
			itRightDown = it - width * height + 1;															\
		}																									\
		else																								\
		{																									\
			itRightDown = it + 1;																			\
		}																									\
	}																										\
}

#define DJV_PROC_PIXEL_LEFT_DOWN(BBehaviour, it, itLeftDown, width, height, preWidth, preHeight, i, j)	\
if (i > 1)																								\
{																										\
	if constexpr (BBehaviour == scp::BorderBehaviour::Zero)												\
	{																									\
		if (j != preHeight)																				\
		{																								\
			++itLeftDown;																				\
		}																								\
	}																									\
	else																								\
	{																									\
		++itLeftDown;																					\
	}																									\
}																										\
else if (i == 1)																						\
{																										\
	if (j == preHeight)																					\
	{																									\
		if constexpr (BBehaviour == scp::BorderBehaviour::Zero)											\
		{																								\
			/* Nothing */																				\
		}																								\
		else if constexpr (BBehaviour == scp::BorderBehaviour::Continuous)								\
		{																								\
			itLeftDown = it - 1;																		\
		}																								\
		else if constexpr (BBehaviour == scp::BorderBehaviour::Periodic)								\
		{																								\
			itLeftDown = it - preHeight * width - 1;													\
		}																								\
	}																									\
	else																								\
	{																									\
		itLeftDown = it + preWidth;																		\
	}																									\
}																										\
else																									\
{																										\
	if constexpr (BBehaviour == scp::BorderBehaviour::Zero)												\
	{																									\
		itLeftDown = &colors::black<typename TPixel::componentCount, TPixel::componentCount>;			\
	}																									\
	else if constexpr (BBehaviour == scp::BorderBehaviour::Continuous)									\
	{																									\
		if (j == preHeight)																				\
		{																								\
			itLeftDown = it;																			\
		}																								\
		else																							\
		{																								\
			itLeftDown = it + width;																	\
		}																								\
	}																									\
	else if constexpr (BBehaviour == scp::BorderBehaviour::Periodic)									\
	{																									\
		if (j == preHeight)																				\
		{																								\
			itLeftDown = it - preHeight * width + preWidth;												\
		}																								\
		else																							\
		{																								\
			itLeftDown = it + width + preWidth;															\
		}																								\
	}																									\
}

#define DJV_PROC_PIXEL_RIGHT_UP(BBehaviour, it, itRightUp, width, height, preWidth, preHeight, i, j)	\
if (i == 0)																								\
{																										\
	if (j == 0)																							\
	{																									\
		if constexpr (BBehaviour == scp::BorderBehaviour::Zero)											\
		{																								\
			itRightUp = &colors::black<typename TPixel::componentCount, TPixel::componentCount>;		\
		}																								\
		else if constexpr (BBehaviour == scp::BorderBehaviour::Continuous)								\
		{																								\
			itRightUp = it + 1;																			\
		}																								\
		else if constexpr (BBehaviour == scp::BorderBehaviour::Periodic)								\
		{																								\
			itRightUp = it + preHeight * width + 1;														\
		}																								\
	}																									\
	else																								\
	{																									\
		itRightUp = it - width + 1;																		\
	}																									\
}																										\
else if (i < preWidth)																					\
{																										\
	if constexpr (BBehaviour == scp::BorderBehaviour::Zero)												\
	{																									\
		if (j != 0)																						\
		{																								\
			++itRightUp;																				\
		}																								\
	}																									\
	else																								\
	{																									\
		++itRightUp;																					\
	}																									\
}																										\
else																									\
{																										\
	if constexpr (BBehaviour == scp::BorderBehaviour::Zero)												\
	{																									\
		itRightUp = &colors::black<typename TPixel::componentCount, TPixel::componentCount>;			\
	}																									\
	else if constexpr (BBehaviour == scp::BorderBehaviour::Continuous)									\
	{																									\
		if (j == 0)																						\
		{																								\
			itRightUp = it;																				\
		}																								\
		else																							\
		{																								\
			itRightUp = it - width;																		\
		}																								\
	}																									\
	else if constexpr (BBehaviour == scp::BorderBehaviour::Periodic)									\
	{																									\
		if (j == 0)																						\
		{																								\
			itRightUp = it + preHeight * width - preWidth;												\
		}																								\
		else																							\
		{																								\
			itRightUp = it - width - preWidth;															\
		}																								\
	}																									\
}

#define DJV_PROC_PIXEL_LEFT_UP(BBehaviour, it, itLeftUp, width, height, preWidth, preHeight, i, j)	\
if (i > 1)																							\
{																									\
	if constexpr (BBehaviour == scp::BorderBehaviour::Zero)											\
	{																								\
		if (j != 0)																					\
		{																							\
			++itLeftUp;																				\
		}																							\
	}																								\
	else																							\
	{																								\
		++itLeftUp;																					\
	}																								\
}																									\
else if (i == 1)																					\
{																									\
	if (j == 0)																						\
	{																								\
		if constexpr (BBehaviour == scp::BorderBehaviour::Zero)										\
		{																							\
			/* Nothing */																			\
		}																							\
		else if constexpr (BBehaviour == scp::BorderBehaviour::Continuous)							\
		{																							\
			itLeftUp = it - 1;																		\
		}																							\
		else if constexpr (BBehaviour == scp::BorderBehaviour::Periodic)							\
		{																							\
			itLeftUp = it - 1 + preHeight * width;													\
		}																							\
	}																								\
	else																							\
	{																								\
		itLeftUp = it - width - 1;																	\
	}																								\
}																									\
else																								\
{																									\
	if constexpr (BBehaviour == scp::BorderBehaviour::Zero)											\
	{																								\
		itLeftUp = &colors::black<typename TPixel::componentCount, TPixel::componentCount>;			\
	}																								\
	else if constexpr (BBehaviour == scp::BorderBehaviour::Continuous)								\
	{																								\
		if (j == 0)																					\
		{																							\
			itLeftUp = it;																			\
		}																							\
		else																						\
		{																							\
			itLeftUp = it - width;																	\
		}																							\
	}																								\
	else if constexpr (BBehaviour == scp::BorderBehaviour::Periodic)								\
	{																								\
		if (j == 0)																					\
		{																							\
			itLeftUp = it + width * height - 1;														\
		}																							\
		else																						\
		{																							\
			itLeftUp = it - 1;																		\
		}																							\
	}																								\
}

#pragma endregion
