#include <SplayLibrary/SplayLibrary.hpp>
#include <SplayLibrary/Core/Private.hpp>

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
		uint32_t compileShader(const std::string& filename, uint32_t shaderType)
		{
			if (filename == "")
			{
				return 0;
			}

			std::ifstream file(filename, std::ios::ate | std::ios::binary);
			if (!file)
			{
				SPL_DEBUG("Could not open file : '%s'", filename.c_str());
				return 0;
			}

			char* shaderSource = nullptr;

			uint64_t length = file.tellg();
			file.seekg(0);

			shaderSource = new char[length+1];
			file.read(shaderSource, length);
			shaderSource[length] = 0;

			file.close();


			uint32_t shader = glCreateShader(shaderType);
			glShaderSource(shader, 1, &shaderSource, nullptr);
			glCompileShader(shader);

			int32_t success = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

			if (!success)
			{
				int32_t infoLogLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
				if (infoLogLength)
				{
					char* infoLog = new char[infoLogLength];
					glGetShaderInfoLog(shader, infoLogLength, nullptr, infoLog);

					SPL_DEBUG("Failed to compile shader :\n%s", infoLog);

					delete[] infoLog;
				}

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
			int32_t infoLogLength = 0;
			glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &infoLogLength);
			if (infoLogLength)
			{
				char* infoLog = new char[infoLogLength];
				glGetProgramInfoLog(_program, infoLogLength, nullptr, infoLog);

				SPL_DEBUG("Failed to link shader :\n%s", infoLog);

				delete[] infoLog;
			}

			glDeleteProgram(_program);
			_program = 0;
		}

		glDeleteShader(vertexShader);
		glDeleteShader(tessellationControlShader);
		glDeleteShader(tessellationEvaluationShader);
		glDeleteShader(geometryShader);
		glDeleteShader(fragmentShader);
	}

	void Shader::use() const
	{
		glUseProgram(_program);
	}

	int32_t Shader::getUniformLocation(const std::string& location)
	{
		assert(_program != 0);

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
		glUniform1f(getUniformLocation(location), value);
	}

	void Shader::setUniform(const std::string& location, const vec2& value)
	{
		glUniform2f(getUniformLocation(location), value.x, value.y);
	}

	void Shader::setUniform(const std::string& location, const vec3& value)
	{
		glUniform3f(getUniformLocation(location), value.x, value.y, value.z);
	}

	void Shader::setUniform(const std::string& location, const vec4& value)
	{
		glUniform4f(getUniformLocation(location), value.x, value.y, value.z, value.w);
	}

	void Shader::setUniform(const std::string& location, const float* values, uint32_t count)
	{
		glUniform1fv(getUniformLocation(location), count, values);
	}

	void Shader::setUniform(const std::string& location, const vec2* values, uint32_t count)
	{
		glUniform2fv(getUniformLocation(location), count, reinterpret_cast<const float*>(values));
	}

	void Shader::setUniform(const std::string& location, const vec3* values, uint32_t count)
	{
		glUniform3fv(getUniformLocation(location), count, reinterpret_cast<const float*>(values));
	}

	void Shader::setUniform(const std::string& location, const vec4* values, uint32_t count)
	{
		glUniform4fv(getUniformLocation(location), count, reinterpret_cast<const float*>(values));
	}

	void Shader::setUniform(const std::string& location, const int32_t value)
	{
		glUniform1i(getUniformLocation(location), value);
	}

	void Shader::setUniform(const std::string& location, const ivec2& value)
	{
		glUniform2i(getUniformLocation(location), value.x, value.y);
	}

	void Shader::setUniform(const std::string& location, const ivec3& value)
	{
		glUniform3i(getUniformLocation(location), value.x, value.y, value.z);
	}

	void Shader::setUniform(const std::string& location, const ivec4& value)
	{
		glUniform4i(getUniformLocation(location), value.x, value.y, value.z, value.w);
	}

	void Shader::setUniform(const std::string& location, const int32_t* values, uint32_t count)
	{
		glUniform1iv(getUniformLocation(location), count, values);
	}

	void Shader::setUniform(const std::string& location, const ivec2* values, uint32_t count)
	{
		glUniform2iv(getUniformLocation(location), count, reinterpret_cast<const int32_t*>(values));
	}

	void Shader::setUniform(const std::string& location, const ivec3* values, uint32_t count)
	{
		glUniform3iv(getUniformLocation(location), count, reinterpret_cast<const int32_t*>(values));
	}

	void Shader::setUniform(const std::string& location, const ivec4* values, uint32_t count)
	{
		glUniform4iv(getUniformLocation(location), count, reinterpret_cast<const int32_t*>(values));
	}

	void Shader::setUniform(const std::string& location, uint32_t value)
	{
		glUniform1ui(getUniformLocation(location), value);
	}

	void Shader::setUniform(const std::string& location, const uvec2& value)
	{
		glUniform2ui(getUniformLocation(location), value.x, value.y);
	}

	void Shader::setUniform(const std::string& location, const uvec3& value)
	{
		glUniform3ui(getUniformLocation(location), value.x, value.y, value.z);
	}

	void Shader::setUniform(const std::string& location, const uvec4& value)
	{
		glUniform4ui(getUniformLocation(location), value.x, value.y, value.z, value.w);
	}

	void Shader::setUniform(const std::string& location, const uint32_t* values, uint32_t count)
	{
		glUniform1uiv(getUniformLocation(location), count, values);
	}

	void Shader::setUniform(const std::string& location, const uvec2* values, uint32_t count)
	{
		glUniform2uiv(getUniformLocation(location), count, reinterpret_cast<const uint32_t*>(values));
	}

	void Shader::setUniform(const std::string& location, const uvec3* values, uint32_t count)
	{
		glUniform3uiv(getUniformLocation(location), count, reinterpret_cast<const uint32_t*>(values));
	}

	void Shader::setUniform(const std::string& location, const uvec4* values, uint32_t count)
	{
		glUniform4uiv(getUniformLocation(location), count, reinterpret_cast<const uint32_t*>(values));
	}

	void Shader::setUniform(const std::string& location, const mat2& value)
	{
		glUniformMatrix2fv(getUniformLocation(location), 1, true, reinterpret_cast<const float*>(&value));
	}

	void Shader::setUniform(const std::string& location, const mat2x3& value)
	{
		glUniformMatrix2x3fv(getUniformLocation(location), 1, true, reinterpret_cast<const float*>(&value));
	}

	void Shader::setUniform(const std::string& location, const mat2x4& value)
	{
		glUniformMatrix2x4fv(getUniformLocation(location), 1, true, reinterpret_cast<const float*>(&value));
	}

	void Shader::setUniform(const std::string& location, const mat3x2& value)
	{
		glUniformMatrix3x2fv(getUniformLocation(location), 1, true, reinterpret_cast<const float*>(&value));
	}

	void Shader::setUniform(const std::string& location, const mat3& value)
	{
		glUniformMatrix3fv(getUniformLocation(location), 1, true, reinterpret_cast<const float*>(&value));
	}

	void Shader::setUniform(const std::string& location, const mat3x4& value)
	{
		glUniformMatrix3x4fv(getUniformLocation(location), 1, true, reinterpret_cast<const float*>(&value));
	}

	void Shader::setUniform(const std::string& location, const mat4x2& value)
	{
		glUniformMatrix4x2fv(getUniformLocation(location), 1, true, reinterpret_cast<const float*>(&value));
	}

	void Shader::setUniform(const std::string& location, const mat4x3& value)
	{
		glUniformMatrix4x3fv(getUniformLocation(location), 1, true, reinterpret_cast<const float*>(&value));
	}

	void Shader::setUniform(const std::string& location, const mat4& value)
	{
		glUniformMatrix4fv(getUniformLocation(location), 1, true, reinterpret_cast<const float*>(&value));
	}

	void Shader::setUniform(const std::string& location, const mat2* value, uint32_t count)
	{
		glUniformMatrix2fv(getUniformLocation(location), count, true, reinterpret_cast<const float*>(&value));
	}

	void Shader::setUniform(const std::string& location, const mat2x3* value, uint32_t count)
	{
		glUniformMatrix2x3fv(getUniformLocation(location), count, true, reinterpret_cast<const float*>(&value));
	}

	void Shader::setUniform(const std::string& location, const mat2x4* value, uint32_t count)
	{
		glUniformMatrix2x4fv(getUniformLocation(location), count, true, reinterpret_cast<const float*>(&value));
	}

	void Shader::setUniform(const std::string& location, const mat3x2* value, uint32_t count)
	{
		glUniformMatrix3x2fv(getUniformLocation(location), count, true, reinterpret_cast<const float*>(&value));
	}

	void Shader::setUniform(const std::string& location, const mat3* value, uint32_t count)
	{
		glUniformMatrix3fv(getUniformLocation(location), count, true, reinterpret_cast<const float*>(&value));
	}

	void Shader::setUniform(const std::string& location, const mat3x4* value, uint32_t count)
	{
		glUniformMatrix3x4fv(getUniformLocation(location), count, true, reinterpret_cast<const float*>(&value));
	}

	void Shader::setUniform(const std::string& location, const mat4x2* value, uint32_t count)
	{
		glUniformMatrix4x2fv(getUniformLocation(location), count, true, reinterpret_cast<const float*>(&value));
	}

	void Shader::setUniform(const std::string& location, const mat4x3* value, uint32_t count)
	{
		glUniformMatrix4x3fv(getUniformLocation(location), count, true, reinterpret_cast<const float*>(&value));
	}

	void Shader::setUniform(const std::string& location, const mat4* value, uint32_t count)
	{
		glUniformMatrix4fv(getUniformLocation(location), count, true, reinterpret_cast<const float*>(&value));
	}

	void Shader::setUniform(const std::string& location, const RawTexture& texture, uint32_t textureUnit)
	{
		RawTexture::bind(texture, texture.getCreationParams().target, textureUnit);
		glUniform1i(getUniformLocation(location), textureUnit);
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

	Shader::~Shader()
	{
		glDeleteProgram(_program);
	}
}