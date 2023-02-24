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
	ShaderProgram::ShaderProgram() :
		_program(0),
		_flags(ShaderProgramFlags::None),
		_linkStatus(0),
		_interfacesInfos(),
		_resourcesInfos(),
		_locations(),
		_locationIndices()
	{
	}

	ShaderProgram::ShaderProgram(const std::filesystem::path& glslCompute, ShaderProgramFlags::Flags flags) : ShaderProgram()
	{
		createFromGlsl(glslCompute, flags);
	}

	ShaderProgram::ShaderProgram(const std::filesystem::path& glslVertex, const std::filesystem::path& glslFragment, ShaderProgramFlags::Flags flags) : ShaderProgram()
	{
		createFromGlsl(glslVertex, glslFragment, flags);
	}

	ShaderProgram::ShaderProgram(const std::filesystem::path& glslVertex, const std::filesystem::path& glslGeometry, const std::filesystem::path& glslFragment, ShaderProgramFlags::Flags flags) : ShaderProgram()
	{
		createFromGlsl(glslVertex, glslGeometry, glslFragment, flags);
	}

	ShaderProgram::ShaderProgram(const std::filesystem::path& glslVertex, const std::filesystem::path& glslTessControl, const std::filesystem::path& glslTessEval, const std::filesystem::path& glslFragment, ShaderProgramFlags::Flags flags) : ShaderProgram()
	{
		createFromGlsl(glslVertex, glslTessControl, glslTessEval, glslFragment, flags);
	}

	ShaderProgram::ShaderProgram(const std::filesystem::path& glslVertex, const std::filesystem::path& glslTessControl, const std::filesystem::path& glslTessEval, const std::filesystem::path& glslGeometry, const std::filesystem::path& glslFragment, ShaderProgramFlags::Flags flags) : ShaderProgram()
	{
		createFromGlsl(glslVertex, glslTessControl, glslTessEval, glslGeometry, glslFragment, flags);
	}

	ShaderProgram::ShaderProgram(const ShaderModule* const* shaders, uint8_t count, ShaderProgramFlags::Flags flags) : ShaderProgram()
	{
		createFromShaderModules(shaders, count, flags);
	}

	bool ShaderProgram::createFromGlsl(const std::filesystem::path& glslCompute, ShaderProgramFlags::Flags flags)
	{
		ShaderModule shader;
		const ShaderModule* shaderArray[] = { &shader };

		if (shader.createFromGlsl(ShaderStage::Compute, glslCompute))
		{
			return createFromShaderModules(shaderArray, 1, flags);
		}

		return false;
	}

	bool ShaderProgram::createFromGlsl(const std::filesystem::path& glslVertex, const std::filesystem::path& glslFragment, ShaderProgramFlags::Flags flags)
	{
		ShaderModule shaders[2];
		const ShaderModule* shaderArray[] = { shaders, shaders + 1 };

		if (shaders[0].createFromGlsl(ShaderStage::Vertex, glslVertex)
			&& shaders[1].createFromGlsl(ShaderStage::Fragment, glslFragment))
		{
			return createFromShaderModules(shaderArray, 2, flags);
		}

		return false;
	}

	bool ShaderProgram::createFromGlsl(const std::filesystem::path& glslVertex, const std::filesystem::path& glslGeometry, const std::filesystem::path& glslFragment, ShaderProgramFlags::Flags flags)
	{
		ShaderModule shaders[3];
		const ShaderModule* shaderArray[] = { shaders, shaders + 1, shaders + 2 };

		if (shaders[0].createFromGlsl(ShaderStage::Vertex, glslVertex)
			&& shaders[1].createFromGlsl(ShaderStage::Geometry, glslGeometry)
			&& shaders[2].createFromGlsl(ShaderStage::Fragment, glslFragment))
		{
			return createFromShaderModules(shaderArray, 3, flags);
		}

		return false;
	}

	bool ShaderProgram::createFromGlsl(const std::filesystem::path& glslVertex, const std::filesystem::path& glslTessControl, const std::filesystem::path& glslTessEval, const std::filesystem::path& glslFragment, ShaderProgramFlags::Flags flags)
	{
		ShaderModule shaders[4];
		const ShaderModule* shaderArray[] = { shaders, shaders + 1, shaders + 2, shaders + 3 };

		if (shaders[0].createFromGlsl(ShaderStage::Vertex, glslVertex)
			&& shaders[1].createFromGlsl(ShaderStage::TessControl, glslTessControl)
			&& shaders[2].createFromGlsl(ShaderStage::TessEvaluation, glslTessEval)
			&& shaders[3].createFromGlsl(ShaderStage::Fragment, glslFragment))
		{
			return createFromShaderModules(shaderArray, 4, flags);
		}

		return false;
	}

	bool ShaderProgram::createFromGlsl(const std::filesystem::path& glslVertex, const std::filesystem::path& glslTessControl, const std::filesystem::path& glslTessEval, const std::filesystem::path& glslGeometry, const std::filesystem::path& glslFragment, ShaderProgramFlags::Flags flags)
	{
		ShaderModule shaders[5];
		const ShaderModule* shaderArray[] = { shaders, shaders + 1, shaders + 2, shaders + 3, shaders + 4 };

		if (shaders[0].createFromGlsl(ShaderStage::Vertex, glslVertex)
			&& shaders[1].createFromGlsl(ShaderStage::TessControl, glslTessControl)
			&& shaders[2].createFromGlsl(ShaderStage::TessEvaluation, glslTessEval)
			&& shaders[3].createFromGlsl(ShaderStage::Geometry, glslGeometry)
			&& shaders[4].createFromGlsl(ShaderStage::Fragment, glslFragment))
		{
			return createFromShaderModules(shaderArray, 5, flags);
		}

		return false;
	}

	bool ShaderProgram::createFromShaderModules(const ShaderModule* const* shaders, uint16_t count, ShaderProgramFlags::Flags flags)
	{
		for (uint16_t i = 0; i < count; ++i)
		{
			assert(shaders[i]->isValid());
		}

		destroy();

		_program = glCreateProgram();
		_flags = flags;
		glProgramParameteri(_program, GL_PROGRAM_SEPARABLE, ((_flags & ShaderProgramFlags::Separable) != 0));
		glProgramParameteri(_program, GL_PROGRAM_BINARY_RETRIEVABLE_HINT, ((_flags & ShaderProgramFlags::BinaryRetrievable) != 0));

		for (uint16_t i = 0; i < count; ++i)
		{
			glAttachShader(_program, shaders[i]->getHandle());
		}
		glLinkProgram(_program);
		glGetProgramiv(_program, GL_LINK_STATUS, &_linkStatus);

		if (_linkStatus)
		{
			_shaderIntrospection();
		}
		else
		{
			int32_t length;
			glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &length);

			char* buffer = reinterpret_cast<char*>(alloca(length));
			glGetProgramInfoLog(_program, length, nullptr, buffer);

			glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_ERROR, 0, GL_DEBUG_SEVERITY_HIGH, length, buffer);
		}

		return _linkStatus;
	}

	void ShaderProgram::destroy()
	{
		if (_program != 0)
		{
			glDeleteProgram(_program);
		}

		_program = 0;
		_flags = ShaderProgramFlags::None;
		_linkStatus = 0;

		_interfacesInfos.fill({});
		_resourcesInfos.fill({});
		_locations.fill({});
		_locationIndices.fill({});
	}

	const ShaderProgramInterfaceInfos& ShaderProgram::getInterfaceInfos(ShaderProgramInterface programInterface) const
	{
		assert(isValid());

		return _interfacesInfos[static_cast<uint8_t>(programInterface)];
	}

	const ShaderProgramResourceInfos& ShaderProgram::getResourceInfos(ShaderProgramInterface programInterface, uint32_t index) const
	{
		assert(isValid());
		assert(index < _interfacesInfos[static_cast<uint8_t>(programInterface)].activeResources);

		return _resourcesInfos[static_cast<uint8_t>(programInterface)][index];
	}

	void ShaderProgram::setUniform(const std::string& name, uint32_t textureUnit, const RawTexture& texture) const
	{
		RawTexture::bind(texture, texture.getCreationParams().target, textureUnit);
		_setUniform(name, GlslType::Int, &textureUnit, 1);
	}

	void ShaderProgram::setUniform(const std::string& name, uint32_t textureUnit, const TextureBase& texture) const
	{
		setUniform(name, textureUnit, texture.getRawTexture());
	}

	void ShaderProgram::setUniformBlockBinding(uint32_t shaderBindingIndex, uint32_t bufferBindingIndex) const
	{
		assert(isValid());
		// TODO: Verifications...

		glUniformBlockBinding(_program, shaderBindingIndex, bufferBindingIndex);
	}

	void ShaderProgram::setShaderStorageBlockBinding(uint32_t shaderBindingIndex, uint32_t bufferBindingIndex) const
	{
		assert(isValid());
		// TODO: Verifications...

		glShaderStorageBlockBinding(_program, shaderBindingIndex, bufferBindingIndex);
	}

	uint32_t ShaderProgram::getHandle() const
	{
		return _program;
	}

	ShaderProgramFlags::Flags ShaderProgram::getFlags() const
	{
		return _flags;
	}

	bool ShaderProgram::isValid() const
	{
		return _program != 0 && _linkStatus != 0;
	}

	ShaderProgram::~ShaderProgram()
	{
		destroy();
	}

	void ShaderProgram::bind(const ShaderProgram& program)
	{
		assert(program.isValid());

		Context* context = Context::getCurrentContext();
		assert(context);
		
		context->_state.shaderBinding = &program;

		glUseProgram(program._program);
	}

	void ShaderProgram::unbind()
	{
		Context* context = Context::getCurrentContext();
		assert(context);

		context->_state.shaderBinding = nullptr;

		glUseProgram(0);
	}

	namespace
	{
		template<uint8_t Interface>
		inline void extractInterfaceInfos(uint32_t program, ShaderProgramInterfaceInfos* infos)
		{
			static constexpr GLenum glInterface = _spl::shaderProgramInterfaceToGLenum(static_cast<ShaderProgramInterface>(Interface));

			glGetProgramInterfaceiv(program, glInterface, GL_ACTIVE_RESOURCES, &infos->activeResources);

			if constexpr (glInterface != GL_ATOMIC_COUNTER_BUFFER
				&& glInterface != GL_TRANSFORM_FEEDBACK_BUFFER)
			{
				glGetProgramInterfaceiv(program, glInterface, GL_MAX_NAME_LENGTH, &infos->maxNameLength);
			}

			if constexpr (glInterface == GL_ATOMIC_COUNTER_BUFFER
				|| glInterface == GL_SHADER_STORAGE_BLOCK
				|| glInterface == GL_TRANSFORM_FEEDBACK_BUFFER
				|| glInterface == GL_UNIFORM_BLOCK)
			{
				glGetProgramInterfaceiv(program, glInterface, GL_MAX_NUM_ACTIVE_VARIABLES, &infos->maxNumActiveVariables);
			}

			if constexpr (glInterface == GL_COMPUTE_SUBROUTINE_UNIFORM
				|| glInterface == GL_VERTEX_SUBROUTINE_UNIFORM
				|| glInterface == GL_TESS_CONTROL_SUBROUTINE_UNIFORM
				|| glInterface == GL_TESS_EVALUATION_SUBROUTINE_UNIFORM
				|| glInterface == GL_GEOMETRY_SUBROUTINE_UNIFORM
				|| glInterface == GL_FRAGMENT_SUBROUTINE_UNIFORM)
			{
				glGetProgramInterfaceiv(program, glInterface, GL_MAX_NUM_COMPATIBLE_SUBROUTINES, &infos->maxNumCompatibleSubroutines);
			}
		}

		template<GLenum Prop, GLenum... Props>
		inline void extractResourceInfo(ShaderProgramResourceInfos* infos, int32_t* params)
		{
			if constexpr (Prop == GL_ARRAY_SIZE)
			{
				infos->arraySize = *params;
			}
			else if constexpr (Prop == GL_ARRAY_STRIDE)
			{
				infos->arrayStride = *params;
			}
			else if constexpr (Prop == GL_ATOMIC_COUNTER_BUFFER_INDEX)
			{
				infos->atomicCounterBufferIndex = *params;
			}
			else if constexpr (Prop == GL_BLOCK_INDEX)
			{
				infos->blockIndex = *params;
			}
			else if constexpr (Prop == GL_BUFFER_BINDING)
			{
				infos->bufferBinding = *params;
			}
			else if constexpr (Prop == GL_BUFFER_DATA_SIZE)
			{
				infos->bufferDataSize = *params;
			}
			else if constexpr (Prop == GL_IS_PER_PATCH)
			{
				infos->isPerPatch = *params;
			}
			else if constexpr (Prop == GL_IS_ROW_MAJOR)
			{
				infos->isRowMajor = *params;
			}
			else if constexpr (Prop == GL_LOCATION_COMPONENT)
			{
				infos->locationComponent = *params;
			}
			else if constexpr (Prop == GL_MATRIX_STRIDE)
			{
				infos->matrixStride = *params;
			}
			else if constexpr (Prop == GL_NAME_LENGTH)
			{
				infos->name.resize(*params);
			}
			else if constexpr (Prop == GL_NUM_ACTIVE_VARIABLES)
			{
				infos->activeVariables.resize(*params);
			}
			else if constexpr (Prop == GL_NUM_COMPATIBLE_SUBROUTINES)
			{
				infos->compatibleSubroutines.resize(*params);
			}
			else if constexpr (Prop == GL_OFFSET)
			{
				infos->offset = *params;
			}
			else if constexpr (Prop == GL_REFERENCED_BY_VERTEX_SHADER)
			{
				if (*params)
				{
					infos->referencedBy = static_cast<ShaderStage::Stage>(infos->referencedBy | ShaderStage::Vertex);
				}
			}
			else if constexpr (Prop == GL_REFERENCED_BY_TESS_CONTROL_SHADER)
			{
				if (*params)
				{
					infos->referencedBy = static_cast<ShaderStage::Stage>(infos->referencedBy | ShaderStage::TessControl);
				}
			}
			else if constexpr (Prop == GL_REFERENCED_BY_TESS_EVALUATION_SHADER)
			{
				if (*params)
				{
					infos->referencedBy = static_cast<ShaderStage::Stage>(infos->referencedBy | ShaderStage::TessEvaluation);
				}
			}
			else if constexpr (Prop == GL_REFERENCED_BY_GEOMETRY_SHADER)
			{
				if (*params)
				{
					infos->referencedBy = static_cast<ShaderStage::Stage>(infos->referencedBy | ShaderStage::Geometry);
				}
			}
			else if constexpr (Prop == GL_REFERENCED_BY_FRAGMENT_SHADER)
			{
				if (*params)
				{
					infos->referencedBy = static_cast<ShaderStage::Stage>(infos->referencedBy | ShaderStage::Fragment);
				}
			}
			else if constexpr (Prop == GL_REFERENCED_BY_COMPUTE_SHADER)
			{
				if (*params)
				{
					infos->referencedBy = static_cast<ShaderStage::Stage>(infos->referencedBy | ShaderStage::Compute);
				}
			}
			else if constexpr (Prop == GL_TOP_LEVEL_ARRAY_SIZE)
			{
				infos->topLevelArraySize = *params;
			}
			else if constexpr (Prop == GL_TOP_LEVEL_ARRAY_STRIDE)
			{
				infos->topLevelArrayStride = *params;
			}
			else if constexpr (Prop == GL_TRANSFORM_FEEDBACK_BUFFER_INDEX)
			{
				infos->transformFeedbackBufferIndex = *params;
			}
			else if constexpr (Prop == GL_TRANSFORM_FEEDBACK_BUFFER_STRIDE)
			{
				infos->transformFeedbackBufferStride = *params;
			}
			else if constexpr (Prop == GL_TYPE)
			{
				infos->type = _spl::glToGlslType(*params);
			}
			else
			{
				assert(false);
			}

			if constexpr (sizeof...(Props) != 0)
			{
				extractResourceInfo<Props...>(infos, params + 1);
			}
		}

		template<GLenum... Props>
		inline void extractResourceInfos(uint32_t program, uint32_t index, ShaderProgramResourceInfos* infos, GLenum glInterface)
		{
			static constexpr GLenum props[] = { Props... };
			static constexpr GLsizei propCount = sizeof...(Props);

			int32_t params[propCount];
			glGetProgramResourceiv(program, glInterface, index, propCount, props, propCount, nullptr, params);

			extractResourceInfo<Props...>(infos, params);
		}

		template<uint8_t Interface>
		inline void extractResourceInfos(uint32_t program, uint32_t index, ShaderProgramResourceInfos* infos)
		{
			static constexpr GLenum glInterface = _spl::shaderProgramInterfaceToGLenum(static_cast<ShaderProgramInterface>(Interface));

			bool hasName = false;
			bool hasActiveVariables = false;

			if constexpr (glInterface == GL_UNIFORM)
			{
				extractResourceInfos<
					GL_ARRAY_SIZE,
					GL_ARRAY_STRIDE,
					GL_BLOCK_INDEX,
					GL_IS_ROW_MAJOR,
					GL_MATRIX_STRIDE,
					GL_ATOMIC_COUNTER_BUFFER_INDEX,
					GL_NAME_LENGTH,
					GL_OFFSET,
					GL_REFERENCED_BY_VERTEX_SHADER,
					GL_REFERENCED_BY_TESS_CONTROL_SHADER,
					GL_REFERENCED_BY_TESS_EVALUATION_SHADER,
					GL_REFERENCED_BY_GEOMETRY_SHADER,
					GL_REFERENCED_BY_FRAGMENT_SHADER,
					GL_REFERENCED_BY_COMPUTE_SHADER,
					GL_TYPE
				>(program, index, infos, glInterface);
				
				hasName = true;
			}
			else if constexpr (glInterface == GL_UNIFORM_BLOCK)
			{
				extractResourceInfos<
					GL_BUFFER_BINDING,
					GL_NUM_ACTIVE_VARIABLES,
					GL_BUFFER_DATA_SIZE,
					GL_NAME_LENGTH,
					GL_REFERENCED_BY_VERTEX_SHADER,
					GL_REFERENCED_BY_TESS_CONTROL_SHADER,
					GL_REFERENCED_BY_TESS_EVALUATION_SHADER,
					GL_REFERENCED_BY_GEOMETRY_SHADER,
					GL_REFERENCED_BY_FRAGMENT_SHADER,
					GL_REFERENCED_BY_COMPUTE_SHADER
				>(program, index, infos, glInterface);

				hasName = true;
				hasActiveVariables = true;
			}
			else if constexpr (glInterface == GL_ATOMIC_COUNTER_BUFFER)
			{
				extractResourceInfos<
					GL_BUFFER_BINDING,
					GL_NUM_ACTIVE_VARIABLES,
					GL_BUFFER_DATA_SIZE,
					GL_REFERENCED_BY_VERTEX_SHADER,
					GL_REFERENCED_BY_TESS_CONTROL_SHADER,
					GL_REFERENCED_BY_TESS_EVALUATION_SHADER,
					GL_REFERENCED_BY_GEOMETRY_SHADER,
					GL_REFERENCED_BY_FRAGMENT_SHADER,
					GL_REFERENCED_BY_COMPUTE_SHADER
				>(program, index, infos, glInterface);

				// TODO: Set type to atomic and check if other things can be set "manually"

				hasName = true;
				hasActiveVariables = true;
			}
			else if constexpr (glInterface == GL_PROGRAM_INPUT || glInterface == GL_PROGRAM_OUTPUT)
			{
				extractResourceInfos<
					GL_ARRAY_SIZE,
					GL_IS_PER_PATCH,
					GL_LOCATION_COMPONENT,
					GL_NAME_LENGTH,
					GL_REFERENCED_BY_VERTEX_SHADER,
					GL_REFERENCED_BY_TESS_CONTROL_SHADER,
					GL_REFERENCED_BY_TESS_EVALUATION_SHADER,
					GL_REFERENCED_BY_GEOMETRY_SHADER,
					GL_REFERENCED_BY_FRAGMENT_SHADER,
					GL_REFERENCED_BY_COMPUTE_SHADER,
					GL_TYPE
				>(program, index, infos, glInterface);

				hasName = true;
			}
			else if constexpr (glInterface == GL_TRANSFORM_FEEDBACK_VARYING)
			{
				extractResourceInfos<
					GL_ARRAY_SIZE,
					GL_NAME_LENGTH,
					GL_OFFSET,
					GL_TRANSFORM_FEEDBACK_BUFFER_INDEX,
					GL_TYPE
				>(program, index, infos, glInterface);

				hasName = true;
			}
			else if constexpr (glInterface == GL_TRANSFORM_FEEDBACK_BUFFER)
			{
				extractResourceInfos<
					GL_BUFFER_BINDING,
					GL_NUM_ACTIVE_VARIABLES,
					GL_TRANSFORM_FEEDBACK_BUFFER_STRIDE
				>(program, index, infos, glInterface);

				hasActiveVariables = true;
			}
			else if constexpr (glInterface == GL_BUFFER_VARIABLE)
			{
				extractResourceInfos<
					GL_ARRAY_SIZE,
					GL_ARRAY_STRIDE,
					GL_BLOCK_INDEX,
					GL_IS_ROW_MAJOR,
					GL_MATRIX_STRIDE,
					GL_NAME_LENGTH,
					GL_OFFSET,
					GL_REFERENCED_BY_VERTEX_SHADER,
					GL_REFERENCED_BY_TESS_CONTROL_SHADER,
					GL_REFERENCED_BY_TESS_EVALUATION_SHADER,
					GL_REFERENCED_BY_GEOMETRY_SHADER,
					GL_REFERENCED_BY_FRAGMENT_SHADER,
					GL_REFERENCED_BY_COMPUTE_SHADER,
					GL_TOP_LEVEL_ARRAY_SIZE,
					GL_TOP_LEVEL_ARRAY_STRIDE,
					GL_TYPE
				>(program, index, infos, glInterface);

				hasName = true;
			}
			else if constexpr (glInterface == GL_SHADER_STORAGE_BLOCK)
			{
				extractResourceInfos<
					GL_BUFFER_BINDING,
					GL_NUM_ACTIVE_VARIABLES,
					GL_BUFFER_DATA_SIZE,
					GL_NAME_LENGTH,
					GL_REFERENCED_BY_VERTEX_SHADER,
					GL_REFERENCED_BY_TESS_CONTROL_SHADER,
					GL_REFERENCED_BY_TESS_EVALUATION_SHADER,
					GL_REFERENCED_BY_GEOMETRY_SHADER,
					GL_REFERENCED_BY_FRAGMENT_SHADER,
					GL_REFERENCED_BY_COMPUTE_SHADER
				>(program, index, infos, glInterface);

				hasName = true;
				hasActiveVariables = true;
			}
			else if constexpr (glInterface == GL_COMPUTE_SUBROUTINE
				|| glInterface == GL_VERTEX_SUBROUTINE
				|| glInterface == GL_TESS_CONTROL_SUBROUTINE
				|| glInterface == GL_TESS_EVALUATION_SUBROUTINE
				|| glInterface == GL_GEOMETRY_SUBROUTINE
				|| glInterface == GL_FRAGMENT_SUBROUTINE)
			{
				extractResourceInfos<
					GL_NAME_LENGTH
				>(program, index, infos, glInterface);

				hasName = true;
				hasActiveVariables = true;
			}
			else if constexpr (glInterface == GL_COMPUTE_SUBROUTINE_UNIFORM
				|| glInterface == GL_VERTEX_SUBROUTINE_UNIFORM
				|| glInterface == GL_TESS_CONTROL_SUBROUTINE_UNIFORM
				|| glInterface == GL_TESS_EVALUATION_SUBROUTINE_UNIFORM
				|| glInterface == GL_GEOMETRY_SUBROUTINE_UNIFORM
				|| glInterface == GL_FRAGMENT_SUBROUTINE_UNIFORM)
			{
				extractResourceInfos<
					GL_ARRAY_SIZE,
					GL_NUM_COMPATIBLE_SUBROUTINES,
					GL_NAME_LENGTH
				>(program, index, infos, glInterface);

				hasName = true;

				static constexpr GLenum prop = GL_COMPATIBLE_SUBROUTINES;
				glGetProgramResourceiv(program, glInterface, index, 1, &prop, infos->compatibleSubroutines.size(), nullptr, reinterpret_cast<int32_t*>(infos->compatibleSubroutines.data()));
			}
			else
			{
				assert(false);
			}

			if (hasName)
			{
				glGetProgramResourceName(program, glInterface, index, infos->name.size(), nullptr, infos->name.data());
			}

			if (hasActiveVariables)
			{
				static constexpr GLenum prop = GL_ACTIVE_VARIABLES;
				glGetProgramResourceiv(program, glInterface, index, 1, &prop, infos->activeVariables.size(), nullptr, reinterpret_cast<int32_t*>(infos->activeVariables.data()));
			}
		}

		template<uint8_t Interface>
		inline void extractResourcesInfos(uint32_t program, uint32_t activeResources, std::vector<ShaderProgramResourceInfos>* infos)
		{
			infos->resize(activeResources);

			ShaderProgramResourceInfos* it = infos->data();
			for (uint32_t i = 0; i < activeResources; ++i, ++it)
			{
				extractResourceInfos<Interface>(program, i, it);
			}
		}

		template<uint8_t Interface>
		inline void extractResourceLocation(uint32_t program, std::unordered_map<std::string, uint32_t>* locations, std::unordered_map<std::string, uint32_t>* locationIndices, const char* name)
		{
			static constexpr GLenum glInterface = _spl::shaderProgramInterfaceToGLenum(static_cast<ShaderProgramInterface>(Interface));

			(*locations)[name] = glGetProgramResourceLocation(program, glInterface, name);

			if constexpr (glInterface == GL_PROGRAM_OUTPUT)
			{
				(*locationIndices)[name] = glGetProgramResourceLocationIndex(program, glInterface, name);
			}
		}

		template<uint8_t Interface>
		inline void extractResourcesLocation(uint32_t program, const std::vector<ShaderProgramResourceInfos>* resourcesInfos, std::unordered_map<std::string, uint32_t>* locations, std::unordered_map<std::string, uint32_t>* locationIndices)
		{
			static constexpr GLenum glInterface = _spl::shaderProgramInterfaceToGLenum(static_cast<ShaderProgramInterface>(Interface));

			if constexpr (glInterface == GL_UNIFORM
				|| glInterface == GL_PROGRAM_INPUT
				|| glInterface == GL_PROGRAM_OUTPUT
				|| glInterface == GL_COMPUTE_SUBROUTINE_UNIFORM
				|| glInterface == GL_VERTEX_SUBROUTINE_UNIFORM
				|| glInterface == GL_TESS_CONTROL_SUBROUTINE_UNIFORM
				|| glInterface == GL_TESS_EVALUATION_SUBROUTINE_UNIFORM
				|| glInterface == GL_GEOMETRY_SUBROUTINE_UNIFORM
				|| glInterface == GL_FRAGMENT_SUBROUTINE_UNIFORM)
			{
				for (const ShaderProgramResourceInfos infos : *resourcesInfos)
				{
					extractResourceLocation<Interface>(program, locations, locationIndices, infos.name.c_str());

					if (infos.name.ends_with("[0]"))
					{
						const uint32_t rootSize = infos.name.size() - 3;
						const uint32_t bufferSize = rootSize + 16;

						char* buffer = reinterpret_cast<char*>(alloca(bufferSize));
						std::copy_n(infos.name.data(), rootSize, buffer);
						std::fill_n(buffer + rootSize, bufferSize - rootSize, '\0');

						extractResourceLocation<Interface>(program, locations, locationIndices, buffer);

						*(buffer + rootSize) = '[';
						char* beginNum = buffer + rootSize + 1;
						char* endNum = buffer + bufferSize;
						for (uint32_t i = 1; i < infos.arraySize; ++i)
						{
							*std::to_chars(beginNum, endNum, i).ptr = ']';
							extractResourceLocation<Interface>(program, locations, locationIndices, buffer);
						}
					}
				}
			}
		}

		template<uint8_t Interface>
		inline void extractInfos(uint32_t program, ShaderProgramInterfaceInfos* interfaceInfos, std::vector<ShaderProgramResourceInfos>* resourcesInfos, std::unordered_map<std::string, uint32_t>* locations, std::unordered_map<std::string, uint32_t>* locationIndices)
		{
			extractInterfaceInfos<Interface>(program, interfaceInfos);
			extractResourcesInfos<Interface>(program, interfaceInfos->activeResources, resourcesInfos);
			extractResourcesLocation<Interface>(program, resourcesInfos, locations, locationIndices);

			if constexpr (Interface != 0)
			{
				extractInfos<Interface - 1>(program, interfaceInfos - 1, resourcesInfos - 1, locations - 1, locationIndices - 1);
			}
		}
	}

	void ShaderProgram::_shaderIntrospection()
	{
		extractInfos<_interfaceCount - 1>(_program, &_interfacesInfos.back(), &_resourcesInfos.back(), &_locations.back(), &_locationIndices.back());
	}

	void ShaderProgram::_setUniform(const std::string& name, GlslType type, const void* values, uint32_t count) const
	{
		assert(isValid());
		assert(_locations[static_cast<uint8_t>(ShaderProgramInterface::Uniform)].find(name) != _locations[static_cast<uint8_t>(ShaderProgramInterface::Uniform)].end());
		// TODO: Check type, array size, etc. corresponds...

		const uint32_t& location = _locations[static_cast<uint8_t>(ShaderProgramInterface::Uniform)].find(name)->second;

		switch (type)
		{
			case GlslType::Float:
				glProgramUniform1fv(_program, location, count, reinterpret_cast<const float*>(values));
				break;
			case GlslType::FloatVec2:
				glProgramUniform2fv(_program, location, count, reinterpret_cast<const float*>(values));
				break;
			case GlslType::FloatVec3:
				glProgramUniform3fv(_program, location, count, reinterpret_cast<const float*>(values));
				break;
			case GlslType::FloatVec4:
				glProgramUniform4fv(_program, location, count, reinterpret_cast<const float*>(values));
				break;
			case GlslType::Double:
				glProgramUniform1dv(_program, location, count, reinterpret_cast<const double*>(values));
				break;
			case GlslType::DoubleVec2:
				glProgramUniform2dv(_program, location, count, reinterpret_cast<const double*>(values));
				break;
			case GlslType::DoubleVec3:
				glProgramUniform3dv(_program, location, count, reinterpret_cast<const double*>(values));
				break;
			case GlslType::DoubleVec4:
				glProgramUniform4dv(_program, location, count, reinterpret_cast<const double*>(values));
				break;
			case GlslType::Int:
				glProgramUniform1iv(_program, location, count, reinterpret_cast<const int32_t*>(values));
				break;
			case GlslType::IntVec2:
				glProgramUniform2iv(_program, location, count, reinterpret_cast<const int32_t*>(values));
				break;
			case GlslType::IntVec3:
				glProgramUniform3iv(_program, location, count, reinterpret_cast<const int32_t*>(values));
				break;
			case GlslType::IntVec4:
				glProgramUniform4iv(_program, location, count, reinterpret_cast<const int32_t*>(values));
				break;
			case GlslType::UnsignedInt:
				glProgramUniform1uiv(_program, location, count, reinterpret_cast<const uint32_t*>(values));
				break;
			case GlslType::UnsignedIntVec2:
				glProgramUniform2uiv(_program, location, count, reinterpret_cast<const uint32_t*>(values));
				break;
			case GlslType::UnsignedIntVec3:
				glProgramUniform3uiv(_program, location, count, reinterpret_cast<const uint32_t*>(values));
				break;
			case GlslType::UnsignedIntVec4:
				glProgramUniform4uiv(_program, location, count, reinterpret_cast<const uint32_t*>(values));
				break;
			case GlslType::FloatMat2x2:
				glProgramUniformMatrix2fv(_program, location, count, true, reinterpret_cast<const float*>(values));
				break;
			case GlslType::FloatMat2x3:
				glProgramUniformMatrix2x3fv(_program, location, count, true, reinterpret_cast<const float*>(values));
				break;
			case GlslType::FloatMat2x4:
				glProgramUniformMatrix2x4fv(_program, location, count, true, reinterpret_cast<const float*>(values));
				break;
			case GlslType::FloatMat3x2:
				glProgramUniformMatrix3x2fv(_program, location, count, true, reinterpret_cast<const float*>(values));
				break;
			case GlslType::FloatMat3x3:
				glProgramUniformMatrix3fv(_program, location, count, true, reinterpret_cast<const float*>(values));
				break;
			case GlslType::FloatMat3x4:
				glProgramUniformMatrix3x4fv(_program, location, count, true, reinterpret_cast<const float*>(values));
				break;
			case GlslType::FloatMat4x2:
				glProgramUniformMatrix4x2fv(_program, location, count, true, reinterpret_cast<const float*>(values));
				break;
			case GlslType::FloatMat4x3:
				glProgramUniformMatrix4x3fv(_program, location, count, true, reinterpret_cast<const float*>(values));
				break;
			case GlslType::FloatMat4x4:
				glProgramUniformMatrix4fv(_program, location, count, true, reinterpret_cast<const float*>(values));
				break;
			case GlslType::DoubleMat2x2:
				glProgramUniformMatrix2dv(_program, location, count, true, reinterpret_cast<const double*>(values));
				break;
			case GlslType::DoubleMat2x3:
				glProgramUniformMatrix2x3dv(_program, location, count, true, reinterpret_cast<const double*>(values));
				break;
			case GlslType::DoubleMat2x4:
				glProgramUniformMatrix2x4dv(_program, location, count, true, reinterpret_cast<const double*>(values));
				break;
			case GlslType::DoubleMat3x2:
				glProgramUniformMatrix3x2dv(_program, location, count, true, reinterpret_cast<const double*>(values));
				break;
			case GlslType::DoubleMat3x3:
				glProgramUniformMatrix3dv(_program, location, count, true, reinterpret_cast<const double*>(values));
				break;
			case GlslType::DoubleMat3x4:
				glProgramUniformMatrix3x4dv(_program, location, count, true, reinterpret_cast<const double*>(values));
				break;
			case GlslType::DoubleMat4x2:
				glProgramUniformMatrix4x2dv(_program, location, count, true, reinterpret_cast<const double*>(values));
				break;
			case GlslType::DoubleMat4x3:
				glProgramUniformMatrix4x3dv(_program, location, count, true, reinterpret_cast<const double*>(values));
				break;
			case GlslType::DoubleMat4x4:
				glProgramUniformMatrix4dv(_program, location, count, true, reinterpret_cast<const double*>(values));
				break;
			default:
				assert(false);
				break;
		}
	}
}
