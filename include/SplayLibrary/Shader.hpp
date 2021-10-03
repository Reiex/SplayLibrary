#pragma once

#include <SplayLibrary/types.hpp>

namespace spl
{
	class Shader
	{
		public:

			Shader(const std::string& vertex, const std::string& fragment);
			Shader(const std::string& vertex, const std::string& geometry, const std::string& fragment);
			Shader(const std::string& vertex, const std::string& tessellationControl, const std::string& tessellationEvaluation, const std::string& geometry, const std::string& fragment);
			Shader(const Shader& shader) = delete;
			Shader(Shader&& shader) = delete;

			Shader& operator=(const Shader& shader) = delete;
			Shader& operator=(Shader&& shader) = delete;

			bool isValid() const;
			uint32_t getHandle() const;

			~Shader();

		private:

			Shader();

			uint32_t _glShaderProgram;
	};
}
