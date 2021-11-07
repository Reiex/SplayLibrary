#include <SplayLibrary/Core/Core.hpp>
#include <SplayLibrary/Core/Private.hpp>

namespace spl
{
	namespace
	{
		static ContextManager* SPL_CONTEXT_MANAGER = nullptr;
	}

	ContextManager::ContextManager() :
		_currentContexts()
	{
	}

	ContextManager* ContextManager::get()
	{
		static std::mutex mutex;

		mutex.lock();
		if (!SPL_CONTEXT_MANAGER)
		{
			if (glfwInit())
			{
				SPL_CONTEXT_MANAGER = new ContextManager();
			}
			else
			{
				SPL_DEBUG("Could not load GLFW.");
			}
		}
		mutex.unlock();

		return SPL_CONTEXT_MANAGER;
	}

	bool ContextManager::setCurrentThreadContext(Window* window)
	{
		static std::mutex mutex;

		mutex.lock();

		std::thread::id currentThreadId = std::this_thread::get_id();
		for (const std::pair<const std::thread::id, Window*>& x : _currentContexts)
		{
			if (x.first == currentThreadId && x.second == window)
			{
				mutex.unlock();	// The context is already assigned to the current thread
				return true;
			}
			else if (x.first == currentThreadId && x.second != window && window != nullptr)
			{
				assert(false);	// Attempting to assign two contexts to a single thread !
				mutex.unlock();
				return false;
			}
			else if (x.first != currentThreadId && x.second == window)
			{
				assert(false);	// Attempting to assign a context to two different threads !
				mutex.unlock();
				return false;
			}
		}

		if (window)
		{
			GLFWwindow* glfwWindow = static_cast<GLFWwindow*>(window->getHandle());
			glfwMakeContextCurrent(glfwWindow);

			if (_currentContexts.empty())
			{
				if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
				{
					SPL_DEBUG("Could not load OpenGL functions.");
					glfwMakeContextCurrent(nullptr);
					mutex.unlock();
					return false;
				}
			}

			_currentContexts[currentThreadId] = window;
		}
		else
		{
			glfwMakeContextCurrent(nullptr);
			_currentContexts.erase(currentThreadId);
		}

		mutex.unlock();

		return true;
	}

	const Window* ContextManager::getCurrentThreadContext() const
	{
		std::thread::id currentThreadId = std::this_thread::get_id();
		const auto& it = _currentContexts.find(currentThreadId);
		if (it != _currentContexts.end())
		{
			return it->second;
		}
		else
		{
			return nullptr;
		}
	}

	ContextManager::~ContextManager()
	{
		glfwTerminate();
	}
}