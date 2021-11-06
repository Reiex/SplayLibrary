#pragma once

#include <SplayLibrary/Core/types.hpp>

namespace spl
{
	class RenderWindow : public Window
	{
		public:

			RenderWindow(const uvec2& size, const std::string& title);
			RenderWindow(const RenderWindow& window) = delete;
			RenderWindow(RenderWindow&& window) = delete;

			const RenderWindow& operator=(const RenderWindow& window) = delete;
			const RenderWindow& operator=(RenderWindow&& window) = delete;
			
			void clear(const vec3& color);
			void draw(const Drawable& mesh);
			void display();

			~RenderWindow();

		private:

			virtual bool processEvent(Event*& event);

			vec3 _clearColor;
	};
}
