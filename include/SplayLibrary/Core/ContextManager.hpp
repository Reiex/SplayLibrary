#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Functions and classes for OpenGL context management, single or multi threaded.
/// \author Reiex
/// 
/// For a more detailed description, see class ContextManager.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SplayLibrary/Core/types.hpp>

namespace spl
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \ingroup Core
	/// \class ContextManager
	/// \brief Class for OpenGL context manipulations. Allow for multithreading using SplayLibrary.
	/// 
	/// This class is a singleton. Only one instance of ContextManager shall exists and it is automatically created and
	/// destroyed by the library.
	/// 
	/// Any context created using SplayLibrary (when opening a window for instance) is registered in the ContextManager
	/// by the library.
	/// 
	/// All methods of ContextManager are thread safe.
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class ContextManager
	{
		public:

			struct Context
			{
				Window* window;

				Framebuffer* currentFramebuffer;
				Shader* currentShader;
			};

			static ContextManager* getContextManager();

			bool setCurrentContext(nullptr_t ptr);
			bool setCurrentContext(Context* context);
			bool setCurrentContext(const Window* window);
			Context* getContext(const Window* window);
			Context* getCurrentContext();

		private:

			ContextManager();

			Context* createContext(Window* window);
			bool destroyContext(Context* context);

			~ContextManager();

			std::unordered_set<Context*> _contexts;
			std::unordered_map<std::thread::id, Context*> _currentContexts;

		friend class Window;
	};
}
