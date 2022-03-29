#include <SplayLibrary/SplayLibrary.hpp>
#include <SplayLibrary/Private/Private.hpp>

namespace spl
{
	void Context::setClearColor(const vec4& clearColor)
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

	void Context::setViewport(const ivec2& offset, const uvec2& size)
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

	Window* Context::getWindow()
	{
		return _window;
	}

	Framebuffer* Context::getCurrentFramebuffer()
	{
		return _currentFramebuffer;
	}

	Shader* Context::getCurrentShader()
	{
		return _currentShader;
	}

	const vec4& Context::getClearColor() const
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

	const ivec2& Context::getViewportOffset() const
	{
		return _viewportOffset;
	}

	const uvec2& Context::getViewportSize() const
	{
		return _viewportSize;
	}

	bool Context::getIsDepthTestEnabled() const
	{
		return _isDepthTestEnabled;
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

	void ContextManager::initContext(Window* window)
	{
		Context* context = window->getContext();
		context->_window = window;
		context->_currentFramebuffer = &window->getFramebuffer();
		context->_currentShader = nullptr;
		context->_clearColor = { 0.f, 0.f, 0.f, 1.f };
		context->_clearDepth = 1.f;
		context->_clearStencil = 0;
		context->_viewportOffset = { 0, 0 };
		context->_viewportSize = window->getSize();
		context->_isDepthTestEnabled = false;
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