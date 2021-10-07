#include <SplayLibrary/SplayLibrary.hpp>
#include <SplayLibrary/Private.hpp>

namespace spl
{
	static void stackEvent(RenderWindow* window, Event* event)
	{
		window->_events.push(event);
	}

	namespace
	{
		std::vector<RenderWindow*> SPL_WINDOWS;

		RenderWindow* getRenderWindowByHandle(GLFWwindow* window)
		{
			for (uint64_t i = 0; i < SPL_WINDOWS.size(); ++i)
			{
				if (SPL_WINDOWS[i]->getHandle() == window)
				{
					return SPL_WINDOWS[i];
				}
			}

			return nullptr;
		}

		void glfwFramebufferSizeCallback(GLFWwindow* window, int width, int height)
		{
			ResizeEvent* event = new ResizeEvent();
			event->type = Event::EventType::ResizeEvent;
			event->size = { static_cast<uint32_t>(width), static_cast<uint32_t>(height) };

			RenderWindow* renderWindow = getRenderWindowByHandle(window);
			if (renderWindow)
			{
				stackEvent(renderWindow, event);
			}
		}
	}

	RenderWindow::RenderWindow() :
		_window(nullptr),
		_size(0, 0),
		_clearColor(0.f, 0.f, 0.f),
		_events({ new Event() })
	{
	}

	RenderWindow::RenderWindow(const uvec2& size, const std::string& title) : RenderWindow()
	{
		if (!glfwInit())
		{
			SPL_DEBUG("Could not initialize GLFW.");
			return;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		_window = glfwCreateWindow(size.x, size.y, title.c_str(), nullptr, nullptr);
		if (!_window)
		{
			SPL_DEBUG("Could not create GLFW Window.");
			return;
		}
		_size = size;

		SPL_WINDOWS.push_back(this);

		glfwMakeContextCurrent(static_cast<GLFWwindow*>(_window));

		if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
		{
			SPL_DEBUG("Could not load OpenGL functions.");
			return;
		}

		glViewport(0, 0, size.x, size.y);

		glfwSetFramebufferSizeCallback(static_cast<GLFWwindow*>(_window), glfwFramebufferSizeCallback);

		glClearColor(_clearColor.x, _clearColor.y, _clearColor.z, 1.0f);
	}

	bool RenderWindow::pollEvent(Event*& event)
	{
		glfwPollEvents();
		return processEvent(event);
	}

	bool RenderWindow::waitEvent(Event*& event, double timeout)
	{
		if (timeout == 0.0)
		{
			glfwWaitEvents();
		}
		else
		{
			glfwWaitEventsTimeout(timeout);
		}

		return processEvent(event);
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

	void RenderWindow::display()
	{
		glfwSwapBuffers(static_cast<GLFWwindow*>(_window));
	}

	bool RenderWindow::processEvent(Event*& event)
	{
		if (_events.size() > 0)
		{
			delete _events.front();
			_events.pop();
		}

		if (_events.size() == 0)
		{
			return false;
		}

		event = _events.front();

		switch (event->type)
		{
			case Event::EventType::ResizeEvent:
			{
				ResizeEvent resizeEvent = event->as<ResizeEvent>();
				glViewport(0, 0, resizeEvent.size.x, resizeEvent.size.y);
				break;
			}
			default:
			{
				break;
			}
		}

		return true;
	}

	bool RenderWindow::shouldClose() const
	{
		return glfwWindowShouldClose(static_cast<GLFWwindow*>(_window));
	}

	const void* RenderWindow::getHandle() const
	{
		return _window;
	}

	RenderWindow::~RenderWindow()
	{
		glfwDestroyWindow(static_cast<GLFWwindow*>(_window));

		for (uint64_t i = 0; i < SPL_WINDOWS.size(); ++i)
		{
			if (SPL_WINDOWS[i] == this)
			{
				SPL_WINDOWS.erase(SPL_WINDOWS.begin() + i);
				break;
			}
		}

		if (SPL_WINDOWS.size() == 0)
		{
			glfwTerminate();
		}
	}
}