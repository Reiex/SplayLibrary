#include <SplayLibrary/Core/Core.hpp>
#include <SplayLibrary/Core/Private.hpp>

namespace spl
{
	namespace
	{
		static std::vector<Window*> SPL_WINDOWS;
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

		int splKeyToGlfwKey(KeyboardKey key)
		{
			switch (key)
			{
			case KeyboardKey::Unknown:
				return GLFW_KEY_UNKNOWN;
			case KeyboardKey::Space:
				return GLFW_KEY_SPACE;
			case KeyboardKey::Apostrophe:
				return GLFW_KEY_APOSTROPHE;
			case KeyboardKey::Comma:
				return GLFW_KEY_COMMA;
			case KeyboardKey::Minus:
				return GLFW_KEY_MINUS;
			case KeyboardKey::Period:
				return GLFW_KEY_PERIOD;
			case KeyboardKey::Slash:
				return GLFW_KEY_SLASH;
			case KeyboardKey::Key0:
				return GLFW_KEY_0;
			case KeyboardKey::Key1:
				return GLFW_KEY_1;
			case KeyboardKey::Key2:
				return GLFW_KEY_2;
			case KeyboardKey::Key3:
				return GLFW_KEY_3;
			case KeyboardKey::Key4:
				return GLFW_KEY_4;
			case KeyboardKey::Key5:
				return GLFW_KEY_5;
			case KeyboardKey::Key6:
				return GLFW_KEY_6;
			case KeyboardKey::Key7:
				return GLFW_KEY_7;
			case KeyboardKey::Key8:
				return GLFW_KEY_8;
			case KeyboardKey::Key9:
				return GLFW_KEY_9;
			case KeyboardKey::Semicolon:
				return GLFW_KEY_SEMICOLON;
			case KeyboardKey::Equal:
				return GLFW_KEY_EQUAL;
			case KeyboardKey::A:
				return GLFW_KEY_A;
			case KeyboardKey::B:
				return GLFW_KEY_B;
			case KeyboardKey::C:
				return GLFW_KEY_C;
			case KeyboardKey::D:
				return GLFW_KEY_D;
			case KeyboardKey::E:
				return GLFW_KEY_E;
			case KeyboardKey::F:
				return GLFW_KEY_F;
			case KeyboardKey::G:
				return GLFW_KEY_G;
			case KeyboardKey::H:
				return GLFW_KEY_H;
			case KeyboardKey::I:
				return GLFW_KEY_I;
			case KeyboardKey::J:
				return GLFW_KEY_J;
			case KeyboardKey::K:
				return GLFW_KEY_K;
			case KeyboardKey::L:
				return GLFW_KEY_L;
			case KeyboardKey::M:
				return GLFW_KEY_M;
			case KeyboardKey::N:
				return GLFW_KEY_N;
			case KeyboardKey::O:
				return GLFW_KEY_O;
			case KeyboardKey::P:
				return GLFW_KEY_P;
			case KeyboardKey::Q:
				return GLFW_KEY_Q;
			case KeyboardKey::R:
				return GLFW_KEY_R;
			case KeyboardKey::S:
				return GLFW_KEY_S;
			case KeyboardKey::T:
				return GLFW_KEY_T;
			case KeyboardKey::U:
				return GLFW_KEY_U;
			case KeyboardKey::V:
				return GLFW_KEY_V;
			case KeyboardKey::W:
				return GLFW_KEY_W;
			case KeyboardKey::X:
				return GLFW_KEY_X;
			case KeyboardKey::Y:
				return GLFW_KEY_Y;
			case KeyboardKey::Z:
				return GLFW_KEY_Z;
			case KeyboardKey::LeftBracket:
				return GLFW_KEY_LEFT_BRACKET;
			case KeyboardKey::Backslash:
				return GLFW_KEY_BACKSLASH;
			case KeyboardKey::RightBracket:
				return GLFW_KEY_RIGHT_BRACKET;
			case KeyboardKey::GraveAccent:
				return GLFW_KEY_GRAVE_ACCENT;
			case KeyboardKey::World1:
				return GLFW_KEY_WORLD_1;
			case KeyboardKey::World2:
				return GLFW_KEY_WORLD_2;
			case KeyboardKey::Escape:
				return GLFW_KEY_ESCAPE;
			case KeyboardKey::Enter:
				return GLFW_KEY_ENTER;
			case KeyboardKey::Tab:
				return GLFW_KEY_TAB;
			case KeyboardKey::Backspace:
				return GLFW_KEY_BACKSPACE;
			case KeyboardKey::Insert:
				return GLFW_KEY_INSERT;
			case KeyboardKey::Delete:
				return GLFW_KEY_DELETE;
			case KeyboardKey::Right:
				return GLFW_KEY_RIGHT;
			case KeyboardKey::Left:
				return GLFW_KEY_LEFT;
			case KeyboardKey::Down:
				return GLFW_KEY_DOWN;
			case KeyboardKey::Up:
				return GLFW_KEY_UP;
			case KeyboardKey::PageUp:
				return GLFW_KEY_PAGE_UP;
			case KeyboardKey::PageDown:
				return GLFW_KEY_PAGE_DOWN;
			case KeyboardKey::Home:
				return GLFW_KEY_HOME;
			case KeyboardKey::End:
				return GLFW_KEY_END;
			case KeyboardKey::CapsLock:
				return GLFW_KEY_CAPS_LOCK;
			case KeyboardKey::ScrollLock:
				return GLFW_KEY_SCROLL_LOCK;
			case KeyboardKey::NumLock:
				return GLFW_KEY_NUM_LOCK;
			case KeyboardKey::PrintScreen:
				return GLFW_KEY_PRINT_SCREEN;
			case KeyboardKey::Pause:
				return GLFW_KEY_PAUSE;
			case KeyboardKey::F1:
				return GLFW_KEY_F1;
			case KeyboardKey::F2:
				return GLFW_KEY_F2;
			case KeyboardKey::F3:
				return GLFW_KEY_F3;
			case KeyboardKey::F4:
				return GLFW_KEY_F4;
			case KeyboardKey::F5:
				return GLFW_KEY_F5;
			case KeyboardKey::F6:
				return GLFW_KEY_F6;
			case KeyboardKey::F7:
				return GLFW_KEY_F7;
			case KeyboardKey::F8:
				return GLFW_KEY_F8;
			case KeyboardKey::F9:
				return GLFW_KEY_F9;
			case KeyboardKey::F10:
				return GLFW_KEY_F10;
			case KeyboardKey::F11:
				return GLFW_KEY_F11;
			case KeyboardKey::F12:
				return GLFW_KEY_F12;
			case KeyboardKey::F13:
				return GLFW_KEY_F13;
			case KeyboardKey::F14:
				return GLFW_KEY_F14;
			case KeyboardKey::F15:
				return GLFW_KEY_F15;
			case KeyboardKey::F16:
				return GLFW_KEY_F16;
			case KeyboardKey::F17:
				return GLFW_KEY_F17;
			case KeyboardKey::F18:
				return GLFW_KEY_F18;
			case KeyboardKey::F19:
				return GLFW_KEY_F19;
			case KeyboardKey::F20:
				return GLFW_KEY_F20;
			case KeyboardKey::F21:
				return GLFW_KEY_F21;
			case KeyboardKey::F22:
				return GLFW_KEY_F22;
			case KeyboardKey::F23:
				return GLFW_KEY_F23;
			case KeyboardKey::F24:
				return GLFW_KEY_F24;
			case KeyboardKey::F25:
				return GLFW_KEY_F25;
			case KeyboardKey::Numpad0:
				return GLFW_KEY_KP_0;
			case KeyboardKey::Numpad1:
				return GLFW_KEY_KP_1;
			case KeyboardKey::Numpad2:
				return GLFW_KEY_KP_2;
			case KeyboardKey::Numpad3:
				return GLFW_KEY_KP_3;
			case KeyboardKey::Numpad4:
				return GLFW_KEY_KP_4;
			case KeyboardKey::Numpad5:
				return GLFW_KEY_KP_5;
			case KeyboardKey::Numpad6:
				return GLFW_KEY_KP_6;
			case KeyboardKey::Numpad7:
				return GLFW_KEY_KP_7;
			case KeyboardKey::Numpad8:
				return GLFW_KEY_KP_8;
			case KeyboardKey::Numpad9:
				return GLFW_KEY_KP_9;
			case KeyboardKey::NumpadDecimal:
				return GLFW_KEY_KP_DECIMAL;
			case KeyboardKey::NumpadDivide:
				return GLFW_KEY_KP_DIVIDE;
			case KeyboardKey::NumpadMultiply:
				return GLFW_KEY_KP_MULTIPLY;
			case KeyboardKey::NumpadSubtract:
				return GLFW_KEY_KP_SUBTRACT;
			case KeyboardKey::NumpadAdd:
				return GLFW_KEY_KP_ADD;
			case KeyboardKey::NumpadEnter:
				return GLFW_KEY_KP_ENTER;
			case KeyboardKey::NumpadEqual:
				return GLFW_KEY_KP_EQUAL;
			case KeyboardKey::LeftShift:
				return GLFW_KEY_LEFT_SHIFT;
			case KeyboardKey::LeftControl:
				return GLFW_KEY_LEFT_CONTROL;
			case KeyboardKey::LeftAlt:
				return GLFW_KEY_LEFT_ALT;
			case KeyboardKey::LeftSuper:
				return GLFW_KEY_LEFT_SUPER;
			case KeyboardKey::RightShift:
				return GLFW_KEY_RIGHT_SHIFT;
			case KeyboardKey::RightControl:
				return GLFW_KEY_RIGHT_CONTROL;
			case KeyboardKey::RightAlt:
				return GLFW_KEY_RIGHT_ALT;
			case KeyboardKey::RightSuper:
				return GLFW_KEY_RIGHT_SUPER;
			case KeyboardKey::Menu:
				return GLFW_KEY_MENU;
			default:
				assert(false);
				return GLFW_KEY_UNKNOWN;
			}
		}

		ButtonAction glfwActionToButtonAction(int action)
		{
			switch (action)
			{
			case GLFW_PRESS:
				return ButtonAction::Pressed;
			case GLFW_REPEAT:
				return ButtonAction::Repeated;
			case GLFW_RELEASE:
				return ButtonAction::Released;
			default:
				assert(false);
				return ButtonAction::Unknown;
			}
		}

		KeyboardModifier::ModifierFlags glfwModifierToSplModifier(int mods)
		{
			int flags = KeyboardModifier::None;

			if (mods & GLFW_MOD_SHIFT)
			{
				flags |= KeyboardModifier::Shift;
			}
			if (mods & GLFW_MOD_CONTROL)
			{
				flags |= KeyboardModifier::Control;
			}
			if (mods & GLFW_MOD_ALT)
			{
				flags |= KeyboardModifier::Alt;
			}
			if (mods & GLFW_MOD_SUPER)
			{
				flags |= KeyboardModifier::Super;
			}
			if (mods & GLFW_MOD_CAPS_LOCK)
			{
				flags |= KeyboardModifier::CapsLock;
			}
			if (mods & GLFW_MOD_NUM_LOCK)
			{
				flags |= KeyboardModifier::NumLock;
			}

			return static_cast<KeyboardModifier::ModifierFlags>(flags);
		}
	
		MouseButton glfwMouseButtonToSplMouseButton(int button)
		{
			switch (button)
			{
			case GLFW_MOUSE_BUTTON_LEFT:
				return MouseButton::Left;
			case GLFW_MOUSE_BUTTON_RIGHT:
				return MouseButton::Right;
			case GLFW_MOUSE_BUTTON_MIDDLE:
				return MouseButton::Middle;
			case GLFW_MOUSE_BUTTON_4:
				return MouseButton::Button4;
			case GLFW_MOUSE_BUTTON_5:
				return MouseButton::Button5;
			case GLFW_MOUSE_BUTTON_6:
				return MouseButton::Button6;
			case GLFW_MOUSE_BUTTON_7:
				return MouseButton::Button7;
			case GLFW_MOUSE_BUTTON_8:
				return MouseButton::Button8;
			default:
				assert(false);
				return MouseButton::Unknown;
			}
		}
	
		int splMouseButtonToGlfwMouseButton(MouseButton button)
		{

			switch (button)
			{
			case MouseButton::Left:
				return GLFW_MOUSE_BUTTON_LEFT;
			case MouseButton::Right:
				return GLFW_MOUSE_BUTTON_RIGHT;
			case MouseButton::Middle:
				return GLFW_MOUSE_BUTTON_MIDDLE;
			case MouseButton::Button4:
				return GLFW_MOUSE_BUTTON_4;
			case MouseButton::Button5:
				return GLFW_MOUSE_BUTTON_5;
			case MouseButton::Button6:
				return GLFW_MOUSE_BUTTON_6;
			case MouseButton::Button7:
				return GLFW_MOUSE_BUTTON_7;
			case MouseButton::Button8:
				return GLFW_MOUSE_BUTTON_8;
			default:
				assert(false);
				return GLFW_MOUSE_BUTTON_1;
			}
		}
	}

	namespace
	{
		int splCursorModeToGlfwCursorMode(CursorMode mode)
		{
			switch (mode)
			{
			case CursorMode::Normal:
				return GLFW_CURSOR_NORMAL;
			case CursorMode::Hidden:
				return GLFW_CURSOR_HIDDEN;
			case CursorMode::Disabled:
				return GLFW_CURSOR_DISABLED;
			default:
				assert(false);
				return GLFW_CURSOR_NORMAL;
			}
		}
	}

	namespace
	{
		void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			KeyboardEvent* event = new KeyboardEvent();
			event->type = EventType::KeyboardEvent;
			event->scancode = scancode;
			event->key = glfwKeyToSplKey(key);
			event->action = glfwActionToButtonAction(action);
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

		void glfwCursorEnterCallback(GLFWwindow* window, int entered)
		{
			if (entered)
			{
				MouseEnterWindowEvent* event = new MouseEnterWindowEvent();
				event->type = EventType::MouseEnterWindowEvent;

				stackEvent(window, event);
			}
			else
			{
				MouseLeaveWindowEvent* event = new MouseLeaveWindowEvent();
				event->type = EventType::MouseLeaveWindowEvent;

				stackEvent(window, event);
			}
		}

		void glfwMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
		{
			MouseButtonEvent* event = new MouseButtonEvent();
			event->type = EventType::MouseButtonEvent;
			event->button = glfwMouseButtonToSplMouseButton(button);
			event->action = glfwActionToButtonAction(action);
			event->modifiers = glfwModifierToSplModifier(mods);

			stackEvent(window, event);
		}

		void glfwScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
		{
			ScrollEvent* event = new ScrollEvent();
			event->type = EventType::MouseButtonEvent;
			event->offset.x = xOffset;
			event->offset.y = yOffset;

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

	Window::Window() :
		_window(nullptr),
		_size(0, 0),
		_events(),
		_lastEventSent(nullptr)
	{
	}

	Window::Window(const uvec2& size, const std::string& title) : Window()
	{
		static std::mutex mutex;

		mutex.lock();
		SPL_WINDOWS.push_back(this);
		mutex.unlock();

		ContextManager* contextManager = ContextManager::get();
		if (!contextManager)
		{
			SPL_DEBUG("Could not retrieve context manager.");
			return;
		}

		mutex.lock();

		// TODO: Gestion de contextes différents (versions d'OpenGL... Vulkan ? Autres ?)
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// TODO: Flags (triple buffering, full screen, etc...)
		// TODO: Gestion du choix du moniteur
		_window = glfwCreateWindow(size.x, size.y, title.c_str(), nullptr, nullptr);

		mutex.unlock();

		if (!contextManager->setCurrentThreadContext(this))
		{
			SPL_DEBUG("Could not assign window context to current thread.");
			return;
		}

		_size = size;

		GLFWwindow* glfwWindow = static_cast<GLFWwindow*>(_window);

		glfwSetInputMode(glfwWindow, GLFW_LOCK_KEY_MODS, GLFW_TRUE);
		glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		if (glfwRawMouseMotionSupported())
		{
			glfwSetInputMode(glfwWindow, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
		}

		glfwSetKeyCallback(glfwWindow, glfwKeyCallback);
		glfwSetCharCallback(glfwWindow, glfwCharacterCallback);
		glfwSetCursorPosCallback(glfwWindow, glfwCursorPosCallback);
		glfwSetCursorEnterCallback(glfwWindow, glfwCursorEnterCallback);
		glfwSetMouseButtonCallback(glfwWindow, glfwMouseButtonCallback);
		glfwSetScrollCallback(glfwWindow, glfwScrollCallback);
		// TODO: Joysticks and gamepads callbacks

		glfwSetFramebufferSizeCallback(glfwWindow, glfwFramebufferSizeCallback);
		// TODO: Window event callbacks
	}

	bool Window::pollEvent(Event*& event)
	{
		assert(isValid());

		glfwPollEvents();
		return processEvent(event);
	}

	bool Window::waitEvent(Event*& event, double timeout)
	{
		assert(isValid());

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

	bool Window::processEvent(Event*& event)
	{
		assert(isValid());

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
				_size = resizeEvent.size;
				break;
			}
			default:
			{
				break;
			}
		}

		return true;
	}

	void Window::setCursorMode(CursorMode mode)
	{
		assert(isValid());

		glfwSetInputMode(static_cast<GLFWwindow*>(_window), GLFW_CURSOR, splCursorModeToGlfwCursorMode(mode));
	}

	bool Window::shouldClose() const
	{
		assert(isValid());

		return glfwWindowShouldClose(static_cast<GLFWwindow*>(_window));
	}

	bool Window::isKeyPressed(KeyboardKey key) const
	{
		assert(isValid());

		return glfwGetKey(static_cast<GLFWwindow*>(_window), splKeyToGlfwKey(key)) == GLFW_PRESS;
	}

	dvec2 Window::getMousePosition() const
	{
		assert(isValid());

		dvec2 pos;
		glfwGetCursorPos(static_cast<GLFWwindow*>(_window), &pos.x, &pos.y);
		return pos;
	}

	bool Window::isCursorInWindow() const
	{
		assert(isValid());

		return glfwGetWindowAttrib(static_cast<GLFWwindow*>(_window), GLFW_HOVERED);
	}

	bool Window::isMouseButtonPressed(MouseButton button) const
	{
		assert(isValid());

		return glfwGetMouseButton(static_cast<GLFWwindow*>(_window), splMouseButtonToGlfwMouseButton(button)) == GLFW_PRESS;
	}

	bool Window::isValid() const
	{
		return _window != nullptr;
	}

	void* Window::getHandle()
	{
		return _window;
	}

	const void* Window::getHandle() const
	{
		return _window;
	}

	const uvec2& Window::getSize() const
	{
		return _size;
	}

	void Window::setCurrentContext(const Window* window)
	{
		if (window)
		{
			assert(window->isValid());
			glfwMakeContextCurrent(static_cast<GLFWwindow*>(window->_window));
		}
		else
		{
			glfwMakeContextCurrent(nullptr);
		}
	}

	Window::~Window()
	{
		static std::mutex mutex;

		mutex.lock();
		SPL_WINDOWS.erase(std::find(SPL_WINDOWS.begin(), SPL_WINDOWS.end(), this));
		mutex.unlock();

		while (!_events.empty())
		{
			delete _events.front();
			_events.pop();
		}

		ContextManager* contextManager = ContextManager::get();
		if (contextManager && contextManager->getCurrentThreadContext())
		{
			contextManager->setCurrentThreadContext(nullptr);
		}

		if (_window)
		{
			glfwDestroyWindow(static_cast<GLFWwindow*>(_window));
		}
	}
}
