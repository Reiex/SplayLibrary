#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Functions and classes for multithreaded OpenGL manipulations.
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
	/// This class is a singleton. Only one instance of ContextManager shall exists and it is automatically created by
	/// SplayLibrary at the first use of `ContextManager::get`.
	/// 
	/// Any context created using SplayLibrary is registered in the ContextManager by the library.
	/// 
	/// All methods of ContextManager are thread safe.
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class ContextManager
	{
		public:

			static ContextManager* get();	///< Returns the context manager (create it if it was never required before).

			bool setCurrentThreadContext(Window* window);	///< Makes `window` the current thread's OpenGL context.
			const Window* getCurrentThreadContext() const;	///< Returns the current thread's current OpenGL context (by its window).

		private:

			ContextManager();
			~ContextManager();

			std::unordered_map<std::thread::id, Window*> _currentContexts;	///< List of contexts of each threads that have an OpenGL context.
	};
}
