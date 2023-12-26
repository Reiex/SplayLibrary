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
		_stage(ShaderStage::None),
		_compileStatus(0)
	{
	}

	ShaderModule::ShaderModule(ShaderStage::Stage stage, const std::filesystem::path& glslFile) : ShaderModule()
	{
		createFromGlsl(stage, glslFile);
	}

	ShaderModule::ShaderModule(ShaderStage::Stage stage, const char* source, uint32_t size) : ShaderModule()
	{
		createFromGlsl(stage, source, size);
	}

	ShaderModule::ShaderModule(ShaderStage::Stage stage, const char* const* sources, const uint32_t* sizes, uint32_t count) : ShaderModule()
	{
		createFromGlsl(stage, sources, sizes, count);
	}

	ShaderModule::ShaderModule(ShaderStage::Stage stage, const std::filesystem::path& spirvFile, const char* entryPoint, const uint32_t* constantIndices, const void* constantValues, uint32_t specializationConstantsCount) : ShaderModule()
	{
		createFromSpirV(stage, spirvFile, entryPoint, constantIndices, constantValues, specializationConstantsCount);
	}

	ShaderModule::ShaderModule(ShaderStage::Stage stage, const void* binary, uint32_t size, const char* entryPoint, const uint32_t* constantIndices, const void* constantValues, uint32_t specializationConstantsCount) : ShaderModule()
	{
		createFromSpirV(stage, binary, size, entryPoint, constantIndices, constantValues, specializationConstantsCount);
	}

	bool ShaderModule::createFromGlsl(ShaderStage::Stage stage, const std::filesystem::path& glslFile)
	{
		bool success = false;

		char* data = nullptr;
		uint32_t size = 0;
		if (_loadFile(glslFile, data, size))
		{
			success = createFromGlsl(stage, data, size);
			delete[] data;
		}

		return success;
	}

	bool ShaderModule::createFromGlsl(ShaderStage::Stage stage, const char* source, uint32_t size)
	{
		return createFromGlsl(stage, &source, &size, 1);
	}

	bool ShaderModule::createFromGlsl(ShaderStage::Stage stage, const char* const* sources, const uint32_t* sizes, uint32_t count)
	{
		assert(count != 0);

		if (_shader != 0 && _stage != stage)
		{
			destroy();
		}

		if (_shader == 0)
		{
			_shader = glCreateShader(_spl::shaderStageToGLenum(stage));
			_stage = stage;
		}

		glShaderSource(_shader, count, sources, reinterpret_cast<const GLint*>(sizes));
		glCompileShader(_shader);
		glGetShaderiv(_shader, GL_COMPILE_STATUS, &_compileStatus);

		if (!_compileStatus)
		{
			int32_t length;
			glGetShaderiv(_shader, GL_INFO_LOG_LENGTH, &length);

			char* buffer = reinterpret_cast<char*>(alloca(length));
			glGetShaderInfoLog(_shader, length, nullptr, buffer);

			glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_ERROR, 0, GL_DEBUG_SEVERITY_HIGH, length, buffer);
		}

		return _compileStatus;
	}

	bool ShaderModule::createFromSpirV(ShaderStage::Stage stage, const std::filesystem::path& spirvFile, const char* entryPoint, const uint32_t* constantIndices, const void* constantValues, uint32_t specializationConstantsCount)
	{
		bool success = false;

		char* data = nullptr;
		uint32_t size = 0;
		if (_loadFile(spirvFile, data, size))
		{
			success = createFromSpirV(stage, data, size, entryPoint, constantIndices, constantValues, specializationConstantsCount);
			delete[] data;
		}

		return success;
	}

	bool ShaderModule::createFromSpirV(ShaderStage::Stage stage, const void* binary, uint32_t size, const char* entryPoint, const uint32_t* constantIndices, const void* constantValues, uint32_t specializationConstantsCount)
	{
		if (_shader != 0 && _stage != stage)
		{
			destroy();
		}

		if (_shader == 0)
		{
			_shader = glCreateShader(_spl::shaderStageToGLenum(stage));
			_stage = stage;
		}

		glShaderBinary(1, &_shader, GL_SHADER_BINARY_FORMAT_SPIR_V, binary, size);
		glSpecializeShader(_shader, entryPoint, specializationConstantsCount, constantIndices, reinterpret_cast<const GLuint*>(constantValues));
		glGetShaderiv(_shader, GL_COMPILE_STATUS, &_compileStatus);

		if (!_compileStatus)
		{
			int32_t length;
			glGetShaderiv(_shader, GL_INFO_LOG_LENGTH, &length);

			char* buffer = reinterpret_cast<char*>(alloca(length));
			glGetShaderInfoLog(_shader, length, nullptr, buffer);

			glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_ERROR, 0, GL_DEBUG_SEVERITY_HIGH, length, buffer);
		}

		return _compileStatus;
	}

	void ShaderModule::destroy()
	{
		if (_shader != 0)
		{
			glDeleteShader(_shader);
		}

		_shader = 0;
		_stage = ShaderStage::None;
		_compileStatus = 0;
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
		destroy();
	}

	void ShaderModule::releaseShaderCompiler()
	{
		glReleaseShaderCompiler();
	}

	bool ShaderModule::_loadFile(const std::filesystem::path& filename, char*& data, uint32_t& size)
	{
		if (!std::filesystem::exists(filename))
		{
			return false;
		}

		std::ifstream file(filename, std::ios::ate | std::ios::binary);
		if (!file)
		{
			return false;
		}

		size = file.tellg();
		file.seekg(0);

		data = new char[size];
		file.read(data, size);

		file.close();

		return true;
	}
}
