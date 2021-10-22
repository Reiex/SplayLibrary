#pragma once

#include <DejaVu/ImageProcessing/FeatureDetection.hpp>

namespace djv
{
	namespace edgeDetectors
	{
		template<typename PixelType>
		Img<PixelType> marrHildreth(const Img<PixelType>& img)
		{
			Img<PixelType> r(img.width(), img.height());
			std::array<Img<PixelType>, 2> grad = operators::simpleGradient(img);
			Img<PixelType> laplacian = operators::simpleLaplacian(img);

			#pragma omp parallel for
			for (int64_t i = 0; i < laplacian.width() - 1; ++i)
			{
				for (int64_t j = 0; j < laplacian.height() - 1; ++j)
				{
					for (uint64_t k = 0; k < PixelType::componentCount; ++k)
					{
						float l = laplacian[i][j][k], lx = laplacian[i + 1][j][k], ly = laplacian[i + 1][j][k];
						if (l*lx < 0 || l*ly < 0)
						{
							float gx = grad[0][i][j][k], gy = grad[1][i][j][k];
							r[i][j][k] = gx*gx + gy*gy;
						}
					}
				}
			}

			return r;
		}

		template<typename PixelType>
		Img<PixelType> canny(const Img<PixelType>& img)
		{
			std::array<Img<PixelType>, 2> grad = operators::simpleGradient(img);
			Img<PixelType> gradMag(img.width(), img.height()), gradArg(img.width(), img.height());

			#pragma omp parallel for
			for (int64_t i = 0; i < gradMag.width(); ++i)
			{
				for (int64_t j = 0; j < gradMag.height(); ++j)
				{
					for (uint64_t k = 0; k < PixelType::componentCount; ++k)
					{
						float gx = grad[0][i][j][k], gy = grad[1][i][j][k];
						gradMag[i][j][k] = gx*gx + gy*gy;
						gradArg[i][j][k] = std::atan2(gy, gx);
					}
				}
			}

			float pi = scp::pi;
			Img<PixelType> r(gradMag);
			#pragma omp parallel for
			for (int64_t i = 0; i < r.width(); ++i)
			{
				for (int64_t j = 0; j < r.height(); ++j)
				{
					for (uint64_t k = 0; k < PixelType::componentCount; ++k)
					{
						int64_t x, y;

						float garg = gradArg[i][j][k];

						if (garg >= 7*pi/8 || garg < -7*pi/8)
						{
							x = -1;
							y = 0;
						}
						else if (garg >= 5*pi/8 && garg < 7*pi/8)
						{
							x = -1;
							y = 1;
						}
						else if (garg >= 3*pi/8 && garg < 5*pi/8)
						{
							x = 0;
							y = 1;
						}
						else if (garg >= pi/8 && garg < 3*pi/8)
						{
							x = 1;
							y = 1;
						}
						else if (garg >= -pi/8 && garg < pi/8)
						{
							x = 1;
							y = 0;
						}
						else if (garg >= -3*pi/8 && garg < -pi/8)
						{
							x = 1;
							y = -1;
						}
						else if (garg >= -5*pi/8 && garg < -3*pi/8)
						{
							x = 0;
							y = -1;
						}
						else
						{
							x = -1;
							y = -1;
						}

						int64_t xForward, xBackward, yForward, yBackward;

						xForward = std::min(std::max(static_cast<int64_t>(i) + x, static_cast<int64_t>(0)), static_cast<int64_t>(r.width() - 1));
						yForward = std::min(std::max(static_cast<int64_t>(j) + y, static_cast<int64_t>(0)), static_cast<int64_t>(r.height() - 1));

						xBackward = std::min(std::max(static_cast<int64_t>(i) - x, static_cast<int64_t>(0)), static_cast<int64_t>(r.width() - 1));
						yBackward = std::min(std::max(static_cast<int64_t>(j) - y, static_cast<int64_t>(0)), static_cast<int64_t>(r.height() - 1));

						float gmag = gradMag[i][j][k], gmagForward = gradMag[xForward][yForward][k], gmagBackward = gradMag[xBackward][yBackward][k];
						if (gmagForward > gmag || gmagBackward > gmag)
						{
							r[i][j][k] = 0.f;
						}
					}
				}
			}

			return r;
		}
	}

	namespace cornerDetectors
	{
		namespace harrisResponses
		{
			template<typename PixelType>
			PixelType defaultResponse(const PixelType& Ixx, const PixelType& Ixy, const PixelType& Iyy)
			{
				return Ixx*Iyy - Ixy*Ixy - 0.05*(Ixx + Iyy);
			}
		}

		template<typename PixelType>
		Img<PixelType> harris(const Img<PixelType>& img, const scp::Mat<float>& window, const std::function<PixelType(const PixelType&, const PixelType&, const PixelType&)>& response)
		{
			uint64_t w = img.width(), h = img.height();
			std::array<Img<PixelType>, 2> grad = operators::simpleGradient(img);
			std::array<Img<PixelType>, 3> gradSq = { Img<PixelType>(w, h), Img<PixelType>(w, h), Img<PixelType>(w, h) };
			Img<PixelType> R(w, h), result(w, h);
			int64_t ox = window.shape(0) / 2, oy = window.shape(1) / 2;

			#pragma omp parallel
			{
				#pragma omp for
				for (int64_t i = 0; i < w; ++i)
				{
					for (int64_t j = 0; j < h; ++j)
					{
						gradSq[0][i][j] = grad[0][i][j] * grad[0][i][j];
						gradSq[1][i][j] = grad[0][i][j] * grad[1][i][j];
						gradSq[2][i][j] = grad[1][i][j] * grad[1][i][j];
					}
				}

				#pragma omp for
				for (int64_t i = 0; i < w; ++i)
				{
					for (int64_t j = 0; j < h; ++j)
					{
						PixelType Ixx(0.f), Ixy(0.f), Iyy(0.f);
						for (int64_t p = 0; p < window.shape(0); ++p)
						{
							for (int64_t q = 0; q < window.shape(1); ++q)
							{
								int64_t x = std::max(std::min(i + p - ox, static_cast<int64_t>(w - 1)), int64_t(0));
								int64_t y = std::max(std::min(j + q - oy, static_cast<int64_t>(h - 1)), int64_t(0));
								Ixx += gradSq[0][x][y] * window[p][q];
								Ixy += gradSq[1][x][y] * window[p][q];
								Iyy += gradSq[2][x][y] * window[p][q];
							}
						}

						R[i][j] = response(Ixx, Ixy, Iyy);
					}
				}

				#pragma omp for
				for (int64_t i = 0; i < w; ++i)
				{
					for (int64_t j = 0; j < h; ++j)
					{
						for (uint64_t k = 0; k < PixelType::componentCount; ++k)
						{
							bool localMaximum(R[i][j][k] > 0);
							if (localMaximum)
							{
								for (int64_t p = -1; p < 2; p++)
								{
									for (int64_t q = -1; q < 2; q++)
									{
										int64_t x = std::max(std::min(i + p, static_cast<int64_t>(w - 1)), int64_t(0));
										int64_t y = std::max(std::min(j + q, static_cast<int64_t>(h - 1)), int64_t(0));
										localMaximum = localMaximum && R[i][j][k] >= R[x][y][k];
									}
								}
							}

							if (localMaximum)
							{
								result[i][j][k] = R[i][j][k];
							}
						}
					}
				}
			}

			return result;
		}
	}
}