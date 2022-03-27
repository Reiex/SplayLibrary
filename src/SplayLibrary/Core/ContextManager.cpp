#include <SplayLibrary/SplayLibrary.hpp>
#include <SplayLibrary/Core/Private.hpp>

namespace spl
{
	namespace
	{
		ContextManager* s_contextManager = nullptr;
		std::mutex s_contextManagerMutex;
	}

	ContextManager::ContextManager() :
		_contexts(),
		_currentContexts()
	{
	}

	ContextManager* ContextManager::getContextManager()
	{
		s_contextManagerMutex.lock();

		if (!s_contextManager)
		{
			if (glfwInit())
			{
				s_contextManager = new ContextManager();
			}
			else
			{
				SPL_DEBUG("Could not load GLFW.");
			}
		}

		s_contextManagerMutex.unlock();

		return s_contextManager;
	}
	
	ContextManager::Context* ContextManager::createContext(Window* window)
	{
		Context* context = new Context;
		context->window = window;
		context->currentFramebuffer = nullptr;
		context->currentShader = nullptr;

		s_contextManagerMutex.lock();
		_contexts.insert(context);
		s_contextManagerMutex.unlock();

		return context;
	}

	bool ContextManager::setCurrentContext(nullptr_t ptr)
	{
		return setCurrentContext(static_cast<Context*>(nullptr));
	}

	bool ContextManager::setCurrentContext(Context* context)
	{
		s_contextManagerMutex.lock();

		if (_contexts.find(context) == _contexts.end())
		{
			assert(false);
			s_contextManagerMutex.unlock();	// Unregistered context !
			return false;
		}

		std::thread::id currentThreadId = std::this_thread::get_id();
		for (const std::pair<const std::thread::id, Context*>& x : _currentContexts)
		{
			if (x.first == currentThreadId && x.second == context)
			{
				s_contextManagerMutex.unlock();	// The context is already assigned to the current thread !
				return true;
			}
			else if (x.first == currentThreadId && x.second != context && context != nullptr)
			{
				assert(false);
				s_contextManagerMutex.unlock();	// Attempting to assign two contexts to a single thread !
				return false;
			}
			else if (x.first != currentThreadId && x.second == context)
			{
				assert(false);
				s_contextManagerMutex.unlock();	// Attempting to assign a context to two different threads !
				return false;
			}
		}

		if (context)
		{
			GLFWwindow* glfwWindow = static_cast<GLFWwindow*>(context->window->getHandle());
			glfwMakeContextCurrent(glfwWindow);

			if (_currentContexts.empty())
			{
				if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
				{
					SPL_DEBUG("Could not load OpenGL functions.");
					s_contextManagerMutex.unlock();
					return false;
				}
			}

			_currentContexts[currentThreadId] = context;
		}
		else
		{
			glfwMakeContextCurrent(nullptr);
			_currentContexts.erase(currentThreadId);
		}

		s_contextManagerMutex.unlock();

		return true;
	}

	bool ContextManager::setCurrentContext(const Window* window)
	{
		return setCurrentContext(getContext(window));
	}

	ContextManager::Context* ContextManager::getContext(const Window* window)
	{
		s_contextManagerMutex.lock();

		for (Context* context : _contexts)
		{
			if (context->window == window)
			{
				s_contextManagerMutex.unlock();
				return context;
			}
		}

		assert(false);	// Context related to window not found !
		s_contextManagerMutex.unlock();

		return nullptr;
	}

	ContextManager::Context* ContextManager::getCurrentContext()
	{
		s_contextManagerMutex.lock();

		std::thread::id currentThreadId = std::this_thread::get_id();
		const auto& it = _currentContexts.find(currentThreadId);

		if (it != _currentContexts.end())
		{
			s_contextManagerMutex.unlock();
			return it->second;
		}
		else
		{
			s_contextManagerMutex.unlock();
			return nullptr;
		}
	}

	bool ContextManager::destroyContext(Context* context)
	{
		s_contextManagerMutex.lock();

		auto it = _contexts.find(context);
		if (it == _contexts.end())
		{
			assert(false);
			s_contextManagerMutex.unlock();	// Context does not exist !
			return false;
		}

		for (const std::pair<const std::thread::id, Context*>& x : _currentContexts)
		{
			if (x.second == context)
			{
				assert(false);
				s_contextManagerMutex.unlock();	// Context is currently used !
				return false;
			}
		}

		delete context;
		_contexts.erase(it);

		if (_contexts.empty())
		{
			delete this;
		}

		s_contextManagerMutex.unlock();

		return true;
	}

	ContextManager::~ContextManager()
	{
		glfwTerminate();
	}
}