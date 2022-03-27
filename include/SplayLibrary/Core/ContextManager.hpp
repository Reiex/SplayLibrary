#pragma once

#include <SplayLibrary/Core/types.hpp>

namespace spl
{
	class ContextManager
	{
		public:

			ContextManager() = delete;

			struct Context
			{
				Window* window;

				const Framebuffer* currentFramebuffer;
				const Shader* currentShader;
			};

			static bool setCurrentContext(std::nullptr_t ptr);
			static bool setCurrentContext(const Window& window);

			static bool isInValidContext();
			static Context* getCurrentContext();

		private:

			static bool createContext(Window& window);

			static bool setCurrentContext(Context* context);

			static Context* getContext(const Window& window);

			static bool destroyContext(Context* context);


			static std::mutex s_mutex;
			static std::unordered_set<Context*> s_contexts;
			static std::unordered_map<std::thread::id, Context*> s_currentContexts;

		friend class Window;
	};
}
