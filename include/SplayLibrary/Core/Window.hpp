#pragma once

#include <SplayLibrary/Core/types.hpp>

namespace spl
{
	class Window
	{
		public:

			// TODO: Context manager (offscreen textures, cursors, window, needs for something "universal"

			Window(const uvec2& size, const std::string& title);
			Window(const Window& window) = delete;
			Window(Window&& window) = delete;

			const Window& operator=(const Window& window) = delete;
			const Window& operator=(Window&& window) = delete;

			bool pollEvent(Event*& event);
			bool waitEvent(Event*& event, double timeout = 0.0);

			bool shouldClose() const;
			bool isKeyPressed(KeyboardKey key) const;
			dvec2 getMousePosition() const;

			static void setCurrentContext(const Window* window);

			bool isValid() const;
			void* getHandle();
			const void* getHandle() const;
			const uvec2& getSize() const;

			~Window();

		protected:

			virtual bool processEvent(Event*& event);

		private:

			Window();

			void* _window;
			uvec2 _size;

			std::queue<Event*> _events;
			Event* _lastEventSent;

		friend void stackEvent(void* window, Event* event);
	};
}
