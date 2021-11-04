#pragma once

#include <SplayLibrary/Core/types.hpp>

namespace spl
{
	class RenderWindow
	{
		public:

			RenderWindow(const uvec2& size, const std::string& title);
			RenderWindow(const RenderWindow& window) = delete;
			RenderWindow(RenderWindow&& window) = delete;

			const RenderWindow& operator=(const RenderWindow& window) = delete;
			const RenderWindow& operator=(RenderWindow&& window) = delete;

			bool pollEvent(Event*& event);
			bool waitEvent(Event*& event, double timeout = 0.0);
			
			void clear(const vec3& color);
			void draw(const Drawable& mesh);
			void display();

			bool shouldClose() const;
			const void* getHandle() const;

			~RenderWindow();

		private:

			RenderWindow();

			bool processEvent(Event*& event);

			void* _window;
			uvec2 _size;

			vec3 _clearColor;

			std::queue<Event*> _events;
			Event* _lastEventSent;

		friend void stackEvent(void* window, Event* event);
	};
}
