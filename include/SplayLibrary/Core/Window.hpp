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

			// TODO: Cursor object
			// TODO: Shared context (here and in ContextManager)

			Window(const uvec2& size, const std::string& title);
			Window(const Window& window) = delete;
			Window(Window&& window) = delete;

			const Window& operator=(const Window& window) = delete;
			const Window& operator=(Window&& window) = delete;

			bool pollEvent(Event*& event);
			bool waitEvent(Event*& event, double timeout = 0.0);

			void display();

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
			const Framebuffer& getFramebuffer() const;

			~Window();

		private:

			Window();

			bool processEvent(Event*& event);

			void* _window;
			uvec2 _size;

			std::queue<Event*> _events;
			Event* _lastEventSent;

			Framebuffer _framebuffer;

		friend void stackEvent(void* window, Event* event);
	};
}
