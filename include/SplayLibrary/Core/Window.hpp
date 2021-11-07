#pragma once

#include <SplayLibrary/Core/types.hpp>

namespace spl
{
	enum class CursorMode
	{
		Normal,
		Hidden,
		Disabled
	};

	class Window
	{
		public:

			// TODO: Before anything else for windows: TEST MULTI WINDOWS IN MULTIPLE THREADS !
			// TODO: Cursor object

			Window(const uvec2& size, const std::string& title);
			Window(const Window& window) = delete;
			Window(Window&& window) = delete;

			const Window& operator=(const Window& window) = delete;
			const Window& operator=(Window&& window) = delete;

			bool pollEvent(Event*& event);
			bool waitEvent(Event*& event, double timeout = 0.0);

			void setCursorMode(CursorMode mode);

			bool shouldClose() const;
			bool isKeyPressed(KeyboardKey key) const;
			dvec2 getMousePosition() const;
			bool isCursorInWindow() const;
			bool isMouseButtonPressed(MouseButton button) const;

			bool isValid() const;
			void* getHandle();
			const void* getHandle() const;
			const uvec2& getSize() const;

			static void setCurrentContext(const Window* window);

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
