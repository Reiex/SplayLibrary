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
		_linkStatus(0)
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

	ShaderProgram::ShaderProgram(const ShaderModule* shaders, uint8_t count, ShaderProgramFlags::Flags flags) : ShaderProgram()
	{
		createFromShaderModules(shaders, count, flags);
	}

	bool ShaderProgram::createFromGlsl(const std::filesystem::path& glslCompute, ShaderProgramFlags::Flags flags)
	{
		ShaderModule shader;

		if (shader.createFromGlsl(ShaderStage::Compute, glslCompute))
		{
			return createFromShaderModules(&shader, 1, flags);
		}

		return false;
	}

	bool ShaderProgram::createFromGlsl(const std::filesystem::path& glslVertex, const std::filesystem::path& glslFragment, ShaderProgramFlags::Flags flags)
	{
		ShaderModule shaders[2];

		if (shaders[0].createFromGlsl(ShaderStage::Vertex, glslVertex)
			&& shaders[1].createFromGlsl(ShaderStage::Fragment, glslFragment))
		{
			return createFromShaderModules(shaders, 2, flags);
		}

		return false;
	}

	bool ShaderProgram::createFromGlsl(const std::filesystem::path& glslVertex, const std::filesystem::path& glslGeometry, const std::filesystem::path& glslFragment, ShaderProgramFlags::Flags flags)
	{
		ShaderModule shaders[3];

		if (shaders[0].createFromGlsl(ShaderStage::Vertex, glslVertex)
			&& shaders[1].createFromGlsl(ShaderStage::Geometry, glslGeometry)
			&& shaders[2].createFromGlsl(ShaderStage::Fragment, glslFragment))
		{
			return createFromShaderModules(shaders, 3, flags);
		}

		return false;
	}

	bool ShaderProgram::createFromGlsl(const std::filesystem::path& glslVertex, const std::filesystem::path& glslTessControl, const std::filesystem::path& glslTessEval, const std::filesystem::path& glslFragment, ShaderProgramFlags::Flags flags)
	{
		ShaderModule shaders[4];

		if (shaders[0].createFromGlsl(ShaderStage::Vertex, glslVertex)
			&& shaders[1].createFromGlsl(ShaderStage::TessControl, glslTessControl)
			&& shaders[2].createFromGlsl(ShaderStage::TessEvaluation, glslTessEval)
			&& shaders[3].createFromGlsl(ShaderStage::Fragment, glslFragment))
		{
			return createFromShaderModules(shaders, 4, flags);
		}

		return false;
	}

	bool ShaderProgram::createFromGlsl(const std::filesystem::path& glslVertex, const std::filesystem::path& glslTessControl, const std::filesystem::path& glslTessEval, const std::filesystem::path& glslGeometry, const std::filesystem::path& glslFragment, ShaderProgramFlags::Flags flags)
	{
		ShaderModule shaders[5];

		if (shaders[0].createFromGlsl(ShaderStage::Vertex, glslVertex)
			&& shaders[1].createFromGlsl(ShaderStage::TessControl, glslTessControl)
			&& shaders[2].createFromGlsl(ShaderStage::TessEvaluation, glslTessEval)
			&& shaders[3].createFromGlsl(ShaderStage::Geometry, glslGeometry)
			&& shaders[4].createFromGlsl(ShaderStage::Fragment, glslFragment))
		{
			return createFromShaderModules(shaders, 5, flags);
		}

		return false;
	}

	bool ShaderProgram::createFromShaderModules(const ShaderModule* shaders, uint16_t count, ShaderProgramFlags::Flags flags)
	{
		for (uint16_t i = 0; i < count; ++i)
		{
			assert(shaders[i].isValid());
		}

		destroy();

		_program = glCreateProgram();
		_flags = flags;
		glProgramParameteri(_program, GL_PROGRAM_SEPARABLE, ((_flags & ShaderProgramFlags::Separable) != 0));
		glProgramParameteri(_program, GL_PROGRAM_BINARY_RETRIEVABLE_HINT, ((_flags & ShaderProgramFlags::BinaryRetrievable) != 0));

		for (uint16_t i = 0; i < count; ++i)
		{
			glAttachShader(_program, shaders[i].getHandle());
		}
		glLinkProgram(_program);
		glGetProgramiv(_program, GL_LINK_STATUS, &_linkStatus);

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

		glUseProgram(program._program);
	}

	void ShaderProgram::unbind()
	{
		glUseProgram(0);
	}
}
