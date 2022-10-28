#pragma once

#include <DejaVu/ImageProcessing/Misc.hpp>

namespace djv
{
	namespace proc
	{
		template<DifferenceMethod DMethod, bool Normalized, scp::BorderBehaviour BBehaviour, ProcessiblePixel TPixel>
		constexpr void differenceX(const Image<TPixel>& image, Image<TPixel>& result)
		{
			assert(image.getWidth() == result.getWidth());
			assert(image.getHeight() == result.getHeight());
			assert(image.getWidth() >= 2 && image.getHeight() >= 2);

			const uint64_t width = image.getWidth();
			const uint64_t height = image.getHeight();
			const uint64_t preWidth = width - 1;
			const uint64_t preHeight = height - 1;

			TPixel* itResult = result.begin();
			const TPixel* it = image.begin();

			if constexpr (DMethod == DifferenceMethod::Naive)
			{
				const TPixel* itRight = nullptr;

				for (uint64_t j = 0; j < height; ++j)
				{
					for (uint64_t i = 0; i < width; ++i, ++it, ++itResult)
					{
						DJV_PROC_PIXEL_RIGHT(BBehaviour, it, itRight, width, height, preWidth, preHeight, i, j);

						if constexpr (Normalized)
						{
							*itResult = (*itRight - *it) / 2;
						}
						else
						{
							*itResult = *itRight - *it;
						}
					}
				}
			}
			else if constexpr (DMethod == DifferenceMethod::Leap)
			{
				const TPixel* itLeft = nullptr;
				const TPixel* itRight = nullptr;

				for (uint64_t j = 0; j < height; ++j)
				{
					for (uint64_t i = 0; i < width; ++i, ++it, ++itResult)
					{
						DJV_PROC_PIXEL_LEFT(BBehaviour, it, itLeft, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_RIGHT(BBehaviour, it, itRight, width, height, preWidth, preHeight, i, j);

						if constexpr (Normalized)
						{
							*itResult = (*itRight - *itLeft) / 2;
						}
						else
						{
							*itResult = *itRight - *itLeft;
						}
					}
				}
			}
			else if constexpr (DMethod == DifferenceMethod::Prewitt)
			{
				const TPixel* itLeftUp = nullptr;
				const TPixel* itLeft = nullptr;
				const TPixel* itLeftDown = nullptr;
				const TPixel* itRightUp = nullptr;
				const TPixel* itRight = nullptr;
				const TPixel* itRightDown = nullptr;

				for (uint64_t j = 0; j < height; ++j)
				{
					for (uint64_t i = 0; i < width; ++i, ++it, ++itResult)
					{
						DJV_PROC_PIXEL_LEFT_UP(BBehaviour, it, itLeftUp, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_LEFT(BBehaviour, it, itLeft, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_LEFT_DOWN(BBehaviour, it, itLeftDown, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_RIGHT_UP(BBehaviour, it, itRightUp, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_RIGHT(BBehaviour, it, itRight, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_RIGHT_DOWN(BBehaviour, it, itRightDown, width, height, preWidth, preHeight, i, j);

						if constexpr (Normalized)
						{
							*itResult = (*itRightUp + *itRight + *itRightDown - *itLeftUp - *itLeft - *itLeftDown) / 6;
						}
						else
						{
							*itResult = *itRightUp + *itRight + *itRightDown - *itLeftUp - *itLeft - *itLeftDown;
						}
					}
				}
			}
			else if constexpr (DMethod == DifferenceMethod::Sobel)
			{
				const TPixel* itLeftUp = nullptr;
				const TPixel* itLeft = nullptr;
				const TPixel* itLeftDown = nullptr;
				const TPixel* itRightUp = nullptr;
				const TPixel* itRight = nullptr;
				const TPixel* itRightDown = nullptr;

				for (uint64_t j = 0; j < height; ++j)
				{
					for (uint64_t i = 0; i < width; ++i, ++it, ++itResult)
					{
						DJV_PROC_PIXEL_LEFT_UP(BBehaviour, it, itLeftUp, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_LEFT(BBehaviour, it, itLeft, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_LEFT_DOWN(BBehaviour, it, itLeftDown, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_RIGHT_UP(BBehaviour, it, itRightUp, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_RIGHT(BBehaviour, it, itRight, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_RIGHT_DOWN(BBehaviour, it, itRightDown, width, height, preWidth, preHeight, i, j);

						if constexpr (Normalized)
						{
							*itResult = (*itRightUp + *itRight * 2 + *itRightDown - *itLeftUp - *itLeft * 2 - *itLeftDown) / 8;
						}
						else
						{
							*itResult = *itRightUp + *itRight * 2 + *itRightDown - *itLeftUp - *itLeft * 2 - *itLeftDown;
						}
					}
				}
			}
		}

		template<DifferenceMethod DMethod, bool Normalized, scp::BorderBehaviour BBehaviour, ProcessiblePixel TPixel>
		constexpr void differenceY(const Image<TPixel>& image, Image<TPixel>& result)
		{
			assert(image.getWidth() == result.getWidth());
			assert(image.getHeight() == result.getHeight());
			assert(image.getWidth() >= 2 && image.getHeight() >= 2);

			const uint64_t width = image.getWidth();
			const uint64_t height = image.getHeight();
			const uint64_t preWidth = width - 1;
			const uint64_t preHeight = height - 1;

			TPixel* itResult = result.begin();
			const TPixel* it = image.begin();

			if constexpr (DMethod == DifferenceMethod::Naive)
			{
				const TPixel* itDown = nullptr;

				for (uint64_t j = 0; j < height; ++j)
				{
					for (uint64_t i = 0; i < width; ++i, ++it, ++itResult)
					{
						DJV_PROC_PIXEL_DOWN(BBehaviour, it, itDown, width, height, preWidth, preHeight, i, j);

						if constexpr (Normalized)
						{
							*itResult = (*itDown - *it) / 2;
						}
						else
						{
							*itResult = *itDown - *it;
						}
					}
				}
			}
			else if constexpr (DMethod == DifferenceMethod::Leap)
			{
				const TPixel* itUp = nullptr;
				const TPixel* itDown = nullptr;

				for (uint64_t j = 0; j < height; ++j)
				{
					for (uint64_t i = 0; i < width; ++i, ++it, ++itResult)
					{
						DJV_PROC_PIXEL_UP(BBehaviour, it, itUp, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_DOWN(BBehaviour, it, itDown, width, height, preWidth, preHeight, i, j);

						if constexpr (Normalized)
						{
							*itResult = (*itDown - *itUp) / 2;
						}
						else
						{
							*itResult = *itDown - *itUp;
						}
					}
				}
			}
			else if constexpr (DMethod == DifferenceMethod::Prewitt)
			{
				const TPixel* itLeftUp = nullptr;
				const TPixel* itUp = nullptr;
				const TPixel* itRightUp = nullptr;
				const TPixel* itLeftDown = nullptr;
				const TPixel* itDown = nullptr;
				const TPixel* itRightDown = nullptr;

				for (uint64_t j = 0; j < height; ++j)
				{
					for (uint64_t i = 0; i < width; ++i, ++it, ++itResult)
					{
						DJV_PROC_PIXEL_LEFT_UP(BBehaviour, it, itLeftUp, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_UP(BBehaviour, it, itUp, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_RIGHT_UP(BBehaviour, it, itRightUp, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_LEFT_DOWN(BBehaviour, it, itLeftDown, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_DOWN(BBehaviour, it, itDown, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_RIGHT_DOWN(BBehaviour, it, itRightDown, width, height, preWidth, preHeight, i, j);

						if constexpr (Normalized)
						{
							*itResult = (*itLeftUp + *itUp + *itRightUp - *itLeftDown - *itDown - *itRightDown) / 6;
						}
						else
						{
							*itResult = *itLeftUp + *itUp + *itRightUp - *itLeftDown - *itDown - *itRightDown;
						}
					}
				}
			}
			else if constexpr (DMethod == DifferenceMethod::Sobel)
			{
				const TPixel* itLeftUp = nullptr;
				const TPixel* itUp = nullptr;
				const TPixel* itRightUp = nullptr;
				const TPixel* itLeftDown = nullptr;
				const TPixel* itDown = nullptr;
				const TPixel* itRightDown = nullptr;

				for (uint64_t j = 0; j < height; ++j)
				{
					for (uint64_t i = 0; i < width; ++i, ++it, ++itResult)
					{
						DJV_PROC_PIXEL_LEFT_UP(BBehaviour, it, itLeftUp, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_UP(BBehaviour, it, itUp, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_RIGHT_UP(BBehaviour, it, itRightUp, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_LEFT_DOWN(BBehaviour, it, itLeftDown, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_DOWN(BBehaviour, it, itDown, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_RIGHT_DOWN(BBehaviour, it, itRightDown, width, height, preWidth, preHeight, i, j);

						if constexpr (Normalized)
						{
							*itResult = (*itLeftUp + *itUp * 2 + *itRightUp - *itLeftDown - *itDown * 2 - *itRightDown) / 8;
						}
						else
						{
							*itResult = *itLeftUp + *itUp * 2 + *itRightUp - *itLeftDown - *itDown * 2 - *itRightDown;
						}
					}
				}
			}
		}

		template<DifferenceMethod DMethod, bool Normalized, scp::BorderBehaviour BBehaviour, ProcessiblePixel TPixel>
		constexpr void differenceXX(const Image<TPixel>& image, Image<TPixel>& result)
		{
			assert(image.getWidth() == result.getWidth());
			assert(image.getHeight() == result.getHeight());
			assert(image.getWidth() >= 2 && image.getHeight() >= 2);

			const uint64_t width = image.getWidth();
			const uint64_t height = image.getHeight();
			const uint64_t preWidth = width - 1;
			const uint64_t preHeight = height - 1;

			TPixel* itResult = result.begin();
			const TPixel* it = image.begin();

			if constexpr (DMethod == DifferenceMethod::Naive)
			{
				const TPixel* itLeft = nullptr;
				const TPixel* itRight = nullptr;

				for (uint64_t j = 0; j < height; ++j)
				{
					for (uint64_t i = 0; i < width; ++i, ++it, ++itResult)
					{
						DJV_PROC_PIXEL_LEFT(BBehaviour, it, itLeft, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_RIGHT(BBehaviour, it, itRight, width, height, preWidth, preHeight, i, j);

						if constexpr (Normalized)
						{
							*itResult = (*itRight - *it * 2 + *itLeft) / 4;
						}
						else
						{
							*itResult = *itRight - *it * 2 + *itLeft;
						}
					}
				}
			}
			else if constexpr (DMethod == DifferenceMethod::Leap)
			{
				assert(false);
			}
			else if constexpr (DMethod == DifferenceMethod::Prewitt)
			{
				const TPixel* itUp = nullptr;
				const TPixel* itLeftUp = nullptr;
				const TPixel* itLeft = nullptr;
				const TPixel* itLeftDown = nullptr;
				const TPixel* itRightUp = nullptr;
				const TPixel* itRight = nullptr;
				const TPixel* itRightDown = nullptr;
				const TPixel* itDown = nullptr;

				for (uint64_t j = 0; j < height; ++j)
				{
					for (uint64_t i = 0; i < width; ++i, ++it, ++itResult)
					{
						DJV_PROC_PIXEL_UP(BBehaviour, it, itUp, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_LEFT_UP(BBehaviour, it, itLeftUp, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_LEFT(BBehaviour, it, itLeft, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_LEFT_DOWN(BBehaviour, it, itLeftDown, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_RIGHT_UP(BBehaviour, it, itRightUp, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_RIGHT(BBehaviour, it, itRight, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_RIGHT_DOWN(BBehaviour, it, itRightDown, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_DOWN(BBehaviour, it, itDown, width, height, preWidth, preHeight, i, j);

						if constexpr (Normalized)
						{
							*itResult = (*itLeftUp + *itLeft + *itLeftDown - (*itUp + *it + *itDown) * 2 + *itRightUp + *itRight + *itRightDown) / 12;
						}
						else
						{
							*itResult = *itLeftUp + *itLeft + *itLeftDown - (*itUp + *it + *itDown) * 2 + *itRightUp + *itRight + *itRightDown;
						}
					}
				}
			}
			else if constexpr (DMethod == DifferenceMethod::Sobel)
			{
				const TPixel* itUp = nullptr;
				const TPixel* itLeftUp = nullptr;
				const TPixel* itLeft = nullptr;
				const TPixel* itLeftDown = nullptr;
				const TPixel* itRightUp = nullptr;
				const TPixel* itRight = nullptr;
				const TPixel* itRightDown = nullptr;
				const TPixel* itDown = nullptr;

				for (uint64_t j = 0; j < height; ++j)
				{
					for (uint64_t i = 0; i < width; ++i, ++it, ++itResult)
					{
						DJV_PROC_PIXEL_UP(BBehaviour, it, itUp, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_LEFT_UP(BBehaviour, it, itLeftUp, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_LEFT(BBehaviour, it, itLeft, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_LEFT_DOWN(BBehaviour, it, itLeftDown, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_RIGHT_UP(BBehaviour, it, itRightUp, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_RIGHT(BBehaviour, it, itRight, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_RIGHT_DOWN(BBehaviour, it, itRightDown, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_DOWN(BBehaviour, it, itDown, width, height, preWidth, preHeight, i, j);

						if constexpr (Normalized)
						{
							*itResult = (*itLeftUp + *itLeftDown + *itRightUp + *itRightDown + (*itLeft + *itRight - *itUp - *itDown - *it * 2) * 2) / 16;
						}
						else
						{
							*itResult = *itLeftUp + *itLeftDown + *itRightUp + *itRightDown + (*itLeft + *itRight - *itUp - *itDown - *it * 2) * 2;
						}
					}
				}
			}
		}

		template<DifferenceMethod DMethod, bool Normalized, scp::BorderBehaviour BBehaviour, ProcessiblePixel TPixel>
		constexpr void differenceXY(const Image<TPixel>& image, Image<TPixel>& result)
		{
			assert(image.getWidth() == result.getWidth());
			assert(image.getHeight() == result.getHeight());
			assert(image.getWidth() >= 2 && image.getHeight() >= 2);

			const uint64_t width = image.getWidth();
			const uint64_t height = image.getHeight();
			const uint64_t preWidth = width - 1;
			const uint64_t preHeight = height - 1;

			TPixel* itResult = result.begin();
			const TPixel* it = image.begin();

			if constexpr (DMethod == DifferenceMethod::Naive)
			{
				const TPixel* itRight = nullptr;
				const TPixel* itDownRight = nullptr;
				const TPixel* itDown = nullptr;

				for (uint64_t j = 0; j < height; ++j)
				{
					for (uint64_t i = 0; i < width; ++i, ++it, ++itResult)
					{
						DJV_PROC_PIXEL_RIGHT(BBehaviour, it, itRight, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_RIGHT_DOWN(BBehaviour, it, itDownRight, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_DOWN(BBehaviour, it, itDown, width, height, preWidth, preHeight, i, j);

						if constexpr (Normalized)
						{
							*itResult = (*it + *itDownRight - *itRight - *itDown) / 4;
						}
						else
						{
							*itResult = *it + *itDownRight - *itRight - *itDown;
						}
					}
				}
			}
			else if constexpr (DMethod == DifferenceMethod::Leap)
			{
				const TPixel* itLeftUp = nullptr;
				const TPixel* itRightUp = nullptr;
				const TPixel* itLeftDown = nullptr;
				const TPixel* itRightDown = nullptr;

				for (uint64_t j = 0; j < height; ++j)
				{
					for (uint64_t i = 0; i < width; ++i, ++it, ++itResult)
					{
						DJV_PROC_PIXEL_LEFT_UP(BBehaviour, it, itLeftUp, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_RIGHT_UP(BBehaviour, it, itRightUp, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_LEFT_DOWN(BBehaviour, it, itLeftDown, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_RIGHT_DOWN(BBehaviour, it, itRightDown, width, height, preWidth, preHeight, i, j);

						if constexpr (Normalized)
						{
							*itResult = (*itLeftUp + *itRightDown - *itRightUp - *itLeftDown) / 4;
						}
						else
						{
							*itResult = *itLeftUp + *itRightDown - *itRightUp - *itLeftDown;
						}
					}
				}
			}
			else if constexpr (DMethod == DifferenceMethod::Prewitt)
			{
				assert(false);
			}
			else if constexpr (DMethod == DifferenceMethod::Sobel)
			{
				assert(false);
			}
		}

		template<DifferenceMethod DMethod, bool Normalized, scp::BorderBehaviour BBehaviour, ProcessiblePixel TPixel>
		constexpr void differenceYY(const Image<TPixel>& image, Image<TPixel>& result)
		{
			assert(image.getWidth() == result.getWidth());
			assert(image.getHeight() == result.getHeight());
			assert(image.getWidth() >= 2 && image.getHeight() >= 2);

			const uint64_t width = image.getWidth();
			const uint64_t height = image.getHeight();
			const uint64_t preWidth = width - 1;
			const uint64_t preHeight = height - 1;

			TPixel* itResult = result.begin();
			const TPixel* it = image.begin();

			if constexpr (DMethod == DifferenceMethod::Naive)
			{
				const TPixel* itUp = nullptr;
				const TPixel* itDown = nullptr;

				for (uint64_t j = 0; j < height; ++j)
				{
					for (uint64_t i = 0; i < width; ++i, ++it, ++itResult)
					{
						DJV_PROC_PIXEL_UP(BBehaviour, it, itUp, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_DOWN(BBehaviour, it, itDown, width, height, preWidth, preHeight, i, j);

						if constexpr (Normalized)
						{
							*itResult = (*itDown - *it * 2 + *itUp) / 4;
						}
						else
						{
							*itResult = *itDown - *it * 2 + *itUp;
						}
					}
				}
			}
			else if constexpr (DMethod == DifferenceMethod::Leap)
			{
				assert(false);
			}
			else if constexpr (DMethod == DifferenceMethod::Prewitt)
			{
				const TPixel* itUp = nullptr;
				const TPixel* itLeftUp = nullptr;
				const TPixel* itLeft = nullptr;
				const TPixel* itLeftDown = nullptr;
				const TPixel* itRightUp = nullptr;
				const TPixel* itRight = nullptr;
				const TPixel* itRightDown = nullptr;
				const TPixel* itDown = nullptr;

				for (uint64_t j = 0; j < height; ++j)
				{
					for (uint64_t i = 0; i < width; ++i, ++it, ++itResult)
					{
						DJV_PROC_PIXEL_UP(BBehaviour, it, itUp, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_LEFT_UP(BBehaviour, it, itLeftUp, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_LEFT(BBehaviour, it, itLeft, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_LEFT_DOWN(BBehaviour, it, itLeftDown, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_RIGHT_UP(BBehaviour, it, itRightUp, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_RIGHT(BBehaviour, it, itRight, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_RIGHT_DOWN(BBehaviour, it, itRightDown, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_DOWN(BBehaviour, it, itDown, width, height, preWidth, preHeight, i, j);

						if constexpr (Normalized)
						{
							*itResult = (*itLeftUp + *itUp + *itRightUp - (*itLeft + *it + *itRight) * 2 + *itLeftDown + *itDown + *itRightDown) / 12;
						}
						else
						{
							*itResult = *itLeftUp + *itUp + *itRightUp - (*itLeft + *it + *itRight) * 2 + *itLeftDown + *itDown + *itRightDown;
						}
					}
				}
			}
			else if constexpr (DMethod == DifferenceMethod::Sobel)
			{
				const TPixel* itUp = nullptr;
				const TPixel* itLeftUp = nullptr;
				const TPixel* itLeft = nullptr;
				const TPixel* itLeftDown = nullptr;
				const TPixel* itRightUp = nullptr;
				const TPixel* itRight = nullptr;
				const TPixel* itRightDown = nullptr;
				const TPixel* itDown = nullptr;

				for (uint64_t j = 0; j < height; ++j)
				{
					for (uint64_t i = 0; i < width; ++i, ++it, ++itResult)
					{
						DJV_PROC_PIXEL_UP(BBehaviour, it, itUp, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_LEFT_UP(BBehaviour, it, itLeftUp, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_LEFT(BBehaviour, it, itLeft, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_LEFT_DOWN(BBehaviour, it, itLeftDown, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_RIGHT_UP(BBehaviour, it, itRightUp, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_RIGHT(BBehaviour, it, itRight, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_RIGHT_DOWN(BBehaviour, it, itRightDown, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_DOWN(BBehaviour, it, itDown, width, height, preWidth, preHeight, i, j);

						if constexpr (Normalized)
						{
							*itResult = (*itLeftUp + *itRightUp + *itLeftDown + *itRightDown + (*itUp + *itDown - *itLeft - *itRight - *it * 2) * 2) / 16;
						}
						else
						{
							*itResult = *itLeftUp + *itRightUp + *itLeftDown + *itRightDown + (*itUp + *itDown - *itLeft - *itRight - *it * 2) * 2;
						}
					}
				}
			}
		}

		template<LaplacianMethod LMethod, bool Normalized, scp::BorderBehaviour BBehaviour, ProcessiblePixel TPixel>
		constexpr void laplacian(const Image<TPixel>& image, Image<TPixel>& result)
		{
			assert(image.getWidth() == result.getWidth());
			assert(image.getHeight() == result.getHeight());
			assert(image.getWidth() >= 2 && image.getHeight() >= 2);

			const uint64_t width = image.getWidth();
			const uint64_t height = image.getHeight();
			const uint64_t preWidth = width - 1;
			const uint64_t preHeight = height - 1;

			TPixel* itResult = result.begin();
			const TPixel* it = image.begin();

			if constexpr (LMethod == LaplacianMethod::Naive)
			{
				const TPixel* itUp = nullptr;
				const TPixel* itDown = nullptr;
				const TPixel* itLeft = nullptr;
				const TPixel* itRight = nullptr;

				for (uint64_t j = 0; j < height; ++j)
				{
					for (uint64_t i = 0; i < width; ++i, ++it, ++itResult)
					{
						DJV_PROC_PIXEL_UP(BBehaviour, it, itUp, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_DOWN(BBehaviour, it, itDown, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_LEFT(BBehaviour, it, itLeft, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_RIGHT(BBehaviour, it, itRight, width, height, preWidth, preHeight, i, j);

						if constexpr (Normalized)
						{
							*itResult = (*itUp + *itDown + *itLeft + *itRight - *it * 4) / 8;
						}
						else
						{
							*itResult = *itUp + *itDown + *itLeft + *itRight - *it * 4;
						}
					}
				}
			}
			else if constexpr (LMethod == LaplacianMethod::Diagonals)
			{
				const TPixel* itUp = nullptr;
				const TPixel* itLeftUp = nullptr;
				const TPixel* itLeft = nullptr;
				const TPixel* itLeftDown = nullptr;
				const TPixel* itRightUp = nullptr;
				const TPixel* itRight = nullptr;
				const TPixel* itRightDown = nullptr;
				const TPixel* itDown = nullptr;

				for (uint64_t j = 0; j < height; ++j)
				{
					for (uint64_t i = 0; i < width; ++i, ++it, ++itResult)
					{
						DJV_PROC_PIXEL_UP(BBehaviour, it, itUp, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_LEFT_UP(BBehaviour, it, itLeftUp, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_LEFT(BBehaviour, it, itLeft, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_LEFT_DOWN(BBehaviour, it, itLeftDown, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_RIGHT_UP(BBehaviour, it, itRightUp, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_RIGHT(BBehaviour, it, itRight, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_RIGHT_DOWN(BBehaviour, it, itRightDown, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_DOWN(BBehaviour, it, itDown, width, height, preWidth, preHeight, i, j);

						if constexpr (Normalized)
						{
							*itResult = (*itLeftUp + *itUp + *itRightUp + *itLeft + *itRight + *itLeftDown + *itDown + *itRightDown - *it * 8) / 16;
						}
						else
						{
							*itResult = *itLeftUp + *itUp + *itRightUp + *itLeft + *itRight + *itLeftDown + *itDown + *itRightDown - *it * 8;
						}
					}
				}
			}
			else if constexpr (LMethod == LaplacianMethod::DiagonalsCorrected)
			{
				const TPixel* itUp = nullptr;
				const TPixel* itLeftUp = nullptr;
				const TPixel* itLeft = nullptr;
				const TPixel* itLeftDown = nullptr;
				const TPixel* itRightUp = nullptr;
				const TPixel* itRight = nullptr;
				const TPixel* itRightDown = nullptr;
				const TPixel* itDown = nullptr;

				constexpr double centerCoeff = -4 * (1 + std::numbers::sqrt2);
				constexpr double normalCoeff = 8 * (1 + std::numbers::sqrt2);

				for (uint64_t j = 0; j < height; ++j)
				{
					for (uint64_t i = 0; i < width; ++i, ++it, ++itResult)
					{
						DJV_PROC_PIXEL_UP(BBehaviour, it, itUp, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_LEFT_UP(BBehaviour, it, itLeftUp, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_LEFT(BBehaviour, it, itLeft, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_LEFT_DOWN(BBehaviour, it, itLeftDown, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_RIGHT_UP(BBehaviour, it, itRightUp, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_RIGHT(BBehaviour, it, itRight, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_RIGHT_DOWN(BBehaviour, it, itRightDown, width, height, preWidth, preHeight, i, j);
						DJV_PROC_PIXEL_DOWN(BBehaviour, it, itDown, width, height, preWidth, preHeight, i, j);

						if constexpr (Normalized)
						{
							*itResult = (*itLeftUp + *itRightUp + *itLeftDown + *itRightDown + (*itUp + *itDown + *itLeft + *itRight) * std::numbers::sqrt2 + *it * centerCoeff) / normalCoeff;
						}
						else
						{
							*itResult = *itLeftUp + *itRightUp + *itLeftDown + *itRightDown + (*itUp + *itDown + *itLeft + *itRight) * std::numbers::sqrt2 + *it * centerCoeff;
						}
					}
				}
			}
		}


		template<scp::BorderBehaviour BBehaviour, PixelConcept TPixel>
		constexpr void blurGaussian(const Image<TPixel>& image, Image<TPixel>& result, float sigma)
		{
			assert(image.getWidth() == result.getWidth());
			assert(image.getHeight() == result.getHeight());

			const uint64_t width = image.getWidth();
			const uint64_t height = image.getHeight();
			const int64_t r = sigma * 2.57;
			const uint64_t d = 2 * r + 1;

			const scp::Tensor<TPixel>* tensor = scp::Tensor<TPixel>::createAroundMemory({ height, width }, const_cast<TPixel*>(image.getData()));
			TPixel* itResult = result.begin();

			const float gaussianFactor = 1 / std::sqrt(2 * std::numbers::pi * sigma * sigma);
			float* weights = reinterpret_cast<float*>(alloca(sizeof(float) * d));
			for (int64_t i = 0, x = -r; i < d; ++i, ++x)
			{
				float ratio = x / sigma;
				weights[i] = std::exp(-ratio * ratio / 2) * gaussianFactor;
			}

			double acc[TPixel::componentCount];

			for (int64_t j = 0; j < height; ++j)
			{
				for (int64_t i = 0; i < width; ++i, ++itResult)
				{
					std::fill_n(acc, TPixel::componentCount, 0.0);
					for (int64_t p = 0, x = i - r; p < d; ++p, ++x)
					{
						const TPixel& pixel = tensor->getOutOfBound<BBehaviour>({ j, x });
						for (uint8_t k = 0; k < TPixel::componentCount; ++k)
						{
							acc[k] += pixel[k] * weights[p];
						}
					}

					for (uint8_t k = 0; k < TPixel::componentCount; ++k)
					{
						(*itResult)[k] = acc[k];
					}
				}
			}

			delete tensor;

			tensor = scp::Tensor<TPixel>::createAroundMemory({ height, width }, const_cast<TPixel*>(result.getData()));
			TPixel* scanline = new TPixel[height];
			const TPixel* const scanlineEnd = scanline;

			for (int64_t i = 0; i < width; ++i)
			{
				for (int64_t j = 0; j < height; ++j, ++scanline)
				{
					std::fill_n(acc, TPixel::componentCount, 0.0);
					for (int64_t q = 0, y = j - r; q < d; ++q, ++y)
					{
						const TPixel& pixel = tensor->getOutOfBound<BBehaviour>({ y, i });
						for (uint8_t k = 0; k < TPixel::componentCount; ++k)
						{
							acc[k] += pixel[k] * weights[q];
						}
					}

					for (uint8_t k = 0; k < TPixel::componentCount; ++k)
					{
						(*scanline)[k] = acc[k];
					}
				}

				itResult = result.begin() + i + width * (height - 1);
				for (; scanline != scanlineEnd; itResult -= width)
				{
					*itResult = *(--scanline);
				}
			}

			delete tensor;
			delete[] scanline;
		}

		template<scp::BorderBehaviour BBehaviour, PixelConcept TPixel>
		constexpr void blurMedian(const Image<TPixel>& image, Image<TPixel>& result, uint64_t radius)
		{
			// TODO
		}

		template<scp::BorderBehaviour BBehaviour, PixelConcept TPixel>
		constexpr void blurMean(const Image<TPixel>& image, Image<TPixel>& result, uint64_t radius)
		{
			assert(image.getWidth() == result.getWidth());
			assert(image.getHeight() == result.getHeight());

			const uint64_t width = image.getWidth();
			const uint64_t height = image.getHeight();
			const uint64_t d = 2 * radius + 1;
			const int64_t r = static_cast<int64_t>(radius);

			const scp::Tensor<TPixel>* tensor = scp::Tensor<TPixel>::createAroundMemory({ height, width }, const_cast<TPixel*>(image.getData()));
			TPixel* itResult = result.begin();

			double acc[TPixel::componentCount];

			for (int64_t j = 0; j < height; ++j)
			{
				std::fill_n(acc, TPixel::componentCount, 0.0);
				for (int64_t i = -r; i <= r; ++i)
				{
					const TPixel& pixel = tensor->getOutOfBound<BBehaviour>({ j, i });
					for (uint8_t k = 0; k < TPixel::componentCount; ++k)
					{
						acc[k] += pixel[k];
					}
				}

				for (uint8_t k = 0; k < TPixel::componentCount; ++k)
				{
					(*itResult)[k] = acc[k] / d;
				}
				++itResult;

				for (int64_t i = 1, iPreced = -r, iNext = 1 + r; i < width; ++i, ++iPreced, ++iNext, ++itResult)
				{
					const TPixel& pixelPreced = tensor->getOutOfBound<BBehaviour>({ j, iPreced });
					const TPixel& pixelNext = tensor->getOutOfBound<BBehaviour>({ j, iNext });
					for (uint8_t k = 0; k < TPixel::componentCount; ++k)
					{
						acc[k] -= pixelPreced[k];
						acc[k] += pixelNext[k];
						(*itResult)[k] = acc[k] / d;
					}
				}
			}

			delete tensor;

			tensor = scp::Tensor<TPixel>::createAroundMemory({ height, width }, const_cast<TPixel*>(result.getData()));
			TPixel* scanline = new TPixel[height];
			const TPixel* const scanlineEnd = scanline;
			
			for (int64_t i = 0; i < width; ++i)
			{
				std::fill_n(acc, TPixel::componentCount, 0.0);
				for (int64_t j = -r; j <= r; ++j)
				{
					const TPixel& pixel = tensor->getOutOfBound<BBehaviour>({ j, i });
					for (uint8_t k = 0; k < TPixel::componentCount; ++k)
					{
						acc[k] += pixel[k];
					}
				}
			
				for (uint8_t k = 0; k < TPixel::componentCount; ++k)
				{
					(*scanline)[k] = acc[k] / d;
				}
				++scanline;
			
				for (int64_t j = 1, jPreced = -r, jNext = 1 + r; j < height; ++j, ++jPreced, ++jNext, ++scanline)
				{
					const TPixel& pixelPreced = tensor->getOutOfBound<BBehaviour>({ jPreced, i });
					const TPixel& pixelNext = tensor->getOutOfBound<BBehaviour>({ jNext, i });
					for (uint8_t k = 0; k < TPixel::componentCount; ++k)
					{
						acc[k] -= pixelPreced[k];
						acc[k] += pixelNext[k];
						(*scanline)[k] = acc[k] / d;
					}
				}
			
				itResult = result.begin() + i + width*(height - 1);
				for (; scanline != scanlineEnd; itResult -= width)
				{
					*itResult = *(--scanline);
				}
			}
			
			delete tensor;
			delete[] scanline;
		}

		template<scp::BorderBehaviour BBehaviour, PixelConcept TPixel>
		constexpr void blurGaussianBilateral(const Image<TPixel>& image, Image<TPixel>& result, float sigmaSpace, float sigmaColor)
		{
			// TODO
		}
	}
}
