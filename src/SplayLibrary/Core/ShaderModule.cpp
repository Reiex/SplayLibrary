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
	ShaderModule::ShaderModule() :
		_shader(0),
		_stage(ShaderStage::Undefined),
		_compileStatus(0)
	{
	}

	ShaderModule::ShaderModule(ShaderStage stage, const std::filesystem::path& glslFile) : ShaderModule()
	{
		compileGlsl(stage, glslFile);
	}

	ShaderModule::ShaderModule(ShaderStage stage, const char* source, uint32_t size) : ShaderModule()
	{
		compileGlsl(stage, source, size);
	}

	ShaderModule::ShaderModule(ShaderStage stage, const char* const* sources, const uint32_t* sizes, uint32_t count) : ShaderModule()
	{
		compileGlsl(stage, sources, sizes, count);
	}

	ShaderModule::ShaderModule(ShaderStage stage, const std::filesystem::path& spirvFile, const char* entryPoint, const uint32_t* constantIndices, const void* constantValues, uint32_t specializationConstantsCount) : ShaderModule()
	{
		compileSpirV(stage, spirvFile, entryPoint, constantIndices, constantValues, specializationConstantsCount);
	}

	ShaderModule::ShaderModule(ShaderStage stage, const void* binary, uint32_t size, const char* entryPoint, const uint32_t* constantIndices, const void* constantValues, uint32_t specializationConstantsCount) : ShaderModule()
	{
		compileSpirV(stage, binary, size, entryPoint, constantIndices, constantValues, specializationConstantsCount);
	}

	bool ShaderModule::compileGlsl(ShaderStage stage, const std::filesystem::path& glslFile)
	{
		return false;
	}

	bool ShaderModule::compileGlsl(ShaderStage stage, const char* source, uint32_t size)
	{
		return compileGlsl(stage, &source, &size, 1);
	}

	bool ShaderModule::compileGlsl(ShaderStage stage, const char* const* sources, const uint32_t* sizes, uint32_t count)
	{
		assert(_spl::shaderStageToGL(stage) != 0);
		assert(count != 0);

		if (_shader != 0 && _stage != stage)
		{
			_destroy();
		}

		if (_shader == 0)
		{
			_shader = glCreateShader(_spl::shaderStageToGL(stage));
			_stage = stage;
		}

		glShaderSource(_shader, count, sources, reinterpret_cast<const GLint*>(sizes));
		glCompileShader(_shader);
		glGetShaderiv(_shader, GL_COMPILE_STATUS, &_compileStatus);

		return _compileStatus;
	}

	bool ShaderModule::compileSpirV(ShaderStage stage, const void* binary, uint32_t size, const char* entryPoint, const uint32_t* constantIndices, const void* constantValues, uint32_t specializationConstantsCount)
	{
		assert(_spl::shaderStageToGL(stage) != 0);

		if (_shader != 0 && _stage != stage)
		{
			_destroy();
		}

		if (_shader == 0)
		{
			_shader = glCreateShader(_spl::shaderStageToGL(stage));
			_stage = stage;
		}

		glShaderBinary(1, &_shader, GL_SHADER_BINARY_FORMAT_SPIR_V, binary, size);
		glSpecializeShader(_shader, entryPoint, specializationConstantsCount, constantIndices, reinterpret_cast<const GLuint*>(constantValues));
		glGetShaderiv(_shader, GL_COMPILE_STATUS, &_compileStatus);

		return _compileStatus;
	}

	bool ShaderModule::compileSpirV(ShaderStage stage, const std::filesystem::path& spirvFile, const char* entryPoint, const uint32_t* constantIndices, const void* constantValues, uint32_t specializationConstantsCount)
	{
		return false;
	}

	uint32_t ShaderModule::getHandle() const
	{
		return _shader;
	}

	bool ShaderModule::isValid() const
	{
		return _shader != 0 && _compileStatus != 0;
	}

	ShaderModule::~ShaderModule()
	{
		_destroy();
	}

	void ShaderModule::releaseShaderCompiler()
	{
		glReleaseShaderCompiler();
	}

	void ShaderModule::_destroy()
	{
		if (_shader != 0)
		{
			glDeleteShader(_shader);
		}

		_shader = 0;
		_stage = ShaderStage::Undefined;
		_compileStatus = 0;
	}
}
