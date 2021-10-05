#pragma once

#include <SplayLibrary/types.hpp>

namespace spl
{
	class RenderWindow
	{
		public:

			RenderWindow(const uvec2& size, const std::string& title);
			RenderWindow(const RenderWindow& window) = delete;

			const RenderWindow& operator=(const RenderWindow& window) = delete;

			bool pollEvent(Event*& event);
			bool waitEvent(Event*& event, double timeout = 0.0);

			void display();

			bool shouldClose() const;
			const void* getHandle() const;

			~RenderWindow();

		private:

			RenderWindow();

			bool processEvent(Event*& event);

			void* _window;
			uvec2 _size;

			std::queue<Event*> _events;

		friend void stackEvent(RenderWindow* window, Event* event);
	};
}
