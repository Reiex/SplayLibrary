#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Functions and classes for shape manipulations.
/// \author Reiex
/// 
/// For a more detailed description, see class Shape.
/// 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <DejaVu/Core/types.hpp>

namespace djv
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \addtogroup Core
	/// \{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \brief Class for manipulating shapes.
	///
	/// Shapes in DejaVu are parametrable iterators on pixels that form a shape.
	/// This class in the abstract class every shape should inherit from.
	/// 
	/// The idea to implement a shape is to think the PixelIterator as an algorithm that run one pixel further each
	/// time you call `getPixel`. The shape itself contains the parameters of the algorithm and the PixelIterator
	/// contains the variables you need in the algorithm.
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class Shape
	{
		public:

			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \brief Class to be implemented by each class inheriting from Shape. 
			///
			/// For a more detailed description, see class Shape.
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			class PixelIterator
			{
				public:

					virtual bool getPixel(int64_t& x, int64_t& y) = 0;
			};

			virtual std::unique_ptr<Shape::PixelIterator> getPixelIterator() const = 0;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	namespace shape
	{
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \addtogroup shapes
		/// \ingroup Core
		/// \{
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Class for manipulating the shape of a rectangle with a border thickness.
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		class ThickRect : public Shape
		{
			public:

				ThickRect(int64_t left, int64_t top, uint64_t width, uint64_t height, uint64_t thickness);

				class PixelIterator : public Shape::PixelIterator
				{
					public:

						PixelIterator(int64_t left, int64_t top, uint64_t width, uint64_t height, uint64_t thickness);

						virtual bool getPixel(int64_t& x, int64_t& y);

					private:

						int64_t _cx, _cy, _x, _y;
						int64_t _a, _b, _c, _d, _e, _f;
						uint64_t _w, _h, _t;
				};

				virtual std::unique_ptr<Shape::PixelIterator> getPixelIterator() const;

			private:

				int64_t _left;
				int64_t _top;
				uint64_t _width;
				uint64_t _height;
				uint64_t _thickness;
		};

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Class for manipulating a filled rectangle shape.
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		class FilledRect : public ThickRect
		{
			public:

				FilledRect(int64_t left, int64_t top, uint64_t width, uint64_t height);
		};

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Class for manipulating a rectangle border shape with only one pixel of thickness.
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		class Rect : public ThickRect
		{
			public:

				Rect(int64_t left, int64_t top, uint64_t width, uint64_t height);
		};

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Class for manipulating a crown shape, which can be seen as a circle with a thickness.
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		class Crown : public Shape
		{
			public:

				Crown(int64_t xCenter, int64_t yCenter, uint64_t outerRadius, uint64_t innerRadius);

				class PixelIterator : public Shape::PixelIterator
				{
					public:

						PixelIterator(int64_t xCenter, int64_t yCenter, uint64_t outerRadius, uint64_t innerRadius);

						virtual bool getPixel(int64_t& x, int64_t& y);

					private:

						int64_t _cx, _cy, _irSq, _orSq;
						int64_t _x0, _y0, _x, _y, _lx, _ly;
				};

				virtual std::unique_ptr<Shape::PixelIterator> getPixelIterator() const;

			private:

				int64_t _xCenter;
				int64_t _yCenter;
				uint64_t _innerRadius;
				uint64_t _outerRadius;
		};

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Class for manipulating a disc shape.
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		class Disc : public Crown
		{
			public:

				Disc(int64_t xCenter, int64_t yCenter, uint64_t radius);
		};

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Class for manipulating a circle shape.
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		class Circle : public Crown
		{
			public:

				Circle(int64_t xCenter, int64_t yCenter, uint64_t radius);
		};

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Class for manipulating a line shape.
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		class Line : public Shape
		{
			public:

				Line(int64_t xStart, int64_t yStart, int64_t xEnd, int64_t yEnd);

				class PixelIterator : public Shape::PixelIterator
				{
					public:

						PixelIterator(int64_t xStart, int64_t yStart, int64_t xEnd, int64_t yEnd);

						virtual bool getPixel(int64_t& x, int64_t& y);

					private:

						bool _verticalFlip, _absOrdExchange;
						int64_t _x1, _y1, _x2, _y2, _dx, _dy, _e, _e10, _e01, _x, _y;
				};

				virtual std::unique_ptr<Shape::PixelIterator> getPixelIterator() const;

			private:

				int64_t _xStart;
				int64_t _yStart;
				int64_t _xEnd;
				int64_t _yEnd;
		};

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
}
