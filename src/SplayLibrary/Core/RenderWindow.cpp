#include <SplayLibrary/Core/Core.hpp>
#include <SplayLibrary/Core/Private.hpp>


#define _SILENCE_ALL_CXX17_CODECVT_DEPRECATION_WARNINGS
#include <codecvt>
#include <locale>

namespace spl
{
	namespace
	{
		thread_local RenderWindow* SPL_THREAD_RENDER_WINDOW = nullptr;
	}

	RenderWindow::RenderWindow(const uvec2& size, const std::string& title) : Window(size, title),
		_clearColor(0.f, 0.f, 0.f)
	{
		if (!isValid())
		{
			return;
		}

		assert(SPL_THREAD_RENDER_WINDOW == nullptr);
		SPL_THREAD_RENDER_WINDOW = this;

		GLFWwindow* glfwWindow = static_cast<GLFWwindow*>(getHandle());
		glfwMakeContextCurrent(glfwWindow);

		if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
		{
			SPL_DEBUG("Could not load OpenGL functions.");
			return;
		}

		glViewport(0, 0, size.x, size.y);
		glClearColor(_clearColor.x, _clearColor.y, _clearColor.z, 1.0f);
	}

	void RenderWindow::clear(const vec3& color)
	{
		if (color != _clearColor)
		{
			_clearColor = color;
			glClearColor(_clearColor.x, _clearColor.y, _clearColor.z, 1.0f);
		}

		glClear(GL_COLOR_BUFFER_BIT);
	}

	void RenderWindow::draw(const Drawable& mesh)
	{
		mesh.draw();
	}

	void RenderWindow::display()
	{
		glfwSwapBuffers(static_cast<GLFWwindow*>(getHandle()));
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
		assert(SPL_THREAD_RENDER_WINDOW == this);
		if (SPL_THREAD_RENDER_WINDOW == this)
		{
			SPL_THREAD_RENDER_WINDOW = nullptr;
		}

		GLFWwindow* glfwWindow = static_cast<GLFWwindow*>(getHandle());
		assert(glfwGetCurrentContext() == glfwWindow);
		if (glfwGetCurrentContext() == glfwWindow)
		{
			glfwMakeContextCurrent(nullptr);
		}
	}
}