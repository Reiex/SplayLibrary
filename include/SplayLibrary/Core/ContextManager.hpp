#pragma once

#include <SplayLibrary/Core/types.hpp>

namespace spl
{
	class Context
	{
		public:

			Context(const Context& context) = delete;
			Context(Context&& context) = delete;

			Context& operator=(const Context& context) = delete;
			Context& operator=(Context&& context) = delete;

			void setClearColor(const vec4& clearColor);
			void setClearDepth(double clearDepth);
			void setClearStencil(int32_t clearStencil);
			void setViewport(const ivec2& offset, const uvec2& size);
			void setIsDepthTestEnabled(bool isEnabled);

			Window* getWindow();
			Framebuffer* getCurrentFramebuffer();
			Shader* getCurrentShader();
			const vec4& getClearColor() const;
			double getClearDepth() const;
			int32_t getClearStencil() const;
			const ivec2& getViewportOffset() const;
			const uvec2& getViewportSize() const;
			bool getIsDepthTestEnabled() const;

			~Context() = default;

		private:

			Context() = default;

			Window* _window;

			Framebuffer* _currentFramebuffer;
			Shader* _currentShader;

			vec4 _clearColor;
			double _clearDepth;
			int32_t _clearStencil;
			ivec2 _viewportOffset;
			uvec2 _viewportSize;
			bool _isDepthTestEnabled;

		friend class ContextManager;
	};

	class ContextManager
	{
		public:

			ContextManager() = delete;

			static bool setCurrentContext(Context* context);

			static bool isInValidContext();
			static Context* getCurrentContext();

		private:

			static Context* createContext();
			static void initContext(Window* window);
			static bool destroyContext(Context* context);


			static std::mutex s_mutex;
			static std::unordered_set<Context*> s_contexts;
			static std::unordered_map<std::thread::id, Context*> s_currentContexts;

		friend class Window;
	};
}
