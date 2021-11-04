#include <SplayLibrary/Core/Core.hpp>
#include <SplayLibrary/Core/Private.hpp>


#define _SILENCE_ALL_CXX17_CODECVT_DEPRECATION_WARNINGS
#include <codecvt>
#include <locale>

namespace spl
{
	namespace
	{
		std::vector<RenderWindow*> SPL_WINDOWS;
		std::mutex SPL_WINDOWS_MUTEX;
	}

	static void stackEvent(void* window, Event* event)
	{
		for (uint32_t i = 0; i < SPL_WINDOWS.size(); ++i)
		{
			if (SPL_WINDOWS[i]->getHandle() == window)
			{
				SPL_WINDOWS[i]->_events.push(event);
				return;
			}
		}
	}

	namespace
	{
		KeyboardKey glfwKeyToSplKey(int key)
		{
			switch (key)
			{
			case GLFW_KEY_UNKNOWN:
				return KeyboardKey::Unknown;
			case GLFW_KEY_SPACE:
				return KeyboardKey::Space;
			case GLFW_KEY_APOSTROPHE:
				return KeyboardKey::Apostrophe;
			case GLFW_KEY_COMMA:
				return KeyboardKey::Comma;
			case GLFW_KEY_MINUS:
				return KeyboardKey::Minus;
			case GLFW_KEY_PERIOD:
				return KeyboardKey::Period;
			case GLFW_KEY_SLASH:
				return KeyboardKey::Slash;
			case GLFW_KEY_0:
				return KeyboardKey::Key0;
			case GLFW_KEY_1:
				return KeyboardKey::Key1;
			case GLFW_KEY_2:
				return KeyboardKey::Key2;
			case GLFW_KEY_3:
				return KeyboardKey::Key3;
			case GLFW_KEY_4:
				return KeyboardKey::Key4;
			case GLFW_KEY_5:
				return KeyboardKey::Key5;
			case GLFW_KEY_6:
				return KeyboardKey::Key6;
			case GLFW_KEY_7:
				return KeyboardKey::Key7;
			case GLFW_KEY_8:
				return KeyboardKey::Key8;
			case GLFW_KEY_9:
				return KeyboardKey::Key9;
			case GLFW_KEY_SEMICOLON:
				return KeyboardKey::Semicolon;
			case GLFW_KEY_EQUAL:
				return KeyboardKey::Equal;
			case GLFW_KEY_A:
				return KeyboardKey::A;
			case GLFW_KEY_B:
				return KeyboardKey::B;
			case GLFW_KEY_C:
				return KeyboardKey::C;
			case GLFW_KEY_D:
				return KeyboardKey::D;
			case GLFW_KEY_E:
				return KeyboardKey::E;
			case GLFW_KEY_F:
				return KeyboardKey::F;
			case GLFW_KEY_G:
				return KeyboardKey::G;
			case GLFW_KEY_H:
				return KeyboardKey::H;
			case GLFW_KEY_I:
				return KeyboardKey::I;
			case GLFW_KEY_J:
				return KeyboardKey::J;
			case GLFW_KEY_K:
				return KeyboardKey::K;
			case GLFW_KEY_L:
				return KeyboardKey::L;
			case GLFW_KEY_M:
				return KeyboardKey::M;
			case GLFW_KEY_N:
				return KeyboardKey::N;
			case GLFW_KEY_O:
				return KeyboardKey::O;
			case GLFW_KEY_P:
				return KeyboardKey::P;
			case GLFW_KEY_Q:
				return KeyboardKey::Q;
			case GLFW_KEY_R:
				return KeyboardKey::R;
			case GLFW_KEY_S:
				return KeyboardKey::S;
			case GLFW_KEY_T:
				return KeyboardKey::T;
			case GLFW_KEY_U:
				return KeyboardKey::U;
			case GLFW_KEY_V:
				return KeyboardKey::V;
			case GLFW_KEY_W:
				return KeyboardKey::W;
			case GLFW_KEY_X:
				return KeyboardKey::X;
			case GLFW_KEY_Y:
				return KeyboardKey::Y;
			case GLFW_KEY_Z:
				return KeyboardKey::Z;
			case GLFW_KEY_LEFT_BRACKET:
				return KeyboardKey::LeftBracket;
			case GLFW_KEY_BACKSLASH:
				return KeyboardKey::Backslash;
			case GLFW_KEY_RIGHT_BRACKET:
				return KeyboardKey::RightBracket;
			case GLFW_KEY_GRAVE_ACCENT:
				return KeyboardKey::GraveAccent;
			case GLFW_KEY_WORLD_1:
				return KeyboardKey::World1;
			case GLFW_KEY_WORLD_2:
				return KeyboardKey::World2;
			case GLFW_KEY_ESCAPE:
				return KeyboardKey::Escape;
			case GLFW_KEY_ENTER:
				return KeyboardKey::Enter;
			case GLFW_KEY_TAB:
				return KeyboardKey::Tab;
			case GLFW_KEY_BACKSPACE:
				return KeyboardKey::Backspace;
			case GLFW_KEY_INSERT:
				return KeyboardKey::Insert;
			case GLFW_KEY_DELETE:
				return KeyboardKey::Delete;
			case GLFW_KEY_RIGHT:
				return KeyboardKey::Right;
			case GLFW_KEY_LEFT:
				return KeyboardKey::Left;
			case GLFW_KEY_DOWN:
				return KeyboardKey::Down;
			case GLFW_KEY_UP:
				return KeyboardKey::Up;
			case GLFW_KEY_PAGE_UP:
				return KeyboardKey::PageUp;
			case GLFW_KEY_PAGE_DOWN:
				return KeyboardKey::PageDown;
			case GLFW_KEY_HOME:
				return KeyboardKey::Home;
			case GLFW_KEY_END:
				return KeyboardKey::End;
			case GLFW_KEY_CAPS_LOCK:
				return KeyboardKey::CapsLock;
			case GLFW_KEY_SCROLL_LOCK:
				return KeyboardKey::ScrollLock;
			case GLFW_KEY_NUM_LOCK:
				return KeyboardKey::NumLock;
			case GLFW_KEY_PRINT_SCREEN:
				return KeyboardKey::PrintScreen;
			case GLFW_KEY_PAUSE:
				return KeyboardKey::Pause;
			case GLFW_KEY_F1:
				return KeyboardKey::F1;
			case GLFW_KEY_F2:
				return KeyboardKey::F2;
			case GLFW_KEY_F3:
				return KeyboardKey::F3;
			case GLFW_KEY_F4:
				return KeyboardKey::F4;
			case GLFW_KEY_F5:
				return KeyboardKey::F5;
			case GLFW_KEY_F6:
				return KeyboardKey::F6;
			case GLFW_KEY_F7:
				return KeyboardKey::F7;
			case GLFW_KEY_F8:
				return KeyboardKey::F8;
			case GLFW_KEY_F9:
				return KeyboardKey::F9;
			case GLFW_KEY_F10:
				return KeyboardKey::F10;
			case GLFW_KEY_F11:
				return KeyboardKey::F11;
			case GLFW_KEY_F12:
				return KeyboardKey::F12;
			case GLFW_KEY_F13:
				return KeyboardKey::F13;
			case GLFW_KEY_F14:
				return KeyboardKey::F14;
			case GLFW_KEY_F15:
				return KeyboardKey::F15;
			case GLFW_KEY_F16:
				return KeyboardKey::F16;
			case GLFW_KEY_F17:
				return KeyboardKey::F17;
			case GLFW_KEY_F18:
				return KeyboardKey::F18;
			case GLFW_KEY_F19:
				return KeyboardKey::F19;
			case GLFW_KEY_F20:
				return KeyboardKey::F20;
			case GLFW_KEY_F21:
				return KeyboardKey::F21;
			case GLFW_KEY_F22:
				return KeyboardKey::F22;
			case GLFW_KEY_F23:
				return KeyboardKey::F23;
			case GLFW_KEY_F24:
				return KeyboardKey::F24;
			case GLFW_KEY_F25:
				return KeyboardKey::F25;
			case GLFW_KEY_KP_0:
				return KeyboardKey::Numpad0;
			case GLFW_KEY_KP_1:
				return KeyboardKey::Numpad1;
			case GLFW_KEY_KP_2:
				return KeyboardKey::Numpad2;
			case GLFW_KEY_KP_3:
				return KeyboardKey::Numpad3;
			case GLFW_KEY_KP_4:
				return KeyboardKey::Numpad4;
			case GLFW_KEY_KP_5:
				return KeyboardKey::Numpad5;
			case GLFW_KEY_KP_6:
				return KeyboardKey::Numpad6;
			case GLFW_KEY_KP_7:
				return KeyboardKey::Numpad7;
			case GLFW_KEY_KP_8:
				return KeyboardKey::Numpad8;
			case GLFW_KEY_KP_9:
				return KeyboardKey::Numpad9;
			case GLFW_KEY_KP_DECIMAL:
				return KeyboardKey::NumpadDecimal;
			case GLFW_KEY_KP_DIVIDE:
				return KeyboardKey::NumpadDivide;
			case GLFW_KEY_KP_MULTIPLY:
				return KeyboardKey::NumpadMultiply;
			case GLFW_KEY_KP_SUBTRACT:
				return KeyboardKey::NumpadSubtract;
			case GLFW_KEY_KP_ADD:
				return KeyboardKey::NumpadAdd;
			case GLFW_KEY_KP_ENTER:
				return KeyboardKey::NumpadEnter;
			case GLFW_KEY_KP_EQUAL:
				return KeyboardKey::NumpadEqual;
			case GLFW_KEY_LEFT_SHIFT:
				return KeyboardKey::LeftShift;
			case GLFW_KEY_LEFT_CONTROL:
				return KeyboardKey::LeftControl;
			case GLFW_KEY_LEFT_ALT:
				return KeyboardKey::LeftAlt;
			case GLFW_KEY_LEFT_SUPER:
				return KeyboardKey::LeftSuper;
			case GLFW_KEY_RIGHT_SHIFT:
				return KeyboardKey::RightShift;
			case GLFW_KEY_RIGHT_CONTROL:
				return KeyboardKey::RightControl;
			case GLFW_KEY_RIGHT_ALT:
				return KeyboardKey::RightAlt;
			case GLFW_KEY_RIGHT_SUPER:
				return KeyboardKey::RightSuper;
			case GLFW_KEY_MENU:
				return KeyboardKey::Menu;
			default:
				assert(false);
				return KeyboardKey::Unknown;
			}
		}

		KeyboardAction glfwActionToSplAction(int action)
		{
			switch (action)
			{
			case GLFW_PRESS:
				return KeyboardAction::KeyPressed;
			case GLFW_REPEAT:
				return KeyboardAction::KeyRepeated;
			case GLFW_RELEASE:
				return KeyboardAction::KeyReleased;
			default:
				assert(false);
				return KeyboardAction::KeyPressed;
			}
		}

		KeyboardModifier::ModifierFlags glfwModifierToSplModifier(int mods)
		{
			KeyboardModifier::ModifierFlags flags = KeyboardModifier::None;

			if (mods & GLFW_MOD_SHIFT)
			{
				flags = (KeyboardModifier::ModifierFlags) (flags & KeyboardModifier::Shift);
			}
			if (mods & GLFW_MOD_CONTROL)
			{
				flags = (KeyboardModifier::ModifierFlags)(flags & KeyboardModifier::Control);
			}
			if (mods & GLFW_MOD_ALT)
			{
				flags = (KeyboardModifier::ModifierFlags)(flags & KeyboardModifier::Alt);
			}
			if (mods & GLFW_MOD_SUPER)
			{
				flags = (KeyboardModifier::ModifierFlags)(flags & KeyboardModifier::Super);
			}
			if (mods & GLFW_MOD_CAPS_LOCK)
			{
				flags = (KeyboardModifier::ModifierFlags)(flags & KeyboardModifier::CapsLock);
			}
			if (mods & GLFW_MOD_NUM_LOCK)
			{
				flags = (KeyboardModifier::ModifierFlags)(flags & KeyboardModifier::NumLock);
			}

			return flags;
		}

		void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			KeyboardEvent* event = new KeyboardEvent();
			event->type = EventType::KeyboardEvent;
			event->scancode = scancode;
			event->key = glfwKeyToSplKey(key);
			event->action = glfwActionToSplAction(action);
			event->modifiers = glfwModifierToSplModifier(mods);

			stackEvent(window, event);
		}

		void glfwCharacterCallback(GLFWwindow* window, unsigned int codepoint)
		{
			TextEvent* event = new TextEvent();
			event->type = EventType::TextEvent;
			event->unicode = codepoint;

			stackEvent(window, event);
		}

		void glfwCursorPosCallback(GLFWwindow* window, double x, double y)
		{
			MouseMoveEvent* event = new MouseMoveEvent();
			event->type = EventType::MouseMoveEvent;
			event->pos.x = x;
			event->pos.y = y;

			stackEvent(window, event);
		}

		void glfwFramebufferSizeCallback(GLFWwindow* window, int width, int height)
		{
			ResizeEvent* event = new ResizeEvent();
			event->type = EventType::ResizeEvent;
			event->size = { static_cast<uint32_t>(width), static_cast<uint32_t>(height) };

			stackEvent(window, event);
		}
	}

	RenderWindow::RenderWindow() :
		_window(nullptr),
		_size(0, 0),
		_clearColor(0.f, 0.f, 0.f),
		_events(),
		_lastEventSent(nullptr)
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

		// TODO: Flags (triple buffering, full screen, etc...)
		// TODO: Gestion du choix du moniteur
		_window = glfwCreateWindow(size.x, size.y, title.c_str(), nullptr, nullptr);
		if (!_window)
		{
			SPL_DEBUG("Could not create GLFW Window.");
			return;
		}
		_size = size;

		SPL_WINDOWS_MUTEX.lock();
		SPL_WINDOWS.push_back(this);
		SPL_WINDOWS_MUTEX.unlock();
		// TODO: Fill values such as max texture size, max buffer size etc...

		GLFWwindow* glfwWindow = static_cast<GLFWwindow*>(_window);

		glfwMakeContextCurrent(glfwWindow);

		if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
		{
			SPL_DEBUG("Could not load OpenGL functions.");
			return;
		}

		glViewport(0, 0, size.x, size.y);

		glfwSetKeyCallback(glfwWindow, glfwKeyCallback);
		glfwSetCharCallback(glfwWindow, glfwCharacterCallback);
		glfwSetCursorPosCallback(glfwWindow, glfwCursorPosCallback);
		glfwSetFramebufferSizeCallback(glfwWindow, glfwFramebufferSizeCallback);

		glClearColor(_clearColor.x, _clearColor.y, _clearColor.z, 1.0f);
	}

	bool RenderWindow::pollEvent(Event*& event)
	{
		glfwPollEvents();
		return processEvent(event);
	}

	bool RenderWindow::waitEvent(Event*& event, double timeout)
	{
		if (timeout <= 0.0)
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

	void RenderWindow::draw(const Drawable& mesh)
	{
		mesh.draw();
	}

	void RenderWindow::display()
	{
		glfwSwapBuffers(static_cast<GLFWwindow*>(_window));
	}

	bool RenderWindow::processEvent(Event*& event)
	{
		if (_events.size() > 0 && _events.front() == _lastEventSent)
		{
			delete _events.front();
			_events.pop();
			_lastEventSent = nullptr;
		}

		if (_events.size() == 0)
		{
			return false;
		}

		event = _events.front();
		_lastEventSent = event;

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
		while (!_events.empty())
		{
			delete _events.front();
			_events.pop();
		}

		glfwDestroyWindow(static_cast<GLFWwindow*>(_window));

		for (uint32_t i = 0; i < SPL_WINDOWS.size(); ++i)
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