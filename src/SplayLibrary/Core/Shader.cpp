///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2021-2023
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SplayLibrary/SplayLibrary.hpp>
#include <SplayLibrary/Private/Private.hpp>

namespace spl
{
	Shader::Shader() :
		_program(0)
	{
	}

	Shader::Shader(const std::string& vertex, const std::string& fragment) : Shader(vertex, "", "", "", fragment)
	{
	}

	Shader::Shader(const std::string& vertex, const std::string& geometry, const std::string& fragment) : Shader(vertex, "", "", geometry, fragment)
	{
	}

	namespace
	{
		uint32_t compileShader(const std::string& filename, GLenum shaderType)
		{
			if (filename.empty())
			{
				return 0;
			}

			std::ifstream file(filename, std::ios::ate | std::ios::binary);
			if (!file)
			{
				assert(false);	// Could not open file
				return 0;
			}

			char* shaderSource = nullptr;

			int32_t length = file.tellg();
			file.seekg(0);

			shaderSource = new char[length];
			file.read(shaderSource, length);

			file.close();


			uint32_t shader = glCreateShader(shaderType);
			glShaderSource(shader, 1, &shaderSource, &length);
			glCompileShader(shader);

			int32_t success = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

			if (!success)
			{
				assert(false);	// Shader compilation failed
				glDeleteShader(shader);
				shader = 0;
			}

			delete[] shaderSource;

			return shader;
		}
	}

	Shader::Shader(const std::string& vertex, const std::string& tessellationControl, const std::string& tessellationEvaluation, const std::string& geometry, const std::string& fragment) : Shader()
	{
		uint32_t vertexShader = compileShader(vertex, GL_VERTEX_SHADER);
		uint32_t tessellationControlShader = compileShader(tessellationControl, GL_TESS_CONTROL_SHADER);
		uint32_t tessellationEvaluationShader = compileShader(tessellationEvaluation, GL_TESS_EVALUATION_SHADER);
		uint32_t geometryShader = compileShader(geometry, GL_GEOMETRY_SHADER);
		uint32_t fragmentShader = compileShader(fragment, GL_FRAGMENT_SHADER);

		assert(vertexShader != 0);
		assert(fragmentShader != 0);
		assert((tessellationControlShader == 0) == (tessellationEvaluationShader == 0));

		_program = glCreateProgram();
		
		glAttachShader(_program, vertexShader);

		if (tessellationControlShader && tessellationEvaluationShader)
		{
			glAttachShader(_program, tessellationControlShader);
			glAttachShader(_program, tessellationEvaluationShader);
		}

		if (geometryShader)
		{
			glAttachShader(_program, geometryShader);
		}

		glAttachShader(_program, fragmentShader);

		glLinkProgram(_program);

		int32_t success = 0;
		glGetProgramiv(_program, GL_LINK_STATUS, &success);
		if (!success)
		{
			assert(false);	// Program could not be linked
			glDeleteProgram(_program);
			_program = 0;
		}

		glDeleteShader(vertexShader);
		glDeleteShader(tessellationControlShader);
		glDeleteShader(tessellationEvaluationShader);
		glDeleteShader(geometryShader);
		glDeleteShader(fragmentShader);
	}

	int32_t Shader::_getUniformLocation(const std::string& location)
	{
		assert(isValid());

		if (_uniformLocations.find(location) == _uniformLocations.end())
		{
			int32_t programLocation = glGetUniformLocation(_program, location.c_str());
			assert(programLocation != -1);

			_uniformLocations[location] = programLocation;
		}

		return _uniformLocations[location];
	}

	void Shader::setUniform(const std::string& location, float value)
	{
		_setUniform(glUniform1f, location, value);
	}

	void Shader::setUniform(const std::string& location, const scp::f32vec2& value)
	{
		_setUniform(glUniform2f, location, value.x, value.y);
	}

	void Shader::setUniform(const std::string& location, const scp::f32vec3& value)
	{
		_setUniform(glUniform3f, location, value.x, value.y, value.z);
	}

	void Shader::setUniform(const std::string& location, const scp::f32vec4& value)
	{
		_setUniform(glUniform4f, location, value.x, value.y, value.z, value.w);
	}

	void Shader::setUniform(const std::string& location, const float* values, uint32_t count)
	{
		_setUniform(glUniform1fv, location, count, values);
	}

	void Shader::setUniform(const std::string& location, const scp::f32vec2* values, uint32_t count)
	{
		_setUniform(glUniform2fv, location, count, reinterpret_cast<const float*>(values));
	}

	void Shader::setUniform(const std::string& location, const scp::f32vec3* values, uint32_t count)
	{
		_setUniform(glUniform3fv, location, count, reinterpret_cast<const float*>(values));
	}

	void Shader::setUniform(const std::string& location, const scp::f32vec4* values, uint32_t count)
	{
		_setUniform(glUniform4fv, location, count, reinterpret_cast<const float*>(values));
	}

	void Shader::setUniform(const std::string& location, const int32_t value)
	{
		_setUniform(glUniform1i, location, value);
	}

	void Shader::setUniform(const std::string& location, const scp::i32vec2& value)
	{
		_setUniform(glUniform2i, location, value.x, value.y);
	}

	void Shader::setUniform(const std::string& location, const scp::i32vec3& value)
	{
		_setUniform(glUniform3i, location, value.x, value.y, value.z);
	}

	void Shader::setUniform(const std::string& location, const scp::i32vec4& value)
	{
		_setUniform(glUniform4i, location, value.x, value.y, value.z, value.w);
	}

	void Shader::setUniform(const std::string& location, const int32_t* values, uint32_t count)
	{
		_setUniform(glUniform1iv, location, count, values);
	}

	void Shader::setUniform(const std::string& location, const scp::i32vec2* values, uint32_t count)
	{
		_setUniform(glUniform2iv, location, count, reinterpret_cast<const int32_t*>(values));
	}

	void Shader::setUniform(const std::string& location, const scp::i32vec3* values, uint32_t count)
	{
		_setUniform(glUniform3iv, location, count, reinterpret_cast<const int32_t*>(values));
	}

	void Shader::setUniform(const std::string& location, const scp::i32vec4* values, uint32_t count)
	{
		_setUniform(glUniform4iv, location, count, reinterpret_cast<const int32_t*>(values));
	}

	void Shader::setUniform(const std::string& location, uint32_t value)
	{
		_setUniform(glUniform1ui, location, value);
	}

	void Shader::setUniform(const std::string& location, const scp::u32vec2& value)
	{
		_setUniform(glUniform2ui, location, value.x, value.y);
	}

	void Shader::setUniform(const std::string& location, const scp::u32vec3& value)
	{
		_setUniform(glUniform3ui, location, value.x, value.y, value.z);
	}

	void Shader::setUniform(const std::string& location, const scp::u32vec4& value)
	{
		_setUniform(glUniform4ui, location, value.x, value.y, value.z, value.w);
	}

	void Shader::setUniform(const std::string& location, const uint32_t* values, uint32_t count)
	{
		_setUniform(glUniform1uiv, location, count, values);
	}

	void Shader::setUniform(const std::string& location, const scp::u32vec2* values, uint32_t count)
	{
		_setUniform(glUniform2uiv, location, count, reinterpret_cast<const uint32_t*>(values));
	}

	void Shader::setUniform(const std::string& location, const scp::u32vec3* values, uint32_t count)
	{
		_setUniform(glUniform3uiv, location, count, reinterpret_cast<const uint32_t*>(values));
	}

	void Shader::setUniform(const std::string& location, const scp::u32vec4* values, uint32_t count)
	{
		_setUniform(glUniform4uiv, location, count, reinterpret_cast<const uint32_t*>(values));
	}

	void Shader::setUniform(const std::string& location, const scp::f32mat2x2& value)
	{
		_setUniform(glUniformMatrix2fv, location, 1, true, reinterpret_cast<const float*>(&value));
	}

	void Shader::setUniform(const std::string& location, const scp::f32mat2x3& value)
	{
		_setUniform(glUniformMatrix2x3fv, location, 1, true, reinterpret_cast<const float*>(&value));
	}

	void Shader::setUniform(const std::string& location, const scp::f32mat2x4& value)
	{
		_setUniform(glUniformMatrix2x4fv, location, 1, true, reinterpret_cast<const float*>(&value));
	}

	void Shader::setUniform(const std::string& location, const scp::f32mat3x2& value)
	{
		_setUniform(glUniformMatrix3x2fv, location, 1, true, reinterpret_cast<const float*>(&value));
	}

	void Shader::setUniform(const std::string& location, const scp::f32mat3x3& value)
	{
		_setUniform(glUniformMatrix3fv, location, 1, true, reinterpret_cast<const float*>(&value));
	}

	void Shader::setUniform(const std::string& location, const scp::f32mat3x4& value)
	{
		_setUniform(glUniformMatrix3x4fv, location, 1, true, reinterpret_cast<const float*>(&value));
	}

	void Shader::setUniform(const std::string& location, const scp::f32mat4x2& value)
	{
		_setUniform(glUniformMatrix4x2fv, location, 1, true, reinterpret_cast<const float*>(&value));
	}

	void Shader::setUniform(const std::string& location, const scp::f32mat4x3& value)
	{
		_setUniform(glUniformMatrix4x3fv, location, 1, true, reinterpret_cast<const float*>(&value));
	}

	void Shader::setUniform(const std::string& location, const scp::f32mat4x4& value)
	{
		_setUniform(glUniformMatrix4fv, location, 1, true, reinterpret_cast<const float*>(&value));
	}

	void Shader::setUniform(const std::string& location, const scp::f32mat2x2* value, uint32_t count)
	{
		_setUniform(glUniformMatrix2fv, location, count, true, reinterpret_cast<const float*>(value));
	}

	void Shader::setUniform(const std::string& location, const scp::f32mat2x3* value, uint32_t count)
	{
		_setUniform(glUniformMatrix2x3fv, location, count, true, reinterpret_cast<const float*>(value));
	}

	void Shader::setUniform(const std::string& location, const scp::f32mat2x4* value, uint32_t count)
	{
		_setUniform(glUniformMatrix2x4fv, location, count, true, reinterpret_cast<const float*>(value));
	}

	void Shader::setUniform(const std::string& location, const scp::f32mat3x2* value, uint32_t count)
	{
		_setUniform(glUniformMatrix3x2fv, location, count, true, reinterpret_cast<const float*>(value));
	}

	void Shader::setUniform(const std::string& location, const scp::f32mat3x3* value, uint32_t count)
	{
		_setUniform(glUniformMatrix3fv, location, count, true, reinterpret_cast<const float*>(value));
	}

	void Shader::setUniform(const std::string& location, const scp::f32mat3x4* value, uint32_t count)
	{
		_setUniform(glUniformMatrix3x4fv, location, count, true, reinterpret_cast<const float*>(value));
	}

	void Shader::setUniform(const std::string& location, const scp::f32mat4x2* value, uint32_t count)
	{
		_setUniform(glUniformMatrix4x2fv, location, count, true, reinterpret_cast<const float*>(value));
	}

	void Shader::setUniform(const std::string& location, const scp::f32mat4x3* value, uint32_t count)
	{
		_setUniform(glUniformMatrix4x3fv, location, count, true, reinterpret_cast<const float*>(value));
	}

	void Shader::setUniform(const std::string& location, const scp::f32mat4x4* value, uint32_t count)
	{
		_setUniform(glUniformMatrix4fv, location, count, true, reinterpret_cast<const float*>(value));
	}

	void Shader::setUniform(const std::string& location, const RawTexture& texture, uint32_t textureUnit)
	{
		RawTexture::bind(texture, texture.getCreationParams().target, textureUnit);
		_setUniform(glUniform1i, location, textureUnit);
	}

	void Shader::setUniform(const std::string& location, const TextureBase& texture, uint32_t textureUnit)
	{
		setUniform(location, texture.getRawTexture(), textureUnit);
	}

	bool Shader::isValid() const
	{
		return _program != 0;
	}

	uint32_t Shader::getHandle() const
	{
		return _program;
	}

	void Shader::bind(const Shader& shader)
	{
		glUseProgram(shader._program);
	}

	void Shader::unbind()
	{
		glUseProgram(0);
	}

	Shader::~Shader()
	{
		glDeleteProgram(_program);
	}
}
