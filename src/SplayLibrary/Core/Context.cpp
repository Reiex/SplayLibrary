///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2021-2023
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SplayLibrary/Core/Core.hpp>
#include <SplayLibrary/Private/PrivateNotIncluded.hpp>

namespace spl
{
	namespace
	{
		void APIENTRY debugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* rawMessage, const void* userParam)
		{
			DebugMessage* message = new DebugMessage();
			message->source = _spl::glToDebugMessageSource(source);
			message->type = _spl::glToDebugMessageType(type);
			message->id = id;
			message->severity = _spl::glToDebugMessageSeverity(severity);
			message->descr.assign(rawMessage, length);

			Context* context = const_cast<Context*>(reinterpret_cast<const Context*>(userParam));

			stackDebugMessage(message, context);
		}
	}

	static void stackDebugMessage(DebugMessage* message, Context* context)
	{
		context->_debugMessages.push(message);
	}


	std::mutex Context::_mutex;
	std::unordered_set<Context*> Context::_contexts;
	std::unordered_map<std::thread::id, Context*> Context::_currentContexts;

	Context::Context() :
		_debugContext(false),
		_debugMessages(),
		_lastDebugMessageSent(nullptr),

		_clearColor(0.f, 0.f, 0.f, 0.f),
		_clearDepth(1.0),
		_clearStencil(0),
		_viewport(0, 0, 0, 0),
		_isSeamlessCubeMapFilteringEnabled(false),
		_isDepthTestEnabled(false),
		_faceCulling(FaceCulling::Disabled),

		_bufferBindings(),
		_indexedBufferBindings(),
		_textureBindings(),
		_framebufferBindings(),
		_shaderBinding(nullptr),

		_window(nullptr),
		_hasBeenActivated(false)
	{
		_bufferBindings.fill(nullptr);
		_indexedBufferBindings.fill({});	// TODO: Replace dynamic size vectors with static size vectors (contexte state queries...) (same for _textureBindings)
		_framebufferBindings.fill(nullptr);
	}

	bool Context::getIsDebugContext() const
	{
		return _debugContext;
	}

	bool Context::pollDebugMessage(DebugMessage*& message)
	{
		if (_debugMessages.size() > 0 && _debugMessages.front() == _lastDebugMessageSent)
		{
			delete _debugMessages.front();
			_debugMessages.pop();
			_lastDebugMessageSent = nullptr;
		}

		if (_debugMessages.size() == 0)
		{
			return false;
		}

		message = _debugMessages.front();
		_lastDebugMessageSent = message;

		return true;
	}

	const ImplementationDependentValues& Context::getImplementationDependentValues() const
	{
		return _implementationDependentValues;
	}

	void Context::setClearColor(float r, float g, float b, float a)
	{
		assert(r >= 0.f && r <= 1);
		assert(g >= 0.f && g <= 1);
		assert(b >= 0.f && b <= 1);
		assert(a >= 0.f && a <= 1);

		_clearColor.x = r;
		_clearColor.y = g;
		_clearColor.z = b;
		_clearColor.w = a;

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

	void Context::setViewport(int32_t xOffset, int32_t yOffset, uint32_t width, uint32_t height)
	{
		_viewport.x = xOffset;
		_viewport.y = yOffset;
		_viewport.z = width;
		_viewport.w = height;

		glViewport(_viewport.x, _viewport.y, _viewport.z, _viewport.w);
	}

	void Context::setIsSeamlessCubeMapFilteringEnabled(bool isEnabled)
	{
		_isSeamlessCubeMapFilteringEnabled = isEnabled;
		if (_isSeamlessCubeMapFilteringEnabled)
		{
			glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
		}
		else
		{
			glDisable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
		}
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

	void Context::setFaceCulling(FaceCulling faceCulling)
	{
		switch (faceCulling)
		{
			case FaceCulling::Disabled:
				glDisable(GL_CULL_FACE);
				return;
			case FaceCulling::BackClockWise:
				glEnable(GL_CULL_FACE);
				glCullFace(GL_BACK);
				glFrontFace(GL_CW);
				return;
			case FaceCulling::BackCounterClockWise:
				glEnable(GL_CULL_FACE);
				glCullFace(GL_BACK);
				glFrontFace(GL_CCW);
				return;
			case FaceCulling::FrontClockWise:
				glEnable(GL_CULL_FACE);
				glCullFace(GL_FRONT);
				glFrontFace(GL_CW);
				return;
			case FaceCulling::FrontCounterClockWise:
				glEnable(GL_CULL_FACE);
				glCullFace(GL_FRONT);
				glFrontFace(GL_CCW);
				return;
			case FaceCulling::FrontAndBackClockWise:
				glEnable(GL_CULL_FACE);
				glCullFace(GL_FRONT_AND_BACK);
				glFrontFace(GL_CW);
				return;
			case FaceCulling::FrontAndBackCounterClockWise:
				glEnable(GL_CULL_FACE);
				glCullFace(GL_FRONT_AND_BACK);
				glFrontFace(GL_CCW);
				return;
			default:
				assert(false);
				return;
		}
	}

	const scp::f32vec4& Context::getClearColor() const
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

	const scp::i32vec4& Context::getViewport() const
	{
		return _viewport;
	}

	bool Context::getIsSeamlessCubeMapFilteringEnabled() const
	{
		return _isSeamlessCubeMapFilteringEnabled;
	}

	bool Context::getIsDepthTestEnabled() const
	{
		return _isDepthTestEnabled;
	}

	FaceCulling Context::getFaceCulling() const
	{
		return _faceCulling;
	}

	const Buffer* Context::getBufferBinding(BufferTarget target, uint32_t index) const
	{
		if (_spl::isIndexedBufferTarget(target))
		{
			if (index < _indexedBufferBindings[_spl::bufferTargetContextIndex(target)].size())
			{
				return _indexedBufferBindings[_spl::bufferTargetContextIndex(target)][index];
			}
			else
			{
				return nullptr;
			}
		}
		else
		{
			return _bufferBindings[_spl::bufferTargetContextIndex(target)];
		}
	}

	const RawTexture* Context::getTextureBinding(TextureTarget target, uint32_t textureUnit) const
	{
		assert(target != TextureTarget::Undefined);

		if (textureUnit < _textureBindings.size())
		{
			return _textureBindings[textureUnit][static_cast<uint32_t>(target) - 1];
		}
		else
		{
			return nullptr;
		}
	}

	const Framebuffer* Context::getFramebufferBinding(FramebufferTarget target) const
	{
		return _framebufferBindings[static_cast<uint32_t>(target)];
	}

	const ShaderProgram* Context::getShaderBinding() const
	{
		return _shaderBinding;
	}

	Window* Context::getWindow()
	{
		return _window;
	}

	bool Context::setCurrentContext(Context* context)
	{
		_mutex.lock();

		if (context != nullptr && _contexts.find(context) == _contexts.end())
		{
			assert(false);
			_mutex.unlock();	// Context does not exist
			return false;
		}

		std::thread::id currentThreadId = std::this_thread::get_id();
		for (const std::pair<const std::thread::id, Context*>& x : _currentContexts)
		{
			if (x.first == currentThreadId && x.second == context)
			{
				_mutex.unlock();	// The context is already assigned to the current thread !
				return true;
			}
			else if (x.first == currentThreadId && x.second != context && context != nullptr)
			{
				assert(false);
				_mutex.unlock();	// Attempting to assign two contexts to a single thread !
				return false;
			}
			else if (x.first != currentThreadId && x.second == context)
			{
				assert(false);
				_mutex.unlock();	// Attempting to assign a context to two different threads !
				return false;
			}
		}

		if (context)
		{
			GLFWwindow* glfwWindow = static_cast<GLFWwindow*>(context->_window->getHandle());
			glfwMakeContextCurrent(glfwWindow);

			if (_currentContexts.empty())
			{
				if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
				{
					_mutex.unlock();	// Could not load GL functions
					return false;
				}
			}

			_currentContexts[currentThreadId] = context;

			if (!context->_hasBeenActivated)
			{
				context->_hasBeenActivated = true;
				context->_onFirstActivation();
			}
		}
		else
		{
			glfwMakeContextCurrent(nullptr);
			_currentContexts.erase(currentThreadId);
		}

		_mutex.unlock();

		return true;
	}

	bool Context::isInValidContext()
	{
		return getCurrentContext() != nullptr;
	}

	Context* Context::getCurrentContext()
	{
		_mutex.lock();

		std::thread::id currentThreadId = std::this_thread::get_id();
		const auto& it = _currentContexts.find(currentThreadId);

		if (it != _currentContexts.end())
		{
			_mutex.unlock();
			return it->second;
		}
		else
		{
			_mutex.unlock();
			return nullptr;
		}
	}

	Context::~Context()
	{
		while (!_debugMessages.empty())
		{
			delete _debugMessages.front();
			_debugMessages.pop();
		}
	}

	Context* Context::_createContext()
	{
		_mutex.lock();

		if (_contexts.empty())
		{
			if (!glfwInit())
			{
				_mutex.unlock();	// Could not initialize glfw
				return nullptr;
			}
		}

		Context* context = new Context();
		_contexts.insert(context);

		_mutex.unlock();

		return context;
	}

	bool Context::_destroyContext(Context* context)
	{
		_mutex.lock();

		auto it = _contexts.find(context);
		if (it == _contexts.end())
		{
			assert(false);
			_mutex.unlock();	// Context does not exist !
			return false;
		}

		for (const std::pair<const std::thread::id, Context*>& x : _currentContexts)
		{
			if (x.second == context)
			{
				assert(false);
				_mutex.unlock();	// Context is currently used !
				return false;
			}
		}

		delete context;
		_contexts.erase(it);

		if (_contexts.empty())
		{
			glfwTerminate();
		}

		_mutex.unlock();

		return true;
	}

	void Context::_setWindow(Window* window)
	{
		_window = window;
		_framebufferBindings.fill(&window->getFramebuffer());
		_viewport.z = window->getSize().x;
		_viewport.w = window->getSize().y;
	}

	void Context::_onFirstActivation()
	{
		if (_debugContext)
		{
			glEnable(GL_DEBUG_OUTPUT);
			glDebugMessageCallback(&debugMessageCallback, this);
			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, true);
		}
		else
		{
			glDisable(GL_DEBUG_OUTPUT);
		}

		setIsSeamlessCubeMapFilteringEnabled(true);
		setIsDepthTestEnabled(true);
		setFaceCulling(FaceCulling::FrontClockWise);

		_loadImplementationDependentValues();
	}

	namespace
	{
		template<typename T>
		inline void loadValue(GLenum name, T* value)
		{
			if constexpr (std::same_as<T, uint32_t> || std::same_as<T, int32_t> || std::same_as<T, scp::u32vec2>)
			{
				glGetIntegerv(name, reinterpret_cast<GLint*>(value));
			}
			else if constexpr (std::same_as<T, uint64_t> || std::same_as<T, int64_t>)
			{
				glGetInteger64v(name, reinterpret_cast<GLint64*>(value));
			}
			else if constexpr (std::same_as<T, bool>)
			{
				glGetBooleanv(name, reinterpret_cast<GLboolean*>(value));
			}
			else if constexpr (std::same_as<T, float> || std::same_as<T, scp::f32vec2>)
			{
				glGetFloatv(name, reinterpret_cast<GLfloat*>(value));
			}
			else if constexpr (std::same_as<T, ContextReleaseBehaviour>)
			{
				GLint buffer;
				glGetIntegerv(name, &buffer);
				*value = _spl::glToContextReleaseBehaviour(buffer);
			}
			else if constexpr (std::same_as<T, ProvokingVertexConvention>)
			{
				GLint buffer;
				glGetIntegerv(name, &buffer);
				*value = _spl::glToProvokingVertexConvention(buffer);
			}
			else if constexpr (std::same_as<T, ContextFlags::Flags>)
			{
				GLint buffer;
				glGetIntegerv(name, &buffer);
				*value = _spl::glToContextFlags(buffer);
			}
			else if constexpr (std::same_as<T, ContextProfileMask::Flags>)
			{
				GLint buffer;
				glGetIntegerv(name, &buffer);
				*value = _spl::glToContextProfileMask(buffer);
			}
			else if constexpr (std::same_as<T, std::string>)
			{
				value->assign(reinterpret_cast<const char*>(glGetString(name)));
			}
			else if constexpr (std::same_as<T, std::vector<std::string>>)
			{
				for (uint32_t i = 0; i < value->size(); ++i)
				{
					(*value)[i].assign(reinterpret_cast<const char*>(glGetStringi(name, i)));
				}
			}
			else if (std::same_as<T, scp::u32vec3>)
			{
				glGetIntegeri_v(name, 0, reinterpret_cast<GLint*>(&value->x));
				glGetIntegeri_v(name, 1, reinterpret_cast<GLint*>(&value->y));
				glGetIntegeri_v(name, 2, reinterpret_cast<GLint*>(&value->z));
			}
		}
	}

	void Context::_loadImplementationDependentValues()
	{
		GLint buffer;

		ImplementationDependent::General& general = _implementationDependentValues.general;
		loadValue(GL_CONTEXT_RELEASE_BEHAVIOR,							&general.contextReleaseBehaviour);
		loadValue(GL_MAX_CLIP_DISTANCES,								&general.maxClipDistances);
		loadValue(GL_MAX_CULL_DISTANCES,								&general.maxCullDistances);
		loadValue(GL_MAX_COMBINED_CLIP_AND_CULL_DISTANCES,				&general.maxCombinedClipAndCullDistances);
		loadValue(GL_SUBPIXEL_BITS,										&general.subpixelBits);
		loadValue(GL_MAX_ELEMENT_INDEX,									&general.maxElementIndex);
		loadValue(GL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED,			&general.primitiveRestartForPatchesSupported);
		loadValue(GL_MAX_3D_TEXTURE_SIZE,								&general.max3dTextureSize);
		loadValue(GL_MAX_TEXTURE_SIZE,									&general.maxTextureSize);
		loadValue(GL_MAX_ARRAY_TEXTURE_LAYERS,							&general.maxArrayTextureLayers);
		loadValue(GL_MAX_TEXTURE_LOD_BIAS,								&general.maxTextureLodBias);
		loadValue(GL_MAX_CUBE_MAP_TEXTURE_SIZE,							&general.maxCubeMapTextureSize);
		loadValue(GL_MAX_RENDERBUFFER_SIZE,								&general.maxRenderbufferSize);
		loadValue(GL_MAX_TEXTURE_MAX_ANISOTROPY,						&general.maxTextureMaxAnisotropy);
		loadValue(GL_MAX_VIEWPORT_DIMS,									&general.maxViewportDims);
		loadValue(GL_MAX_VIEWPORTS,										&general.maxViewports);
		loadValue(GL_VIEWPORT_SUBPIXEL_BITS,							&general.viewportSubpixelBits);
		loadValue(GL_VIEWPORT_BOUNDS_RANGE,								&general.viewportBoundsRange);
		loadValue(GL_LAYER_PROVOKING_VERTEX,							&general.layerProvokingVertex);
		loadValue(GL_VIEWPORT_INDEX_PROVOKING_VERTEX,					&general.viewportIndexProvokingVertex);
		loadValue(GL_POINT_SIZE_RANGE,									&general.pointSizeRange);
		loadValue(GL_POINT_SIZE_GRANULARITY,							&general.pointSizeGranularity);
		loadValue(GL_ALIASED_LINE_WIDTH_RANGE,							&general.aliasedLineWidthRange);
		loadValue(GL_SMOOTH_LINE_WIDTH_RANGE,							&general.smoothLineWidthRange);
		loadValue(GL_SMOOTH_LINE_WIDTH_GRANULARITY,						&general.smoothLineWidthGranularity);
		loadValue(GL_MAX_ELEMENTS_INDICES,								&general.maxElementsIndices);
		loadValue(GL_MAX_ELEMENTS_VERTICES,								&general.maxElementsVertices);
		loadValue(GL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET,					&general.maxVertexAttribRelativeOffset);
		loadValue(GL_MAX_VERTEX_ATTRIB_BINDINGS,						&general.maxVertexAttribBindings);
		loadValue(GL_MAX_VERTEX_ATTRIB_STRIDE,							&general.maxVertexAttribStride);
		loadValue(GL_NUM_COMPRESSED_TEXTURE_FORMATS,					&buffer); general.compressedTextureFormats.resize(buffer);
		loadValue(GL_COMPRESSED_TEXTURE_FORMATS,						general.compressedTextureFormats.data());
		loadValue(GL_MAX_TEXTURE_BUFFER_SIZE,							&general.maxTextureBufferSize);
		loadValue(GL_MAX_RECTANGLE_TEXTURE_SIZE,						&general.maxRectangleTextureSize);
		loadValue(GL_NUM_SHADER_BINARY_FORMATS,							&buffer); general.shaderBinaryFormats.resize(buffer);
		loadValue(GL_SHADER_BINARY_FORMATS,								general.shaderBinaryFormats.data());
		loadValue(GL_NUM_PROGRAM_BINARY_FORMATS,						&buffer); general.programBinaryFormats.resize(buffer);
		loadValue(GL_PROGRAM_BINARY_FORMATS,							general.programBinaryFormats.data());
		loadValue(GL_SHADER_COMPILER,									&general.shaderCompiler);
		loadValue(GL_MIN_MAP_BUFFER_ALIGNMENT,							&general.minMapBufferAlignment);
		loadValue(GL_TEXTURE_BUFFER_OFFSET_ALIGNMENT,					&general.textureBufferOffsetAlignment);
		loadValue(GL_MAX_FRAMEBUFFER_WIDTH,								&general.maxFramebufferWidth);
		loadValue(GL_MAX_FRAMEBUFFER_HEIGHT,							&general.maxFramebufferHeight);
		loadValue(GL_MAX_FRAMEBUFFER_LAYERS,							&general.maxFramebufferLayers);
		loadValue(GL_MAX_FRAMEBUFFER_SAMPLES,							&general.maxFramebufferSamples);
		loadValue(GL_MAX_SAMPLE_MASK_WORDS,								&general.maxSampleMaskWords);
		loadValue(GL_MAX_SAMPLES,										&general.maxSamples);
		loadValue(GL_MAX_COLOR_TEXTURE_SAMPLES,							&general.maxColorTextureSamples);
		loadValue(GL_MAX_DEPTH_TEXTURE_SAMPLES,							&general.maxDepthTextureSamples);
		loadValue(GL_MAX_INTEGER_SAMPLES,								&general.maxIntegerSamples);
		loadValue(GL_MAX_SERVER_WAIT_TIMEOUT,							&general.maxServerWaitTimeout);
		loadValue(GL_MIN_FRAGMENT_INTERPOLATION_OFFSET,					&general.minFragmentInterpolationOffset);
		loadValue(GL_MAX_FRAGMENT_INTERPOLATION_OFFSET,					&general.maxFragmentInterpolationOffset);
		loadValue(GL_FRAGMENT_INTERPOLATION_OFFSET_BITS,				&general.fragmentInterpolationOffsetBits);
		loadValue(GL_MAX_DRAW_BUFFERS,									&general.maxDrawBuffers);
		loadValue(GL_MAX_DUAL_SOURCE_DRAW_BUFFERS,						&general.maxDualSourceDrawBuffers);
		loadValue(GL_MAX_COLOR_ATTACHMENTS,								&general.maxColorAttachments);

		ImplementationDependent::Version& version = _implementationDependentValues.version;
		loadValue(GL_MAJOR_VERSION,										&version.majorVersion);
		loadValue(GL_MINOR_VERSION,										&version.minorVersion);
		loadValue(GL_CONTEXT_FLAGS,										&version.contextFlags);
		loadValue(GL_CONTEXT_PROFILE_MASK,								&version.contextProfile);
		loadValue(GL_NUM_EXTENSIONS,									&buffer); version.extensions.resize(buffer);
		loadValue(GL_EXTENSIONS,										&version.extensions);
		loadValue(GL_RENDERER,											&version.renderer);
		loadValue(GL_NUM_SHADING_LANGUAGE_VERSIONS,						&buffer); version.shadingLanguageVersions.resize(buffer);
		loadValue(GL_SHADING_LANGUAGE_VERSION,							&version.shadingLanguageVersions);
		loadValue(GL_NUM_SPIR_V_EXTENSIONS,								&buffer); version.spirvExtensions.resize(buffer);
		loadValue(GL_SPIR_V_EXTENSIONS,									&version.spirvExtensions);
		loadValue(GL_VENDOR,											&version.vendor);

		ImplementationDependent::VertexShaderLimits& vertexShader = _implementationDependentValues.vertexShader;
		loadValue(GL_MAX_VERTEX_ATTRIBS,								&vertexShader.maxVertexAttribs);
		loadValue(GL_MAX_VERTEX_UNIFORM_COMPONENTS,						&vertexShader.maxVertexUniformComponents);
		loadValue(GL_MAX_VERTEX_UNIFORM_VECTORS,						&vertexShader.maxVertexUniformVectors);
		loadValue(GL_MAX_VERTEX_UNIFORM_BLOCKS,							&vertexShader.maxVertexUniformBlocks);
		loadValue(GL_MAX_VERTEX_OUTPUT_COMPONENTS,						&vertexShader.maxVertexOutputComponents);
		loadValue(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,					&vertexShader.maxVertexTextureImageUnits);
		loadValue(GL_MAX_VERTEX_ATOMIC_COUNTER_BUFFERS,					&vertexShader.maxVertexAtomicCounterBuffers);
		loadValue(GL_MAX_VERTEX_ATOMIC_COUNTERS,						&vertexShader.maxVertexAtomicCounters);
		loadValue(GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS,					&vertexShader.maxVertexShaderStorageBlocks);

		ImplementationDependent::TessellationShaderLimits& tessellationShader = _implementationDependentValues.tessellationShader;
		loadValue(GL_MAX_TESS_GEN_LEVEL,								&tessellationShader.maxTessGenLevel);
		loadValue(GL_MAX_PATCH_VERTICES,								&tessellationShader.maxPatchVertices);
		loadValue(GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS,				&tessellationShader.maxTessControlUniformComponents);
		loadValue(GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS,				&tessellationShader.maxTessControlTextureImageUnits);
		loadValue(GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS,				&tessellationShader.maxTessControlOutputComponents);
		loadValue(GL_MAX_TESS_PATCH_COMPONENTS,							&tessellationShader.maxTessPatchComponents);
		loadValue(GL_MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS,			&tessellationShader.maxTessControlTotalOutputComponents);
		loadValue(GL_MAX_TESS_CONTROL_INPUT_COMPONENTS,					&tessellationShader.maxTessControlInputComponents);
		loadValue(GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS,					&tessellationShader.maxTessControlUniformBlocks);
		loadValue(GL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS,			&tessellationShader.maxTessControlAtomicCounterBuffers);
		loadValue(GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS,					&tessellationShader.maxTessControlAotmicCounters);
		loadValue(GL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS,			&tessellationShader.maxTessControlShaderStorageBlocks);
		loadValue(GL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS,			&tessellationShader.maxTessEvaluationUniformComponents);
		loadValue(GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS,			&tessellationShader.maxTessEvaluationTextureImageUnits);
		loadValue(GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS,				&tessellationShader.maxTessEvaluationOutputComponents);
		loadValue(GL_MAX_TESS_EVALUATION_INPUT_COMPONENTS,				&tessellationShader.maxTessEvaluationInputComponents);
		loadValue(GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS,				&tessellationShader.maxTessEvaluationUniformBlocks);
		loadValue(GL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS,		&tessellationShader.maxTessEvaluationAtomicCounterBuffers);
		loadValue(GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS,				&tessellationShader.maxTessEvaluationAtomicCounters);
		loadValue(GL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS,			&tessellationShader.maxTessEvaluationShaderStorageBlocks);

		ImplementationDependent::GeometryShaderLimits& geometryShader = _implementationDependentValues.geometryShader;
		loadValue(GL_MAX_GEOMETRY_UNIFORM_COMPONENTS,					&geometryShader.maxGeometryUniformComponents);
		loadValue(GL_MAX_GEOMETRY_UNIFORM_BLOCKS,						&geometryShader.maxGeometryUniformBlocks);
		loadValue(GL_MAX_GEOMETRY_INPUT_COMPONENTS,						&geometryShader.maxGeometryInputComponents);
		loadValue(GL_MAX_GEOMETRY_OUTPUT_COMPONENTS,					&geometryShader.maxGeometryOutputComponents);
		loadValue(GL_MAX_GEOMETRY_OUTPUT_VERTICES,						&geometryShader.maxGeometryOutputVertices);
		loadValue(GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS,				&geometryShader.maxGeometryTotalOutputComponents);
		loadValue(GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS,					&geometryShader.maxGeometryTextureImageUnits);
		loadValue(GL_MAX_GEOMETRY_SHADER_INVOCATIONS,					&geometryShader.maxGeometryShaderInvocations);
		loadValue(GL_MAX_VERTEX_STREAMS,								&geometryShader.maxVertexStreams);
		loadValue(GL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS,				&geometryShader.maxGeometryAtomicCounterBuffers);
		loadValue(GL_MAX_GEOMETRY_ATOMIC_COUNTERS,						&geometryShader.maxGeometryAtomicCounters);
		loadValue(GL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS,				&geometryShader.maxGeometryShaderStorageBlocks);

		ImplementationDependent::FragmentShaderLimits& fragmentShader = _implementationDependentValues.fragmentShader;
		loadValue(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,					&fragmentShader.maxFragmentUniformComponents);
		loadValue(GL_MAX_FRAGMENT_UNIFORM_VECTORS,						&fragmentShader.maxFragmentUniformVectors);
		loadValue(GL_MAX_FRAGMENT_UNIFORM_BLOCKS,						&fragmentShader.maxFragmentUniformBlocks);
		loadValue(GL_MAX_FRAGMENT_INPUT_COMPONENTS,						&fragmentShader.maxFragmentInputComponents);
		loadValue(GL_MAX_TEXTURE_IMAGE_UNITS,							&fragmentShader.maxTextureImageUnits);
		loadValue(GL_MIN_PROGRAM_TEXTURE_GATHER_OFFSET,					&fragmentShader.minProgramTextureGatherOffset);
		loadValue(GL_MAX_PROGRAM_TEXTURE_GATHER_OFFSET,					&fragmentShader.maxProgramTextureGatherOffset);
		loadValue(GL_MAX_FRAGMENT_ATOMIC_COUNTER_BUFFERS,				&fragmentShader.maxFragmentAtomicCounterBuffers);
		loadValue(GL_MAX_FRAGMENT_ATOMIC_COUNTERS,						&fragmentShader.maxFragmentAtomicCounters);
		loadValue(GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS,				&fragmentShader.maxFragmentShaderStorageBlocks);

		ImplementationDependent::ComputeShaderLimits& computeShader = _implementationDependentValues.computeShader;
		loadValue(GL_MAX_COMPUTE_WORK_GROUP_COUNT,						&computeShader.maxComputeWorkGroupCount);
		loadValue(GL_MAX_COMPUTE_WORK_GROUP_SIZE,						&computeShader.maxComputeWorkGroupSize);
		loadValue(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS,				&computeShader.maxComputeWorkGroupInvocations);
		loadValue(GL_MAX_COMPUTE_UNIFORM_BLOCKS,						&computeShader.maxComputeUniformBlocks);
		loadValue(GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS,					&computeShader.maxComputeTextureImageUnits);
		loadValue(GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS,				&computeShader.maxComputeAtomicCounterBuffers);
		loadValue(GL_MAX_COMPUTE_ATOMIC_COUNTERS,						&computeShader.maxComputeAtomicCounters);
		loadValue(GL_MAX_COMPUTE_SHARED_MEMORY_SIZE,					&computeShader.maxComputeSharedMemorySize);
		loadValue(GL_MAX_COMPUTE_UNIFORM_COMPONENTS,					&computeShader.maxComputeUniformComponents);
		loadValue(GL_MAX_COMPUTE_IMAGE_UNIFORMS,						&computeShader.maxComputeImageUniforms);
		loadValue(GL_MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS,			&computeShader.maxCombinedComputeUniformComponents);
		loadValue(GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS,					&computeShader.maxComputeShaderStorageBlocks);

		ImplementationDependent::AggregateShaderLimits& shader = _implementationDependentValues.shader;
		loadValue(GL_MIN_PROGRAM_TEXEL_OFFSET,							&shader.minProgramTexelOffset);
		loadValue(GL_MAX_PROGRAM_TEXEL_OFFSET,							&shader.maxProgramTexelOffset);
		loadValue(GL_MAX_UNIFORM_BUFFER_BINDINGS,						&shader.maxUniformBufferBindings);
		loadValue(GL_MAX_UNIFORM_BLOCK_SIZE,							&shader.maxUniformBlockSize);
		loadValue(GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT,					&shader.uniformBufferOffsetAlignment);
		loadValue(GL_MAX_COMBINED_UNIFORM_BLOCKS,						&shader.maxCombinedUniformBlocks);
		loadValue(GL_MAX_VARYING_COMPONENTS,							&shader.maxVaryingComponents);
		loadValue(GL_MAX_VARYING_VECTORS,								&shader.maxVaryingVectors);
		loadValue(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,					&shader.maxCombinedTextureImageUnits);
		loadValue(GL_MAX_SUBROUTINES,									&shader.maxSubroutines);
		loadValue(GL_MAX_SUBROUTINE_UNIFORM_LOCATIONS,					&shader.maxSubroutineUniformLocations);
		loadValue(GL_MAX_UNIFORM_LOCATIONS,								&shader.maxUniformLocations);
		loadValue(GL_MAX_ATOMIC_COUNTER_BUFFER_BINDINGS,				&shader.maxAtomicCounterBufferBindings);
		loadValue(GL_MAX_ATOMIC_COUNTER_BUFFER_SIZE,					&shader.maxAtomicCounterBufferSize);
		loadValue(GL_MAX_COMBINED_ATOMIC_COUNTER_BUFFERS,				&shader.maxCombinedAtomicCounterBuffers);
		loadValue(GL_MAX_COMBINED_ATOMIC_COUNTERS,						&shader.maxCombinedAtomicCounters);
		loadValue(GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS,				&shader.maxShaderStorageBufferBindings);
		loadValue(GL_MAX_SHADER_STORAGE_BLOCK_SIZE,						&shader.maxShaderStorageBlockSize);
		loadValue(GL_MAX_COMBINED_SHADER_STORAGE_BLOCKS,				&shader.maxCombinedShaderStorageBlocks);
		loadValue(GL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT,			&shader.shaderStorageBufferOffsetAlignment);
		loadValue(GL_MAX_IMAGE_UNITS,									&shader.maxImageUnits);
		loadValue(GL_MAX_COMBINED_SHADER_OUTPUT_RESOURCES,				&shader.maxCombinedShaderOutputResources);
		loadValue(GL_MAX_IMAGE_SAMPLES,									&shader.maxImageSamples);
		loadValue(GL_MAX_VERTEX_IMAGE_UNIFORMS,							&shader.maxVertexImageUniforms);
		loadValue(GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS,					&shader.maxTessControlImageUniforms);
		loadValue(GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS,				&shader.maxTessEvaluationImageUniforms);
		loadValue(GL_MAX_GEOMETRY_IMAGE_UNIFORMS,						&shader.maxGeometryImageUniforms);
		loadValue(GL_MAX_FRAGMENT_IMAGE_UNIFORMS,						&shader.maxFragmentImageUniforms);
		loadValue(GL_MAX_COMBINED_IMAGE_UNIFORMS,						&shader.maxCombinedImageUniforms);
		loadValue(GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS,			&shader.maxCombinedVertexUniformComponents);
		loadValue(GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS,			&shader.maxCombinedGeometryUniformComponents);
		loadValue(GL_MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS,		&shader.maxCombinedTessControlUniformComponents);
		loadValue(GL_MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS,	&shader.maxCombinedTessEvaluationUniformComponents);
		loadValue(GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS,			&shader.maxCombinedFragmentUniformComponents);

		ImplementationDependent::Debug& debug = _implementationDependentValues.debug;
		loadValue(GL_MAX_DEBUG_MESSAGE_LENGTH,							&debug.maxDebugMessageLength);
		loadValue(GL_MAX_DEBUG_LOGGED_MESSAGES,							&debug.maxDebugLoggedMessages);
		loadValue(GL_MAX_DEBUG_GROUP_STACK_DEPTH,						&debug.maxDebugGroupStackDepth);
		loadValue(GL_MAX_LABEL_LENGTH,									&debug.maxLabelLength);

		ImplementationDependent::TransformFeedbackLimits& transformFeedback = _implementationDependentValues.transformFeedback;
		loadValue(GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS,		&transformFeedback.maxTransformFeedbackInterleavedComponents);
		loadValue(GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS,			&transformFeedback.maxTransformFeedbackSeparateAttribs);
		loadValue(GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS,		&transformFeedback.maxTransformFeedbackSeparateComponents);
		loadValue(GL_MAX_TRANSFORM_FEEDBACK_BUFFERS,					&transformFeedback.maxTransformFeedbackBuffers);
	}
}
