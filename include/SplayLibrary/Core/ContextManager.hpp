///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2019-2022
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <SplayLibrary/Core/types.hpp>

namespace spl
{
	enum class DebugMessageSource
	{
		Api,
		ShaderCompiler,
		WindowSystem,
		ThirdParty,
		Application,
		Other
	};

	enum class DebugMessageType
	{
		Error,
		DeprecatedBehavior,
		UndefinedBehavior,
		Performance,
		Portability,
		Marker,
		PushGroup,
		PopGroup,
		Other
	};

	enum class DebugMessageSeverity
	{
		High,
		Medium,
		Low,
		Notification
	};

	struct DebugMessage
	{
		DebugMessageSource source;
		DebugMessageType type;
		uint32_t id;

		DebugMessageSeverity severity;
		std::string descr;
	};

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

			bool pollDebugMessage(DebugMessage*& message);

			Window* getWindow();
			bool getIsDebugContext() const;
			Framebuffer* getCurrentFramebuffer();
			Shader* getCurrentShader();
			const vec4& getClearColor() const;
			double getClearDepth() const;
			int32_t getClearStencil() const;
			const ivec2& getViewportOffset() const;
			const uvec2& getViewportSize() const;
			bool getIsDepthTestEnabled() const;

			~Context();

		private:

			Context();

			void setWindow(Window* window);
			void onFirstActivation();

			Window* _window;
			bool _debugContext;
			bool _hasBeenActivated;

			// TODO ? (costly, maybe in debug) : Check buffers binding
			Framebuffer* _currentFramebuffer;
			Shader* _currentShader;

			vec4 _clearColor;
			double _clearDepth;
			int32_t _clearStencil;
			ivec2 _viewportOffset;
			uvec2 _viewportSize;
			bool _isDepthTestEnabled;

			std::queue<DebugMessage*> _debugMessages;
			DebugMessage* _lastDebugMessageSent;

		friend class ContextManager;
		friend class Window;
		friend void stackDebugMessage(DebugMessage* message, Context* context);
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
			static bool destroyContext(Context* context);


			static std::mutex s_mutex;
			static std::unordered_set<Context*> s_contexts;
			static std::unordered_map<std::thread::id, Context*> s_currentContexts;

		friend class Window;
	};
}
