#pragma once

#include <SplayLibrary/Core/types.hpp>

namespace spl
{
	class ContextManager
	{
		public:

			static ContextManager* get();

			bool setCurrentThreadContext(Window* window);
			const Window* getCurrentThreadContext() const;

		private:

			ContextManager();
			~ContextManager();

			std::unordered_map<std::thread::id, Window*> _currentContexts;
	};
}
