#include <SplayLibrary/SplayLibrary.hpp>
#include <SplayLibrary/Private.hpp>

namespace spl
{
	Shader::Shader() :
		_glShaderProgram(0)
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
				SPL_DEBUG("Could not open file : '%s'", filename);
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

		_glShaderProgram = glCreateProgram();
		
		glAttachShader(_glShaderProgram, vertexShader);

		if (tessellationControlShader && tessellationEvaluationShader)
		{
			glAttachShader(_glShaderProgram, tessellationControlShader);
			glAttachShader(_glShaderProgram, tessellationEvaluationShader);
		}

		if (geometryShader)
		{
			glAttachShader(_glShaderProgram, geometryShader);
		}

		glAttachShader(_glShaderProgram, fragmentShader);

		glLinkProgram(_glShaderProgram);

		int32_t success = 0;
		glGetProgramiv(_glShaderProgram, GL_LINK_STATUS, &success);
		if (!success)
		{
			int32_t infoLogLength = 0;
			glGetProgramiv(_glShaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
			if (infoLogLength)
			{
				char* infoLog = new char[infoLogLength];
				glGetProgramInfoLog(_glShaderProgram, infoLogLength, nullptr, infoLog);

				SPL_DEBUG("Failed to link shader :\n%s", infoLog);

				delete[] infoLog;
			}

			glDeleteProgram(_glShaderProgram);
			_glShaderProgram = 0;
		}

		glDeleteShader(vertexShader);
		glDeleteShader(tessellationControlShader);
		glDeleteShader(tessellationEvaluationShader);
		glDeleteShader(geometryShader);
		glDeleteShader(fragmentShader);
	}

	bool Shader::isValid() const
	{
		return _glShaderProgram != 0;
	}

	uint32_t Shader::getHandle() const
	{
		return _glShaderProgram;
	}

	Shader::~Shader()
	{
		glDeleteProgram(_glShaderProgram);
	}
}