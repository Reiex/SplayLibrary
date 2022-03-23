#include <SplayLibrary/SplayLibrary.hpp>
#include <SplayLibrary/Core/Private.hpp>

namespace spl
{
	RenderWindow::RenderWindow(const uvec2& size, const std::string& title) : Window(size, title),
		_framebuffer(this)
	{
		if (!isValid())
		{
			return;
		}

		glViewport(0, 0, size.x, size.y);
		glEnable(GL_DEPTH_TEST);
	}

	void RenderWindow::display()
	{
		glfwSwapBuffers(static_cast<GLFWwindow*>(getHandle()));
	}

	const Framebuffer& RenderWindow::getFramebuffer() const
	{
		return _framebuffer;
	}

	bool RenderWindow::processEvent(Event*& event)
	{
		bool result = Window::processEvent(event);

		if (result)
		{
			switch (event->type)
			{
				case EventType::ResizeEvent:
				{
					ResizeEvent resizeEvent = event->specialize<EventType::ResizeEvent>();
					glViewport(0, 0, resizeEvent.size.x, resizeEvent.size.y);
					break;
				}
				default:
				{
					break;
				}
			}
		}

		return result;
	}

	RenderWindow::~RenderWindow()
	{
	}
}