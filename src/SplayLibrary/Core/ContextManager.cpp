///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2019-2022
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SplayLibrary/SplayLibrary.hpp>
#include <SplayLibrary/Private/Private.hpp>

namespace spl
{
	namespace
	{
		DebugMessageSource glToDebugMessageSource(GLenum source)
		{
			switch (source)
			{
				case GL_DEBUG_SOURCE_API:
					return DebugMessageSource::Api;
				case GL_DEBUG_SOURCE_SHADER_COMPILER:
					return DebugMessageSource::ShaderCompiler;
				case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
					return DebugMessageSource::WindowSystem;
				case GL_DEBUG_SOURCE_THIRD_PARTY:
					return DebugMessageSource::ThirdParty;
				case GL_DEBUG_SOURCE_APPLICATION:
					return DebugMessageSource::Application;
				case GL_DEBUG_SOURCE_OTHER:
					return DebugMessageSource::Other;
				default:
					assert(false);
					return DebugMessageSource::Other;
			}
		}

		DebugMessageType glToDebugMessageType(GLenum type)
		{
			switch (type)
			{
				case GL_DEBUG_TYPE_ERROR:
					return DebugMessageType::Error;
				case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
					return DebugMessageType::DeprecatedBehavior;
				case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
					return DebugMessageType::UndefinedBehavior;
				case GL_DEBUG_TYPE_PERFORMANCE:
					return DebugMessageType::Performance;
				case GL_DEBUG_TYPE_PORTABILITY:
					return DebugMessageType::Portability;
				case GL_DEBUG_TYPE_MARKER:
					return DebugMessageType::Marker;
				case GL_DEBUG_TYPE_PUSH_GROUP:
					return DebugMessageType::PushGroup;
				case GL_DEBUG_TYPE_POP_GROUP:
					return DebugMessageType::PopGroup;
				case GL_DEBUG_TYPE_OTHER:
					return DebugMessageType::Other;
				default:
					assert(false);
					return DebugMessageType::Other;
			}
		}
		
		DebugMessageSeverity glToDebugMessageSeverity(GLenum severity)
		{
			switch (severity)
			{
				case GL_DEBUG_SEVERITY_HIGH:
					return DebugMessageSeverity::High;
				case GL_DEBUG_SEVERITY_MEDIUM:
					return DebugMessageSeverity::Medium;
				case GL_DEBUG_SEVERITY_LOW:
					return DebugMessageSeverity::Low;
				case GL_DEBUG_SEVERITY_NOTIFICATION:
					return DebugMessageSeverity::Notification;
				default:
					assert(false);
					return DebugMessageSeverity::High;
			}
		}
	}

	namespace
	{
		GLvoid debugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* rawMessage, const GLvoid* userParam)
		{
			DebugMessage* message = new DebugMessage();
			message->source = glToDebugMessageSource(source);
			message->type = glToDebugMessageType(type);
			message->id = id;
			message->severity = glToDebugMessageSeverity(severity);
			message->descr.assign(rawMessage, length);

			Context* context = const_cast<Context*>(reinterpret_cast<const Context*>(userParam));

			stackDebugMessage(message, context);
		}
	}

	static void stackDebugMessage(DebugMessage* message, Context* context)
	{
		context->_debugMessages.push(message);
	}


	Context::Context() :
		_window(nullptr),
		_debugContext(false),
		_hasBeenActivated(false),
		_currentFramebuffer(nullptr),
		_currentShader(nullptr),
		_clearColor(0.f, 0.f, 0.f, 1.f),
		_clearDepth(1.f),
		_clearStencil(0),
		_viewportOffset(0, 0),
		_viewportSize(0, 0),
		_isDepthTestEnabled(false),
		_debugMessages(),
		_lastDebugMessageSent(nullptr)
	{
	}

	void Context::setClearColor(const scp::f32vec4& clearColor)
	{
		assert(clearColor.x >= 0.f && clearColor.x <= 1);
		assert(clearColor.y >= 0.f && clearColor.y <= 1);
		assert(clearColor.z >= 0.f && clearColor.z <= 1);
		assert(clearColor.w >= 0.f && clearColor.w <= 1);

		_clearColor = clearColor;
		glClearColor(_clearColor.x, _clearColor.y, _clearColor.z, _clearColor.w);
	}

	void Context::setClearDepth(double clearDepth)
	{
		assert(clearDepth >= 0.f && clearDepth <= 1);

		_clearDepth = clearDepth;
		glClearDepth(_clearDepth);
	}

	void Context::setClearStencil(int32_t clearStencil)
	{
		_clearStencil = clearStencil;
		glClearStencil(_clearStencil);
	}

	void Context::setViewport(const scp::i32vec2& offset, const scp::u32vec2& size)
	{
		_viewportOffset = offset;
		_viewportSize = size;
		glViewport(_viewportOffset.x, _viewportOffset.y, _viewportSize.x, _viewportSize.y);
	}

	void Context::setIsDepthTestEnabled(bool isEnabled)
	{
		_isDepthTestEnabled = isEnabled;
		if (_isDepthTestEnabled)
		{
			glEnable(GL_DEPTH_TEST);
		}
		else
		{
			glDisable(GL_DEPTH_TEST);
		}
	}

	bool Context::pollDebugMessage(DebugMessage*& message)
	{
		if (_debugMessages.size() > 0 && _debugMessages.front() == _lastDebugMessageSent)
		{
			delete _debugMessages.front();
			_debugMessages.pop();
			_lastDebugMessageSent = nullptr;
		}

		if (_debugMessages.size() == 0)
		{
			return false;
		}

		message = _debugMessages.front();
		_lastDebugMessageSent = message;

		return true;
	}

	Window* Context::getWindow()
	{
		return _window;
	}

	bool Context::getIsDebugContext() const
	{
		return _debugContext;
	}

	Framebuffer* Context::getCurrentFramebuffer()
	{
		return _currentFramebuffer;
	}

	Shader* Context::getCurrentShader()
	{
		return _currentShader;
	}

	const scp::f32vec4& Context::getClearColor() const
	{
		return _clearColor;
	}

	double Context::getClearDepth() const
	{
		return _clearDepth;
	}

	int32_t Context::getClearStencil() const
	{
		return _clearStencil;
	}

	const scp::i32vec2& Context::getViewportOffset() const
	{
		return _viewportOffset;
	}

	const scp::u32vec2& Context::getViewportSize() const
	{
		return _viewportSize;
	}

	bool Context::getIsDepthTestEnabled() const
	{
		return _isDepthTestEnabled;
	}

	Context::~Context()
	{
		while (!_debugMessages.empty())
		{
			delete _debugMessages.front();
			_debugMessages.pop();
		}
	}

	void Context::setWindow(Window* window)
	{
		_window = window;
		_currentFramebuffer = &window->getFramebuffer();
		_viewportSize = window->getSize();
	}

	void Context::onFirstActivation()
	{
		if (_debugContext)
		{
			glEnable(GL_DEBUG_OUTPUT);
			glDebugMessageCallback((GLDEBUGPROC)(&debugMessageCallback), this);
			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, true);
		}
		else
		{
			glDisable(GL_DEBUG_OUTPUT);
		}
	}


	std::mutex ContextManager::s_mutex;
	std::unordered_set<Context*> ContextManager::s_contexts;
	std::unordered_map<std::thread::id, Context*> ContextManager::s_currentContexts;

	Context* ContextManager::createContext()
	{
		s_mutex.lock();

		if (s_contexts.empty())
		{
			if (!glfwInit())
			{
				s_mutex.unlock();	// Could not initialize glfw
				return nullptr;
			}
		}

		Context* context = new Context();
		s_contexts.insert(context);

		s_mutex.unlock();

		return context;
	}

	bool ContextManager::setCurrentContext(Context* context)
	{
		s_mutex.lock();

		if (context != nullptr && s_contexts.find(context) == s_contexts.end())
		{
			assert(false);
			s_mutex.unlock();	// Context does not exist
			return false;
		}

		std::thread::id currentThreadId = std::this_thread::get_id();
		for (const std::pair<const std::thread::id, Context*>& x : s_currentContexts)
		{
			if (x.first == currentThreadId && x.second == context)
			{
				s_mutex.unlock();	// The context is already assigned to the current thread !
				return true;
			}
			else if (x.first == currentThreadId && x.second != context && context != nullptr)
			{
				assert(false);
				s_mutex.unlock();	// Attempting to assign two contexts to a single thread !
				return false;
			}
			else if (x.first != currentThreadId && x.second == context)
			{
				assert(false);
				s_mutex.unlock();	// Attempting to assign a context to two different threads !
				return false;
			}
		}

		if (context)
		{
			GLFWwindow* glfwWindow = static_cast<GLFWwindow*>(context->_window->getHandle());
			glfwMakeContextCurrent(glfwWindow);

			if (s_currentContexts.empty())
			{
				if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
				{
					s_mutex.unlock();	// Could not load GL functions
					return false;
				}
			}

			s_currentContexts[currentThreadId] = context;

			if (!context->_hasBeenActivated)
			{
				context->_hasBeenActivated = true;
				context->onFirstActivation();
			}
		}
		else
		{
			glfwMakeContextCurrent(nullptr);
			s_currentContexts.erase(currentThreadId);
		}

		s_mutex.unlock();

		return true;
	}

	bool ContextManager::isInValidContext()
	{
		return getCurrentContext() != nullptr;
	}

	Context* ContextManager::getCurrentContext()
	{
		s_mutex.lock();

		std::thread::id currentThreadId = std::this_thread::get_id();
		const auto& it = s_currentContexts.find(currentThreadId);

		if (it != s_currentContexts.end())
		{
			s_mutex.unlock();
			return it->second;
		}
		else
		{
			s_mutex.unlock();
			return nullptr;
		}
	}

	bool ContextManager::destroyContext(Context* context)
	{
		s_mutex.lock();

		auto it = s_contexts.find(context);
		if (it == s_contexts.end())
		{
			assert(false);
			s_mutex.unlock();	// Context does not exist !
			return false;
		}

		for (const std::pair<const std::thread::id, Context*>& x : s_currentContexts)
		{
			if (x.second == context)
			{
				assert(false);
				s_mutex.unlock();	// Context is currently used !
				return false;
			}
		}

		delete context;
		s_contexts.erase(it);

		if (s_contexts.empty())
		{
			glfwTerminate();
		}

		s_mutex.unlock();

		return true;
	}
}
