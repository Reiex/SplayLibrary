#include <SplayLibrary/SplayLibrary.hpp>
#include <SplayLibrary/Private/Private.hpp>

namespace spl
{
	std::mutex ContextManager::s_mutex;
	std::unordered_set<ContextManager::Context*> ContextManager::s_contexts;
	std::unordered_map<std::thread::id, ContextManager::Context*> ContextManager::s_currentContexts;

	bool ContextManager::createContext(Window& window)
	{
		s_mutex.lock();

		if (s_contexts.empty())
		{
			if (!glfwInit())
			{
				s_mutex.unlock();	// Could not initialize GLFW
				return false;
			}
		}

		Context* context = new Context;
		context->window = &window;
		context->currentFramebuffer = &window.getFramebuffer();
		context->currentShader = nullptr;
		s_contexts.insert(context);
		
		s_mutex.unlock();

		return true;
	}

	bool ContextManager::setCurrentContext(nullptr_t ptr)
	{
		return setCurrentContext(static_cast<Context*>(nullptr));
	}

	bool ContextManager::setCurrentContext(const Window& window)
	{
		return setCurrentContext(getContext(window));
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
			GLFWwindow* glfwWindow = static_cast<GLFWwindow*>(context->window->getHandle());
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

	ContextManager::Context* ContextManager::getCurrentContext()
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

	ContextManager::Context* ContextManager::getContext(const Window& window)
	{
		s_mutex.lock();

		for (Context* context : s_contexts)
		{
			if (context->window == &window)
			{
				s_mutex.unlock();
				return context;
			}
		}

		assert(false);	// Context related to window not found !
		s_mutex.unlock();

		return nullptr;
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